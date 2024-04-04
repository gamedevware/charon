@echo off

rem ###### DETERMINE CURRENT DIRECTORY ##########

rem uppercase the drive letter
SETLOCAL ENABLEDELAYEDEXPANSION
set DRIVE_LETTER=%~d0
FOR %%Z IN (A B C D E F G H I J K L M N O P Q R S T U V W X Y Z) DO SET DRIVE_LETTER=!DRIVE_LETTER:%%Z=%%Z!
SETLOCAL DISABLEDELAYEDEXPANSION

set "SCRIPT_DIR=%DRIVE_LETTER%%~p0"
set "EXECUTABLE_DIR=%DRIVE_LETTER%%~p0"
set "EXECUTABLE_NAME=Charon.exe"
set "EXECUTABLE_PATH=%EXECUTABLE_DIR%\%EXECUTABLE_NAME%"
set EXITCODE=0
set RESTORE_IS_DONE=0

rem ###### LOCATING CHARON.EXE ##########

:Locate_Executable
set "FILE_NAME=Charon.exe"
for /d %%D in ("%SCRIPT_DIR%\gamedevware.charon\*") do (
    if exist "%%D\tools\%EXECUTABLE_NAME%" (
        set "EXECUTABLE_DIR=%%D\tools"
        set "EXECUTABLE_PATH=%%D\tools\%EXECUTABLE_NAME%"
        goto Run_Executable
    )
)

if "%RESTORE_IS_DONE%"=="1" goto Exit_Failure_No_Executable

IF NOT EXIST "%SCRIPT_DIR%\Charon.csproj" (
    (
    echo ^<Project Sdk="Microsoft.NET.Sdk"^>
    echo   ^<PropertyGroup^>
    echo     ^<TargetFramework^>net472^</TargetFramework^>
    echo   ^</PropertyGroup^>
    echo   ^<ItemGroup^>
    echo     ^<PackageReference Include="GameDevWare.Charon" Version="*"  /^>
    echo   ^</ItemGroup^>
    echo ^</Project^>
    ) > "%SCRIPT_DIR%\Charon.csproj"
)

rem ###### RESTORING NUGET PACKAGE ##########
pushd "%SCRIPT_DIR%"
call dotnet restore --packages "." --force --ignore-failed-sources >nul
popd
set RESTORE_IS_DONE=1

if "%EXITCODE%" NEQ "0" goto Exit_Failure_Dotnet_Restore_Failed

goto Locate_Executable

rem ###### RUNNING EXECUTABLE ##########
:Run_Executable

IF NOT EXIST "%SCRIPT_DIR%\appsettings.json" (
    (
    echo { 
    echo     "Logging": { 
    echo         "LogLevel": { 
    echo             "Default": "Debug" 
    echo         } 
    echo     }, 
    echo     "Serilog": { 
    echo         "Using": [ "Serilog.Sinks.Console", "Serilog.Sinks.File" ], 
    echo         "MinimumLevel": "Debug", 
    echo         "WriteTo": [ 
    echo             { 
    echo                 "Name": "File", 
    echo                 "Args": { 
    echo                     "path": "logs/log_.txt", 
    echo                     "rollingInterval": "Day", 
    echo                     "buffered": false, 
    echo                     "fileSizeLimitBytes": 10485760, 
    echo                     "rollOnFileSizeLimit": true, 
    echo                     "outputTemplate": "[{Timestamp:HH:mm:ss} {Level}] {SourceContext}: {Message}{NewLine}{Exception}" 
    echo                 } 
    echo             } 
    echo         ], 
    echo         "Enrich": [ "FromLogContext", "WithMachineName", "WithThreadId" ], 
    echo         "Properties": { 
    echo             "Application": "Charon" 
    echo         } 
    echo     } 
    echo }
    ) > "%SCRIPT_DIR%\appsettings.json"
)

set "STANDALONE__APPLICATIONDATAPATH=%SCRIPT_DIR%\data"
set "STANDALONE__APPLICATIONTEMPPATH=%SCRIPT_DIR%\temp"
set "SERILOG__WRITETO__0__NAME=File"
set "SERILOG__WRITETO__0__ARGS__PATH=%SCRIPT_DIR%\logs\log_.txt"

rem Drop in configuration file before launching executable
copy /Y "%SCRIPT_DIR%\appsettings.json" "%EXECUTABLE_DIR%\appsettings.json" >nul
rem Run Charon.exe with passed parameters
call "%EXECUTABLE_PATH%" %*

set EXITCODE=%ERRORLEVEL%

if "%EXITCODE%" NEQ "0" (
    goto Exit_Failure
) else (
    goto Exit_Success
)

goto Exit_Success

rem ###### HANDLING ERRORS ##########

:Exit_Failure_Dotnet_Restore_Failed
set EXITCODE=-2
echo Failed to execute the 'dotnet restore' command to retrieve the latest package version from NuGet. Ensure that the 'dotnet' tool is installed and available in the 'PATH'. Check 'https://dotnet.microsoft.com/en-us/download' for the installer.
goto Exit_Failure

:Exit_Failure_No_Executable
set EXITCODE=-1
echo Unable to find the '%FILE_NAME%' executable in './gamedevware.charon/*/tools' subfolders.
goto Exit_Failure

:Exit_Failure
exit /B %EXITCODE%

:Exit_Success
exit /B 0