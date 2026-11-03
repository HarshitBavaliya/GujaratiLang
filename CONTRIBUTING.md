# Contributing to GujaratiLang

Welcome! We are excited that you want to contribute to **GujaratiLang (ગુજરાતી લેંગ્વેજ)** — the 100% pure C99 interpreter, compiler, and trilingual runtime engine.

Whether you are fixing a bug, implementing a new built-in function, expanding language tests, improving documentation, or optimizing performance, your contributions are warmly welcomed.

---

## 🧭 Developer Guides & Documentation

Before opening a pull request, please review the specialized developer guides in the [`docs/`](docs/) directory:

- 🚀 **[Getting Started Guide](docs/GETTING_STARTED.md)**: How to set up your environment, write your first GujaratiLang program, use the REPL, and scaffold projects with starter kits.
- 🛠️ **[Core Engine Developer Guide](docs/DEVELOPER_GUIDE.md)**: How to build from source, understand memory management in C99, and add new built-in functions step-by-step.
- 🏛️ **[Runtime Architecture](docs/ARCHITECTURE.md)**: Deep dive into the tokenizer, recursive descent parser, `Value` tagged union, lexical environments, and C99 subsystems.
- 📖 **[Complete Language Reference](docs/LANGUAGE_REFERENCE.md)**: Catalog of all keywords, syntax forms, and standard library built-ins across English, Romanized, and Native Gujarati.

---

## ⚡ The Three Core Contributor Rules

To ensure long-term stability, portability, and philosophical integrity, every pull request must satisfy these three rules:

1. **Zero External C Dependencies (Pure C99)**:
   The entire engine is contained in standard C99 (`src/main.c`). Do not introduce dependencies on third-party C libraries (`libcurl`, `openssl`, etc.). Everything must compile cleanly with standard C99 headers and platform networking.

2. **Trilingual Keyword & Function Parity**:
   Every new keyword, built-in function, and CLI command must have first-class representation in:
   - **English** (e.g. `dtn_bundle_create`)
   - **Romanized Gujarati** (e.g. `dtn_bundle_bnavo`)
   - **Native Gujarati Unicode** (e.g. `ડીટીએન_બંડલ_બનાવો`)

3. **100% Automated Test Pass Rate**:
   The automated test suite runs via CTest across Windows, Linux, and macOS. All tests (**870 / 870** in v3.9.0) must pass 100% with zero failures.

---

## 🛠️ Local Build & Test Workflow

### 1. Build the Interpreter
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build build --config Release
```

### 2. Run the Full Test Suite
```bash
ctest --test-dir build -j8 --output-on-failure
```

### 3. Run a Specific Test
```bash
ctest --test-dir build -R "v390_dtn_bundle_create" --output-on-failure
```

---

## 📋 Pull Request Checklist

Before submitting a Pull Request:
- [ ] Code is written in portable ANSI C99.
- [ ] Source files and `.gj` code are saved as **UTF-8**.
- [ ] New built-in functions are registered in the tokenizer validator (`is_builtin_...`), implemented in a C helper, and dispatched in `parse_..._builtins`.
- [ ] Trilingual names are provided for all additions.
- [ ] Automated tests are added in `tests/run_test.cmake` and listed in `CMakeLists.txt`.
- [ ] Full regression suite passes 100% locally (`ctest --test-dir build -j8`).
- [ ] Documentation updated in `docs/` and `release/RELEASE_NOTES.md`.

Thank you for helping make GujaratiLang a world-class trilingual programming language!
