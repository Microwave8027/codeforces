param(
    [Parameter(Mandatory = $true)]
    [string]$Name,
    [switch]$Sanitize
)

$root = Split-Path -Parent $PSScriptRoot
$src = Join-Path $root "problems\$Name.cpp"
$exe = Join-Path $root "build\$Name.exe"
$inputFile = Join-Path $root "io\input.txt"

if (-not (Test-Path $src)) {
    Write-Error "Source file not found: $src"
    exit 1
}

$flags = @("-std=c++17", "-O2", "-Wall", "-Wextra", "-Wshadow", "-DLOCAL", "-Wl,--stack,268435456")
if ($Sanitize) {
    $flags += @("-g", "-fsanitize=address,undefined")
}

& g++ @flags $src -o $exe
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

if (Test-Path $inputFile) {
    Get-Content -Raw $inputFile | & $exe
} else {
    & $exe
}
