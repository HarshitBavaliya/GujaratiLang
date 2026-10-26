# GujaratiLang syntax highlighting for Visual Studio Code

This folder contains a small TextMate grammar and language configuration for
GujaratiLang source files. It highlights Gujarati and romanized keywords,
comments, strings, numbers, operators, and function calls in `.gj` files.

## Install locally

The extension is not published to the Visual Studio Marketplace. To install it
for your current VS Code user:

1. Copy this `vscode` folder into the VS Code extensions directory and rename
   the copied folder to `harshitbavaliya.gujarati-0.1.0`.
   - Windows: `%USERPROFILE%\.vscode\extensions\`
   - Linux/macOS: `~/.vscode/extensions/`
2. Run **Developer: Reload Window** from the Command Palette.
3. Open any `.gj` file. VS Code should show **GujaratiLang** as the language
   mode in the status bar.

For example, from the repository root in PowerShell:

```powershell
$destination = Join-Path $HOME ".vscode\extensions\harshitbavaliya.gujarati-0.1.0"
New-Item -ItemType Directory -Force -Path (Split-Path $destination) | Out-Null
Copy-Item -Recurse .\editors\vscode $destination
```

To try changes without installing them, open this folder in VS Code and press
F5 to launch an Extension Development Host.
