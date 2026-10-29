# Set .gj file association and icon in CurrentUser classes (no admin required)
$ErrorActionPreference = "Stop"

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$icoPath = Join-Path $scriptDir "gujarati.ico"
$compilerExe = Join-Path $scriptDir "..\build\gujarati.exe"

if (-not (Test-Path $icoPath)) {
    Write-Error "Icon file not found: $icoPath"
    exit 1
}

$icoFullPath = (Resolve-Path $icoPath).Path

# 1. Map .gj to GujaratiLang.File ProgID
New-Item -Path "HKCU:\Software\Classes\.gj" -Force | Out-Null
Set-ItemProperty -Path "HKCU:\Software\Classes\.gj" -Name "(Default)" -Value "GujaratiLang.File"
Set-ItemProperty -Path "HKCU:\Software\Classes\.gj" -Name "Content Type" -Value "text/plain"
Set-ItemProperty -Path "HKCU:\Software\Classes\.gj" -Name "PerceivedType" -Value "text"

# 2. Configure GujaratiLang.File ProgID
New-Item -Path "HKCU:\Software\Classes\GujaratiLang.File" -Force | Out-Null
Set-ItemProperty -Path "HKCU:\Software\Classes\GujaratiLang.File" -Name "(Default)" -Value "GujaratiLang Source File"

# 3. Set DefaultIcon to gujarati.ico
New-Item -Path "HKCU:\Software\Classes\GujaratiLang.File\DefaultIcon" -Force | Out-Null
Set-ItemProperty -Path "HKCU:\Software\Classes\GujaratiLang.File\DefaultIcon" -Name "(Default)" -Value "$icoFullPath,0"

# 4. Configure Shell actions (Open with VS Code and Run)
New-Item -Path "HKCU:\Software\Classes\GujaratiLang.File\shell\open" -Force | Out-Null
Set-ItemProperty -Path "HKCU:\Software\Classes\GujaratiLang.File\shell\open" -Name "(Default)" -Value "Open with VS Code"
New-Item -Path "HKCU:\Software\Classes\GujaratiLang.File\shell\open\command" -Force | Out-Null
Set-ItemProperty -Path "HKCU:\Software\Classes\GujaratiLang.File\shell\open\command" -Name "(Default)" -Value 'code "%1"'

if (Test-Path $compilerExe) {
    $compilerFullPath = (Resolve-Path $compilerExe).Path
    New-Item -Path "HKCU:\Software\Classes\GujaratiLang.File\shell\run" -Force | Out-Null
    Set-ItemProperty -Path "HKCU:\Software\Classes\GujaratiLang.File\shell\run" -Name "(Default)" -Value "Run with GujaratiLang"
    New-Item -Path "HKCU:\Software\Classes\GujaratiLang.File\shell\run\command" -Force | Out-Null
    Set-ItemProperty -Path "HKCU:\Software\Classes\GujaratiLang.File\shell\run\command" -Name "(Default)" -Value "`"$compilerFullPath`" `"%1`""
}

# 5. Notify Windows Shell of association change
$code = @"
using System;
using System.Runtime.InteropServices;
public class ShellNotify {
    [DllImport("shell32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern void SHChangeNotify(int wEventId, uint uFlags, IntPtr dwItem1, IntPtr dwItem2);
}
"@
Add-Type -TypeDefinition $code -ErrorAction SilentlyContinue
try {
    [ShellNotify]::SHChangeNotify(0x08000000, 0, [IntPtr]::Zero, [IntPtr]::Zero)
} catch {}

Write-Host "Success! .gj files are now associated with the GujaratiLang icon in Windows File Explorer." -ForegroundColor Green
Write-Host "Icon path: $icoFullPath" -ForegroundColor Cyan
