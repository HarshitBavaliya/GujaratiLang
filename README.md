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
- Variables declared with `રાખો` and reassigned with `=`
- Gujarati or English-letter variable names, with digits and underscores
  allowed after the first character
- `જો`, `અથવા જો`, and `અથવા` conditional blocks with braces
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

Example (`examples/hello.gj`):

```text
આવો
રાખો ગણતરી = 3;
ગણતરી = ગણતરી + 2;
છાપો ગણતરી;
છાપો 1 + 2 * (3 + 4);
છાપો -8 / 2;
છાપો 5 >= 5;
જો (ગણતરી > 3) {
    છાપો "શરત સાચી છે";
} અથવા જો (2 == 3) {
    છાપો "આ શાખા ચાલશે નહીં";
} અથવા {
    છાપો નકામો;
}
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

Variables can contain numbers, strings, or `નકામો`. Declare a name once with
`રાખો`; later assignments update it. Assigning to an undeclared name or
declaring the same name twice is an error. Variables declared in a conditional
block remain available for the rest of the program.

## Build and run

Requires a C99 compiler and CMake 3.16 or newer.

```powershell
cmake -S . -B build
cmake --build build
.\build\Debug\gujarati.exe .\examples\hello.gj
```

For a single-configuration generator, the executable may instead be at
`build/gujarati.exe`.

## Tests

CTest runs the interpreter regression suite after building:

```powershell
ctest --test-dir build --output-on-failure
```

GitHub Actions builds and runs the tests on Windows and Ubuntu for pushes and
pull requests.

## Roadmap

1. **Core syntax:** lexer, expression parser, arithmetic, and print statements.
2. **Values and names:** variables, booleans, and Gujarati identifiers.
3. **Control flow:** logical operators and loops.
4. **Runtime:** functions, useful standard-library operations, and a REPL.
5. **Language quality:** tests, error recovery, documentation, and packaging.

The early syntax and keyword vocabulary are intentionally small; we can refine
them as the language takes shape.

## Contributing

Bug reports and pull requests are welcome. See [CONTRIBUTING.md](CONTRIBUTING.md)
for build and contribution guidelines. GujaratiLang is licensed under the
[MIT License](LICENSE).
