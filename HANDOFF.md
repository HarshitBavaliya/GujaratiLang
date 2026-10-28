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

- Latest interpreter release: [GujaratiLang v0.9.0](https://github.com/HarshitBavaliya/GujaratiLang/releases/tag/v0.9.0).
  It provides Windows x64, Linux x64, macOS Intel, and macOS arm64 packages,
  along with SHA-256 checksums.
- The cross-platform release workflow successfully built and tested each
  platform before publishing v0.9.0.
- The VS Code extension is
  [GujaratiLang on the Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=harshitbavaliya.gujarati),
  published as `HarshitBavaliya.gujarati`, currently v1.0.0.
- Install the extension with:

  ```powershell
  code --install-extension HarshitBavaliya.gujarati
  ```

- The extension has a 128x128 icon, Gujarati and romanized syntax highlighting (updated for all 50 features), full instant single-letter auto-completion snippets (e.g. typing `k` auto-completes full `kary` function boilerplate), and brace-aware indentation and code block folding. Version 1.0.0 is published on the Visual Studio Marketplace.
- CI passed on Windows, Ubuntu, macOS Intel, and macOS arm64 for the interpreter
  and has dedicated extension validation.

## Latest repository changes

Latest commit on origin: `6e3b37a` — **Bump interpreter project version to 0.8.0**.

Recent completed work includes:

- Added standard library built-ins to the C interpreter:
  - `ગોળ(number)` / `gol(number)`: rounds number to nearest integer.
  - `નીચે(number)` / `niche(number)`: floors number.
  - `ઉપર(number)` / `upar(number)`: ceils number.
  - `પુનરાવર્તન(string, count)` / `punravartan(string, count)`: repeats a string count times.
  - `ટુકડો(list, start[, length])` / `tukdo(list, start[, length])`: slices a sub-list.
  - `સ્થાન(list, item[, start])` / `sthan(list, item[, start])`: finds the 0-based first index of an item in a list (-1.0 if not found).
  - `મૂકો(list, index, item)` / `muko(list, index, item)`: inserts an item into a list at index in-place.
  - `ડાબે_ભરો(string, width[, pad])` / `dabe_bharo(string, width[, pad])`: pads a string on the left to target width.
  - `જમણે_ભરો(string, width[, pad])` / `jamne_bharo(string, width[, pad])`: pads a string on the right to target width.
  - `સીમા(value, min, max)` / `sima(value, min, max)`: clamps a numeric value between minimum and maximum bounds.
  - `યાદચ્છિક([min, max])` / `yadachhik([min, max])`: generates a pseudo-random float in [0.0, 1.0) or random integer in range [min, max].
  - `બીજ(seed)` / `beej(seed)`: sets pseudo-random number generator seed for deterministic simulation and testing.
  - `વિસ્તારો(list, other)` / `vistaro(list, other)`: appends all items from another list in-place and evaluates to the list.
  - `પાઈ()` / `pi()`: mathematical constant pi (~3.141592653589793).
  - `ઈ()` / `e()`: mathematical constant e (~2.718281828459045).
  - `ચિહ્ન(number)` / `chihna(number)`: returns the sign of a number (1.0, -1.0, or 0.0).
  - `લઘુગણક(number[, base])` / `laghuganak(number[, base])`: calculates natural logarithm or logarithm with base.
  - `અક્ષર_કોડ(string[, index])` / `akshar_kod(string[, index])`: returns the Unicode code point of character at index (default 0).
  - `કોડ_થી_અક્ષર(code)` / `kod_thi_akshar(code)`: creates a single-character string from a Unicode code point.
  - `યાદી_ભરો(count, value)` / `yadi_bharo(count, value)`: creates a new list filled with count copies of value.
  - `સરવાળો_યાદી(list)` / `sarvalo_yadi(list)`: sums all numeric elements in a list (0 for empty list).
  - `યાદી_ન્યૂનતમ(list)` / `yadi_nyunatam(list)`: finds the minimum number in a list.
  - `યાદી_મહત્તમ(list)` / `yadi_mahatam(list)`: finds the maximum number in a list.
  - `ગણતરી(seq, item)` / `ganatari(seq, item)` (alias `ગણતરી_વસ્તુ` / `ganatari_vastu`): counts item occurrences in a list or substring occurrences in a string.
  - `ડાબે_કાપો(string)` / `dabe_kapo(string)` (alias `ડાબે_સાફ` / `dabe_saf`): trims leading whitespace.
  - `જમણે_કાપો(string)` / `jamne_kapo(string)` (alias `જમણે_સાફ` / `jamne_saf`): trims trailing whitespace.
  - `વિભાજન_પંક્તિ(string)` / `vibhaajan_pankti(string)` (alias `પંક્તિઓ` / `panktiyo`): splits a multi-line string into lines.
  - `અક્ષરો(string)` / `aksharo(string)`: splits a string into a list of individual UTF-8 characters.
  - `પર્યાવરણ(name)` / `paryavaran(name)`: retrieves system environment variable, or returns `નકામો` (`null`) if not found.
  - `બહાર([code])` / `bahar([code])`: exits program immediately with exit code (default 0).
  - `ચકાસો(condition[, message])` / `chakaso(condition[, message])`: asserts condition is truthy, triggering runtime failure otherwise.
  - `સમાવે_લખાણ(haystack, needle)` / `samave_lakhan(haystack, needle)`: returns 1.0 if string contains substring, 0.0 otherwise.
  - `બદલો(string, target, replacement)` / `badlo(string, target, replacement)`: replaces occurrences of a substring.
  - `શરૂઆત_સાથે(string, prefix)` / `sharuat_sathe(string, prefix)`: returns 1.0 if string starts with prefix, 0.0 otherwise.
  - `અંત_સાથે(string, suffix)` / `ant_sathe(string, suffix)`: returns 1.0 if string ends with suffix, 0.0 otherwise.
  - `સમાવે_છે(list, item)` / `samave_chhe(list, item)`: returns 1.0 if item is in list, 0.0 otherwise.
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
  - [`examples/text_filter.gj`](examples/text_filter.gj) combining `vancho`, `sharuat_sathe`, `ant_sathe`, `badlo`, `samave_chhe`, `bhag`, `saf`, `umero`, and `jodo`.
  - [`examples/report_generator.gj`](examples/report_generator.gj) combining `vancho`, `punravartan`, `gol`, `tukdo`, `bhag`, `saf`, `umero`, and `jodo`.
  - [`examples/invoice_generator.gj`](examples/invoice_generator.gj) combining `vancho`, `sima`, `sthan`, `muko`, `dabe_bharo`, `jamne_bharo`, `punravartan`, and `gol`.
  - [`examples/random_game.gj`](examples/random_game.gj) simulating dice rolls and number guessing with `beej`, `yadachhik`, `sarvalo_yadi`, `yadi_nyunatam`, `yadi_mahatam`, `ganatari`, `sankhya`, and `chakaso`.
  - Automated stdin/stdout regression tests in [`tests/examples/`](tests/examples/) registered under CTest.
- Prepared VS Code extension v0.3.0 in [`editors/vscode/package.json`](editors/vscode/package.json) and [`editors/vscode/CHANGELOG.md`](editors/vscode/CHANGELOG.md):
  - Updated syntax highlighting grammar [`editors/vscode/syntaxes/gujarati.tmLanguage.json`](editors/vscode/syntaxes/gujarati.tmLanguage.json)
    with rules for all new built-ins (`yadachhik`, `beej`, `vistaro`, `pi`, `e`, `chihna`, `laghuganak`, `akshar_kod`, `kod_thi_akshar`, `yadi_bharo`, `sarvalo_yadi`, `yadi_nyunatam`, `yadi_mahatam`, `ganatari`, `dabe_kapo`, `jamne_kapo`, `vibhaajan_pankti`, `aksharo`, `paryavaran`, `bahar`, `chakaso`, `samave_lakhan`).
  - Added starter snippets in [`editors/vscode/snippets/gujarati.code-snippets`](editors/vscode/snippets/gujarati.code-snippets)
    for all new built-ins in both Gujarati and romanized forms.
- Updated project landing page [`website/index.html`](website/index.html) with v0.9.0 downloads, VS Code extension v0.3.0 showcase, and new built-ins features.
- Expanded test suite to **281 passing test cases (100% pass rate)** in [`tests/run_test.cmake`](tests/run_test.cmake) and [`CMakeLists.txt`](CMakeLists.txt).
- Project milestone: Complete 30-point release v0.9.0.

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
./examples/string_utils.gj`. The test suite has 232 passing cases (100% pass rate).

## Suggested next work

1. **Random Number Generator built-in (`યાદચ્છિક` / `yadachhik`)**:
   Implement `yadachhik()` returning pseudo-random float `[0.0, 1.0)` or `yadachhik(min, max)` returning random integer in range.
2. **List Concatenation / Extend built-in (`વિસ્તારો` / `vistaro` or `જોડો_યાદી` / `jodo_yadi`)**:
   Extend a list by appending all items from another list in-place.
3. **String Character Replace / Regex-like Multi-replace**:
   Extended string transformation utilities.
4. **Math Constants (`પાઈ` / `pi` and `ઈ` / `e`)**:
   Built-in numeric constants or functions for mathematical calculations.
5. **Release v0.9.0**:
   Bump version in CMakeLists.txt to 0.9.0, tag, push, and release binaries with automated GitHub Actions cross-platform builds.

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
