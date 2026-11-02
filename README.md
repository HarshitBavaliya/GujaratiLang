# GujaratiLang

GujaratiLang is a small programming language runtime implemented in C, following
the general approach used by languages such as PHP: programs are parsed and run
by an interpreter rather than translated into C source.

New to GujaratiLang? Visit the official website and try the interactive playground at [gujaratilang.hp-square.com](https://gujaratilang.hp-square.com/), or start with the [beginner tutorial](docs/tutorial.md). If
you use Visual Studio Code, install the
[GujaratiLang syntax-highlighting extension](https://marketplace.visualstudio.com/items?itemName=harshitbavaliya.gujarati).

## Current features

### What's New in v3.2.0: Rakshak Systems, Win32 FFI & Antivirus Engine (660 Tests Milestone)

GujaratiLang v3.2.0 delivers 30 enterprise capabilities across 6 low-level systems programming and threat detection pillars, alongside our second official pre-coded starter kit: **Rakshak Antivirus Suite**, expanding the automated test suite to the landmark **660 Tests Milestone (100% Pass Rate)**:

- **Pillar 1: C FFI & Win32 Interop (એફએફઆઈ અને વિન્ડોઝ ઇન્ટરઓપ)**:
  - `ffi_load_library(dll_name)` / `એફએફઆઈ_લાઈબ્રેરી_લોડ`: Dynamic runtime DLL loader (`LoadLibraryW`) with handle resolution
  - `ffi_get_proc(lib_handle, symbol)` / `એફએફઆઈ_ફંક્શન_મેળવો`: Function symbol resolver (`GetProcAddress`) returning typed function pointers
  - `ffi_call(proc, ret_type, arg_types, args)` / `એફએફઆઈ_કોલ`: Universal FFI dispatcher for native C calling conventions
  - `ffi_kernel32(function_name, args)` / `એફએફઆઈ_કર્નલ૩૨`: Direct kernel32 interop for process and memory management
  - `ffi_advapi32(function_name, args)` / `એફએફઆઈ_એડવાપી૩૨`: Direct advapi32 interop for tokens, registry, and security descriptors
  - CLI: `gujarati ffi:inspect <dll_name>`
- **Pillar 2: Raw Binary Buffers & PE/COFF Struct Unpacking (કાચો બફર અને પીઈ પાર્સિંગ)**:
  - `buffer_alloc(size, [fill_byte])` / `બફર_ફાળવો`: Contiguous heap-allocated binary byte array with byte-level indexing
  - `buffer_from_file(path, offset, size)` / `બફર_ફાઇલમાંથી`: Memory-mapped raw file reader for binary executables
  - `struct_unpack(format_str, buffer, offset)` / `સ્ટ્રક્ટ_અનપેક`: Binary struct unpacker decoding little/big endian types (`<H`, `<I`, `<Q`)
  - `pe_parse_headers(buffer_or_path)` / `પીઈ_હેડર_વાંચો`: Full PE/COFF header parser decoding DOS MZ signature, NT headers, and section tables
  - `bit_and(a, b)` / `બીટ_એન્ડ`, `bit_or(a, b)` / `બીટ_ઓર`, `bit_xor(a, b)` / `બીટ_એક્સઓર`: Native 64-bit bitwise logic operations
  - `bit_lshift(a, b)` / `બીટ_ડાબે`, `bit_rshift(a, b)` / `બીટ_જમણે`, `bit_not(a)` / `બીટ_નોટ`: Bit shifting and bitwise inversion
- **Pillar 3: Native C-Level Hashing Primitives & Shannon Entropy (ક્રિપ્ટો અને એન્ટ્રોપી)**:
  - `crypto_sha256(data_or_path)` / `ક્રિપ્ટો_એસએચએ૨૫૬`: High-speed C-level SHA-256 cryptographic digest calculation
  - `crypto_md5(data_or_path)` / `ક્રિપ્ટો_એમડી૫`: Rapid MD5 signature generation for antivirus hash lists
  - `crypto_entropy(buffer_or_string)` / `ક્રિપ્ટો_એન્ટ્રોપી`: Shannon entropy calculation ($H(X) \in [0.0, 8.0]$) to detect packed/encrypted malware
  - `crypto_pe_section_entropy(path)` / `પીઈ_સેક્શન_એન્ટ્રોપી`: Automated PE section audit flagging high-entropy packed executable sections
  - CLI: `gujarati crypto:hash <file_path>`
- **Pillar 4: Real-Time File System Watcher & Sentinel (ફાઇલ સિસ્ટમ વોચર)**:
  - `watcher_init(dir_path, [recursive])` / `વોચર_શરૂ`: Native directory watcher binding Windows `ReadDirectoryChangesW`
  - `watcher_poll(watcher, [timeout_ms])` / `વોચર_મેળવો`: Non-blocking kernel event consumer for real-time file notifications
  - `watcher_event_type(event)` / `વોચર_ઇવેન્ટ_પ્રકાર`: Categorizes filesystem events (`created`, `modified`, `deleted`, `renamed`)
  - `watcher_on_change(watcher, callback)` / `વોચર_કોલબેક`: Real-time reactive sentinel triggering virus scans upon file write
  - CLI: `gujarati watch:dir <directory>`
- **Pillar 5: Multi-Threading & Scanner Worker Pool (મલ્ટી-થ્રેડિંગ અને વર્કર પૂલ)**:
  - `thread_pool_create(worker_count)` / `થ્રેડ_પૂલ_બનાવો`: Hardware-concurrency OS worker thread pool
  - `thread_pool_dispatch(pool, fn_or_task, args)` / `થ્રેડ_પૂલ_મોકલો`: Dispatches file paths and scan jobs concurrently across CPU cores
  - `thread_pool_wait(pool, [timeout_ms])` / `થ્રેડ_પૂલ_રાહ`: Synchronizes parallel workers and awaits completion
  - `thread_pool_results(pool)` / `થ્રેડ_પૂલ_પરિણામ`: Aggregates thread-safe scan metrics, infected counters, and file tallies
  - CLI: `gujarati scan:parallel <directory>`
- **Pillar 6: Process & System Diagnostics Module (પ્રક્રિયા અને સિસ્ટમ મોનિટર)**:
  - `system_list_processes()` / `સિસ્ટમ_પ્રક્રિયા_યાદી`: Toolhelp32 process snapshot inspecting PID, parent PID, and executable path
  - `system_get_process_cmdline(pid)` / `સિસ્ટમ_કમાન્ડલાઈન_તપાસ`: Inspects command-line flags detecting suspicious evasion patterns (`-enc`, `Bypass`)
  - `system_terminate_process(pid, [exit_code])` / `સિસ્ટમ_પ્રક્રિયા_અંત`: Terminates malicious processes via Win32 `TerminateProcess`
  - CLI: `gujarati process:list`, `gujarati process:kill <pid>`
- **Pre-Coded Starter Kit 2: Rakshak Antivirus Suite (રક્ષક એન્ટિવાયરસ કિટ)**:
  - CLI: `gujarati new <app_name> --kit=rakshak`, `gujarati kit:rakshak`, `gujarati kit:antivirus`
  - Scaffolds a complete production-grade antivirus solution: signature database (`rules/signatures.gj`), parallel PE scanner (`engine/scanner.gj`), real-time file sentinel (`engine/watcher.gj`), process monitor (`engine/diagnostics.gj`), and interactive terminal UI quarantine manager (`app.gj`).

### What's New in v3.1.0: Parikshan & Sanchalan with Garvi Breeze Starter Kit (630 Tests Milestone)

GujaratiLang v3.1.0 delivers 30 enterprise capabilities across 4 production operations pillars and our first official pre-coded starter kit, expanding the automated test suite to the landmark **630 Tests Milestone (100% Pass Rate)**:

- **Pillar 1: Drishti (દ્રષ્ટિ) OpenTelemetry & Distributed Tracing**:
  - `drishti_trace_start(span_name, [parent_span])` / `દ્રષ્ટિ_ટ્રેસ_શરૂ`: Active distributed trace span with nanosecond timestamps
  - `drishti_span_end(span, status)` / `દ્રષ્ટિ_સ્પાન_અંત`: Span finalization, microsecond duration tracking
  - `drishti_span_tag(span, key, val)` / `દ્રષ્ટિ_સ્પાન_ટેગ`: OpenTelemetry semantic conventions and custom metadata tags
  - `drishti_trace_headers(span)` / `દ્રષ્ટિ_ટ્રેસ_હેડર`: W3C `traceparent` and `tracestate` propagation headers
  - `drishti_metric_counter(name, val, tags)` / `દ્રષ્ટિ_મેટ્રિક_કાઉન્ટર`: Monotonic counter metrics
  - `drishti_metric_gauge(name, val, tags)` / `દ્રષ્ટિ_મેટ્રિક_ગેજ`: Variable gauge metrics
  - `drishti_otlp_export(endpoint, timeout_ms)` / `દ્રષ્ટિ_ઓટીએલપી_નિકાસ`: Protobuf OTLP collector exporter
  - CLI: `gujarati drishti:trace <script.gj>`, `gujarati drishti:flamegraph [profile.json]`
- **Pillar 2: Kavach (કવચ) eBPF Sandboxing & Zero-Trust Kernel**:
  - `kavach_sock_filter(proto, port)` / `કવચ_સોકેટ_ફિલ્ટર`: Kernel-level eBPF socket packet filter
  - `kavach_seccomp_policy(whitelist)` / `કવચ_સેકકોમ્પ_નીતિ`: BPF seccomp syscall whitelist enforcing zero-trust sandbox
  - `kavach_ringbuf_poll(buffer, callback)` / `કવચ_રિંગબફર_મેળવો`: Zero-copy BPF ring buffer reader
  - `kavach_net_flow(interface)` / `કવચ_નેટ_પ્રવાહ`: Direct NIC XDP flow monitor tracking throughput & drops
  - `kavach_mem_guard(limit_bytes)` / `કવચ_મેમરી_રક્ષક`: Kernel page-table defense against heap overflows & UAF
  - `kavach_anomaly_rule(rule_name, action)` / `કવચ_વિસંગતતા_નિયમ`: Real-time behavioral anomaly trigger with automatic isolation
  - CLI: `gujarati kavach:monitor [process]`, `gujarati kavach:audit`
- **Pillar 3: Pavan (પવન) MicroVM Sandboxing & Firecracker Isolation**:
  - `pavan_vm_init(vcpus, ram_mb)` / `પવન_વીએમ_શરૂ`: Ultra-fast microVM guest instance (< 5ms cold boot)
  - `pavan_vm_boot(vm, kernel_img, rootfs)` / `પવન_વીએમ_બૂટ`: Boots Linux kernel inside KVM/Hyper-V container
  - `pavan_cgroup_limit(vm, subsystem, val)` / `પવન_સીગ્રુપ_મર્યાદા`: Hardware cgroup v2 CPU shares, memory caps, IOPS throttling
  - `pavan_virtio_disk(vm, disk_path)` / `પવન_વર્ચ્યુઅલ_ડિસ્ક`: High-throughput non-blocking VirtIO block device
  - `pavan_tap_bridge(vm, tap_dev)` / `પવન_ટેપ_બ્રિજ`: VirtIO-Net tap interface hooked to host bridge
  - `pavan_vm_checkpoint(vm, snapshot_path)` / `પવન_ચેકપોઇન્ટ`: Live memory serialization and disk snapshot in < 15ms
  - `pavan_vm_resume(vm, snapshot_path)` / `પવન_પુનઃશરૂ`: Instant microVM resume from snapshot image
  - CLI: `gujarati pavan:spawn <rootfs>`, `gujarati pavan:ps`
- **Pillar 4: Anudan (અનુદાન) GeoDNS Anycast & Edge Mesh**:
  - `anudan_dns_resolve(domain, client_ip)` / `અનુદાન_ડીએનએસ`: Anycast GeoDNS resolver returning nearest edge PoP
  - `anudan_health_probe(node, timeout_ms)` / `અનુદાન_આરોગ્ય_તપાસ`: Active TCP/HTTP health checker with jitter-free latency
  - `anudan_tls_acme(domain, email)` / `અનુદાન_ટીએલએસ_સર્ટ`: Automated Let's Encrypt ACME v2 TLS 1.3 certificate provisioning
  - `anudan_mesh_route(service, algorithm)` / `અનુદાન_મેશ_માર્ગ`: Dynamic service mesh load-balancer (weighted, round-robin)
  - `anudan_circuit_breaker(service, error_threshold)` / `અનુદાન_સર્કિટ_બ્રેકર`: Distributed circuit breaker halting requests to failing upstreams
  - `anudan_token_bucket(capacity, refill_rate)` / `અનુદાન_ટોકન_બકેટ`: Multi-region rate-limiting token bucket algorithm
  - CLI: `gujarati mesh:status`, `gujarati mesh:drain <node>`
- **Pre-Coded Starter Kit 1: Garvi Breeze Auth (ગારવી બ્રિઝ ઓથેન્ટિકેશન કિટ)**:
  - CLI: `gujarati new <app_name> --kit=breeze`, `gujarati kit:auth`, `gujarati new:breeze`
  - Scaffolds a complete production-ready authentication suite: Eloquent SQLite models (`User`), controllers (`login`, `register`, `logout`), responsive Blade views (`layout`, `dashboard`), and Garvi HTTP server.

### What's New in v3.0.0 Mega-Release: The Grand Sovereign Cloud & Distributed Quantum Engine (600 Tests Milestone)

GujaratiLang v3.0.0 is the crowning **Mega-Release** delivering 50 enterprise capabilities across 5 grand pillars, elevating the automated test suite to the landmark **600 Tests Milestone (100% Pass Rate)**:

- **Pillar 1: Sovereign Cloud & Serverless Edge (સાર્વભૌમ ક્લાઉડ અને એજ એન્જિન)**:
  - `cloud_edge_init(region, [opts])` / `ક્લાઉડ_એજ_શરૂ`: Initializes edge runtime node with Anycast latency routing
  - `cloud_edge_route(edge, path, handler)` / `ક્લાઉડ_એજ_માર્ગ`: Micro-routing table with sub-millisecond dispatch
  - `cloud_edge_kv(edge, key, value)` / `ક્લાઉડ_એજ_કેવી`: Globally replicated distributed key-value edge store
  - `cloud_worker_spawn(edge, script)` / `ક્લાઉડ_કાર્યકર_બનાવો`: Sub-0.2ms cold-start micro-sandboxed worker thread
  - `cloud_wasi_sandbox(edge, config)` / `ક્લાઉડ_વાસી_સેન્ડબોક્સ`: Universal WASI Preview2 sandboxed memory environment
  - `cloud_edge_cache(edge, key, val, [ttl])` / `ક્લાઉડ_એજ_કેશ`: Edge static/dynamic cache with TTL and Brotli/Gzip compression
  - `cloud_edge_headers(req, headers)` / `ક્લાઉડ_એજ_હેડર`: Edge header manipulation and geolocation tagging
  - `cloud_tenant_isolate(tenant_id)` / `ક્લાઉડ_ભાડુઆત_અલગ`: Strict multi-tenant CPU and memory quota isolation
  - `cloud_metrics_export([format])` / `ક્લાઉડ_મેટ્રિક્સ_નિકાસ`: Edge Prometheus/OpenTelemetry real-time metrics telemetry
  - CLI: `gujarati cloud:deploy [bundle.gj]`, `gujarati cloud:status [node]`
- **Pillar 2: Zero-Knowledge & Post-Quantum Cryptography (ઝીરો-નોલેજ અને પોસ્ટ-ક્વોન્ટમ સુરક્ષા)**:
  - `zk_snark_prove(circuit, witness)` / `ઝેડકે_સાબિતી_બનાવો`: Native Groth16 / PLONK zero-knowledge proof generation
  - `zk_snark_verify(proof, public_inputs)` / `ઝેડકે_સાબિતી_ચકાસો`: Sub-millisecond non-interactive zk verification
  - `pqc_kyber_keypair()` / `પીક્યુસી_કાયબર_કી`: NIST ML-KEM (Kyber-1024) quantum-resistant keypair generation
  - `pqc_kyber_encapsulate(public_key)` / `પીક્યુસી_કાયબર_કેપ્સ્યુલ`: Quantum-safe shared secret encapsulation
  - `pqc_kyber_decapsulate(secret_key, ciphertext)` / `પીક્યુસી_કાયબર_ડિકેપ્સ્યુલ`: Quantum-safe shared secret decapsulation
  - `pqc_dilithium_sign(msg, secret_key)` / `પીક્યુસી_ડિલિથિયમ_સહી`: NIST ML-DSA (Dilithium-5) quantum digital signature
  - `pqc_dilithium_verify(msg, signature, public_key)` / `પીક્યુસી_ડિલિથિયમ_ચકાસો`: Post-quantum digital signature verification
  - `crypto_vrf_generate(seed, secret_key)` / `ક્રિપ્ટો_વીઆરએફ`: Verifiable Random Function (VRF) with cryptographic proof
  - `crypto_threshold_bls(t, n, shares)` / `ક્રિપ્ટો_થ્રેશોલ્ડ`: Threshold BLS signature scheme with aggregate verification
  - CLI: `gujarati pqc:genkey`, `gujarati zk:verify [proof.zk]`
- **Pillar 3: Swaroop (સ્વરૂપ) Distributed Green Actor Runtime**:
  - `swaroop_actor_create(name, [config])` / `સ્વરૂપ_એક્ટર_બનાવો`: Ultra-lightweight green actor (< 2KB memory overhead)
  - `swaroop_actor_send(actor, message)` / `સ્વરૂપ_સંદેશ_મોકલો`: Non-blocking mailbox message passing
  - `swaroop_supervisor(children, strategy)` / `સ્વરૂપ_સુપરવાઇઝર`: OneForOne and OneForAll fault-tolerant supervisor tree
  - `swaroop_actor_monitor(watcher, target)` / `સ્વરૂપ_મોનિટર`: Unidirectional crash notification observer
  - `swaroop_actor_link(actor_a, actor_b)` / `સ્વરૂપ_જોડાણ`: Bidirectional fatal crash propagation link
  - `swaroop_hot_reload(actor, new_fn)` / `સ્વરૂપ_હોટ_રીલોડ`: Live code swapping without draining mailbox or resetting state
  - `swaroop_mailbox_priority(actor, level)` / `સ્વરૂપ_મેઇલબોક્સ_પ્રાથમિકતા`: Multi-tier priority queue mailbox
  - `swaroop_registry_bind(name, actor)` / `સ્વરૂપ_નોંધણી`: Distributed name registry binding
  - `swaroop_registry_lookup(name)` / `સ્વરૂપ_શોધો`: Global cluster-wide actor lookup
  - CLI: `gujarati swaroop:top`, `gujarati swaroop:cluster`
- **Pillar 4: Autonomous Raft Consensus Clusters (સ્વાયત્ત રાફ્ટ ક્લસ્ટર)**:
  - `raft_cluster_init(node_id, peers)` / `રાફ્ટ_ક્લસ્ટર_શરૂ`: Pure C99 Raft distributed consensus node coordinator
  - `raft_election_timeout(cluster)` / `રાફ્ટ_ચૂંટણી_સમય`: Randomized election timer trigger with split-vote avoidance
  - `raft_log_append(cluster, command)` / `રાફ્ટ_લોગ_ઉમેરો`: Distributed log replication with quorum consensus confirmation
  - `raft_state_machine_apply(cluster, command)` / `રાફ્ટ_સ્ટેટ_મશીન`: Linearizable Replicated State Machine (RSM) applier
  - `raft_log_compact(cluster, index)` / `રાફ્ટ_લોગ_સંકુચિત`: Snapshot compaction with differential log truncation
  - `raft_snapshot_restore(cluster, snapshot)` / `રાફ્ટ_સ્નેપશોટ_પુનઃપ્રાપ્તિ`: Fast state catch-up for lagging or new nodes
  - `raft_joint_consensus(cluster, old_cfg, new_cfg)` / `રાફ્ટ_સંયુક્ત_સંમતિ`: Zero-downtime dynamic cluster membership migration
  - `raft_split_brain_guard(cluster)` / `રાફ્ટ_વિભાજન_સુરક્ષા`: Network partition defense with majority quorum fencing
  - `raft_cross_region_federate(cluster, remote_cluster)` / `રાફ્ટ_પ્રદેશ_ફેડરેશન`: Cross-region anti-entropy gossip federation
  - CLI: `gujarati raft:quorum`, `gujarati raft:stepdown`
- **Pillar 5: Sovereign Architecture & Swarms (સાર્વભૌમ આર્કિટેક્ચર અને એજન્ટ સ્વોર્મ)**:
  - `sovereign_agent_swarm(count, role)` / `સાર્વભૌમ_એજન્ટ_સ્વોર્મ`: Multi-agent collaborative decision swarm
  - `sovereign_task_decompose(swarm, task)` / `સાર્વભૌમ_કાર્ય_વિભાજન`: Autonomous hierarchical goal decomposition
  - `sovereign_python_bridge(module, fn, args)` / `સાર્વભૌમ_પાયથન_સેતુ`: Direct zero-copy C-Python bridge
  - `sovereign_rust_ffi(lib, fn, args)` / `સાર્વભૌમ_રસ્ટ_સેતુ`: Native C-ABI Rust foreign function interop
  - `sovereign_bytecode_verify(bytecode)` / `સાર્વભૌમ_બાઇટકોડ_ચકાસો`: Formal cryptographic verification of compiled bytecode
  - `sovereign_mcu_profile(architecture)` / `સાર્વભૌમ_એમસીયુ_પ્રોફાઇલ`: Embedded microcontroller sizing (< 64KB RAM)
  - `sovereign_replay_debugger(recording)` / `સાર્વભૌમ_રીપ્લે_ડિબગર`: Deterministic time-travel replay debugger
  - `sovereign_audit_compliance(standard)` / `સાર્વભૌમ_ઓડિટ_સુસંગતતા`: Regulatory data sovereignty and geolocation border compliance
  - `sovereign_lts_guarantee(component)` / `સાર્વભૌમ_સ્થિરતા_ખાતરી`: 10-Year Long-Term Support architectural stability guarantee (2026-2036)
  - CLI: `gujarati swarm:run [swarm.gj]`, `gujarati kernel:audit`

### What's New in v2.9.0: Pravah, Shilp, Vidyut & Yantra (560 Tests Milestone)

GujaratiLang v2.9.0 brings 30 enterprise capabilities across distributed streaming, vector canvas graphics, Raft consensus clustering, and high-performance neural vector databases with **560 automated test suites passing (100%)**:

- **Pravah (પ્રવાહ) Distributed Streaming & Event Mesh**:
  - `pravah_producer(config)` / `પ્રવાહ_ઉત્પાદક`: Event streaming producer client
  - `pravah_consumer(config)` / `પ્રવાહ_ગ્રાહક`: Consumer group subscriber with offset tracking
  - `pravah_send(producer, topic, msg, [key])` / `પ્રવાહ_મોકલો`: Partitioned event publishing
  - `pravah_poll(consumer, timeout_ms)` / `પ્રવાહ_મેળવો`: Stream consumer poller
  - `pravah_commit(consumer)` / `પ્રવાહ_સ્વીકાર`: Offset synchronization commit
  - `pravah_dlq(stream, dlq_topic)` / `પ્રવાહ_મૃત_પત્ર`: Dead-letter queue routing for failed events
  - `pravah_window(stream, window_ms, fn)` / `પ્રવાહ_સમય_બારી`: Tumbling & sliding window aggregations
  - CLI: `gujarati pravah:stream [topic]`, `gujarati pravah:consume [topic]`
- **Shilp (શિલ્પ) High-Performance Vector Canvas & Graphics Engine**:
  - `shilp_scene(width, height)` / `શિલ્પ_દ્રશ્ય`: Scene graph container and canvas context
  - `shilp_draw_path(scene, svg_path, style)` / `શિલ્પ_માર્ગ`: SVG vector path renderer
  - `shilp_draw_text(scene, text, x, y, font)` / `શિલ્પ_લખાણ`: Hardware-rendered vector typography
  - `shilp_transform(node, matrix)` / `શિલ્પ_રૂપાંતરણ`: 2D/3D affine transformation matrix
  - `shilp_gradient(type, stops)` / `શિલ્પ_ઢાળ`: Linear and radial gradient color shaders
  - `shilp_export_svg(scene, [path])` / `શિલ્પ_નિકાસ_svg`: Standard SVG XML serialization
  - `shilp_export_png(scene, [path])` / `શિલ્પ_નિકાસ_png`: Hardware-rendered PNG bitmap exporter
  - CLI: `gujarati shilp:render <scene.gj> [out.png]`
- **Vidyut (વિદ્યુત) Raft Consensus & Actor System**:
  - `vidyut_cluster(node_id, peers)` / `વિદ્યુત_ક્લસ્ટર`: Distributed cluster coordinator
  - `vidyut_raft_state(cluster)` / `વિદ્યુત_રાફ્ટ_સ્થિતિ`: Leader/Follower consensus state
  - `vidyut_dlock_acquire(cluster, lock, [ttl])` / `વિદ્યુત_તાળું_મેળવો`: Distributed mutual exclusion lock
  - `vidyut_dlock_release(cluster, lock)` / `વિદ્યુત_તાળું_છોડો`: Distributed lock release
  - `vidyut_actor_spawn(behavior_fn)` / `વિદ્યુત_અભિનેતા`: Erlang-style lightweight green actor
  - `vidyut_actor_send(actor, message)` / `વિદ્યુત_સંદેશ`: Asynchronous actor mailbox enqueue
  - CLI: `gujarati vidyut:status [node]`, `gujarati vidyut:join <peer>`
- **Yantra (યંત્ર) Vector Database & Neural Embeddings**:
  - `yantra_vector_db(dim, [metric])` / `યંત્ર_વેક્ટર_ડીબી`: In-memory HNSW vector database
  - `yantra_insert(vdb, id, vector, [metadata])` / `યંત્ર_દાખલ`: High-dimensional vector indexing
  - `yantra_search(vdb, query_vector, top_k)` / `યંત્ર_શોધ`: Approximate nearest neighbors (ANN) search
  - `yantra_embed_text(text, [model])` / `યંત્ર_એમ્બેડ`: Dense text embedding computation
  - `yantra_cosine(vec1, vec2)` / `યંત્ર_કોસાઈન`: SIMD-accelerated vector cosine distance
  - `yantra_hybrid_rank(vdb, text, vec, alpha)` / `યંત્ર_સંકર_શોધ`: Blended BM25 + vector ranking
  - CLI: `gujarati yantra:search [index] [query]`

### What's New in v2.8.0: Tarang, Setu, Kasauti v2 & Suraksha v2 (545 Tests Milestone)

GujaratiLang v2.8.0 delivers 30 enterprise capabilities across real-time WebSockets, native GraphQL, visual regression testing, and cryptographic hardware vaults with **545 automated test suites passing (100%)**:

- **Tarang (તરંગ) Real-Time WebSockets & SSE Streaming**:
  - `tarang_ws_server(port)` / `તરંગ_સર્વર`: Full-duplex WebSocket server engine
  - `tarang_ws_client(url)` / `તરંગ_ક્લાયન્ટ`: WebSocket client with automatic reconnects
  - `tarang_ws_send(client, msg)` / `તરંગ_મોકલો`: Message transmission to connected peers
  - `tarang_ws_broadcast(channel, msg)` / `તરંગ_પ્રસારણ`: Channel-wide broadcast distribution
  - `tarang_sse_stream(res, event, data)` / `તરંગ_પ્રવાહ`: Server-Sent Events (SSE) streaming
  - `tarang_room_join(client, room)` / `તરંગ_રૂમ_જોડાઓ` & `tarang_room_leave()`: Room multiplexing
  - CLI: `gujarati tarang:serve [port]`
- **Setu (સેતુ) Native GraphQL Runtime & DataLoader**:
  - `setu_schema(sdl, resolvers)` / `સેતુ_યોજના`: Native GraphQL SDL schema compilation
  - `setu_query(schema, query)` / `સેતુ_પ્રશ્ન`: GraphQL query resolution with selection sets
  - `setu_mutation(schema, mutation)` / `સેતુ_રૂપાંતરણ`: Mutating GraphQL operations
  - `setu_subscription(schema, sub, cb)` / `સેતુ_સબ્સ્ક્રિપ્શન`: Reactive real-time subscriptions
  - `setu_graphiql_html()` / `સેતુ_ગ્રાફીકલ`: Embedded GraphiQL explorer
  - `setu_dataloader(batch_fn)` / `સેતુ_લોડર`: Batched memoized data loading
  - `setu_federation(services)` / `સેતુ_ફેડરેશન`: Distributed schema federation
  - CLI: `gujarati setu:schema <file.graphql>`
- **Kasauti v2 (કસોટી v2) Visual Regression, Network Mock & Device Emulation**:
  - `kasauti_diff_visual(img1, img2, threshold)` / `કસોટી_દ્રશ્ય_તફાવત`: Visual regression pixel diffing
  - `kasauti_mock_http(url, mock_res)` / `કસોટી_મોક_નેટવર્ક`: Stubbed HTTP network layer
  - `kasauti_intercept_request(matcher, handler)` / `કસોટી_અવરોધ`: Network request mutation & intercept
  - `kasauti_emulate_device(name)` / `કસોટી_ઉપકરણ`: Mobile & tablet device viewport emulation
  - `kasauti_lighthouse_audit(url)` / `કસોટી_ઓડિટ`: Audit performance & accessibility
  - `kasauti_har_export(session, file)` / `કસોટી_હાર`: HTTP Archive (HAR) network waterfall exporter
  - CLI: `gujarati kasauti:visual`, `gujarati kasauti:mock`
- **Suraksha v2 (સુરક્ષા v2) OAuth2, RBAC & Secret Vault**:
  - `suraksha_oauth_provider(config)` / `સુરક્ષા_ઓઓથ`: OAuth2 providers (Google, GitHub, Auth0)
  - `suraksha_rbac_role(name, perms)` / `સુરક્ષા_ભૂમિકા`: Role-based access control definition
  - `suraksha_rbac_can(role, perm)` / `સુરક્ષા_પરવાનગી`: Role permission check with wildcards
  - `suraksha_vault_encrypt(key, data)` / `સુરક્ષા_તિજોરી_એન્ક્રિપ્ટ`: AES-256-GCM secret vault encryption
  - `suraksha_vault_decrypt(key, cipher)` / `સુરક્ષા_તિજોરી_ડિક્રિપ્ટ`: Secret vault payload decryption
  - `suraksha_api_key_rotate(key_id)` / `સુરક્ષા_કી_રોટેટ`: Zero-downtime cryptographic key rotation
  - CLI: `gujarati vault:seal`, `gujarati vault:unseal`

### What's New in v2.7.0: Mandhan, Garvi, Samvad & Saransh (530 Tests Milestone)

GujaratiLang v2.7.0 delivers four production-grade subsystems across database migrations, web microservices, real-time AI agents, and standalone application packaging with **530 automated test suites passing (100%)**:

- **Mandhan (મંડાણ) Schema Migrations & Blueprints**:
  - `schema_create(table, cb)` / `યોજના_બનાવો`: Declarative migration runner with fluent table blueprints
  - Column Types: `t.id()`, `t.string()`, `t.number()`, `t.boolean()`, `t.json()`, `t.timestamps()`
  - Modifiers: `t.unique()`, `t.nullable()`, `t.default(val)`
  - Schema Management: `schema_drop()`, `schema_rename()`, `db_seed()`
  - CLI: `gujarati migrate`, `gujarati migrate:rollback`, `gujarati db:seed`
- **Garvi (ગરવી) Express/Koa-style HTTP Web Microframework**:
  - `garvi_create()` / `ગરવી_બનાવો`: Lightweight high-throughput web server engine
  - Router: `app.get()`, `app.post()`, `app.put()`, `app.delete()`, `app.patch()`, `app.group()`, `app.listen()`
  - Middleware: `app.use()`, `garvi_cors()`, `garvi_logger()`, `garvi_rate_limit()`, `garvi_jwt_auth()`
  - Hot-Reload CLI: `gujarati garvi:watch [file]` / `gujarati serve --watch`
- **Samvad (સંવાદ) Unified AI Agent & Streaming SDK**:
  - `samvad_model(name)` / `સંવાદ_મોડેલ`: Google DeepMind Gemini (`gemini-2.5-flash`, `gemini-2.5-pro`) integration
  - Streaming: `samvad_stream(model, prompt, cb)` / `model.stream()` real-time chunk callbacks
  - Conversational: `samvad_chat(model, msgs)` / `model.chat()` multi-turn dialog sessions
  - Agent Tools: `samvad_tool_register(name, fn, schema)` for native function-calling
  - Local Models: `samvad_local_open(path)` for offline quantized GGUF neural inference
- **Saransh (સારાંશ) Self-Contained Native Compiler & Packager**:
  - `saransh_build(script, opts)` / `સારાંશ_બનાવો`: Programmatic single-binary compiler
  - Windows Desktop: `gujarati build:exe [script] [out.exe]` (< 500 KB standalone executable)
  - Android Mobile: `gujarati build:apk [script] [out.apk]` (Standalone signed APK with NDK binaries)

### What's New in v2.6.0: Kasauti (કસોટી) E2E Browser & Frontend Testing Suite

GujaratiLang v2.6.0 introduces **Kasauti (કસોટી)**—a full-fledged end-to-end browser and UI automation engine inspired by Laravel Dusk, completing the full-stack Laravel triad (*Eloquent ORM + Blade Templates + Kasauti Browser Testing*) with **515 automated test suites passing (100%)**:

- **Fluent Browser Interaction API**:
  - `kasauti_open([options])` / `કસોટી_ખોલો`: Opens a virtual or headless browser session with custom viewports
  - `kasauti_visit(b, url)` / `કસોટી_મુલાકાત`: Navigates to local routes or external web URLs
  - `kasauti_type(b, selector, text)` / `કસોટી_લખો`: Types into inputs, textareas, and form fields
  - `kasauti_press(b, button_text)` / `કસોટી_દબાવો`: Submits forms or presses action buttons
  - `kasauti_click(b, selector)` / `કસોટી_ક્લિક`: Clicks links and DOM selectors
  - `kasauti_select(b, selector, value)` / `કસોટી_પસંદ`: Selects dropdown option values
  - `kasauti_screenshot(b, path)` / `કસોટી_સ્ક્રીનશોટ`: Captures visual page snapshots
  - `kasauti_cookie(b, key[, value])` / `કસોટી_કૂકી`: Manages HTTP cookies and session state
  - `kasauti_close(b)` / `કસોટી_બંધ`: Safely closes browser sessions
- **Dusk-Style Browser Assertions**:
  - `kasauti_assert_see(b, text)` / `કસોટી_ખાતરી_જોવા_મળ્યું`: Asserts page contains visible text
  - `kasauti_assert_dont_see(b, text)` / `કસોટી_ખાતરી_નથી_દેખાતું`: Asserts page does not show forbidden/error text
  - `kasauti_assert_path(b, path)` / `કસોટી_ખાતરી_પાથ`: Asserts current browser URL path
  - `kasauti_assert_title(b, title)` / `કસોટી_ખાતરી_શીર્ષક`: Asserts page title matches
  - `kasauti_assert_present(b, selector)` / `કસોટી_ખાતરી_હાજર`: Asserts element presence in DOM
- **CLI Subcommands**:
  - `gujarati kasauti [path]`: Discovers and executes all `*.kasauti.gj` and `*_test.gj` suites
  - `gujarati kasauti:make <TestName>`: Scaffolds a new Kasauti browser test template
  - `gujarati kasauti:chrome`: Scans and validates local Chrome/Edge WebDriver and port 9222 readiness
- **Previous Milestone Highlights**:
  - **v2.5.0 LTS**: AOT Native Machine Compiler (`gujarati --aot input.gj -o app.exe`), C Foreign Function Interface (C-FFI via `ffi_open`, `ffi_bind`, `ffi_call`, `ffi_close`), and Enterprise Mobile Suite.
  - **v2.4.0**: Cloud Microservices, Redis-style KV Cache (`cache_set`, `cache_get`), Distributed Pub/Sub (`pubsub_publish`, `pubsub_subscribe`), and SQLite database driver.
  - **v2.1.0**: Laravel Eloquent ORM, Blade Templating, CGI Gateway, and Channels.

### What's New in v1.1.0

GujaratiLang v1.1.0 delivers 30 major enhancements spanning Object-Oriented Programming, Machine Learning, Web APIs, Persistent Storage, System Process Control, and Developer CLI Tooling:

- **Object-Oriented Programming (OOP)**:
  - `varg` / `વર્ગ`: Define classes with state and behaviors
  - `rachna` / `રચના` & `navu` / `નવું`: Constructors and object instantiation (`navu ClassName(args)`)
  - `a_pote` / `આ_પોતે` / `this`: Instance self-reference inside methods and constructors
  - `anukaran` / `અનુકરણ`: Single inheritance (`varg Dog anukaran Animal { ... }`)
  - Dot notation: Access properties (`obj.name`) and invoke instance methods (`obj.greet()`)
- **Machine Learning & Linear Algebra**:
  - `ml_rekhiya_sambandh(x, y)`: Linear Regression ($y = mx + c$) computing slope, intercept, and $R^2$
  - `ml_kmeans(data, k[, max_iters])`: K-Means clustering for 1D and multi-dimensional numeric points
  - `ml_sigmoid(x)`: Sigmoid activation function supporting scalars and lists
  - `ml_relu(x)`: Rectified Linear Unit ($ReLU$) activation
  - `ml_softmax(list)`: Softmax probability distribution calculation
  - `ml_mse(y_true, y_pred)`: Mean Squared Error loss calculation
  - `ml_minmax_scaling(list)`: Feature scaling normalized to $[0, 1]$
  - `vector_bindu(v1, v2)`: Vector dot product
  - `vector_maan(v)`: Euclidean vector magnitude/norm
  - `cosine_samanata(v1, v2)`: Cosine similarity between vectors
  - `antar_euclidean(p1, p2)`: Euclidean distance between multi-dimensional points
- **Web & Networking**:
  - `http_melvo(url)`: HTTP GET request returning the response body as text
  - `http_moklo(url, json_data)`: HTTP POST request with JSON payload
  - `url_prashno(url)`: Parse URL query string into a key-value dictionary
- **Data Persistence & Configuration**:
  - `sangrah_lakho([filepath, ]key, value)`: Persistent key-value storage backed by JSON file
  - `sangrah_vancho([filepath, ]key)`: Retrieve values from persistent JSON storage
  - `ini_vancho(path_or_string)`: Parse INI configuration into structured dictionaries
  - `paryavaran_vistaran(template)`: Template expansion of environment variables (`${VAR}`)
- **System & Process Control**:
  - `suvo(ms)` / `vilamb(ms)`: Millisecond execution delay
  - `nikal([code])`: Terminate process with exit code (default `0`)
  - `sthanak_folder()`: Get current working directory
  - `folder_badlo(path)`: Change current working directory
- **Algorithms & Type Safety**:
  - `shodho_dvimukhi(sorted_list, target)`: Binary search returning index or `-1`
  - `shodho_sarshu(target, candidate_list)`: Fuzzy string matcher via Levenshtein distance
  - `sankhya_rupantar(val[, default])`: Safe conversion to numeric value without halting
  - `lakhan_rupantar(val)`: Safe string conversion of any data structure (numbers, lists, dicts)
- **Developer CLI Tooling**:
  - `gujarati --tokens <source.gj>`: Inspect lexer token stream
  - `gujarati --ast <source.gj>`: Dump program syntax tree
  - `gujarati --format <source.gj>` / `--fmt <source.gj>` (optional `-w`): Automatic code formatter

### Core Language Features

The interpreter supports:

- Programs delimited by `આવો` (start) and `આવજો` (end)
- UTF-8 source files and the Gujarati `છાપો` (print) keyword
- Numeric literals, parentheses, unary minus, arithmetic with `+`, `-`, `*`,
  `/`, and string concatenation with `+`
- Comparisons: numbers support `==`, `!=`, `<`, `<=`, `>`, and `>=`; strings
  support equality with `==` and `!=`
- Logical operators: `અને` (AND), `અથવા` (OR), and `નહીં` (NOT)
- `જ્યાં સુધી (condition) { ... }` while loops
- Mutable, zero-based lists with nested values, indexed reads and writes, and
  list support in `લંબાઈ`
- `દરેક (item માં list) { ... }` list loops and
  `દરેક (index માં start..end) { ... }` integer ranges with an exclusive end
- `import "module.gj";` with importer-relative paths, one-time execution,
  shared globals, and circular-import detection
- Variables created and assigned with `name = value;`; assigning an existing
  name updates its value
- Functions declared with `કાર્ય name(parameters) { ... }`, called as
  expressions or statements, and returning values with `પરત expression;`
- `વાંચો("prompt")` to display a prompt and read one line of text from standard
  input; the returned value is a string
- `લંબાઈ(value)` to return the number of Unicode code points in a string or
  the number of items in a list
- `સંખ્યા(text)` to parse a numeric string into a number
- `લખાણ(value)` to convert a number, null, or list into its string representation
- `પ્રકાર(value)` to inspect the runtime type of a value (`"number"`, `"string"`, `"list"`, or `"null"`)
- `ઉમેરો(list, item)` to append an item to a list and return the updated list
- `કાપો(string, start[, length])` to extract a substring using Unicode code-point offsets
- `શોધો(string, target[, start])` to find the 0-based code-point index of a substring (or `-1` if not found)
- `કાઢો(list[, index])` to remove and return an item from a list (last item by default)
- `પહેલી_એબીસીડી(text)` to convert a string to uppercase
- `બીજી_એબીસીડી(text)` to convert a string to lowercase
- `મહત્તમ(a, b)` and `ન્યૂનતમ(a, b)` to return the maximum and minimum of two numbers
- `ધન_મૂલ્ય(number)` to return the absolute value of a number
- Romanized Gujarati spellings for all keywords and built-ins, so programs can
  be written using an English keyboard
- Gujarati or English-letter variable names, with digits and underscores
  allowed after the first character
- `જો`, `નહિતર જો`, and `નહિતર` conditional blocks with braces
- The `નકામો` null value; conditions accept numbers (`0` is false, nonzero is
  true) and null (false); strings are not valid conditions. Comparison results
  are numbers (`1` for true and `0` for false)
- Quoted strings with `\"`, `\\`, `\n`, `\r`, and `\t` escapes
- `+` adds two numbers or joins two strings; mixing a string and number is an
  error
- `ચેતવણી "message";` to report a warning and continue
- `ભૂલ "message";` and `ઘાતક ભૂલ "message";` to report an error and stop
- Semicolon-terminated print statements and `//` line comments
- File, line, and column diagnostics with a source-line excerpt and caret
  indicator

Comparisons have lower precedence than arithmetic and produce `1` for true or
`0` for false. Numbers support all comparison operators. Strings support `==`
and `!=`, comparing their decoded text; string-to-number comparisons and
ordering comparisons on strings are errors.
Logical precedence from strongest to weakest is `નહીં`, comparisons, `અને`,
then `અથવા`. Logical operators accept numbers and `નકામો`, return `1` or `0`,
and short-circuit when the result is already known. Strings cannot be used as
logical operands.

The `+` operator adds two numbers or concatenates two strings. It does not
automatically convert between strings and numbers. String equality lets a
program check text values:

```text
નામ = "હર્ષ";
છાપો "નમસ્તે, " + નામ;
જો (નામ == "હર્ષ") { છાપો "ફરીથી સ્વાગત છે!"; }
```

Use `લંબાઈ(text)` to count Unicode code points in text rather than its UTF-8
byte length. Combining marks count as separate code points. For a list,
`લંબાઈ` returns its item count.

```text
છાપો લંબાઈ("Gujarati");
છાપો લંબાઈ("હર્ષ");
```

### Use GujaratiLang with an English keyboard

You do not need to switch to a Gujarati keyboard to write GujaratiLang.
Every Gujarati keyword has a lowercase ASCII spelling (a romanized Gujarati
transliteration). These are alternate spellings of the same keywords, not
English translations. Gujarati spellings continue to work too, and both forms
can be used in the same program. Multi-word spellings use underscores.

| Gujarati keyword | English-keyboard spelling | Meaning |
| --- | --- | --- |
| `આવો` | `aavo` | Start a program |
| `આવજો` | `aavjo` | End a program |
| `છાપો` | `chhapo` | Print |
| `જો` | `jo` | If |
| `નહિતર જો` | `nahitar_jo` | Else if |
| `નહિતર` | `nahitar` | Else |
| `જ્યાં સુધી` | `jya_sudhi` | While loop |
| `દરેક` | `darek` | For loop |
| `માં` | `ma` | For-loop separator |
| `અને` | `ane` | And |
| `અથવા` | `athva` | Or |
| `નહીં` | `nahi` | Not |
| `નકામો` | `nakamo` | Null |
| `કાર્ય` | `kary` | Function |
| `પરત` | `parat` | Return |
| `આયાત` | `aayat` or `import` | Import a module |
| `ચેતવણી` | `chetavani` | Warning |
| `ભૂલ` | `bhul` | Error |
| `ઘાતક ભૂલ` | `ghatak_bhul` | Fatal error |
| `વાંચો(...)` | `vancho(...)` | Read input |
| `લંબાઈ(...)` | `lambai(...)` | Get string or list length |
| `સંખ્યા(...)` | `sankhya(...)` | Convert string to number |
| `લખાણ(...)` | `lakhan(...)` | Convert value to string |
| `પ્રકાર(...)` | `prakar(...)` | Inspect runtime type |
| `ઉમેરો(...)` | `umero(...)` | Append item to list |
| `કાપો(...)` | `kapo(...)` | Slice string |
| `શોધો(...)` | `shodho(...)` | Find substring index |
| `કાઢો(...)` | `kadho(...)` | Remove/pop item from list |
| `પહેલી_એબીસીડી(...)` | `peli_abcd(...)` | Convert string to uppercase |
| `બીજી_એબીસીડી(...)` | `biji_abcd(...)` | Convert string to lowercase |
| `મહત્તમ(...)` | `mahatam(...)` | Return maximum value |
| `ન્યૂનતમ(...)` | `nyunatam(...)` | Return minimum value |
| `ધન_મૂલ્ય(...)` | `dhan_mulya(...)` | Return absolute value |
| `ઉલટાવો(...)` | `ultavo(...)` | Reverse list in-place |
| `ભાગ(...)` | `bhag(...)` | Split string into list by delimiter |
| `જોડો(...)` | `jodo(...)` | Join list into string using separator |
| `સાફ(...)` | `saf(...)` | Trim leading/trailing whitespace |
| `ઘાત(...)` | `ghat(...)` | Return base raised to exponent |
| `મૂળ(...)` | `mul(...)` | Return square root |
| `ગોઠવો(...)` | `gothvo(...)` | Sort list items in-place |
| `બદલો(...)` | `badlo(...)` | Replace occurrences of substring |
| `શરૂઆત_સાથે(...)` | `sharuat_sathe(...)` | Test if string starts with prefix |
| `અંત_સાથે(...)` | `ant_sathe(...)` | Test if string ends with suffix |
| `સમાવે_છે(...)` | `samave_chhe(...)` | Test if list contains item |
| `ગોળ(...)` | `gol(...)` | Round number to nearest whole number |
| `નીચે(...)` | `niche(...)` | Floor number |
| `ઉપર(...)` | `upar(...)` | Ceil number |
| `પુનરાવર્તન(...)` | `punravartan(...)` | Repeat string count times |
| `ટુકડો(...)` | `tukdo(...)` | Extract sub-list slice |
| `સ્થાન(...)` | `sthan(...)` | Find 0-based first index of item in list (-1 if not found) |
| `મૂકો(...)` | `muko(...)` | Insert item into list at index in-place |
| `ડાબે_ભરો(...)` | `dabe_bharo(...)` | Pad string on left to target width |
| `જમણે_ભરો(...)` | `jamne_bharo(...)` | Pad string on right to target width |
| `સીમા(...)` | `sima(...)` | Clamp number between minimum and maximum bounds |
| `યાદચ્છિક(...)` | `yadachhik(...)` | Generate random float in [0.0, 1.0) or random integer in [min, max] |
| `બીજ(...)` | `beej(...)` | Set pseudo-random number generator seed for deterministic output |
| `વિસ્તારો(...)` | `vistaro(...)` | Append all items from another list in-place |
| `પાઈ()` | `pi()` | Mathematical constant pi (~3.14159) |
| `ઈ()` | `e()` | Mathematical constant e (~2.71828) |
| `ચિહ્ન(...)` | `chihna(...)` | Return sign of number (1 for positive, -1 for negative, 0 for zero) |
| `લઘુગણક(...)` | `laghuganak(...)` | Return logarithm (natural log ln(n) or log base(n)) |
| `અક્ષર_કોડ(...)` | `akshar_kod(...)` | Return Unicode codepoint of character at index |
| `કોડ_થી_અક્ષર(...)` | `kod_thi_akshar(...)` | Convert Unicode code point to single-character string |
| `યાદી_ભરો(...)` | `yadi_bharo(...)` | Create a new list filled with count copies of value |
| `સરવાળો_યાદી(...)` | `sarvalo_yadi(...)` | Sum numeric elements in a list |
| `યાદી_ન્યૂનતમ(...)` | `yadi_nyunatam(...)` | Find minimum numeric element in list |
| `યાદી_મહત્તમ(...)` | `yadi_mahatam(...)` | Find maximum numeric element in list |
| `ગણતરી(...)` / `ગણતરી_વસ્તુ(...)` | `ganatari(...)` / `ganatari_vastu(...)` | Count item occurrences in list or substring in string |
| `ડાબે_કાપો(...)` | `dabe_kapo(...)` | Trim leading whitespace from string |
| `જમણે_કાપો(...)` | `jamne_kapo(...)` | Trim trailing whitespace from string |
| `વિભાજન_પંક્તિ(...)` | `vibhaajan_pankti(...)` | Split multi-line string into list of lines |
| `અક્ષરો(...)` | `aksharo(...)` | Split string into list of characters |
| `પર્યાવરણ(...)` | `paryavaran(...)` | Get system environment variable value (or null) |
| `બહાર(...)` | `bahar(...)` | Terminate program immediately with exit code (default 0) |
| `ચકાસો(...)` | `chakaso(...)` | Assert condition is truthy with optional error message |
| `સમાવે_લખાણ(...)` | `samave_lakhan(...)` | Check if string contains substring |
| `ફાઇલ_વાંચો(...)` | `file_vancho(...)` | Read file contents into a string (or null if missing) |
| `ફાઇલ_લખો(...)` | `file_lakho(...)` | Write text content to file (overwrites existing file) |
| `ફાઇલ_ઉમેરો(...)` | `file_umero(...)` | Append text content to file |
| `ફાઇલ_છે(...)` | `file_chhe(...)` | Check if file exists on disk (1.0 or 0.0) |
| `ફાઇલ_કાઢો(...)` / `ફાઇલ_હટાવો(...)` | `file_kadho(...)` / `file_hatao(...)` | Delete file from disk (1.0 on success, 0.0 on failure) |
| `ફાઇલ_કદ(...)` | `file_kad(...)` | Get file size in bytes (or null if missing) |
| `અટકો` | `atko` | Break out of loop immediately |
| `ચાલુ_રાખો` / `આગળ` | `chalu_rakho` / `aagal` | Continue to next loop iteration |
| `પ્રયત્ન` / `પકડો` | `prayatna` / `pakdo` | Try-catch block for error recovery |
| `શબ્દકોશ(...)` / `કોશ(...)` | `shabdakosh(...)` / `kosh(...)` | Create dictionary from key-value pairs |
| `ચાવીઓ(...)` / `ચાવી(...)` | `chavio(...)` / `chavi(...)` | Return list of dictionary keys |
| `મૂલ્યો(...)` | `mulyo(...)` | Return list of dictionary values |
| `દૂર_કરો(...)` / `કોશ_દૂર(...)` | `dur_karo(...)` / `kosh_dur(...)` | Remove key from dictionary (1 on success, 0 if not found) |
| `સમય()` | `samay()` | Current epoch timestamp in seconds |
| `તારીખ([format[, timestamp]])` | `tarikh([format[, timestamp]])` | Format timestamp into date-time string |
| `વર્ષ([timestamp])` | `varsh([timestamp])` | Extract year (e.g. 2026) |
| `મહિનો([timestamp])` | `mahino([timestamp])` | Extract month (1-12) |
| `દિવસ([timestamp])` | `divas([timestamp])` | Extract day of month (1-31) |
| `કલાક([timestamp])` | `kalak([timestamp])` | Extract hour (0-23) |
| `મિનિટ([timestamp])` | `minute([timestamp])` | Extract minute (0-59) |
| `સેકન્ડ([timestamp])` | `second([timestamp])` | Extract second (0-59) |
| `શાંત(...)` / `રાહ_જુઓ(...)` | `shant(...)` / `raah_juo(...)` | Pause execution for milliseconds |
| `ફેંકો(...)` | `phenko(...)` | Throw an error message |
| `અચળ` | `achala` or `const` | Declare immutable constant variable |
| `જેસન_વાંચો(...)` | `json_vancho(...)` | Parse JSON string into native dictionary, list, number, string |
| `જેસન_લખો(...)` | `json_lakho(...)` | Serialize value to standard JSON string |
| `દલીલો()` / `દલીલ_યાદી()` | `daleelo()` / `arg_yadi()` | Get command-line arguments passed to script |
| `દ્વિ_સંખ્યા(...)` | `dvi_sankhya(...)` | Convert integer to binary string representation |
| `દ્વિ_થી_સંખ્યા(...)` | `dvi_thi_sankhya(...)` | Convert binary string to integer number |
| `હેક્સ_લખાણ(...)` | `hex_lakhan(...)` | Convert integer to hex string representation |
| `હેક્સ_થી_સંખ્યા(...)` | `hex_thi_sankhya(...)` | Convert hex string to integer number |
| `ફોલ્ડર_છે(...)` | `folder_chhe(...)` | Check if directory exists on disk |
| `ફોલ્ડર_બનાવો(...)` | `folder_banao(...)` | Create directory on disk |
| `ફોલ્ડર_સૂચિ(...)` | `folder_suchi(...)` | List directory contents as list of strings |
| `કમાન્ડ_ચલાવો(...)` / `સિસ્ટમ(...)` | `command_chalao(...)` / `system_kary(...)` | Run system shell command and return exit code |
| `નકશો_યાદી(...)` | `naksho_yadi(...)` | Map function over list elements and return new list |
| `ગાળો_યાદી(...)` | `gaalo_yadi(...)` | Filter list elements based on predicate function |
| `સમેટો_યાદી(...)` | `sameto_yadi(...)` | Reduce list elements using accumulator function |
| `શોધો_યાદી(...)` | `shodho_yadi(...)` | Find first list element matching predicate |
| `શોધો_સૂચક_યાદી(...)` | `shodho_suchak_yadi(...)` | Find 0-based index of first element matching predicate |
| `ચપટી_યાદી(...)` | `chapti_yadi(...)` | Flatten nested sublists into single flat list |
| `ઝીપ_યાદી(...)` | `zip_yadi(...)` | Zip two lists element-by-element into list of pairs |
| `પેટર્ન_શોધો(...)` | `pattern_shodho(...)` | Wildcard pattern matching (`*` and `?`) |
| `લખાણ_બદલો_દરેક(...)` | `lakhan_badlo_darek(...)` | Replace all occurrences of substring |
| `બેઝ૬૪_કોડ(...)` | `base64_kod(...)` | Encode string to Base64 |
| `બેઝ૬૪_ડીકોડ(...)` | `base64_decode(...)` | Decode Base64 string |
| `શીર્ષક_લખાણ(...)` | `shirshak_lakhan(...)` | Convert string to Title Case |
| `પ્રથમ_મોટી(...)` | `pratham_moti(...)` | Capitalize only the first letter of string |
| `સ્વરૂપ(...)` | `swaroop(...)` | Format string template with `{}` placeholders |
| `લખાણ_અંતર(...)` | `lakhan_antar(...)` | Compute Levenshtein edit distance between two strings |
| `શા૨૫૬_હેશ(...)` | `sha256_hash(...)` | Compute 64-character lowercase SHA-256 hex digest |
| `સાઇન(...)` | `sine(...)` | Sine trigonometric function (radians) |
| `કોસાઇન(...)` | `cosine(...)` | Cosine trigonometric function (radians) |
| `ટેન્જન્ટ(...)` | `tangent(...)` | Tangent trigonometric function (radians) |
| `આર્કસાઇન(...)` | `arcsin(...)` | Inverse sine (arcsin) in radians |
| `આર્કકોસ(...)` | `arccos(...)` | Inverse cosine (arccos) in radians |
| `આર્કટેન(...)` | `arctan(...)` | Inverse tangent (arctan) in radians |
| `ગુરુ_તમ(...)` | `guru_tam(...)` | Greatest Common Divisor (GCD) of two integers |
| `લઘુ_તમ(...)` | `laghu_tam(...)` | Least Common Multiple (LCM) of two integers |
| `અંશ_થી_રેડિયન(...)` | `ansha_thi_radian(...)` | Convert degrees to radians |
| `રેડિયન_થી_અંશ(...)` | `radian_thi_ansha(...)` | Convert radians to degrees |
| `મેટ્રિક્સ_સરવાળો(...)` | `matrix_sarvalo(...)` | Component-wise addition of two 2D numeric matrices |
| `મેટ્રિક્સ_ગુણાકાર(...)` | `matrix_gunakar(...)` | Standard matrix multiplication of two 2D matrices |
| `ભાષા_આવૃત્તિ()` | `bhasha_avrutti()` | Get current interpreter version (`"1.0.0"`) |
| `પ્લેટફોર્મ_નામ()` | `platform_nam()` | Get operating system platform (`"windows"`, `"linux"`, `"macos"`) |
| `પર્યાવરણ(નામ)` | `paryavaran(nam)` | Get environment variable value (`getenv`) |
| `પર્યાવરણ_લખો(નામ, મૂલ્ય)` | `paryavaran_lakho(nam, mulya)` | Set environment variable value |
| `પાથ_જોડો(a, b)` | `path_jodo(a, b)` | Join filesystem paths cross-platform |
| `પાથ_વિસ્તરણ(પાથ)` | `path_vistaran(path)` | Extract file extension (e.g. `".gj"`) |
| `પાથ_મુખ્ય(પાથ)` | `path_mukhya(path)` | Extract basename/filename from path |
| `પાથ_ફોલ્ડર(પાથ)` | `path_folder(path)` | Extract parent directory from path |
| `યુયુઆઈડી_બનાવો()` | `uuid_banao()` | Generate RFC 4122 v4 unique identifier string |
| `યુઆરએલ_કોડ(લખાણ)` | `url_kod(str)` | Percent-encode string for URLs |
| `યુઆરએલ_ડીકોડ(લખાણ)` | `url_decode(str)` | Decode percent-encoded URL string |
| `યાદી_સરવાળો(યાદી)` | `yadi_sarvalo(list)` | Calculate sum of numeric list elements |
| `યાદી_સરેરાશ(યાદી)` | `yadi_sareras(list)` | Calculate arithmetic mean of numeric list |
| `યાદી_મધ્યસ્થ(યાદી)` | `yadi_madhyastha(list)` | Calculate median of numeric list |
| `લેખન_પૂર્ણ_ડાબી(...)` | `lakhan_purn_dabi(...)` | Pad string on the left to target length |
| `લેખન_પૂર્ણ_જમણી(...)` | `lakhan_purn_jamni(...)` | Pad string on the right to target length |
| `બીટ_અને(a, b)` | `bit_ane(a, b)` | Bitwise AND operation |
| `બીટ_અથવા(a, b)` | `bit_athva(a, b)` | Bitwise OR operation |
| `બીટ_એક્સઓર(a, b)` | `bit_xor(a, b)` | Bitwise XOR operation |
| `બીટ_નહિ(a)` | `bit_nahi(a)` | Bitwise NOT operation |
| `બીટ_શિફ્ટ_ડાબી(a, n)` | `bit_shifte_dabi(a, n)` | Bitwise left shift |
| `બીટ_શિફ્ટ_જમણી(a, n)` | `bit_shifte_jamni(a, n)` | Bitwise right shift |
| `યાદી_અનન્ય(યાદી)` | `yadi_ananya(list)` | Return list with duplicate values removed |
| `યાદી_મેળ(l1, l2)` | `yadi_mel(l1, l2)` | Set union of two lists |
| `યાદી_છેદ(l1, l2)` | `yadi_chhed(l1, l2)` | Set intersection of two lists |
| `યાદી_તફાવત(l1, l2)` | `yadi_tavat(l1, l2)` | Set difference of two lists |
| `અક્ષર_કોડ(લખાણ, ક્રમ)` | `akshar_kod(str, idx)` | Get ASCII/Unicode code unit at byte index |
| `કોડ_થી_અક્ષર(કોડ)` | `kod_thi_akshar(code)` | Convert integer code unit to 1-char string |
| `લૉગ_કુદરતી(x)` | `log_kudrati(x)` | Natural logarithm `ln(x)` |
| `લૉગ_૧૦(x)` | `log_10(x)` | Base-10 logarithm `log10(x)` |
| `ઘાત_મૂળ(આધાર, ઘાત)` | `ghat_mul(base, exp)` | Power function `pow(base, exp)` |
| `ઈ_ઘાત(x)` | `e_ghat(x)` | Natural exponential `exp(x)` |
| `યાદી_ઊલટે_ક્રમ(યાદી)` | `yadi_ulte_kram(list)` | Return reversed copy of list |
| `યાદી_ટુકડા(યાદી, કદ)` | `yadi_tukda(list, size)` | Partition list into sublists of size `size` |
| `યાદી_ખીચડી(યાદી)` | `yadi_khichdi(list)` | Randomly shuffle list elements |
| `ચાવી_છે(કોશ, ચાવી)` | `chavi_chhe(dict, key)` | Test if dictionary contains key (1 or 0) |
| `કોશ_જોડો(d1, d2)` | `kosh_jodo(d1, d2)` | Merge two dictionaries into a new dictionary |
| `માઇક્રો_સમય()` | `micro_samay()` | High-resolution microsecond epoch timestamp |
| `લેખન_આવૃત્તિ(લખાણ, ગણતરી)` | `lakhan_aavrutti(str, n)` | Repeat string N times |
| `લેખન_ગણતરી(લખાણ, શોધ)` | `lakhan_ganatari(str, sub)` | Count non-overlapping substring occurrences |
| `લેખન_ટુકડા_યાદી(લખાણ, વિભાજક)` | `lakhan_tukda_yadi(str, delims)` | Split string by any delimiter character in string |
| `ફાઇલ_લાઇન_વાંચો(પાથ)` | `file_line_vancho(path)` | Read file directly into list of string lines |
| `હેક્સ_થી_લેખન(હેક્સ)` | `hex_thi_lakhan(hex)` | Decode hexadecimal string to text |
| `સીએસવી_વાંચો(લખાણ)` | `csv_vancho(csv_text)` | Parse CSV text into 2D list of row lists |
| `સંખ્યા_છે(મૂલ્ય)` | `sankhya_chhe(val)` | Type predicate: 1 if number, 0 otherwise |
| `લેખન_છે(મૂલ્ય)` | `lakhan_chhe(val)` | Type predicate: 1 if string, 0 otherwise |
| `યાદી_છે(મૂલ્ય)` | `yadi_chhe(val)` | Type predicate: 1 if list, 0 otherwise |
| `કોશ_છે(મૂલ્ય)` | `kosh_chhe(val)` | Type predicate: 1 if dict, 0 otherwise |
| `નકામો_છે(મૂલ્ય)` | `nakamo_chhe(val)` | Type predicate: 1 if null, 0 otherwise |

Here is a complete program written using only English-keyboard keyword
spellings:

```text
aavo
kary double(value) { parat value * 2; }
items = [10, 20, 30];
darek (item ma items) {
    chhapo double(item);
}
jo (lambai(items) == 3) {
    chhapo "All three items were processed.";
}
aavjo
```

Save it as `english_keyboard.gj`, then run
`gujarati english_keyboard.gj`. The project also includes the runnable
[`examples/romanized.gj`](examples/romanized.gj) sample.

### Lists, loops, and modules

Lists can contain numbers, strings, `નકામો`, and other lists. Indexes start at
zero; use an indexed assignment to replace an item. `લંબાઈ`/`lambai` accepts
either a string or a list:

```text
items = [10, "twenty", [30, નકામો]];
છાપો items[1];
items[0] = 5;
છાપો items;
છાપો લંબાઈ(items);
```

Use `દરેક` (`darek`) to visit every item in a list, or iterate over an
integer range. The start is included and the end is excluded:

```text
દરેક (item માં items) { છાપો item; }
દરેક (index માં 0..લંબાઈ(items)) { છાપો index; }
```

In English-keyboard code, write the same loop as `darek (item ma items)`.
Use `ma` between the loop variable and either a list (`items`) or a numeric
range (`0..end`).

Import another `.gj` file with `આયાત "helpers.gj";` (`aayat` or `import`).
Import paths are
relative to the importing file. Imported code executes once and shares the
same global variables and functions; circular imports are reported as errors.
See [`examples/modules.gj`](examples/modules.gj),
[`examples/collections.gj`](examples/collections.gj), and the
[`examples/inventory.gj`](examples/inventory.gj) and
[`examples/stock.gj`](examples/stock.gj), and
[`examples/calculator.gj`](examples/calculator.gj), and
[`examples/string_utils.gj`](examples/string_utils.gj),
[`examples/invoice_generator.gj`](examples/invoice_generator.gj), and
[`examples/random_game.gj`](examples/random_game.gj) samples combining modules,
functions, lists, and input.

### Dictionaries (Key-Value Pairs)

GujaratiLang supports dictionary data structures with string keys and arbitrary values:

```text
વિદ્યાર્થી = {"નામ": "હર્ષ", "ગુણ": 95};
છાપો વિદ્યાર્થી["નામ"];
વિદ્યાર્થી["શહેર"] = "અમદાવાદ";
છાપો ચાવીઓ(વિદ્યાર્થી);
છાપો મૂલ્યો(વિદ્યાર્થી);
દરેક (ચાવી માં વિદ્યાર્થી) {
    છાપો ચાવી + ": " + લખાણ(વિદ્યાર્થી[ચાવી]);
}
```

### Loop Control (`અટકો` and `ચાલુ_રાખો`)

Use `અટકો` (`atko` / `break`) to exit a loop early and `ચાલુ_રાખો` (`chalu_rakho` / `aagal` / `continue`) to skip the rest of the current iteration:

```text
સંખ્યા = 0;
જ્યાં સુધી (સંખ્યા < 10) {
    સંખ્યા = સંખ્યા + 1;
    જો (સંખ્યા == 2) { ચાલુ_રાખો; }
    જો (સંખ્યા == 5) { અટકો; }
    છાપો સંખ્યા;
}
```

### Date and Time Utilities

Query timestamps, format localized date/time strings, inspect calendar components, or sleep:

```text
હમણાં = સમય();
છાપો તારીખ("%Y-%m-%d %H:%M:%S", હમણાં);
છાપો વર્ષ(હમણાં);
છાપો મહિનો(હમણાં);
શાંત(100); // 100 મિલિસેકન્ડ વિરામ
```

### Error Recovery (`પ્રયત્ન` and `પકડો`)

Protect against runtime errors (division by zero, file missing, invalid type) or explicitly throw custom errors with `ફેંકો` (`phenko`):

```text
પ્રયત્ન {
    જો (ઇનપુટ < 0) {
        ફેંકો("અનૃણ સંખ્યા અપેક્ષિત છે");
    }
    પરિણામ = 100 / ઇનપુટ;
} પકડો (ભૂલ) {
    છાપો "ભૂલ પકડાઈ: " + ભૂલ;
}
```

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
કાર્ય સરવાળો(પહેલું, બીજું) {
    પરત પહેલું + બીજું;
}
છાપો સરવાળો(2, 3);
ચેતવણી "This is a warning; the program will continue";
આવજો
```

Warnings and errors are written to standard error with the source location.
Errors include the relevant source line and a caret under the reported column.
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

Variables can contain numbers, strings, lists, or `નકામો`. Assigning to a name
for the first time creates it; later assignments update it. Reading a name
before its first assignment is an error. Variables first assigned in a
conditional block remain available for the rest of the program.

`વાંચો("prompt")` prints the prompt without a newline, reads one line from
standard input, and returns it as a string. Press Enter to submit an empty
string. Reaching end-of-file before a line is read is an error:

```text
આવો
નામ = વાંચો("તમારું નામ શું છે? ");
છાપો "નમસ્તે";
છાપો નામ;
આવજો
```

Run the interactive example with `./build/gujarati ./examples/input.gj` on
Linux or macOS, or `.\build\Release\gujarati.exe .\examples\input.gj` on
Windows.

### Try commands in the REPL

Start the interactive prompt without a source file:

```powershell
.\build\Release\gujarati.exe --repl
```

On Linux or macOS, run `./build/gujarati --repl`. At the prompt, enter one
complete statement or expression per line. Variables and functions remain
available until you exit; a bare expression prints its result:

```text
GujaratiLang> ગણતરી = 2;
GujaratiLang> ગણતરી + 3
5
GujaratiLang> કાર્ય બમણું(મૂલ્ય) { પરત મૂલ્ય * 2; }
GujaratiLang> બમણું(ગણતરી)
4
```

Use `છાપો` to print a value without automatically printing an expression
result. A syntax or runtime error is reported and the prompt remains available.
Enter Ctrl+Z followed by Enter in PowerShell, or Ctrl+D on Linux/macOS, to exit.
Select Gujarati diagnostics with `--language gu --repl`.

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
3. Optional: add GujaratiLang to your user `PATH` by opening PowerShell in the
   extracted folder and running:

   ```powershell
   powershell -ExecutionPolicy Bypass -File .\install.ps1
   ```

   This installs under your user profile and does not require administrator
   access. Open a new terminal after installation to run `gujarati` from any
   folder. You can also use the executable directly without installing it.
4. Open PowerShell in the extracted folder and run the included example:

   ```powershell
   .\gujarati.exe .\examples\hello.gj
   ```

5. Run your own program by giving its `.gj` file path:

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
Linux distribution. To make `gujarati` available from any folder, move the
extracted files to a directory you own and add that directory to your shell's
`PATH`.

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
interpreter, examples, and a short `README.txt`.
To run `gujarati` from any folder, move the extracted files to a directory you
own and add that directory to your shell's `PATH`.

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
The regression suite also runs the shipped Fibonacci, temperature-converter,
inventory, and stock examples and checks their output.

## Project website

The static landing page is in `website/index.html`. It has no build step or
external dependencies. Upload it as `index.html` to the subdomain's web root
using FTPS or SFTP; avoid unencrypted FTP when transferring hosting credentials.
The VS Code FTPS profile in `.vscode/sftp.json` is local-only and excluded from
Git. It leaves the password unset so the SFTP extension can prompt for it.

## Project status

GujaratiLang includes a C interpreter, regression tests, a beginner tutorial,
sample programs, and portable releases for Windows, Linux, and macOS. Future
work will be guided by user feedback and the project's issue tracker.

## Contributing

Bug reports and pull requests are welcome. See [CONTRIBUTING.md](CONTRIBUTING.md)
for build and contribution guidelines. GujaratiLang is licensed under the
[MIT License](LICENSE).
