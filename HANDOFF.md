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
  and romanized syntax highlighting, starter snippets, and brace-aware indentation
  and code block folding.
- CI passed on Windows, Ubuntu, macOS Intel, and macOS arm64 for the interpreter
  and has dedicated extension validation.

## Latest repository changes

Latest commit on origin: `bc46ddc` — **Improve VS Code indentation and code folding**.

Recent completed work includes:

- `editors/vscode/`: Marketplace extension published as v0.1.3 with brace-aware
  indentation and code block folding.
- `editors/vscode/README.md`: documented local package installation and
  repeatable extension release process (`vsce package` / `vsce publish`).
- `.github/workflows/ci.yml`: added `validate-extension` job to validate extension
  JSON schemas and package integrity with `@vscode/vsce package`.
- `.gitignore`: added `*.vsix` to root ignores.
- `examples/inventory.gj` and `examples/inventory_helpers.gj`: multi-feature runnable
  example combining user input (`vancho`), functions (`kary`), lists and loops
  (`darek`), and modular code (`import`).
- `tests/run_example.cmake` & `CMakeLists.txt`: added optional `INPUT_FILE` support
  for example regression tests; registered `example_inventory`.
- `tests/examples/inventory.stdin` and `tests/examples/inventory.stdout`: automated
  test assertions for the inventory example.
- `README.md` & `docs/tutorial.md`: cross-referenced `inventory.gj` example.
- The test suite has 91 passing cases (100% pass rate), including negative and boundary tests for module imports and list indexing.

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
./examples/hello.gj`. The test suite has 86 passing cases after the
inventory example test was added.

## Suggested next work

1. Review `git status` and commit the extension CI validation, inventory example,
   docs, and handoff updates.
2. Push the commits to `origin/main` and verify that the newly added
   `validate-extension` CI job and all 86 CTest test cases pass across Windows,
   Ubuntu, macOS Intel, and macOS Apple Silicon.
3. Add negative / error-handling tests for edge cases (e.g., circular module imports
   across nested directories or missing module error diagnostics).
4. Expand standard library built-ins (e.g. type introspection, string splitting/joining,
   or numeric conversion utilities).
5. Add a Gujarati-script version of the multi-feature example program (`દાખલો` /
   `સ્ટોક`) alongside the romanized `inventory.gj`.

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
