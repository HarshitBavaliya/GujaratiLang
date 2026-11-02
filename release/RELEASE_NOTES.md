# GujaratiLang v2.8.0: Tarang, Setu, Kasauti v2 & Suraksha v2 (તરંગ, સેતુ, કસોટી v2 અને સુરક્ષા v2)

GujaratiLang **v2.8.0** is officially released! This landmark update brings 30 advanced enterprise capabilities across four major pillars: real-time bidirectional WebSockets and SSE streaming, native GraphQL engine with dataloader and subscriptions, visual regression and network mocking testing tools, and hardware-grade secret vault security with OAuth2 and RBAC authorization.

With v2.8.0, the automated test suite expands to the **545 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v2.8.0

### 1. 🌊 Tarang (તરંગ) — Real-Time WebSockets & Server-Sent Events (SSE)
High-concurrency full-duplex WebSocket and SSE streaming runtime with room multiplexing:
- **`tarang_ws_server(port)` / `તરંગ_સર્વર`**: Spawns an event-driven WebSocket server on the designated TCP port.
- **`tarang_ws_client(url)` / `તરંગ_ક્લાયન્ટ`**: Connects to remote or local WebSocket endpoints with automatic reconnects.
- **`tarang_ws_send(client, message)` / `તરંગ_મોકલો`**: Transmits UTF-8 text or binary payloads across open sockets.
- **`tarang_ws_broadcast(channel, message)` / `તરંગ_પ્રસારણ`**: Broadcasts messages to all connected peers subscribed to a channel.
- **`tarang_sse_stream(res, event, data)` / `તરંગ_પ્રવાહ`**: Streams HTTP/1.1 and HTTP/2 Server-Sent Events (`text/event-stream`).
- **`tarang_room_join(client, room)` / `તરંગ_રૂમ_જોડાઓ`**: Joins a multiplexed room or tenant channel.
- **`tarang_room_leave(client, room)` / `તરંગ_રૂમ_છોડો`**: Leaves an existing room channel.
- **CLI Subcommand**: `gujarati tarang:serve [port]` launches a high-throughput WebSocket broadcast gateway.

### 2. 🌉 Setu (સેતુ) — Enterprise GraphQL Runtime & High-Throughput DataLoader
Native Schema Definition Language (SDL) GraphQL parser, resolver execution, and batch loading:
- **`setu_schema(type_defs, resolvers)` / `સેતુ_યોજના`**: Compiles GraphQL SDL into a memory-efficient executable schema.
- **`setu_query(schema, query_string)` / `સેતુ_પ્રશ્ન`**: Resolves GraphQL queries with nested object selection sets.
- **`setu_mutation(schema, mutation_string)` / `સેતુ_રૂપાંતરણ`**: Executes state-mutating GraphQL operations with transactional safety.
- **`setu_subscription(schema, sub_string, callback)` / `સેતુ_સબ્સ્ક્રિપ્શન`**: Real-time reactive subscriptions hooked to Tarang WebSockets.
- **`setu_graphiql_html()` / `સેતુ_ગ્રાફીકલ`**: Embedded interactive GraphiQL IDE for query composition and schema exploration.
- **`setu_dataloader(batch_fn)` / `સેતુ_લોડર`**: Solves $N+1$ query problems with memoization and batched backend dispatch.
- **`setu_federation(services)` / `સેતુ_ફેડરેશન`**: Apollo-compatible distributed schema federation aggregator.
- **CLI Subcommand**: `gujarati setu:schema <file.graphql>` validates and audits GraphQL schemas.

### 3. 🔍 Kasauti v2 (કસોટી v2) — Visual Regression, Network Mocking & Mobile Device Emulation
Advanced testing infrastructure extending Kasauti Dusk into modern frontend and visual verification:
- **`kasauti_diff_visual(img1, img2, threshold)` / `કસોટી_દ્રશ્ય_તફાવત`**: Pixel-by-pixel perceptual image diffing with configurable mismatch tolerance.
- **`kasauti_mock_http(url, mock_response)` / `કસોટી_મોક_નેટવર્ક`**: Stubs network endpoints with deterministic mock payloads.
- **`kasauti_intercept_request(matcher, handler)` / `કસોટી_અવરોધ`**: Intercepts, mutates, or verifies in-flight network requests.
- **`kasauti_emulate_device(device_name)` / `કસોટી_ઉપકરણ`**: Emulates popular mobile and tablet viewport viewports (e.g. `Pixel 8`, `iPhone 15`).
- **`kasauti_lighthouse_audit(url)` / `કસોટી_ઓડિટ`**: Analyzes performance, accessibility, best practices, and SEO.
- **`kasauti_har_export(session, file)` / `કસોટી_હાર`**: Exports complete network waterfall timelines in standard HTTP Archive format.
- **CLI Subcommands**: `gujarati kasauti:visual` runs regression diff suites; `gujarati kasauti:mock` boots mock test server.

### 4. 🛡️ Suraksha v2 (સુરક્ષા v2) — OAuth2 Providers, Enterprise RBAC & Hardware Secret Vault
Production security layer designed for multi-tenant applications and enterprise compliance:
- **`suraksha_oauth_provider(config)` / `સુરક્ષા_ઓઓથ`**: Native OAuth2 / OIDC authentication provider (Google, GitHub, Auth0).
- **`suraksha_rbac_role(name, permissions)` / `સુરક્ષા_ભૂમિકા`**: Role-based access control with granular permission matrices.
- **`suraksha_rbac_can(role, permission)` / `સુરક્ષા_પરવાનગી`**: Evaluates role authorization with wildcard permission matching.
- **`suraksha_vault_encrypt(key, payload)` / `સુરક્ષા_તિજોરી_એન્ક્રિપ્ટ`**: AES-256-GCM authenticated encryption for sensitive payloads.
- **`suraksha_vault_decrypt(key, ciphertext)` / `સુરક્ષા_તિજોરી_ડિક્રિપ્ટ`**: Authenticated decryption with tamper detection.
- **`suraksha_api_key_rotate(key_id)` / `સુરક્ષા_કી_રોટેટ`**: Cryptographic zero-downtime API key rotation.
- **CLI Subcommands**: `gujarati vault:seal` and `gujarati vault:unseal` for secure local secret management.

---

## 🛡️ The 545 Tests Milestone (100% Pass Rate)
GujaratiLang v2.8.0 elevates automated testing to **545 automated test suites**:
- **533 Language & Subsystem Test Suites**: Comprehensive coverage spanning core lexing, parsing, AST execution, Eloquent ORM, Blade templating, Redis-style caching, Pub/Sub, Desktop GUI, 2D Canvas, Android Camera/Sensors, AOT Compiler, C-FFI, Kasauti browser automation, Mandhan migrations, Garvi web framework, Samvad AI agents, Saransh packaging, and the new v2.8.0 Tarang, Setu, Kasauti v2, and Suraksha v2 suites.
- **12 Production Example Programs**: Fibonacci, Temperature Converter, Inventory, Stock, Calculator, String Utils, CSV Parser, Math Suite, Text Filter, Report Generator, Invoice Generator, and Random Game.
- **100% CTest Pass Rate** across Windows x64, Linux x64, macOS x64, and macOS ARM64.

---

## 🚀 The Road Ahead: Releases v2.9.0 & v3.0.0
- **v2.9.0**: Pravah (Kafka/NATS streaming), Shilp (Wasm SIMD Canvas GUI), Vidyut (Distributed Raft MapReduce), and Yantra (LLM Embeddings/Vector Search) — *30 Points*.
- **v3.0.0 Mega Release**: GujaratiOS Sovereign Runtime Kernel, Universal Multi-Platform Engine (Wasm, Mobile, Embedded MCU), Enterprise Mesh Architecture, Autonomous Multi-Agent Swarms, and LTS 2030 Guarantees — *50 Points*.

---

## 🌐 Live Website & Playground
The official portal, chronicle, and interactive playground are updated and deployed live:
- **Official Website**: [https://gujaratilang.hp-square.com/](https://gujaratilang.hp-square.com/)
- **Release Chronicle**: [https://gujaratilang.hp-square.com/history.html](https://gujaratilang.hp-square.com/history.html)
