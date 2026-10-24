# GujaratiLang

GujaratiLang is a small programming language runtime implemented in C, following
the general approach used by languages such as PHP: programs are parsed and run
by an interpreter rather than translated into C source.

## First milestone

The initial interpreter supports:

- Programs delimited by `આવો` (start) and `આવજો` (end)
- UTF-8 source files and the Gujarati `છાપો` (print) keyword
- Numeric literals, parentheses, unary minus, and `+`, `-`, `*`, `/`
- Numeric comparisons: `==`, `!=`, `<`, `<=`, `>`, and `>=`
- Logical operators: `અને` (AND), `અથવા` (OR), and `નહીં` (NOT)
- `જ્યાં સુધી (condition) { ... }` while loops
- Variables created and assigned with `name = value;`; assigning an existing
  name updates its value
- Functions declared with `કાર્ય name(parameters) { ... }`, called as
  expressions or statements, and returning values with `પરત expression;`
- Gujarati or English-letter variable names, with digits and underscores
  allowed after the first character
- `જો`, `નહિતર જો`, and `નહિતર` conditional blocks with braces
- The `નકામો` null value; conditions accept numbers (`0` is false, nonzero is
  true) and null (false); strings are not valid conditions. Comparison results
  are numbers (`1` for true and `0` for false)
- Quoted strings with `\"`, `\\`, `\n`, `\r`, and `\t` escapes
- `ચેતવણી "message";` to report a warning and continue
- `ભૂલ "message";` and `ઘાતક ભૂલ "message";` to report an error and stop
- Semicolon-terminated print statements and `//` line comments
- Clear file, line, and column diagnostics for invalid input

Comparisons have lower precedence than arithmetic. They require numeric
operands and produce `1` for true or `0` for false.
Logical precedence from strongest to weakest is `નહીં`, comparisons, `અને`,
then `અથવા`. Logical operators accept numbers and `નકામો`, return `1` or `0`,
and short-circuit when the result is already known. Strings cannot be used as
logical operands.

Example (`examples/hello.gj`):

```text
આવો
ગણતરી = 3;
ગણતરી = ગણતરી + 2;
છાપો ગણતરી;
છાપો 1 + 2 * (3 + 4);
છાપો -8 / 2;
છાપો 5 >= 5;
જો (ગણતરી > 3) {
    છાપો "શરત સાચી છે";
} નહિતર જો (2 == 3) {
    છાપો "આ શાખા ચાલશે નહીં";
} નહિતર {
    છાપો નકામો;
}
કાર્ય ઉમેરો(પહેલું, બીજું) {
    પરત પહેલું + બીજું;
}
છાપો ઉમેરો(2, 3);
ચેતવણી "This is a warning; the program will continue";
આવજો
```

Warnings and errors are written to standard error with the source location.
Warnings let the program continue; both error statements stop execution and
return a failure status. Built-in errors and warning labels are English by
default, regardless of the Gujarati keywords used in source. Select Gujarati
diagnostics with the `--language gu` option; use `--language en` to select
English explicitly. Messages supplied by the program remain exactly as written.

```powershell
.\build\gujarati.exe --language gu .\examples\hello.gj
```

Diagnostic messages and printed strings support `\"`, `\\`, `\n`, `\r`, and
`\t` escapes.

Variables can contain numbers, strings, or `નકામો`. Assigning to a name for the
first time creates it; later assignments update it. Reading a name before its
first assignment is an error. Variables first assigned in a conditional block
remain available for the rest of the program.

`જ્યાં સુધી` checks its condition before each iteration and repeats the block
while the condition is true:

```text
ગણતરી = 0;
જ્યાં સુધી (ગણતરી < 3) {
    ગણતરી = ગણતરી + 1;
    છાપો ગણતરી;
}
```

Declare a function before calling it. Parameters and newly assigned variables
are local to that call. Assignments to existing names, including globals,
update those variables. Functions can call themselves or other previously
declared functions. A function returns
`નકામો` if it reaches the end or uses `પરત;` without a value:

```text
કાર્ય ગુણાકાર(n) {
    જો (n <= 1) { પરત 1; }
    પરત n * ગુણાકાર(n - 1);
}
છાપો ગુણાકાર(5);
```

## Install, build, and run

### Run a prebuilt release

Prebuilt packages are available for Windows x64, Linux x64, and macOS on both
Intel (x64) and Apple Silicon (arm64). Download the matching package from the
[latest GitHub release](https://github.com/HarshitBavaliya/GujaratiLang/releases/latest).
The release includes SHA-256 checksums for all platform packages.

#### Windows x64

1. Download the latest
   [GujaratiLang Windows 64-bit release](https://github.com/HarshitBavaliya/GujaratiLang/releases/latest/download/gujaratilang-windows-x64.zip).
2. Extract the ZIP file.
3. Open PowerShell in the extracted folder and run the included example:

   ```powershell
   .\gujarati.exe .\examples\hello.gj
   ```

4. Run your own program by giving its `.gj` file path:

   ```powershell
   .\gujarati.exe C:\path\to\your-program.gj
   ```

#### Linux x64

Download `gujaratilang-linux-x64.tar.gz`, then extract and run it from a
terminal:

```sh
tar -xzf gujaratilang-linux-x64.tar.gz
./gujarati ./examples/hello.gj
./gujarati /path/to/your-program.gj
```

This package is built on Ubuntu 22.04 and requires a compatible glibc-based
Linux distribution.

#### macOS Intel and Apple Silicon

Download `gujaratilang-macos-x64.tar.gz` for Intel Macs or
`gujaratilang-macos-arm64.tar.gz` for Apple Silicon Macs. In Terminal, extract
the matching package and run the example:

```sh
tar -xzf gujaratilang-macos-arm64.tar.gz
./gujarati ./examples/hello.gj
./gujarati /path/to/your-program.gj
```

Use the `macos-x64` archive on Intel instead of the `macos-arm64` archive shown
in the extraction command. The macOS binaries are not signed or notarized, so
macOS may display a security warning. The release package contains the
interpreter, example program, and a short `README.txt`.

To build from source or contribute, follow the developer setup below.

### Build from source

Building requires Git, CMake 3.16 or newer, and a C99 compiler. On Windows,
install Visual Studio or Build Tools with the **Desktop development with C++**
workload. On Debian or Ubuntu, install the tools with
`sudo apt install build-essential cmake git`. On macOS, install Xcode Command
Line Tools and CMake.

Then clone, build, and run the example:

```text
git clone https://github.com/HarshitBavaliya/GujaratiLang.git
cd GujaratiLang
cmake -S . -B build
cmake --build build --config Release
```

On Windows, run
`.\build\Release\gujarati.exe .\examples\hello.gj`. On Linux or macOS, run
`./build/gujarati ./examples/hello.gj`. For a single-configuration CMake
generator, the executable may instead be at `build/gujarati.exe` on Windows.

If PowerShell says `cmake` is not recognized, install CMake, add it to `PATH`,
and open a new PowerShell window.

## Tests

CTest runs the interpreter regression suite after building:

```powershell
ctest --test-dir build --output-on-failure
```

GitHub Actions builds and runs the tests on Windows, Ubuntu, and both Intel and
Apple Silicon macOS runners for pushes and pull requests. Tagged releases
publish prebuilt packages for all four supported platform targets.

## Project website

The static landing page is in `website/index.html`. It has no build step or
external dependencies. Upload it as `index.html` to the subdomain's web root
using FTPS or SFTP; avoid unencrypted FTP when transferring hosting credentials.
The VS Code FTPS profile in `.vscode/sftp.json` is local-only and excluded from
Git. It leaves the password unset so the SFTP extension can prompt for it.

## Roadmap

1. **Core language:** expressions, values, variables, conditionals, loops, and
   functions.
2. **Runtime:** useful standard-library operations and a REPL.
3. **Language quality:** error recovery, documentation, and packaging.

The early syntax and keyword vocabulary are intentionally small; we can refine
them as the language takes shape.

## Contributing

Bug reports and pull requests are welcome. See [CONTRIBUTING.md](CONTRIBUTING.md)
for build and contribution guidelines. GujaratiLang is licensed under the
[MIT License](LICENSE).
