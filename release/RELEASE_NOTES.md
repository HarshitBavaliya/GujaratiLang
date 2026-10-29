# GujaratiLang v1.5.0 — The Ecosystem & Production Super-Release 🚀

GujaratiLang **v1.5.0** marks a monumental milestone in the evolution of the language, expanding it from an interpreted scripting engine into a **complete, self-sustaining developer ecosystem**. 

This release introduces **30 major features across 6 core pillars**, including our official Package Manager (`gjpm`), WebAssembly compiler (`.wasm`), native wire SQL database drivers (PostgreSQL & MySQL), 24-bit BMP image engine & terminal computer vision, stackless async coroutines, and a built-in unit testing & benchmarking framework.

All **392 test cases** pass with 100% success rate across Windows, Linux, macOS Apple Silicon, and macOS Intel with **zero third-party dependencies**.

---

## 🌟 What's New in v1.5.0 (The 6 Core Pillars)

### 📦 1. Gujarati Package Manager (`gjpm`) & Modular Imports
- **CLI Commands**:
  - `gujarati pkg init`: Create a `gujarati.pkg.json` project manifest.
  - `gujarati pkg install <pkg>`: Download and install packages into `.gujarati_packages/`.
  - `gujarati pkg list`: List installed packages and dependencies.
- **Built-in Package Functions**:
  - `pkg_info("name")` / `પેકેજ_માહિતી("નામ")`: Inspect package metadata, versions, and installation status.
  - `pkg_load("name")` / `પેકેજ_લોડ("નામ")`: Dynamically load installed package modules into runtime memory.

### 🌐 2. WebAssembly (`.wasm`) & Browser DOM Engine
- **AST to WebAssembly Compiler**:
  - `wasm_compile(code)` / `વોસમ_કમ્પાઇલ(કોડ)`: Compiles GujaratiLang code into WebAssembly binary representations (`\0asm` magic byte headers).
- **Virtual DOM Primitives**:
  - `dom_select(selector)` / `ડોમ_પસંદ`: Select virtual DOM elements.
  - `dom_set_html(el, html)` / `ડોમ_લખાણ`: Dynamic inner HTML manipulation.
  - `dom_set_style(el, styles)` / `ડોમ_શૈલી`: Inline style updates.
  - `dom_on_event(el, event, callback)` / `ડોમ_ઘટના`: Interactive event listener binding.

### 🗄️ 3. Wire SQL Protocols (PostgreSQL & MySQL)
- **Direct Wire-Level Database Connectors**:
  - `pg_connect("postgres://...")` / `પીજી_જોડો`: Native PostgreSQL connection.
  - `pg_query(conn, "SELECT ...")` / `પીજી_પ્રશ્ન`: Query execution returning structured dictionaries.
  - `mysql_connect("mysql://...")` / `માયએસક્યુએલ_જોડો`: Native MySQL connection.
  - `mysql_query(conn, "SELECT ...")` / `માયએસક્યુએલ_પ્રશ્ન`: Query execution.
- **Transactions & Connection Pooling**:
  - `tx_begin(conn)` / `વ્યવહાર_શરૂ`, `tx_commit(conn)` / `વ્યવહાર_માન્ય`, `tx_rollback(conn)` / `વ્યવહાર_રદ`.
  - `db_pool_create(conn, size)` / `ડેટાબેઝ_પૂલ_બનાવો`: Connection pooling for high concurrency.
  - `sql_prepare(sql, params)` / `એસક્યુએલ_તૈયાર`: SQL injection-safe parameterized query formatting.

### 🖼️ 4. Native Image Processing Engine & Terminal Graphics (BMP)
- **24-bit RGB Canvas Engine**:
  - `image_create(w, h, color)` / `ચિત્ર_બનાવો`: Allocate in-memory pixel buffers with hex color fills.
  - `image_write_bmp(img, path)` / `ચિત્ર_સાચવો`: Encode and save RFC-standard 24-bit BMP bitmap files with standard headers.
  - `image_read_bmp(path)` / `ચિત્ર_વાંચો`: Decode BMP files extracting width, height, and pixel streams.
  - `image_resize(img, new_w, new_h)` / `ચિત્ર_માપ`: Bilinear image resizing.
  - `image_filter(img, "grayscale")` / `ચિત્ર_ફિલ્ટર`: Apply image filters (grayscale, invert, threshold).
  - `image_terminal(img, w, h)` / `ચિત્ર_ટર્મિનલ`: Render images directly inside terminal consoles via ANSI TrueColor.

### ⚡ 5. Async/Await & Stackless Coroutines
- **Cooperative Concurrency**:
  - `async_task(fn, args)` / `અસંકેત_કાર્ય`: Spawn background asynchronous tasks.
  - `async_await(task)` / `પ્રતીક્ષા`: Yield execution until coroutines finish and fetch results.
  - `async_all([t1, t2])` / `અસંકેત_બધા`: Concurrent task aggregation (`Promise.all` equivalent).
  - `async_sleep(ms)` / `અસંકેત_ઊંઘ`: Non-blocking coroutine sleep timer.
  - `event_emitter()` / `ઘટના_ઉત્સર્જક`: Node-style event dispatching with `.on()` and `.emit()`.

### 🧪 6. Built-in Unit Testing & Benchmark Framework
- **Native Test Runner CLI**:
  - `gujarati test [directory]`: Automated test discovery and reporting for `*_test.gj` files.
  - `gujarati bench <file.gj>`: Run execution benchmarks with iteration counters and timing statistics.
- **Assertion Primitives**:
  - `assert_eq(a, b)` / `ચકાસણી_સરખું`: Strict value equality verification.
  - `assert_true(cond)` / `ચકાસણી_સાચું`: Boolean truth assertions.
  - `assert_throws(fn)` / `ચકાસણી_ભૂલ`: Verify exceptions and error throws.
  - `bench_run(fn, iters)` / `પ્રદર્શન_ચકાસો`: Measure throughput and ops/second.

---

## 💻 Native Scripts Supported
All new features are 100% available in both **Romanized Gujarati** (`pkg_info`, `wasm_compile`, `pg_connect`, `image_create`, `async_await`, `assert_eq`) and **Native Gujarati Script** (`પેકેજ_માહિતી`, `વોસમ_કમ્પાઇલ`, `પીજી_જોડો`, `ચિત્ર_બનાવો`, `પ્રતીક્ષા`, `ચકાસણી_સરખું`).

---

## 📦 Multi-Platform Downloads & Verification
All official pre-built binary distributions include the `gujarati` runtime executable, example programs, documentation, and automated installers:

| Platform | Archive | Architecture |
| :--- | :--- | :--- |
| **Windows** | `gujaratilang-windows-x64.zip` | x86_64 (Intel / AMD) |
| **Linux** | `gujaratilang-linux-x64.tar.gz` | x86_64 (glibc 2.31+) |
| **macOS Apple Silicon** | `gujaratilang-macos-arm64.tar.gz` | ARM64 (M1 / M2 / M3 / M4) |
| **macOS Intel** | `gujaratilang-macos-x64.tar.gz` | x86_64 (Intel Core) |
| **Checksums** | `checksums.txt` | SHA-256 Hashes |
