# GujaratiLang project handoff

Use this file to resume work on GujaratiLang in a later session or with another
coding assistant. It summarizes the project state as of 2026-10-27. Recheck the
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

- Latest interpreter release: [GujaratiLang v0.7.0](https://github.com/HarshitBavaliya/GujaratiLang/releases/tag/v0.7.0).
  It provides Windows x64, Linux x64, macOS Intel, and macOS arm64 packages,
  along with SHA-256 checksums.
- The cross-platform release workflow successfully built and tested each
  platform before publishing v0.7.0.
- The VS Code extension is
  [GujaratiLang on the Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=harshitbavaliya.gujarati),
  published as `HarshitBavaliya.gujarati`, currently v0.1.4 (v0.1.7 prepared locally).
- Install the extension with:

  ```powershell
  code --install-extension HarshitBavaliya.gujarati
  ```

- The extension has a 128x128 icon derived from `website/favicon.svg`, Gujarati
  and romanized syntax highlighting (updated for all v0.7.0+ built-ins), starter snippets,
  and brace-aware indentation and code block folding. Version 0.1.4 is published on the Visual Studio Marketplace.
- CI passed on Windows, Ubuntu, macOS Intel, and macOS arm64 for the interpreter
  and has dedicated extension validation.

## Latest repository changes

Latest commit on origin: `2029d30` — **Add built-ins for list, string, and math operations with examples and VS Code v0.1.7 extension**.

Recent completed work includes:

- Added standard library built-ins to the C interpreter:
  - `સાફ(string)` / `saf(string)`: trims leading and trailing ASCII whitespace.
  - `ઘાત(base, exponent)` / `ghat(base, exponent)`: calculates exponentiation.
  - `મૂળ(number)` / `mul(number)`: calculates square root with domain error checking.
  - `ગોઠવો(list)` / `gothvo(list)`: sorts list items in-place in ascending order.
  - `ઉલટાવો(list)` / `ultavo(list)`: reverses list elements in-place and evaluates to the list.
  - `ભાગ(string, delimiter)` / `bhag(string, delimiter)`: splits a string by a delimiter into a list of strings.
  - `જોડો(list, separator)` / `jodo(list, separator)`: joins list elements into a single formatted string with separator.
  - `સંખ્યા(text)` / `sankhya(text)`: converts numeric strings to numbers.
  - `લખાણ(value)` / `lakhan(value)`: converts numbers, null, strings, and lists to strings.
  - `પ્રકાર(value)` / `prakar(value)`: returns value runtime type (`"number"`, `"string"`, `"list"`, or `"null"`).
  - `ઉમેરો(list, item)` / `umero(list, item)`: appends an item to a list dynamically in-place and returns the list.
  - `કાઢો(list[, index])` / `kadho(list[, index])`: removes and returns an element from a list (last element by default).
  - `કાપો(string, start[, length])` / `kapo(string, start[, length])`: slices strings using Unicode codepoints.
  - `શોધો(string, target[, start])` / `shodho(string, target[, start])`: searches for substring codepoint position (`-1` if not found).
  - `પહેલી_એબીસીડી(text)` / `peli_abcd(text)`: converts string to uppercase.
  - `બીજી_એબીસીડી(text)` / `biji_abcd(text)`: converts string to lowercase.
  - `મહત્તમ(a, b)` / `mahatam(a, b)`: returns the maximum of two numbers.
  - `ન્યૂનતમ(a, b)` / `nyunatam(a, b)`: returns the minimum of two numbers.
  - `ધન_મૂલ્ય(number)` / `dhan_mulya(number)`: returns the absolute value of a number.
- Created interactive runnable examples:
  - [`examples/calculator.gj`](examples/calculator.gj) combining `vancho`, `sankhya`, and `lakhan`.
  - [`examples/string_utils.gj`](examples/string_utils.gj) combining `vancho`, `shodho`, `kapo`, `peli_abcd`, `biji_abcd`, `umero`, and `kadho`.
  - [`examples/csv_parser.gj`](examples/csv_parser.gj) combining `vancho`, `bhag`, `jodo`, `sankhya`, `lakhan`, and `ultavo`.
  - [`examples/math_suite.gj`](examples/math_suite.gj) combining `vancho`, `ghat`, `mul`, `sankhya`, `lakhan`, `saf`, `gothvo`, and `ultavo`.
  - Automated stdin/stdout regression tests in [`tests/examples/`](tests/examples/) registered under CTest.
- Prepared VS Code extension v0.1.7 in [`editors/vscode/package.json`](editors/vscode/package.json) and [`editors/vscode/CHANGELOG.md`](editors/vscode/CHANGELOG.md):
  - Updated syntax highlighting grammar [`editors/vscode/syntaxes/gujarati.tmLanguage.json`](editors/vscode/syntaxes/gujarati.tmLanguage.json)
    with rules for `saf`, `ghat`, `mul`, and `gothvo` (both Gujarati script and romanized).
  - Added starter snippets in [`editors/vscode/snippets/gujarati.code-snippets`](editors/vscode/snippets/gujarati.code-snippets)
    for `gj-trim` (`સાફ`), `gj-power` (`ઘાત`), `gj-sqrt` (`મૂળ`), and `gj-sort` (`ગોઠવો`).
- Updated project landing page [`website/index.html`](website/index.html) with v0.7.0 downloads, VS Code extension v0.1.4 showcase, and new built-ins features.
- Expanded test suite to **136 passing test cases (100% pass rate)** in [`tests/run_test.cmake`](tests/run_test.cmake) and [`CMakeLists.txt`](CMakeLists.txt).

## Build and test

Requirements: CMake 3.16+, a C99 compiler, and Git. On Windows, use Visual
Studio Build Tools with the Desktop development with C++ workload.

```powershell
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Release
ctest --test-dir build --build-config Release --output-on-failure
.\build\gujarati.exe .\examples\string_utils.gj
```

On Linux/macOS, run the built interpreter as `./build/gujarati
./examples/string_utils.gj`. The test suite has 136 passing cases (100% pass rate).

## Suggested next work

1. **String Replacement built-in (`બદલો` / `badlo`)**:
   Implement `બદલો(string, target, replacement)` / `badlo(string, target, replacement)` in `src/main.c` to replace occurrences of a substring.
2. **String Prefix / Suffix Check built-ins (`શરૂઆત_સાથે` / `sharuat_sathe`, `અંત_સાથે` / `ant_sathe`)**:
   Implement string `startsWith` and `endsWith` checking returning boolean (1.0 or 0.0).
3. **List Search / Contains built-in (`સમાવે_છે` / `samave_chhe`)**:
   Implement membership testing `samave_chhe(list, item)` returning 1.0 if item is in the list and 0.0 otherwise.
4. **VS Code extension v0.1.8 preparation**:
   Bump to `0.1.8`, add syntax highlighting and snippets for `badlo`, `sharuat_sathe`, `ant_sathe`, and `samave_chhe`.
5. **Text Transformation & Search Runnable Example (`examples/text_filter.gj`)**:
   Create a runnable example demonstrating `sharuat_sathe`, `ant_sathe`, `badlo`, and `samave_chhe` with automated CTest assertions.

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
