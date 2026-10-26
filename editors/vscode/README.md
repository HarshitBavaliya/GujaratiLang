# GujaratiLang

Syntax highlighting for GujaratiLang source files in Visual Studio Code.
Highlights Gujarati and romanized keywords, comments, strings, numbers,
operators, and function calls in `.gj` files.

## Install from the Visual Studio Marketplace

Search for **GujaratiLang** in the Extensions view, or install it from the
[Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=harshitbavaliya.gujarati).
Open any `.gj` file; VS Code will select GujaratiLang as its language mode.

## Install a local build

To try the extension before it is available in the Marketplace, package it
from this directory with `npx @vscode/vsce package --no-dependencies`, then
open the generated `.vsix` file with VS Code or install it from the command
line:

```powershell
code --install-extension .\gujarati-0.1.0.vsix
```

To develop the extension, open this folder in VS Code and press F5 to launch
an Extension Development Host.
