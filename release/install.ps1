$ErrorActionPreference = "Stop"

$sourceExecutable = Join-Path $PSScriptRoot "gujarati.exe"
if (-not (Test-Path -LiteralPath $sourceExecutable -PathType Leaf)) {
    throw "gujarati.exe was not found beside this installer. Extract the complete release ZIP and run install.ps1 from the extracted folder."
}

$installDirectory = Join-Path $env:LOCALAPPDATA "Programs\GujaratiLang"
New-Item -ItemType Directory -Path $installDirectory -Force | Out-Null
Copy-Item -LiteralPath $sourceExecutable `
    -Destination (Join-Path $installDirectory "gujarati.exe") -Force

$sourceExamples = Join-Path $PSScriptRoot "examples"
if (Test-Path -LiteralPath $sourceExamples -PathType Container) {
    $examplesDirectory = Join-Path $installDirectory "examples"
    New-Item -ItemType Directory -Path $examplesDirectory -Force | Out-Null
    Get-ChildItem -LiteralPath $sourceExamples -Force |
        Copy-Item -Destination $examplesDirectory -Recurse -Force
}

$sourceReadme = Join-Path $PSScriptRoot "README.txt"
if (Test-Path -LiteralPath $sourceReadme -PathType Leaf) {
    Copy-Item -LiteralPath $sourceReadme `
        -Destination (Join-Path $installDirectory "README.txt") -Force
}

$userPath = [Environment]::GetEnvironmentVariable("Path", "User")
$pathEntries = @()
if (-not [string]::IsNullOrWhiteSpace($userPath)) {
    $pathEntries = @($userPath -split ";" | Where-Object { $_ -ne "" })
}
$alreadyOnPath = $false
foreach ($entry in $pathEntries) {
    if ([string]::Equals(
            $entry.TrimEnd("\"),
            $installDirectory.TrimEnd("\"),
            [StringComparison]::OrdinalIgnoreCase)) {
        $alreadyOnPath = $true
        break
    }
}
if (-not $alreadyOnPath) {
    $pathEntries += $installDirectory
    [Environment]::SetEnvironmentVariable("Path", ($pathEntries -join ";"), "User")
}

Write-Host "GujaratiLang installed to $installDirectory"
Write-Host "Open a new terminal, then run: gujarati --repl"
