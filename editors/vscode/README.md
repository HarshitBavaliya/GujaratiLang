# GujaratiLang

Syntax highlighting for GujaratiLang source files in Visual Studio Code.
Highlights Gujarati and romanized keywords, comments, strings, numbers,
operators, and function calls in `.gj` files. Includes starter snippets for
Gujarati and romanized source, plus brace-aware indentation and folding.

## Install from the Visual Studio Marketplace

Search for **GujaratiLang** in the Extensions view, or install it from the
[Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=harshitbavaliya.gujarati).
Open any `.gj` file; VS Code will select GujaratiLang as its language mode.
Type a snippet prefix such as `gj-program`, `gj-function`, `gj-if`,
`gj-while`, or `gj-for`, then select the matching completion.

## Install a local build

To try the extension locally, package it from this directory with
`npx @vscode/vsce package --no-git-tag-version`, then open the generated `.vsix`
file with VS Code or install it from the command line:

```powershell
code --install-extension .\gujarati-0.1.4.vsix
```

To develop the extension, open this folder in VS Code and press F5 to launch
an Extension Development Host.

## Extension release workflow

1. Increment `"version"` in [`package.json`](package.json).
2. Add a new release section with changes in [`CHANGELOG.md`](CHANGELOG.md).
3. Package and verify locally:
   ```powershell
   npx @vscode/vsce package --no-git-tag-version
   ```
4. Publish to Visual Studio Marketplace:
   ```powershell
   npx @vscode/vsce publish
   ```
