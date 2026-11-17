param(
    [Parameter(Mandatory = $true)]
    [string]$Name
)

$root = Split-Path -Parent $PSScriptRoot
$template = Join-Path $root "template.cpp"
$dest = Join-Path $root "problems\$Name.cpp"

if (Test-Path $dest) {
    Write-Error "File already exists: $dest"
    exit 1
}

Copy-Item $template $dest
Write-Host "Created $dest"
