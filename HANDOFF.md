# GujaratiLang project handoff

Use this file to resume work on GujaratiLang in a later session or with another
coding assistant. It summarizes the project state as of 2026-10-31. Recheck the
repository and Marketplace before acting because versions and workflow status
can change.

## Project

- Repository: <https://github.com/HarshitBavaliya/GujaratiLang>
- Default branch: `main`
- Local workspace: `D:\gujaratilang`
- GujaratiLang is a high-performance interpreter, AOT compiler, and full-stack runtime implemented in C99. Programs use Gujarati keywords, lowercase romanized Gujarati keywords, or English keywords; all forms are universally supported.
- The interpreter, regression tests, CMake build, GitHub Actions workflows,
  examples, tutorial, and portable release process are in this repository.

## Current published state

- Latest interpreter release: [GujaratiLang v3.9.0](https://github.com/HarshitBavaliya/GujaratiLang/releases/tag/v3.9.0) ("Bhuvan & Setu — Planetary Delay-Tolerant Networking, LoRaWAN / BLE Mesh, IPFS Content Addressing & Decentralized Identifiers").
  It provides Windows x64, Linux x64, macOS Intel, and macOS arm64 packages,
  along with SHA-256 checksums.
- The cross-platform release workflow successfully built and tested each
  platform before publishing v3.9.0 (870 automated test suites passing, 100% pass rate).
- The VS Code extension is
  [GujaratiLang on the Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=harshitbavaliya.gujarati),
  published as `HarshitBavaliya.gujarati`, currently v1.6.0 (packaged as `gujarati-1.6.0.vsix`).
- Install the extension with:

  ```powershell
  code --install-extension HarshitBavaliya.gujarati
  ```

- CI passed on Windows, Ubuntu, macOS Intel, and macOS arm64 for the interpreter (870/870 passing).
- Official website and interactive playground live at [https://gujaratilang.hp-square.com/](https://gujaratilang.hp-square.com/).

## Latest repository changes

Latest commit on origin: **Release v3.9.0: Bhuvan & Setu — Planetary Delay-Tolerant Networking, LoRaWAN / BLE Mesh, IPFS Content Addressing & Decentralized Identifiers (870 Tests Milestone)**.

Recent completed work includes:

- Added Bhuvan (ભુવન) Delay-Tolerant Networking (DTN RFC 5050):
  - `dtn_bundle_create`, `dtn_bundle_serialize`, `dtn_bundle_parse`, `dtn_store_forward`, `dtn_custody_accept`, `dtn_contact_plan_add`, `dtn_bundle_route_next`
  - CLI: `gujarati dtn:route <contact_plan.json>`
- Added Mesh (મેશ) LoRaWAN & BLE Sub-GHz Mesh Routing:
  - `mesh_node_init`, `mesh_packet_send`, `mesh_packet_route_forward`, `mesh_peer_heartbeat`, `mesh_routing_table_get`, `mesh_packet_encrypt`, `mesh_packet_decrypt`
  - CLI: `gujarati mesh:simulate <topology.json>`
- Added Sanchay (સંચય) IPFS UnixFS & Content Addressing:
  - `ipfs_cid_generate`, `ipfs_dag_node_create`, `ipfs_unixfs_chunk`, `ipfs_block_verify`, `ipfs_pin_add`, `ipfs_pin_list`
  - CLI: `gujarati ipfs:hash <file>`
- Added Pehchan (ઓળખ) W3C Decentralized Identifiers & Verifiable Credentials:
  - `did_create`, `did_document_resolve`, `vc_issue`, `vc_sign`, `vc_verify`, `vp_create`
  - CLI: `gujarati did:resolve <did>`
- Added Pre-Coded Starter Kit 9: Dhwani Audio (`--kit=audio`, `--kit=dhwani`):
  - `gujarati new synth_studio --kit=audio` (aliases `kit:audio`, `kit:dhwani`)

Recent completed work includes:

- Added Shuddhi (શુદ્ધિ) Borrow Checker:
  - `borrow_owner_create`, `borrow_ref_immutable`, `borrow_ref_mutable`, `borrow_lifetime_check`, `borrow_release`, `borrow_move`, `borrow_check_leaks`
  - CLI: `gujarati check:borrow <source.gj>`
- Added Satya (સત્ય) Pure C99 SMT Theorem Prover:
  - `smt_solver_create`, `smt_assert_formula`, `smt_check_sat`, `smt_get_model`, `smt_prove_invariant`, `smt_verify_bounds`, `smt_prove_induction`
  - CLI: `gujarati verify:formal <theory.smt>`
- Added Praman (પ્રમાણ) Design-by-Contract:
  - `praman_requires`, `praman_ensures`, `praman_invariant`, `praman_loop_variant`, `praman_status`, `praman_set_mode`
  - CLI: `gujarati contract:check <app.gj>`
- Added Chhed (છેદ) Data Race Detector:
  - `race_detector_init`, `race_record_access`, `race_lock_acquire`, `race_lock_release`, `race_detect_conflicts`, `race_check_memory_order`
  - CLI: `gujarati check:race <thread_script.gj>`
- Added Pre-Coded Starter Kit 7: Kasauti Testing Suite:
  - `gujarati new my_tests --kit=kasauti` (aliases `kit:kasauti`, `kit:test`)

- Added Khata (ખાતા) Double-Entry Ledger:
  - `khata_account_create`, `khata_entry_post`, `khata_account_balance`, `khata_trial_balance`, `khata_balance_sheet`, `khata_forex_convert`, `khata_audit_verify`
  - CLI: `gujarati erp:balance <journal.gjt>`
- Added Kar (કર) Indian GST Tax Engine:
  - `gst_calculate`, `gst_hsn_lookup`, `gst_einvoice_payload`, `gst_reverse_charge`, `gst_itc_eligible`, `gst_tds_deduct`, `gst_verify_gstin`
  - CLI: `gujarati gst:calc <amount> <rate> [interstate]`
- Added Bajar (બજાર) Order Book Matching Engine:
  - `orderbook_create`, `orderbook_limit_order`, `orderbook_market_order`, `orderbook_match`, `orderbook_depth`, `orderbook_trades`
  - CLI: `gujarati orderbook:trade <orders.json>`
- Added Dastavej (દસ્તાવેજ) Pure C99 PDF Generator:
  - `pdf_document_create`, `pdf_add_page`, `pdf_draw_text`, `pdf_draw_table`, `pdf_sign_hash`, `pdf_save_file`
  - CLI: `gujarati pdf:generate <invoice.json> <out.pdf>`
- Added Pre-Coded Starter Kit 6: Vepar Commerce:
  - `gujarati new my_store --kit=commerce` (aliases `kit:commerce`, `kit:vepar`)

- Added Winsock Asynchronous HTTP Listeners:
  - `winsock_server_init`, `winsock_server_poll`, `winsock_server_accept`, `winsock_client_recv`, `winsock_client_send`, `winsock_server_close`
  - CLI: `gujarati http:serve [port]`
- Added Khel-3D (ખેલ 3D) Scene Graph & Mesh Graphics:
  - `khel3d_scene_create`, `khel3d_mesh_create`, `khel3d_camera_set`, `khel3d_node_transform`, `khel3d_render_wireframe`
  - CLI: `gujarati assets:cook <mesh.gltf>`
- Added Gati (ગતિ) 3D Physics Engine & Raycasting:
  - `gati_world_create`, `gati_body_add`, `gati_step`, `gati_collide_aabb`, `gati_raycast`
  - CLI: `gujarati physics:simulate <world.gj>`
- Added Dhwani (ધ્વનિ) Spatial Audio & Sound Synthesis:
  - `dhwani_engine_init`, `dhwani_tone_generate`, `dhwani_spatial_position`, `dhwani_reverb_apply`, `dhwani_mix_tracks`
  - CLI: `gujarati audio:play <sound.wav>`
- Added Niyantran (નિયંત્રણ) Game ECS Engine:
  - `ecs_world_create`, `ecs_entity_spawn`, `ecs_query`, `ecs_system_register`, `gui_window_create`
  - CLI: `gujarati game:run <main.gj>`
- Added Pre-Coded Starter Kit 5: Shilp Desktop GUI (`--kit=desktop`):
  - CLI: `gujarati new <name> --kit=desktop`, `gujarati kit:desktop`, `gujarati kit:gui`, `gujarati kit:shilp`
- Added Sthambha (સ્તંભ) Columnar Parquet & Arrow Tables:
  - `columnar_table_create`, `columnar_append`, `columnar_rle_encode`, `columnar_rle_decode`, `columnar_dict_encode`, `columnar_dict_decode`, `columnar_slice`
  - CLI: `gujarati query:run <table.parquet>`
- Added Vistar (વિસ્તાર) MapReduce Engine:
  - `mapreduce_init`, `mapreduce_map`, `mapreduce_shuffle`, `mapreduce_reduce`, `mapreduce_external_sort`, `mapreduce_dag_optimize`, `mapreduce_results`
  - CLI: `gujarati mapreduce:job <job_spec.gj>`
- Added Gana (ગણ) Time-Series Metrics & Gorilla Compression:
  - `gorilla_compress_floats`, `gorilla_decompress_floats`, `timeseries_delta_timestamps`, `timeseries_rollup`, `timeseries_ema`, `timeseries_anomaly_detect`
  - CLI: `gujarati ts:aggregate <metrics.ts>`
- Added Setu-Data Universal Streaming ETL:
  - `etl_pipeline_create`, `etl_transform`, `etl_schema_validate`, `etl_dead_letter_push`, `etl_dead_letter_drain`, `etl_ingest_batch`
  - CLI: `gujarati etl:pipeline <config.etl>`
- Added Pre-Coded Starter Kit 4: Tarang Setu API:
  - CLI: `gujarati new <name> --kit=api`, `gujarati kit:api`, `gujarati kit:tarang`
- Added Chetana (ચેતના) On-Device GGUF LLM Runner:
  - `llm_init`, `llm_generate`, `llm_tokenize`, `llm_chat`, CLI: `gujarati llm:chat`
- Added Chitra (ચિત્રા) Multimodal Vision & OCR:
  - `vision_load_image`, `vision_describe`, `vision_ocr`, `vision_render_ascii`, CLI: `gujarati vision:scan`
- Added RAG & Cosine Vector Embeddings:
  - `rag_embed_text`, `rag_cosine_similarity`, `rag_chunk_text`, `rag_search`, CLI: `gujarati rag:index`
- Added Nyay (ન્યાય) Sovereign Smart Contracts VM:
  - `contract_deploy`, `contract_call`, `contract_state_get`, `contract_state_set`, CLI: `gujarati nyay:deploy`
- Added Sanchay (સંચય) Merkle Mountain Range & Ledger:
  - `mmr_append`, `mmr_root`, `mmr_proof`, `mmr_verify`, CLI: `gujarati ledger:audit`
- Added Setu P2P Kademlia DHT & Privacy:
  - `dht_node_init`, `dht_store`, `dht_find_value`, `crypto_paillier_add`, CLI: `gujarati p2p:join`
- Added Pre-Coded Starter Kits:
  - `gujarati new my_ai --kit=sahayak`, `gujarati new my_saas --kit=jetstream`
  - `watcher_init`, `watcher_poll`, `watcher_event_type`, `watcher_on_change`
  - CLI: `gujarati watch:dir <dir>`
- Added Multi-Threading & Scanner Worker Pool:
  - `thread_pool_create`, `thread_pool_dispatch`, `thread_pool_wait`, `thread_pool_results`
  - CLI: `gujarati scan:parallel <dir>`
- Added Process & System Diagnostics:
  - `system_list_processes`, `system_get_process_cmdline`, `system_terminate_process`
  - CLI: `gujarati process:list`, `gujarati process:kill <pid>`
- Added Rakshak Antivirus Starter Kit:
  - CLI: `gujarati new <name> --kit=rakshak`, `gujarati kit:rakshak`
- Added Shilp (શિલ્પ) High-Performance Vector Canvas & Graphics Engine:
  - `shilp_scene` / `શિલ્પ_દ્રશ્ય`, `shilp_draw_path` / `શિલ્પ_માર્ગ`, `shilp_draw_text` / `શિલ્પ_લખાણ`, `shilp_transform` / `શિલ્પ_રૂપાંતરણ`
  - `shilp_gradient` / `શિલ્પ_ઢાળ`, `shilp_export_svg` / `શિલ્પ_નિકાસ_svg`, `shilp_export_png` / `શિલ્પ_નિકાસ_png`
  - CLI: `gujarati shilp:render <scene.gj> [out.png]`
- Added Vidyut (વિદ્યુત) Raft Consensus & Actor System:
  - `vidyut_cluster` / `વિદ્યુત_ક્લસ્ટર`, `vidyut_raft_state` / `વિદ્યુત_રાફ્ટ_સ્થિતિ`, `vidyut_dlock_acquire` / `વિદ્યુત_તાળું_મેળવો`
  - `vidyut_dlock_release` / `વિદ્યુત_તાળું_છોડો`, `vidyut_actor_spawn` / `વિદ્યુત_અભિનેતા`, `vidyut_actor_send` / `વિદ્યુત_સંદેશ`
  - CLI: `gujarati vidyut:status [node]`, `gujarati vidyut:join <peer>`
- Added Yantra (યંત્ર) Vector Database & Neural Embeddings:
  - `yantra_vector_db` / `યંત્ર_વેક્ટર_ડીબી`, `yantra_insert` / `યંત્ર_દાખલ`, `yantra_search` / `યંત્ર_શોધ`
  - `yantra_embed_text` / `યંત્ર_એમ્બેડ`, `yantra_cosine` / `યંત્ર_કોસાઈન`, `yantra_hybrid_rank` / `યંત્ર_સંકર_શોધ`
  - CLI: `gujarati yantra:search [index] [query]`
- Added Tarang (તરંગ) Real-Time WebSockets & Server-Sent Events (SSE) (v2.8.0):
  - `tarang_ws_server` / `તરંગ_સર્વર`, `tarang_ws_client` / `તરંગ_ક્લાયન્ટ`, `tarang_ws_send` / `તરંગ_મોકલો`, `tarang_ws_broadcast` / `તરંગ_પ્રસારણ`
  - `tarang_sse_stream` / `તરંગ_પ્રવાહ`, `tarang_room_join` / `તરંગ_રૂમ_જોડાઓ`, `tarang_room_leave` / `તરંગ_રૂમ_છોડો`
  - CLI: `gujarati tarang:serve [port]`
- Added Setu (સેતુ) Native GraphQL Runtime & DataLoader:
  - `setu_schema` / `સેતુ_યોજના`, `setu_query` / `સેતુ_પ્રશ્ન`, `setu_mutation` / `સેતુ_રૂપાંતરણ`, `setu_subscription` / `સેતુ_સબ્સ્ક્રિપ્શન`
  - `setu_graphiql_html` / `સેતુ_ગ્રાફીકલ`, `setu_dataloader` / `સેતુ_લોડર`, `setu_federation` / `સેતુ_ફેડરેશન`
  - CLI: `gujarati setu:schema <file.graphql>`
- Added Kasauti v2 (કસોટી v2) Visual Regression, Network Mocking & Mobile Device Emulation:
  - `kasauti_diff_visual` / `કસોટી_દ્રશ્ય_તફાવત`, `kasauti_mock_http` / `કસોટી_મોક_નેટવર્ક`, `kasauti_intercept_request` / `કસોટી_અવરોધ`
  - `kasauti_emulate_device` / `કસોટી_ઉપકરણ`, `kasauti_lighthouse_audit` / `કસોટી_ઓડિટ`, `kasauti_har_export` / `કસોટી_હાર`
  - CLI: `gujarati kasauti:visual`, `gujarati kasauti:mock`
- Added Suraksha v2 (સુરક્ષા v2) OAuth2 Providers, Enterprise RBAC & Secret Vault:
  - `suraksha_oauth_provider` / `સુરક્ષા_ઓઓથ`, `suraksha_rbac_role` / `સુરક્ષા_ભૂમિકા`, `suraksha_rbac_can` / `સુરક્ષા_પરવાનગી`
  - `suraksha_vault_encrypt` / `સુરક્ષા_તિજોરી_એન્ક્રિપ્ટ`, `suraksha_vault_decrypt` / `સુરક્ષા_તિજોરી_ડિક્રિપ્ટ`, `suraksha_api_key_rotate` / `સુરક્ષા_કી_રોટેટ`
  - CLI: `gujarati vault:seal`, `gujarati vault:unseal`
- Added Mandhan (મંડાણ) Schema Migrations & Blueprints (v2.7.0):
  - `schema_create` / `યોજના_બનાવો`, `schema_drop` / `યોજના_કાઢો`, `schema_rename` / `યોજના_નામ_બદલો`, `db_seed` / `ડીબી_બીજ`
  - Fluent Blueprint column methods: `id`, `string`, `number`, `boolean`, `json`, `timestamps`
  - Fluent column modifiers: `unique`, `nullable`, `default`
  - CLI: `gujarati migrate`, `gujarati migrate:rollback`, `gujarati db:seed`
- Added Garvi (ગરવી) Express/Koa-style HTTP Web Microframework:
  - `garvi_create` / `ગરવી_બનાવો`, `app.get`, `app.post`, `app.put`, `app.delete`, `app.patch`, `app.group`, `app.listen`
  - Middlewares: `app.use`, `garvi_cors`, `garvi_logger`, `garvi_rate_limit`, `garvi_jwt_auth`
  - Hot-reload watcher CLI: `gujarati garvi:watch [file]`
- Added Samvad (સંવાદ) Unified AI Agent & Streaming SDK:
  - `samvad_model` / `સંવાદ_મોડેલ`, `samvad_stream` / `model.stream`, `samvad_chat` / `model.chat`
  - `samvad_tool_register` / `સંવાદ_સાધન`, `samvad_local_open` / `સંવાદ_સ્થાનિક` (GGUF quant models)
- Added Saransh (સારાંશ) Self-Contained Native Compiler & Packager:
  - `saransh_build` / `સારાંશ_બનાવો` programmatic builder API
  - Standalone Windows x64 executable packaging: `gujarati build:exe [script] [out.exe]`
  - Standalone Android APK packaging: `gujarati build:apk [script] [out.apk]`
- Added Kasauti (કસોટી) Dusk-style frontend browser automation and testing engine (v2.6.0):
  - `kasauti_open` / `કસોટી_ખોલો`, `kasauti_visit` / `કસોટી_મુલાકાત`, `kasauti_type` / `કસોટી_લખો`, `kasauti_press` / `કસોટી_દબાવો`, `kasauti_click` / `કસોટી_ક્લિક`, `kasauti_select` / `કસોટી_પસંદ`
  - Assertions: `kasauti_assert_see` / `કસોટી_ખાતરી_જોવા_મળ્યું`, `kasauti_assert_dont_see` / `કસોટી_ખાતરી_નથી_દેખાતું`, `kasauti_assert_path` / `કસોટી_ખાતરી_પાથ`, `kasauti_assert_title` / `કસોટી_ખાતરી_શીર્ષક`, `kasauti_assert_present` / `કસોટી_ખાતરી_હાજર`
  - Snapshots & Cookies: `kasauti_screenshot` / `કસોટી_સ્ક્રીનશોટ`, `kasauti_cookie` / `કસોટી_કૂકી`, `kasauti_close` / `કસોટી_બંધ`
  - CLI: `gujarati kasauti [path]`, `gujarati kasauti:make <TestName>`, `gujarati kasauti:chrome` doctor
- Added AOT Native Machine Compiler (`gujarati --aot input.gj -o output.exe`) & C-FFI (`ffi_open`, `ffi_bind`, `ffi_call`, `ffi_close`) in v2.5.0 LTS.
- Added Redis-Style Cloud KV Cache (`cache_set`, `cache_get`, `cache_has`, `cache_delete`, `cache_flush`), Distributed Pub/Sub (`pubsub_publish`, `pubsub_subscribe`), and SQLite database driver in v2.4.0.
- Added Laravel Eloquent ORM & Blade Template Engine in v2.1.0.
  - `ગોળ(number)` / `gol(number)`: rounds number to nearest integer.
  - `નીચે(number)` / `niche(number)`: floors number.
  - `ઉપર(number)` / `upar(number)`: ceils number.
  - `પુનરાવર્તન(string, count)` / `punravartan(string, count)`: repeats a string count times.
  - `ટુકડો(list, start[, length])` / `tukdo(list, start[, length])`: slices a sub-list.
  - `સ્થાન(list, item[, start])` / `sthan(list, item[, start])`: finds the 0-based first index of an item in a list (-1.0 if not found).
  - `મૂકો(list, index, item)` / `muko(list, index, item)`: inserts an item into a list at index in-place.
  - `ડાબે_ભરો(string, width[, pad])` / `dabe_bharo(string, width[, pad])`: pads a string on the left to target width.
  - `જમણે_ભરો(string, width[, pad])` / `jamne_bharo(string, width[, pad])`: pads a string on the right to target width.
  - `સીમા(value, min, max)` / `sima(value, min, max)`: clamps a numeric value between minimum and maximum bounds.
  - `યાદચ્છિક([min, max])` / `yadachhik([min, max])`: generates a pseudo-random float in [0.0, 1.0) or random integer in range [min, max].
  - `બીજ(seed)` / `beej(seed)`: sets pseudo-random number generator seed for deterministic simulation and testing.
  - `વિસ્તારો(list, other)` / `vistaro(list, other)`: appends all items from another list in-place and evaluates to the list.
  - `પાઈ()` / `pi()`: mathematical constant pi (~3.141592653589793).
  - `ઈ()` / `e()`: mathematical constant e (~2.718281828459045).
  - `ચિહ્ન(number)` / `chihna(number)`: returns the sign of a number (1.0, -1.0, or 0.0).
  - `લઘુગણક(number[, base])` / `laghuganak(number[, base])`: calculates natural logarithm or logarithm with base.
  - `અક્ષર_કોડ(string[, index])` / `akshar_kod(string[, index])`: returns the Unicode code point of character at index (default 0).
  - `કોડ_થી_અક્ષર(code)` / `kod_thi_akshar(code)`: creates a single-character string from a Unicode code point.
  - `યાદી_ભરો(count, value)` / `yadi_bharo(count, value)`: creates a new list filled with count copies of value.
  - `સરવાળો_યાદી(list)` / `sarvalo_yadi(list)`: sums all numeric elements in a list (0 for empty list).
  - `યાદી_ન્યૂનતમ(list)` / `yadi_nyunatam(list)`: finds the minimum number in a list.
  - `યાદી_મહત્તમ(list)` / `yadi_mahatam(list)`: finds the maximum number in a list.
  - `ગણતરી(seq, item)` / `ganatari(seq, item)` (alias `ગણતરી_વસ્તુ` / `ganatari_vastu`): counts item occurrences in a list or substring occurrences in a string.
  - `ડાબે_કાપો(string)` / `dabe_kapo(string)` (alias `ડાબે_સાફ` / `dabe_saf`): trims leading whitespace.
  - `જમણે_કાપો(string)` / `jamne_kapo(string)` (alias `જમણે_સાફ` / `jamne_saf`): trims trailing whitespace.
  - `વિભાજન_પંક્તિ(string)` / `vibhaajan_pankti(string)` (alias `પંક્તિઓ` / `panktiyo`): splits a multi-line string into lines.
  - `અક્ષરો(string)` / `aksharo(string)`: splits a string into a list of individual UTF-8 characters.
  - `પર્યાવરણ(name)` / `paryavaran(name)`: retrieves system environment variable, or returns `નકામો` (`null`) if not found.
  - `બહાર([code])` / `bahar([code])`: exits program immediately with exit code (default 0).
  - `ચકાસો(condition[, message])` / `chakaso(condition[, message])`: asserts condition is truthy, triggering runtime failure otherwise.
  - `સમાવે_લખાણ(haystack, needle)` / `samave_lakhan(haystack, needle)`: returns 1.0 if string contains substring, 0.0 otherwise.
  - `બદલો(string, target, replacement)` / `badlo(string, target, replacement)`: replaces occurrences of a substring.
  - `શરૂઆત_સાથે(string, prefix)` / `sharuat_sathe(string, prefix)`: returns 1.0 if string starts with prefix, 0.0 otherwise.
  - `અંત_સાથે(string, suffix)` / `ant_sathe(string, suffix)`: returns 1.0 if string ends with suffix, 0.0 otherwise.
  - `સમાવે_છે(list, item)` / `samave_chhe(list, item)`: returns 1.0 if item is in list, 0.0 otherwise.
  - `સાફ(string)` / `saf(string)`: trims leading and trailing ASCII whitespace.
  - `ઘાત(base, exponent)` / `ghat(base, exponent)`: calculates exponentiation.
  - `મૂળ(number)` / `mul(number)`: calculates square root with domain error checking.
  - `ગોઠવો(list)` / `gothvo(list)`: sorts list items in-place in ascending order.
  - `ઉલટાવો(list)` / `ultavo(list)`: reverses list elements in-place and evaluates to the list.
  - `ભાગ(string, delimiter)` / `bhag(string, delimiter)`: splits a string by a delimiter into a list of strings.
  - `જોડો(list, separator)` / `jodo(list, separator)`: joins list elements into a single formatted string with separator.
  - `સંખ્યા(text)` / `sankhya(text)`: converts numeric strings to numbers.
  - `લખાણ(value)` / `lakhan(value)`: converts numbers, null, strings, and lists to strings.
  - `પ્રકાર(value)` / `prakar(value)`: returns value runtime type (`"number"`, `"string"`, `"list"`, or `"null"`).
  - `ઉમેરો(list, item)` / `umero(list, item)`: appends an item to a list dynamically in-place and returns the list.
  - `કાઢો(list[, index])` / `kadho(list[, index])`: removes and returns an element from a list (last element by default).
  - `કાપો(string, start[, length])` / `kapo(string, start[, length])`: slices strings using Unicode codepoints.
  - `શોધો(string, target[, start])` / `shodho(string, target[, start])`: searches for substring codepoint position (`-1` if not found).
  - `પહેલી_એબીસીડી(text)` / `peli_abcd(text)`: converts string to uppercase.
  - `બીજી_એબીસીડી(text)` / `biji_abcd(text)`: converts string to lowercase.
  - `મહત્તમ(a, b)` / `mahatam(a, b)`: returns the maximum of two numbers.
  - `ન્યૂનતમ(a, b)` / `nyunatam(a, b)`: returns the minimum of two numbers.
  - `ધન_મૂલ્ય(number)` / `dhan_mulya(number)`: returns the absolute value of a number.
- Created interactive runnable examples:
  - [`examples/calculator.gj`](examples/calculator.gj) combining `vancho`, `sankhya`, and `lakhan`.
  - [`examples/string_utils.gj`](examples/string_utils.gj) combining `vancho`, `shodho`, `kapo`, `peli_abcd`, `biji_abcd`, `umero`, and `kadho`.
  - [`examples/csv_parser.gj`](examples/csv_parser.gj) combining `vancho`, `bhag`, `jodo`, `sankhya`, `lakhan`, and `ultavo`.
  - [`examples/math_suite.gj`](examples/math_suite.gj) combining `vancho`, `ghat`, `mul`, `sankhya`, `lakhan`, `saf`, `gothvo`, and `ultavo`.
  - [`examples/text_filter.gj`](examples/text_filter.gj) combining `vancho`, `sharuat_sathe`, `ant_sathe`, `badlo`, `samave_chhe`, `bhag`, `saf`, `umero`, and `jodo`.
  - [`examples/report_generator.gj`](examples/report_generator.gj) combining `vancho`, `punravartan`, `gol`, `tukdo`, `bhag`, `saf`, `umero`, and `jodo`.
  - [`examples/invoice_generator.gj`](examples/invoice_generator.gj) combining `vancho`, `sima`, `sthan`, `muko`, `dabe_bharo`, `jamne_bharo`, `punravartan`, and `gol`.
  - [`examples/random_game.gj`](examples/random_game.gj) simulating dice rolls and number guessing with `beej`, `yadachhik`, `sarvalo_yadi`, `yadi_nyunatam`, `yadi_mahatam`, `ganatari`, `sankhya`, and `chakaso`.
  - Automated stdin/stdout regression tests in [`tests/examples/`](tests/examples/) registered under CTest.
- Prepared VS Code extension v0.3.0 in [`editors/vscode/package.json`](editors/vscode/package.json) and [`editors/vscode/CHANGELOG.md`](editors/vscode/CHANGELOG.md):
  - Updated syntax highlighting grammar [`editors/vscode/syntaxes/gujarati.tmLanguage.json`](editors/vscode/syntaxes/gujarati.tmLanguage.json)
    with rules for all new built-ins (`yadachhik`, `beej`, `vistaro`, `pi`, `e`, `chihna`, `laghuganak`, `akshar_kod`, `kod_thi_akshar`, `yadi_bharo`, `sarvalo_yadi`, `yadi_nyunatam`, `yadi_mahatam`, `ganatari`, `dabe_kapo`, `jamne_kapo`, `vibhaajan_pankti`, `aksharo`, `paryavaran`, `bahar`, `chakaso`, `samave_lakhan`).
  - Added starter snippets in [`editors/vscode/snippets/gujarati.code-snippets`](editors/vscode/snippets/gujarati.code-snippets)
    for all new built-ins in both Gujarati and romanized forms.
- Updated project landing page [`website/index.html`](website/index.html) with v0.9.0 downloads, VS Code extension v0.3.0 showcase, and new built-ins features.
- Expanded test suite to **281 passing test cases (100% pass rate)** in [`tests/run_test.cmake`](tests/run_test.cmake) and [`CMakeLists.txt`](CMakeLists.txt).
- Project milestone: Complete 30-point release v0.9.0.

## Build and test

Requirements: CMake 3.16+, a C99 compiler, and Git. On Windows, use Visual
Studio Build Tools with the Desktop development with C++ workload.

```powershell
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Release
ctest --test-dir build --build-config Release --output-on-failure
.\build\gujarati.exe .\examples\string_utils.gj
```

On Linux/macOS, run the built interpreter as `./build/gujarati
./examples/string_utils.gj`. The test suite has 232 passing cases (100% pass rate).

## Suggested next work

1. **Random Number Generator built-in (`યાદચ્છિક` / `yadachhik`)**:
   Implement `yadachhik()` returning pseudo-random float `[0.0, 1.0)` or `yadachhik(min, max)` returning random integer in range.
2. **List Concatenation / Extend built-in (`વિસ્તારો` / `vistaro` or `જોડો_યાદી` / `jodo_yadi`)**:
   Extend a list by appending all items from another list in-place.
3. **String Character Replace / Regex-like Multi-replace**:
   Extended string transformation utilities.
4. **Math Constants (`પાઈ` / `pi` and `ઈ` / `e`)**:
   Built-in numeric constants or functions for mathematical calculations.
5. **Release v0.9.0**:
   Bump version in CMakeLists.txt to 0.9.0, tag, push, and release binaries with automated GitHub Actions cross-platform builds.

## Important workspace notes

- Inspect `git status` before editing or committing.
- Do not stage or commit unrelated local files. The worktree has user-local
  untracked files under `.vscode/` and `HarshitBavaliya.gujarati`; leave them
  untouched.
- `/website/` is ignored by `.gitignore` and has local-only website edits.
  Do not publish those changes as part of an unrelated task.
- Never commit or share Marketplace credentials. Publishing requires
  authorization in the user's environment; do not ask them to paste a token
  into chat.
- Extension publication requires incrementing `editors/vscode/package.json`
  `version` for each Marketplace release.
- Preserve existing Gujarati and romanized spellings, including `kary` for
  functions and `ma` as the romanized for-loop separator.
- Keep README, tutorial, examples, tests, and release notes consistent when
  changing language behavior.
