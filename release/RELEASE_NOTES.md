# GujaratiLang v1.6.0 — Networking, Multi-Threading & Language Server Protocol (LSP) 🚀

GujaratiLang **v1.6.0** is a major milestone that elevates GujaratiLang into a high-performance, networked, multi-threaded runtime with dedicated modern IDE tooling.

This release introduces **30 major features across 6 core pillars**, including Native Outbound HTTP Client, Built-in Micro Web Server, Native Byte Buffers & JSON Engine, Native Cryptography & Digest (MD5, SHA-256, HMAC, UUID v4), Language Server Protocol (LSP) Engine (`gujarati lsp`), OS-Level Multi-Threading & Mutex synchronization, and Production Process & Signal Control.

All **399 test cases** pass with a 100% success rate across Windows, Linux, macOS Apple Silicon, and macOS Intel with **zero third-party dependencies**.

---

## 🌟 What's New in v1.6.0 (The 6 Core Pillars)

### 🌐 1. HTTP Server & Outbound Web Client (Native Networking)
- **Native Outbound HTTP Client**:
  - `http_get(url, [headers])` / `નેટ_મેળવો(url, [શીર્ષક])`: Issue HTTP GET requests to external REST APIs and web services.
  - `http_post(url, body, [headers])` / `નેટ_મોકલો(url, વિગત, [શીર્ષક])`: Issue HTTP POST payloads with customizable headers.
- **Built-in Micro HTTP Web Server**:
  - `server_create(port, handler)` / `સર્વર_બનાવો(પોર્ટ, નિયંત્રક)`: Spin up an HTTP microservice directly from a single `.gj` script.
  - `server_listen(server, [max_requests])` / `સર્વર_સાંભળો(સર્વર, [મહત્તમ])`: Accept incoming connections, route requests, and serve HTTP responses.
  - `server_close(server)` / `સર્વર_બંધ(સર્વર)`: Gracefully terminate server sockets and clean up open ports.

### 💾 2. Native JSON & Byte Stream Engine
- **Direct Serialized Data Handling**:
  - `json_parse(str)` / `જેસન_વાંચો(str)`: Parse JSON payloads directly into native Gujarati dictionaries and lists.
  - `json_stringify(kosh)` / `જેસન_લખો(કોશ)`: Format native dictionary objects into valid JSON strings.
- **Raw Binary Buffer Primitives**:
  - `buffer_create(size)` / `બફર_બનાવો(કદ)`: Allocate raw binary memory buffers without string encoding overhead.
  - `buffer_read_u8(buffer, offset)` / `બફર_વાંચો(બફર, સ્થાન)`: Read unsigned 8-bit integers from byte streams.
  - `buffer_write_bytes(buffer, offset, data)` / `બફર_લખો(બફર, સ્થાન, માહિતી)`: Write raw byte payloads directly into allocated buffers.

### 🔐 3. Native Cryptography & Security Primitives
- **Hashing & Digest Engines**:
  - `hash_md5(data)` / `હેશ_એમડી૫(માહિતી)`: RFC 1321 MD5 hash digest algorithm generating standard 32-hex output.
  - `hash_sha256(data)` / `હેશ_૨૫૬(માહિતી)`: Cryptographic SHA-256 digest engine.
  - `hmac_sha256(key, data)` / `એચમેક(ચાવી, માહિતી)`: Keyed-hash message authentication code (HMAC-SHA256).
- **Encoding & UUID**:
  - `base64_encode(str)` / `બેઝ૬૪_એન્કોડ(લખાણ)`: RFC-compliant base64 binary-to-text encoder.
  - `base64_decode(str)` / `બેઝ૬૪_ડીકોડ(લખાણ)`: Base64 decoder extracting original data.
  - `crypto_uuid()` / `યાદચ્છિક_આઈડી()`: Generate secure UUID v4 tokens for sessions and database primary keys.

### 🧠 4. Language Server Protocol (LSP) Engine
- **Dedicated CLI Subcommand**:
  - `gujarati lsp`: Launch the Language Server over standard I/O (stdin/stdout) using the JSON-RPC 2.0 protocol.
  - `gujarati lsp --capabilities`: Report server capabilities for IDE editors.
  - `gujarati lsp --check <file>`: Validate source syntax and output diagnostics.
- **IDE Intelligence Features**:
  - Hover documentation with function signatures in both Gujarati and English.
  - Real-time diagnostics and syntax verification.
  - Autocomplete support for standard library built-ins.

### 🧵 5. Multi-Threading & Worker Threads (True Parallelism)
- **OS-Level Worker Threads**:
  - `thread_spawn(fn, [arg])` / `તાંતણો_શરૂ(કાર્ય, [દલીલ])`: Spawn native operating-system threads (Windows Threads / POSIX pthreads) for compute-heavy parallel workloads.
  - `thread_join(thread)` / `તાંતણો_જોડો(તાંતણો)`: Await worker thread termination and collect return codes.
  - `thread_pool([size])` / `તાંતણા_પૂલ([કદ])`: Managed thread pool executor for high-concurrency tasks.
- **Mutex Synchronization**:
  - `mutex_create()` / `મ્યુટેક્સ_બનાવો()`: Initialize mutual exclusion locks to prevent race conditions.
  - `mutex_lock(mutex)` / `મ્યુટેક્સ_તાળું(મ્યુટેક્સ)`: Acquire exclusive access to shared resources.
  - `mutex_unlock(mutex)` / `મ્યુટેક્સ_ખોલો(મ્યુટેક્સ)`: Release mutex lock safely.

### 🖥️ 6. Process Control, Environment & Signals
- **Production Container & Cloud Tooling**:
  - `env_get(key)` / `પર્યાવરણ_મેળવો(ચાવી)`: Fetch environment variables for Docker/Kubernetes container deployments.
  - `env_set(key, value)` / `પર્યાવરણ_ગોઠવો(ચાવી, મૂલ્ય)`: Modify and set runtime process environment variables.
  - `process_args()` / `આદેશ_દલીલો()`: Access command-line arguments passed into executing scripts.
  - `process_run(cmd)` / `પ્રક્રિયા_ચલાવો(આદેશ)`: Execute shell commands and subprocesses, capturing `stdout` and `exit_code`.
  - `signal_trap(signum, handler)` / `સિગ્નલ_પકડો(સિગ્નલ, નિયંત્રક)`: Intercept OS termination signals (SIGINT, SIGTERM) for graceful resource shutdown.

---

## 💻 Native Scripts Supported
All 30 new features are 100% available in both **Romanized Gujarati** (`http_get`, `server_create`, `buffer_create`, `hash_md5`, `thread_spawn`, `mutex_lock`, `env_get`) and **Native Gujarati Script** (`નેટ_મેળવો`, `સર્વર_બનાવો`, `બફર_બનાવો`, `હેશ_એમડી૫`, `તાંતણો_શરૂ`, `મ્યુટેક્સ_તાળું`, `પર્યાવરણ_મેળવો`).

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
