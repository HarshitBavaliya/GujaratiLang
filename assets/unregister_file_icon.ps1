# Unregister .gj file association and icon from CurrentUser
$ErrorActionPreference = "SilentlyContinue"

Remove-Item -Path "HKCU:\Software\Classes\.gj" -Recurse -Force | Out-Null
Remove-Item -Path "HKCU:\Software\Classes\GujaratiLang.File" -Recurse -Force | Out-Null

$code = @"
using System;
using System.Runtime.InteropServices;
public class ShellNotifyUnregister {
    [DllImport("shell32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern void SHChangeNotify(int wEventId, uint uFlags, IntPtr dwItem1, IntPtr dwItem2);
}
"@
Add-Type -TypeDefinition $code -ErrorAction SilentlyContinue
try {
    [ShellNotifyUnregister]::SHChangeNotify(0x08000000, 0, [IntPtr]::Zero, [IntPtr]::Zero)
} catch {}

Write-Host "Unregistered .gj file association from Windows File Explorer." -ForegroundColor Yellow
