# GujaratiLang Core Engine Contributor Guide

This guide is for developers contributing to the **GujaratiLang compiler, interpreter, runtime engine, and automated test suite**.

If you want to add a new built-in function, optimize runtime execution, enhance syntax parsing, or add new CLI developer tools, this document explains the architectural principles, codebase structure, step-by-step implementation workflows, and quality assurance gates.

---

## 1. Core Engineering Principles (Non-Negotiable)

Every contribution to the GujaratiLang core engine must strictly uphold three foundational tenets:

### 1. 100% Pure C99 with Zero External C Dependencies
- The core runtime engine is written entirely in portable ANSI C99 (`src/main.c`).
- External C third-party libraries (e.g. OpenSSL, libcurl, Boost, PCRE) are strictly forbidden. All algorithms (cryptographic SHA-256, HMAC, AES, SMT solvers, JSON parsers, CSV parsers, ROS2 CDR encoders, IPFS Base58/Base32 encoders, W3C DID resolvers) are implemented cleanly from first principles in standard C.
- The standard C library headers (`<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<math.h>`, `<time.h>`, `<errno.h>`) and operating-system networking/threading primitives (`<winsock2.h>` on Windows, `<sys/socket.h>` / `<pthread.h>` on POSIX) are the only permitted runtime headers.

### 2. Trilingual Keyword & Function Parity Rule
- Every language keyword, built-in function, and CLI command **must** have first-class representation in all three official representations:
  1. **Standard English** (e.g. `dtn_bundle_create`, `start`, `print`)
  2. **Romanized Gujarati** (e.g. `dtn_bundle_bnavo`, `aavo`, `chhapo`)
  3. **Native Gujarati Unicode** (e.g. `ડીટીએન_બંડલ_બનાવો`, `આવો`, `છાપો`)
- A pull request that introduces an English built-in without its corresponding Romanized and Native Gujarati counterparts will not pass code review.

### 3. 100% Automated Test Pass Rate
- Every single test case in the regression test suite must pass across all target operating systems (Windows x64, Linux x64, macOS x64, macOS Apple Silicon ARM64).
- As of v4.3.0, GujaratiLang has **990 / 990 tests passing 100%**. No regression or flaky test is permitted in `main`.

---

## 2. Setting Up Your Development Environment

### Prerequisites
- **Git** (2.x+)
- **CMake** (3.16+)
- **A C99-compliant C Compiler**:
  - **Windows**: Microsoft Visual Studio 2022 / 2026 Build Tools (with "Desktop development with C++" workload) or Clang/GCC (MinGW-w64).
  - **Linux**: GCC (9+) or Clang (10+) with `build-essential`.
  - **macOS**: Apple Clang (Xcode Command Line Tools).

### Building on Windows (PowerShell / Visual Studio)
Open the **x64 Native Tools Command Prompt for VS** or configure via standard PowerShell:
```powershell
# 1. Clone repository
git clone https://github.com/HarshitBavaliya/GujaratiLang.git
cd GujaratiLang

# 2. Configure with CMake
cmake -S . -B build -DBUILD_TESTING=ON

# 3. Compile Release executable
cmake --build build --config Release

# 4. Run full automated test suite (990 tests)
ctest --test-dir build --build-config Release -j8 --output-on-failure

# 5. Run compiled interpreter
.\build\Release\gujarati.exe examples\string_utils.gj
```

### Building on Linux & macOS (Bash / Zsh)
```bash
# 1. Clone repository
git clone https://github.com/HarshitBavaliya/GujaratiLang.git
cd GujaratiLang

# 2. Configure & Build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build build -j$(nproc 2>/dev/null || sysctl -n hw.ncpu)

# 3. Run regression tests
ctest --test-dir build -j8 --output-on-failure

# 4. Run compiled interpreter
./build/gujarati examples/string_utils.gj
```

---

## 3. Engine Codebase Structure

The GujaratiLang repository is organized cleanly:

```text
gujaratilang/
├── src/
│   └── main.c              # Core C99 single-file engine (Lexer, Parser, AST, Runtime, Builtins)
├── CMakeLists.txt          # CMake build definitions, compiler flags, and test suite list
├── tests/
│   ├── run_test.cmake      # CTest regression test harness executing code & checking output
│   ├── run_example.cmake   # Integration test runner for interactive CLI examples
│   └── examples/           # Pre-recorded stdin/stdout fixture files for examples
├── examples/               # Standalone runnable GujaratiLang programs (.gj)
├── docs/                   # Architectural guides, tutorials, and language references
├── release/
│   └── RELEASE_NOTES.md    # Historical release chronicles & changelogs
├── website/                # Official landing page & interactive web playground
└── editors/
    └── vscode/             # Visual Studio Code syntax highlighting extension & snippets
```

---

## 4. How to Add a New Built-in Function (Step-by-Step)

Adding a new built-in function to GujaratiLang is a streamlined, 5-step process. In this example, we will implement a hypothetical mathematical function: `calculate_hypotenuse(a, b)` / `karan_ganatri(a, b)` / `કર્ણ_ગણતરી(a, b)`.

### Step 1: Register Identifier Tokens in Builtin Validator
In `src/main.c`, locate the appropriate versioned `is_builtin_v...` function (or create a new sub-validator if adding for a new minor release). Add all three keyword spellings:

```c
static int is_builtin_v4(Parser *parser, Token name)
{
    // ... existing checks ...
    if (token_matches(parser, name, "calculate_hypotenuse")) return 1;
    if (token_matches(parser, name, "karan_ganatri")) return 1;
    if (token_matches(parser, name, "કર્ણ_ગણતરી")) return 1;
    return 0;
}
```

> [!NOTE]
> Ensure the new validator is called from `is_builtin_function_name(parser, name)`. This prevents users from unintentionally shadowing built-ins with user-defined function declarations.

### Step 2: Implement the C Runtime Helper
Implement the C99 helper function in `src/main.c`. Use the standard `Parser *parser, Token name, Value arg1, Value arg2...` signature:

```c
static Value calculate_hypotenuse_helper(Parser *parser, Token name, Value a_v, Value b_v) {
    (void)parser;
    if (a_v.kind != VALUE_NUMBER || b_v.kind != VALUE_NUMBER) {
        report_error(parser, name.line, name.column, "arguments to 'calculate_hypotenuse' must be numbers");
        return null_value();
    }
    double a = a_v.number;
    double b = b_v.number;
    double c = sqrt(a * a + b * b);
    return number_value(c);
}
```

### Step 3: Register in Parser Dispatch
In `src/main.c`, find the modular versioned dispatch function (e.g. `parse_v390_builtins` or create `parse_v400_builtins`):

```c
static Value parse_v400_builtins(Parser *parser, Token name, Value *arguments, size_t argument_count, int execute, int *handled) {
    if (token_matches(parser, name, "calculate_hypotenuse") ||
        token_matches(parser, name, "karan_ganatri") ||
        token_matches(parser, name, "કર્ણ_ગણતરી")) {
        *handled = 1;
        if (execute) {
            return calculate_hypotenuse_helper(parser, name,
                argument_count > 0 ? arguments[0] : null_value(),
                argument_count > 1 ? arguments[1] : null_value());
        }
        return null_value();
    }
    // ... other built-ins ...
    return null_value();
}
```

> [!IMPORTANT]
> **MSVC Compiler Recursion Depth Safety**:
> Do **NOT** chain long `if (...) return; else if (...) return; else if...` constructs exceeding 100 branches. Deep nesting causes MSVC's recursive descent parser to trigger `fatal error C1026: parser stack overflow, program too complex`.
> Instead, write independent `if (...) { *handled = 1; return ...; }` blocks so nesting depth remains constant at 1.

### Step 4: Write Automated Regression Tests in `tests/run_test.cmake`
Add your test case to `tests/run_test.cmake`:

```cmake
elseif(TEST_CASE STREQUAL "v400_calculate_hypotenuse")
    set(source [=[start
h1 = calculate_hypotenuse(3.0, 4.0);
h2 = karan_ganatri(5.0, 12.0);
h3 = કર્ણ_ગણતરી(8.0, 15.0);
print h1;
print h2;
print h3;
end]=])
    set(expected_stdout [=[5
13
17
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
```

### Step 5: Register the Test in `CMakeLists.txt`
Add the test name to `CMakeLists.txt` under `foreach(test_case IN ITEMS ...)`:

```cmake
            v400_calculate_hypotenuse
```

Reconfigure and run the test:
```bash
ctest --test-dir build -R "v400_calculate_hypotenuse" --output-on-failure
```

---

## 5. Memory Management Guidelines in C99

GujaratiLang manages values dynamically using a tagged union (`Value`). When allocating heap memory:

1. **Allocating Strings**:
   Always use `copy_string(const char *src)` or `gj_string(parser, name, c_str)` to register strings into the interpreter's string storage.
   ```c
   Value str_val = gj_string(parser, name, "my_string");
   ```
2. **Allocating Dictionaries (Hash Tables)**:
   ```c
   Dict *d = create_dict(parser, name);
   gj_dict_set(parser, d, "key", number_value(42.0), name);
   Value dict_val = gj_dict(d);
   ```
3. **Allocating Dynamic Lists**:
   ```c
   List *l = create_list(parser, name);
   append_list_item(parser, l, gj_string(parser, name, "element"), name);
   Value list_val = gj_list(l);
   ```
4. **Freeing Temporary C Strings**:
   If you extract a temporary C string using `value_to_c_string(parser, val)`, you are responsible for freeing it before the function returns:
   ```c
   char *str = value_to_c_string(parser, arg_v);
   // ... do work ...
   if (str) free(str);
   ```

---

## 6. Testing Best Practices

1. **Test Trilingual Synonyms**: Always test that the English, Romanized, and Gujarati function calls produce identical results.
2. **Test Error Handling**: For functions with required argument counts or types, add a failure test asserting `set(expect_failure TRUE)` and verify the exact expected error message in `expected_stderr`.
3. **Parallel Testing**: Always run `ctest -j8` to ensure tests execute concurrently without race conditions, file lock collisions, or shared global state corruption.

---

## 7. Submitting Your Contribution

1. Create a descriptive Git branch: `git checkout -b feat/your-feature-name`.
2. Format your C code cleanly adhering to C99 standards.
3. Ensure `ctest --test-dir build --output-on-failure` passes **100% of all tests**.
4. Update the relevant documentation in `docs/` and `release/RELEASE_NOTES.md`.
5. Open a Pull Request on [GitHub](https://github.com/HarshitBavaliya/GujaratiLang/pulls).
