# GujaratiLang project handoff

Use this file to resume work on GujaratiLang in a later session or with another
coding assistant. It summarizes the project state as of 2026-10-26. Recheck the
repository and Marketplace before acting because versions and workflow status
can change.

## Project

- Repository: <https://github.com/HarshitBavaliya/GujaratiLang>
- Default branch: `main`
- Local workspace: `D:\gujaratilang`
- GujaratiLang is a C99 interpreter. Programs use Gujarati keywords or lowercase
  romanized Gujarati keywords; both forms are supported.
- The interpreter, regression tests, CMake build, GitHub Actions workflows,
  examples, tutorial, and portable release process are in this repository.

## Current published state

- Latest interpreter release: [GujaratiLang v0.6.0](https://github.com/HarshitBavaliya/GujaratiLang/releases/tag/v0.6.0).
  It provides Windows x64, Linux x64, macOS Intel, and macOS arm64 packages,
  along with SHA-256 checksums.
- The cross-platform release workflow successfully built and tested each
  platform before publishing v0.6.0.
- The VS Code extension is
  [GujaratiLang on the Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=harshitbavaliya.gujarati),
  published as `HarshitBavaliya.gujarati`, currently v0.1.3.
- Install the extension with:

  ```powershell
  code --install-extension HarshitBavaliya.gujarati
  ```

- The extension has a 128x128 icon derived from `website/favicon.svg`, Gujarati
  and romanized syntax highlighting (updated for v0.7.0 built-ins), starter snippets,
  and brace-aware indentation and code block folding. Version 0.1.4 is prepared and
  tested locally.
- CI passed on Windows, Ubuntu, macOS Intel, and macOS arm64 for the interpreter
  and has dedicated extension validation.

## Latest repository changes

Latest commit on origin: `302a97c` — **Add native Gujarati stock example with automated assertions**.

Recent completed work includes:

- Added standard library built-ins to the C interpreter:
  - `સંખ્યા(text)` / `sankhya(text)`: converts numeric strings to numbers.
  - `લખાણ(value)` / `lakhan(value)`: converts numbers, null, strings, and lists to strings.
  - `પ્રકાર(value)` / `prakar(value)`: returns value runtime type (`"number"`, `"string"`, `"list"`, or `"null"`).
- Extended VS Code grammar [`editors/vscode/syntaxes/gujarati.tmLanguage.json`](editors/vscode/syntaxes/gujarati.tmLanguage.json)
  with keyword and function highlighting for the new built-ins.
- Prepared VS Code extension v0.1.4 in [`editors/vscode/package.json`](editors/vscode/package.json),
  updated [`editors/vscode/CHANGELOG.md`](editors/vscode/CHANGELOG.md), and verified packaging locally.
- Bumped project version to `0.7.0` in [`CMakeLists.txt`](CMakeLists.txt).
- Added 6 regression tests covering valid and error cases for the new built-ins in
  [`tests/run_test.cmake`](tests/run_test.cmake) and registered them in [`CMakeLists.txt`](CMakeLists.txt).
- Multi-feature runnable examples:
  - [`examples/inventory.gj`](examples/inventory.gj) / [`examples/inventory_helpers.gj`](examples/inventory_helpers.gj) (romanized).
  - [`examples/stock.gj`](examples/stock.gj) / [`examples/stock_helpers.gj`](examples/stock_helpers.gj) (native Gujarati script).
- Extended [`tests/run_example.cmake`](tests/run_example.cmake) with `ENCODING UTF-8` and stdin file support.
- Documented new built-ins and examples in [`README.md`](README.md) and [`docs/tutorial.md`](docs/tutorial.md).
- The test suite has **98 passing cases (100% pass rate)**.

## Build and test

Requirements: CMake 3.16+, a C99 compiler, and Git. On Windows, use Visual
Studio Build Tools with the Desktop development with C++ workload.

```powershell
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Release
ctest --test-dir build --build-config Release --output-on-failure
.\build\gujarati.exe .\examples\hello.gj
```

On Linux/macOS, run the built interpreter as `./build/gujarati
./examples/hello.gj`. The test suite has 98 passing cases after the
new built-in tests were added.

## Suggested next work

1. Commit and push the new standard library built-ins (`sankhya`, `lakhan`, `prakar`),
   syntax highlighting updates, tests, and documentation.
2. Verify all CI jobs pass across Windows, Ubuntu, macOS Intel, and macOS arm64
   on GitHub Actions.
3. Update `editors/vscode/package.json` to version `0.1.4`, update
   `editors/vscode/CHANGELOG.md`, and publish `v0.1.4` to the Visual Studio Marketplace.
4. Prepare and tag GujaratiLang runtime release `v0.7.0` (updating `project(gujaratilang VERSION 0.7.0)`
   in `CMakeLists.txt`).
5. Add an interactive example script utilizing `sankhya(vancho("..."))` to calculate
   totals or averages from user terminal input.

## Important workspace notes

- Inspect `git status` before editing or committing.
- Do not stage or commit unrelated local files. The worktree has user-local
  untracked files under `.vscode/` and `HarshitBavaliya.gujarati`; leave them
  untouched.
- `/website/` is ignored by `.gitignore` and has local-only website edits.
  Do not publish those changes as part of an unrelated task.
- Never commit or share Marketplace credentials. Publishing requires
  authorization in the user's environment; do not ask them to paste a token
  into chat.
- Extension publication requires incrementing `editors/vscode/package.json`
  `version` for each Marketplace release.
- Preserve existing Gujarati and romanized spellings, including `kary` for
  functions and `ma` as the romanized for-loop separator.
- Keep README, tutorial, examples, tests, and release notes consistent when
  changing language behavior.
