# GujaratiLang v1.9.0 — Fortress: Zero-Trust Security Hardening, RCE Immunity & Sandboxing 🛡️

GujaratiLang **v1.9.0 ("Fortress")** brings enterprise-grade security hardening, RCE immunity against command injection (PHP2Shell defense), proactive AST taint analysis, strict execution sandboxing, path traversal guards, safe payload deserialization, and canary memory boundary protection.

This release introduces **30 security features across 6 core pillars**, fortifying GujaratiLang applications against arbitrary code execution, supply chain tampering, memory corruptions, and injection vectors with **zero third-party dependencies**.

All **420 test cases** pass with a 100% success rate across Windows, Linux, macOS Apple Silicon, and macOS Intel.

---

## 🌟 What's New in v1.9.0 (The 6 Core Security Pillars)

### 🛡️ 1. RCE Defense & Shell Injection Shield (PHP2Shell Immunity)
- **Eliminate Arbitrary Code Execution**:
  - `sec_sanitize_shell(cmd)` / `સુરક્ષા_કમાન્ડ_શુદ્ધ(કમાન્ડ)`: Neutralizes dangerous shell metacharacters (`;`, `&`, `|`, `` ` ``, `$`, `>`, `<`, `\0`, `\r`, `\n`, `!`, parentheses, braces).
  - `sec_validate_binary(path)` / `સુરક્ષા_બાઇનરી_ચકાસો(પાથ)`: Validates executable binaries against malicious reverse shells (`nc`, `bash`, `powershell`, `socat`, `python`, `cmd.exe`) and command chaining.
  - `sec_exec_restricted(cmd, [timeout])` / `સુરક્ષા_પ્રક્રિયા_મર્યાદિત(કમાન્ડ, [સમય])`: Safe subprocess runner preventing raw shell spawns and blocking injection attempts with exit code audit.
  - `sec_shell_escape(arg)` / `સુરક્ષા_કમાન્ડ_એસ્કેપ(દલીલ)`: Robust argument quoting and delimiter escaping for safe subprocess calls.
  - CLI Flag `--safe-exec`: Global enforcement requiring all external system calls to pass rigorous binary validation and character neutralization.

### 📦 2. Sandbox Execution & Fine-Grained Permissions
- **Principle of Least Privilege**:
  - `sandbox_enter(perms)` / `સેન્ડબોક્સ_શરૂ(પરવાનગી)`: Locks the runtime into restricted sandbox mode with granular permission bits (`NONE`, `READ`, `WRITE`, `NET`, `PROC`, `ALL`).
  - `sandbox_check_perm(perm)` / `સેન્ડબોક્સ_ચકાસો(પરવાનગી)`: Verifies whether the calling context holds necessary operational permissions.
  - `sandbox_set_max_memory(bytes)` / `સેન્ડબોક્સ_મેમરી_મર્યાદા(બાઇટ્સ)`: Enforces hard memory boundaries to prevent denial-of-service / memory exhaustion attacks.
  - `sandbox_set_timeout(seconds)` / `સેન્ડબોક્સ_સમય_મર્યાદા(સેકન્ડ)`: Imposes CPU execution timeouts to terminate infinite loops and runaway tasks.
  - CLI Flag `--sandbox`: Executes standalone scripts in strict sandbox mode out-of-the-box.

### 📁 3. Path Traversal Guards & Safe File Operations
- **Filesystem Isolation**:
  - `path_canonical(path)` / `પાથ_પ્રમાણિત(પાથ)`: Canonicalizes relative paths, collapses redundant segments (`./`, `../`), and resolves drive/root anchors.
  - `path_is_safe(path, base_dir)` / `પાથ_સુરક્ષિત_છે(પાથ, આધાર)`: Validates that a path is strictly confined within `base_dir`, blocking `../` escaping attempts.
  - `path_safe_join(base_dir, rel_path)` / `પાથ_સુરક્ષિત_જોડો(આધાર, સંબંધિત)`: Joins directories with automatic boundary clamping if traversal is attempted.
  - `fs_secure_delete(path, [passes])` / `ફાઇલ_સુરક્ષિત_કાઢી_નાખો(પાથ, [પાસ])`: Securely shreds confidential files by multi-pass pattern overwriting before unlinking.
  - `fs_is_symlink_safe(path)` / `સિમ્બોલિક_લિંક_સુરક્ષિત(પાથ)`: Guards against symlink exploitation targeting sensitive operating system files.

### 🧪 4. AST Taint Analysis & Data Flow Tracking
- **Untrusted Input Quarantine**:
  - `taint_mark(val, [tag])` / `દૂષિત_ચિહ્ન(મૂલ્ય, [ટેગ])`: Tags untrusted data origins (HTTP request parameters, headers, external feeds).
  - `taint_check(val)` / `દૂષિત_ચકાસો(મૂલ્ય)`: Detects if values or composite strings contain un-sanitized tainted data.
  - `taint_cleanse(val)` / `દૂષિત_શુદ્ધ(મૂલ્ય)`: Clears taint status upon successful validation and sanitization.
  - `taint_report()` / `દૂષિત_અહેવાલ()`: Returns a comprehensive audit report of tainted and cleansed inputs.
  - CLI Flag `--taint-check`: Enables proactive data-flow taint tracking and audit warnings.

### 🔒 5. Secure Deserialization & Payload Defense
- **Defending the Serialization Boundary**:
  - `sec_json_safe(json, [max_depth])` / `સુરક્ષા_જેસન_સુરક્ષિત(જેસન, [ઊંડાઈ])`: Prototype pollution-immune JSON parser rejecting dangerous object keys (`__proto__`, `constructor`, `prototype`) and recursive depth bombs.
  - `sec_verify_hmac(data, key, expected)` / `સુરક્ષા_એચમેક_ચકાસો(ડેટા, કી, અપેક્ષિત)`: Computes HMAC-SHA256 and validates integrity via constant-time comparison.
  - `sec_mask_sensitive(str, [char], [keep])` / `સુરક્ષા_છુપાવો(ટેક્સ્ટ, [અક્ષર], [રાખો])`: Automatically masks confidential data (passwords, payment cards, tokens).
  - `sec_crc32(data)` / `સુરક્ષા_સીઆરસી૩૨(ડેટા)`: Computes standard IEEE 802.3 CRC32 checksums for network message integrity.
  - `sec_token_compare(a, b)` / `સુરક્ષા_ટોકન_સરખાવો(ટોકન૧, ટોકન૨)`: Constant-time string comparison preventing side-channel timing attacks.

### 🧠 6. Memory Boundary Protection & Guard Canaries
- **Buffer Safety & Volatile Memory Erasure**:
  - `mem_zero(buffer)` / `મેમરી_શૂન્ય(બફર)`: Cryptographically wipes sensitive memory buffers using volatile pointers to prevent compiler dead store elimination.
  - `mem_guard_alloc(size)` / `મેમરી_રક્ષિત(કદ)`: Allocates memory guarded by head and tail canary words (`0xDEADBEEF` & `0xCAFEBABE`).
  - `mem_canary_check(handle)` / `મેમરી_કેનેરી_ચકાસો(હેન્ડલ)`: Verifies canary integrity to detect buffer overflows and underflows instantly.
  - `mem_secure_free(handle)` / `મેમરી_સુરક્ષિત_મુક્ત(હેન્ડલ)`: Securely overwrites allocated blocks before returning memory to the heap.
  - `sec_audit_log(event, severity)` / `સુરક્ષા_ઓડિટ_નોંધ(ઘટના, ગંભીરતા)`: Records structured security events to internal audit rings.

---

## 📊 Summary of Functions Added in v1.9.0

| Function (Romanized / English) | Function (Native Gujarati) | Purpose |
| :--- | :--- | :--- |
| `sec_sanitize_shell(cmd)` | `સુરક્ષા_કમાન્ડ_શુદ્ધ(કમાન્ડ)` | Neutralize shell metacharacters and injection |
| `sec_validate_binary(path)` | `સુરક્ષા_બાઇનરી_ચકાસો(પાથ)` | Validate executable binary against RCE tools |
| `sec_exec_restricted(cmd, [timeout])`| `સુરક્ષા_પ્રક્રિયા_મર્યાદિત(કમાન્ડ, [સમય])` | Restricted subprocess execution with audit |
| `sec_shell_escape(arg)` | `સુરક્ષા_કમાન્ડ_એસ્કેપ(દલીલ)` | Safe command-line argument escaping |
| `sandbox_enter(perms)` | `સેન્ડબોક્સ_શરૂ(પરવાનગી)` | Lock runtime into sandboxed security profile |
| `sandbox_check_perm(perm)` | `સેન્ડબોક્સ_ચકાસો(પરવાનગી)` | Query active permission entitlements |
| `sandbox_set_max_memory(bytes)` | `સેન્ડબોક્સ_મેમરી_મર્યાદા(બાઇટ્સ)` | Enforce maximum RAM allocation limits |
| `sandbox_set_timeout(seconds)` | `સેન્ડબોક્સ_સમય_મર્યાદા(સેકન્ડ)` | Enforce execution timeout limits |
| `path_canonical(path)` | `પાથ_પ્રમાણિત(પાથ)` | Resolve and canonicalize filesystem paths |
| `path_is_safe(path, base)` | `પાથ_સુરક્ષિત_છે(પાથ, આધાર)` | Verify path stays confined within base directory |
| `path_safe_join(base, rel)` | `પાથ_સુરક્ષિત_જોડો(આધાર, સંબંધિત)` | Safe path concatenation with boundary clamping |
| `fs_secure_delete(path, [passes])` | `ફાઇલ_સુરક્ષિત_કાઢી_નાખો(પાથ, [પાસ])` | Multi-pass secure file shredder |
| `fs_is_symlink_safe(path)` | `સિમ્બોલિક_લિંક_સુરક્ષિત(પાથ)` | Validate symbolic links against system hijacking |
| `taint_mark(val, [tag])` | `દૂષિત_ચિહ્ન(મૂલ્ય, [ટેગ])` | Tag untrusted data in taint tracking table |
| `taint_check(val)` | `દૂષિત_ચકાસો(મૂલ્ય)` | Check if data contains untrusted tainted bytes |
| `taint_cleanse(val)` | `દૂષિત_શુદ્ધ(મૂલ્ય)` | Clear taint tag upon verification |
| `taint_report()` | `દૂષિત_અહેવાલ()` | Generate runtime taint statistics |
| `sec_json_safe(json, [max_depth])` | `સુરક્ષા_જેસન_સુરક્ષિત(જેસન, [ઊંડાઈ])` | Prototype pollution-safe JSON deserializer |
| `sec_verify_hmac(data, key, exp)` | `સુરક્ષા_એચમેક_ચકાસો(ડેટા, કી, અપેક્ષિત)` | Constant-time HMAC-SHA256 signature verification |
| `sec_mask_sensitive(str, [char], [k])`| `સુરક્ષા_છુપાવો(ટેક્સ્ટ, [અક્ષર], [રાખો])` | Mask sensitive data with configurable retain length |
| `sec_crc32(data)` | `સુરક્ષા_સીઆરસી૩૨(ડેટા)` | Standard IEEE 802.3 CRC32 checksum |
| `sec_token_compare(a, b)` | `સુરક્ષા_ટોકન_સરખાવો(ટોકન૧, ટોકન૨)` | Constant-time string equality check |
| `mem_zero(buffer)` | `મેમરી_શૂન્ય(બફર)` | Volatile memory erasure preventing RAM lingering |
| `mem_guard_alloc(size)` | `મેમરી_રક્ષિત(કદ)` | Allocate buffer protected with canary words |
| `mem_canary_check(handle)` | `મેમરી_કેનેરી_ચકાસો(હેન્ડલ)` | Verify integrity of guard canaries |
| `mem_secure_free(handle)` | `મેમરી_સુરક્ષિત_મુક્ત(હેન્ડલ)` | Zero-wipe and free guarded allocation |
| `sec_audit_log(event, severity)` | `સુરક્ષા_ઓડિટ_નોંધ(ઘટના, ગંભીરતા)` | Log security events to internal audit stream |

---

## 🛠️ Upgrading & Compatibility
- **100% Backwards Compatible**: Existing programs run without changes.
- **Cross-Platform Availability**: Windows x64, macOS Apple Silicon (ARM64), macOS Intel (x64), and Linux (x86_64).
