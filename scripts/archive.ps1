param(
    [Parameter(Mandatory = $true)]
    [string]$ContestName
)

$root = Split-Path -Parent $PSScriptRoot
$archiveDir = Join-Path $root "archive\$ContestName"
$probDir = Join-Path $root "problems"
$tcDir = Join-Path $root "testcases"

New-Item -ItemType Directory -Force -Path $archiveDir | Out-Null

Get-ChildItem -Path $probDir -Filter "*.cpp" | ForEach-Object {
    Move-Item $_.FullName -Destination $archiveDir
}

$tcDest = Join-Path $archiveDir "testcases"
$tcFiles = Get-ChildItem -Path $tcDir -Exclude ".gitkeep"
if ($tcFiles.Count -gt 0) {
    New-Item -ItemType Directory -Force -Path $tcDest | Out-Null
    $tcFiles | Move-Item -Destination $tcDest
}

Write-Host "Archived active problems and testcases to $archiveDir"
