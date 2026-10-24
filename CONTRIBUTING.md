# Contributing to GujaratiLang

Thanks for your interest in contributing!

## Report an issue

Open a GitHub issue for bugs, questions, or feature ideas. For a bug report,
include the GujaratiLang source that reproduces it, the command you ran, and
the output you expected and received.

## Make a change

1. Fork the repository and create a branch for your change.
2. Keep source files and `.gj` examples encoded as UTF-8.
3. Build the interpreter, run the regression tests, and run the sample program:

   ```powershell
   cmake -S . -B build
   cmake --build build
   ctest --test-dir build --output-on-failure
   .\build\gujarati.exe .\examples\hello.gj
   ```

   With a multi-configuration CMake generator, the executable may instead be
   at `build\Debug\gujarati.exe`.
4. Open a pull request describing what changed and how you checked it.

When changing language syntax, update the README and add a small example when
appropriate.
