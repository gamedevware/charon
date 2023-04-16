@echo off
@cd %~dp0

set DOTNET_SKIP_FIRST_TIME_EXPERIENCE=1
set DOTNET_CLI_TELEMETRY_OPTOUT=0
set DOTNET_NOLOGO=1

dotnet tool restore --verbosity 0 >NUL  2>NUL
@if %ERRORLEVEL% neq 0 goto :eof

dotnet cake "update_and_launch.cake" --verbosity Normal -- %*
