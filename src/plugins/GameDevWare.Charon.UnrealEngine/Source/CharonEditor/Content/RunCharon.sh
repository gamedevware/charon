#!/bin/bash

# ###### DETERMINE CURRENT DIRECTORY ##########
SCRIPT_DIR=$(cd "`dirname "$0"`" && pwd)
EXECUTABLE_DIR=$SCRIPT_DIR
EXECUTABLE_NAME="Charon.exe"
EXITCODE=0
RESTORE_IS_DONE=0

# ###### LOCATING CHARON.EXE ##########

locate_executable() {
    FILE_NAME="Charon.exe"
    for D in "$SCRIPT_DIR"/gamedevware.charon/*/; do
        if [[ -e "$D/tools/$EXECUTABLE_NAME" ]]; then
            EXECUTABLE_DIR="$D/tools"
            return
        fi
    done

    if [[ "$RESTORE_IS_DONE" == "1" ]]; then
        exit_failure_no_executable
    fi

    # ###### RESTORING NUGET PACKAGE ##########
    pushd "$SCRIPT_DIR"
    dotnet restore --packages "." --force --ignore-failed-sources > /dev/null
    EXITCODE=$?
    popd
    RESTORE_IS_DONE=1

    if [[ "$EXITCODE" != "0" ]]; then
        exit_failure_dotnet_restore_failed
    fi

    locate_executable
}

# ###### RUNNING EXECUTABLE ##########
found_executable() {
    pushd "$EXECUTABLE_DIR"
    STANDALONE__APPLICATIONDATAPATH="$SCRIPT_DIR/data"
    STANDALONE__APPLICATIONTEMPPATH="$SCRIPT_DIR/temp"
    SERILOG__WRITETO__0__NAME="File"
    SERILOG__WRITETO__0__ARGS__PATH="$SCRIPT_DIR/logs/log_unrealengine_.txt"

    # Drop in configuration file before launching executable
    cp "$SCRIPT_DIR/appsettings.json" "./appsettings.json"
    # Run Charon.exe with passed parameters
    "./$EXECUTABLE_NAME" "$@"
    EXITCODE=$?
    popd

    if [[ "$EXITCODE" != "0" ]]; then
        exit_failure
    else
        exit_success
    fi
}

# ###### HANDLING ERRORS ##########

exit_failure_dotnet_restore_failed() {
    EXITCODE=-2
    echo "Failed to execute the 'dotnet restore' command to retrieve the latest package version from NuGet. Ensure that the 'dotnet' tool is installed and available in the 'PATH'. Check 'https://dotnet.microsoft.com/en-us/download' for the installer."
    exit_failure
}

exit_failure_no_executable() {
    EXITCODE=-1
    echo "Unable to find the '$FILE_NAME' executable in './gamedevware.charon/*/tools' subfolders."
    exit_failure
}

exit_failure() {
    exit $EXITCODE
}

exit_success() {
    exit 0
}

# Start the process
locate_executable
found_executable