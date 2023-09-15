$ErrorActionPreference = 'Stop'

Set-Location -LiteralPath $PSScriptRoot

$env:DOTNET_SKIP_FIRST_TIME_EXPERIENCE = '1'
$env:DOTNET_CLI_TELEMETRY_OPTOUT = '0'
$env:DOTNET_NOLOGO = '1'

dotnet tool restore | Out-Null
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

dotnet cake "update_and_launch.cake" --verbosity Quiet -- -- @args
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
