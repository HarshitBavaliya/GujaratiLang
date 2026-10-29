# GujaratiLang v1.7.0 — Standalone Executable Bundler (`gujarati bundle`), IPC & Enterprise Web Architecture 🚀

GujaratiLang **v1.7.0** delivers the most requested enterprise capabilities: self-contained binary packaging without requiring runtime installations, local inter-process communication (IPC) through named pipes, a Trie-based HTTP routing & middleware engine, high-resolution hardware profiling, advanced string encoding (Hex & Punycode for Gujarati IDNs), and hot-reloading file system watchers.

This release introduces **30 major features across 6 core pillars**, expanding GujaratiLang's production surface for standalone deployments, microservices, and system monitoring.

All **406 test cases** pass with a 100% success rate across Windows, Linux, macOS Apple Silicon, and macOS Intel with **zero third-party dependencies**.

---

## 🌟 What's New in v1.7.0 (The 6 Core Pillars)

### 📦 1. Standalone Single-Binary Bundler (`gujarati bundle`)
- **CLI Subcommand**:
  - `gujarati bundle <source.gj> -o <app>`: Pack any `.gj` script into an independent, standalone executable binary.
  - Automatically bundles embedded bytecode and self-executing bootstrap headers.
- **Bundle Introspection**:
  - `bundle_info(path)` / `બંડલ_માહિતી(પાથ)`: Inspect standalone binary metadata, entry file, size, and compiler version.

### 🔌 2. Inter-Process Communication (IPC & Named Pipes)
- **Local Stream Pipes**:
  - `ipc_pipe_create(name)` / `આઈપીસી_પાઇપ_બનાવો(નામ)`: Allocate local stream pipe channels.
  - `ipc_pipe_connect(name)` / `આઈપીસી_પાઇપ_જોડો(નામ)`: Connect to an active local IPC pipe stream.
  - `ipc_pipe_write(pipe, data)` / `આઈપીસી_પાઇપ_લખો(પાઇપ, ડેટા)`: Stream byte payloads across process boundaries.
  - `ipc_pipe_read(pipe, [max_bytes])` / `આઈપીસી_પાઇપ_વાંચો(પાઇપ, [બાઇટ્સ])`: Receive buffered IPC data from connected peers.
  - `ipc_pipe_close(pipe)` / `આઈપીસી_પાઇપ_બંધ(પાઇપ)`: Gracefully close IPC handles and free buffers.

### 🛣️ 3. Enterprise Web Routing & HTTP Middleware Engine
- **Prefix Trie Router**:
  - `router_create()` / `રાઉટર_બનાવો()`: Initialize high-performance HTTP URL routing instances.
  - `router_get(router, path, handler)` / `રાઉટર_મેળવો`: Register GET routes with parameterized dynamic segments (`/users/:id`).
  - `router_post(router, path, handler)` / `રાઉટર_મોકલો`: Register POST routes with parameterized matching.
  - `router_use(router, middleware)` / `રાઉટર_વાપરો`: Attach interceptor middleware (CORS, auth, request logging).
  - `router_match(router, method, path)` / `રાઉટર_મેળ`: Resolve route handlers and extract URL parameters dictionary `{ "id": "42" }`.

### ⏱️ 4. High-Resolution Hardware Profiling & Diagnostics
- **Performance & System Telemetry**:
  - `profile_cpu_start()` / `પ્રોફાઇલ_શરૂ()`: Nanosecond hardware performance timer.
  - `profile_cpu_stop()` / `પ્રોફાઇલ_બંધ()`: Conclude CPU profiling session, returning elapsed milliseconds and cycles.
  - `sys_cpu_cores()` / `સીપીયુ_કોર()`: Detect online logical and physical CPU cores for worker threads.
  - `sys_memory_usage()` / `સિસ્ટમ_મેમરી()`: Inspect process RSS, peak memory, and total system RAM.
  - `sys_disk_space(path)` / `ડિસ્ક_જગ્યા(પાથ)`: Query disk volume capacity and free storage bytes.

### 🔠 5. Advanced String Encoding, Hex & Punycode (Gujarati IDN)
- **Encoding & Unicode Support**:
  - `hex_encode(str)` / `હેક્સ_એન્કોડ(લખાણ)`: Convert raw string or binary buffer into lowercase hexadecimal strings.
  - `hex_decode(hex)` / `હેક્સ_ડીકોડ(હેક્સ)`: Decode hex strings back into original characters.
  - `punycode_encode(domain)` / `પ્યુનીકોડ_એન્કોડ(ડોમેન)`: Encode Gujarati domain names to RFC Punycode (`ગુજરાતી.ભારત` ➔ `xn--...`).
  - `punycode_decode(puny)` / `પ્યુનીકોડ_ડીકોડ(લખાણ)`: Decode Punycode domains back to native UTF-8.
  - `utf8_normalize(str, [form])` / `યુટીએફ૮_સામાન્ય(લખાણ, [ફોર્મ])`: Unicode canonical normalization for conjuncts.

### 📂 6. File System Watching & Live Hot-Reload
- **Live Watcher & File Ops**:
  - `fs_watch(path, callback)` / `ફાઇલ_નિરીક્ષણ(પાથ, કાર્ય)`: Register event listeners on directories/files for modifications.
  - `fs_unwatch(watch_id)` / `ફાઇલ_નિરીક્ષણ_બંધ(આઈડી)`: Deregister file system watchers.
  - `fs_touch(path)` / `ફાઇલ_ટચ(પાથ)`: Create empty files or update file timestamps.
  - `fs_temp_file([prefix])` / `કામચલાઉ_ફાઇલ([પૂર્વાક્ષર])`: Generate collision-free temporary file paths.
  - `gujarati watch <file.gj>`: CLI live-reload runner that automatically executes on file save.

---

## 💻 Native Scripts Supported
All 30 new features are available with 100% parity across both **Romanized Gujarati** (`bundle_info`, `ipc_pipe_create`, `router_create`, `profile_cpu_start`, `hex_encode`, `fs_watch`) and **Native Gujarati Script** (`બંડલ_માહિતી`, `આઈપીસી_પાઇપ_બનાવો`, `રાઉટર_બનાવો`, `પ્રોફાઇલ_શરૂ`, `હેક્સ_એન્કોડ`, `ફાઇલ_નિરીક્ષણ`).

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
