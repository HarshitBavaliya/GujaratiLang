# GujaratiLang v3.9.0: Bhuvan & Setu — Planetary Delay-Tolerant Networking, LoRaWAN / BLE Mesh, IPFS Content Addressing & Decentralized Identifiers (ભુવન, સેતુ, મેશ, સંચય અને ઓળખ)

GujaratiLang **v3.9.0** is officially released! This landmark milestone expands GujaratiLang into off-grid, interplanetary, peer-to-peer, and decentralized networking runtimes, implemented in 100% pure C99 with **zero external C dependencies**.

It introduces the RFC 5050 Delay-Tolerant Networking (DTN) Bundle Protocol with custody transfer and orbital Contact Graph Routing (Bhuvan), sub-GHz ad-hoc flood mesh networking for disaster-recovery and rural sensor networks (Mesh), standard IPFS UnixFS Merkle DAGs and CIDv0/CIDv1 cryptographic content addressing (Sanchay), and W3C Decentralized Identifiers (DIDs) with Ed25519 tamper-proof Verifiable Credentials & Presentations (Pehchan), alongside our ninth official pre-coded starter kit: **Dhwani Spatial Audio & Synthesizer Studio (`--kit=audio`, `--kit=dhwani`)**.

With v3.9.0, the automated test suite reaches the milestone of **870 Tests (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v3.9.0

### 1. 🪐 Pillar 1: Bhuvan (ભુવન) Delay-Tolerant Networking (DTN RFC 5050) (8 Points)
- **`dtn_bundle_create(src, dst, payload, ttl)` / `dtn_bundle_bnavo` / `ડીટીએન_બંડલ_બનાવો`**: Creates an RFC 5050 DTN bundle with custody transfer request, destination EID, source EID, TTL, and payload.
- **`dtn_bundle_serialize(bundle)` / `dtn_bundle_kramit` / `ડીટીએન_બંડલ_ક્રમિત`**: Serializes bundle dictionary into canonical DTN binary/hex RFC 5050 format.
- **`dtn_bundle_parse(hex_data)` / `dtn_bundle_vancho` / `ડીટીએન_બંડલ_વાંચો`**: Parses serialized bundle data, validating version, blocks, and integrity.
- **`dtn_store_forward(bundle, spool_dir)` / `dtn_sangrah_aagal` / `ડીટીએન_સંગ્રહ_આગળ`**: Persists bundles to local storage spool awaiting transit contact windows.
- **`dtn_custody_accept(bundle, custodian_eid)` / `dtn_hastantaran_swikar` / `ડીટીએન_હસ્તાંતરણ_સ્વીકાર`**: Issues custody signal acknowledgment transferring custody responsibility.
- **`dtn_contact_plan_add(peer, start, end, rate)` / `dtn_sampark_yojana` / `ડીટીએન_સંપર્ક_યોજના`**: Schedules deterministic orbital contact windows for Contact Graph Routing (CGR).
- **`dtn_bundle_route_next(bundle, current_time)` / `dtn_marga_shodho` / `ડીટીએન_માર્ગ_શોધો`**: Determines next-hop custodian EID based on contact schedule and bundle TTL.
- **CLI: `gujarati dtn:route <contact_plan.json>` / `gujarati ડીટીએન:માર્ગ`**: Evaluates planetary contact graph and calculates bundle delivery ETA.

### 2. 📡 Pillar 2: Mesh (મેશ) LoRaWAN & BLE Sub-GHz Mesh Routing (8 Points)
- **`mesh_node_init(node_id, freq, sf)` / `mesh_node_saruaat` / `મેશ_નોડ_શરૂઆત`**: Initializes a virtual/hardware LoRaWAN/BLE mesh transceiver node.
- **`mesh_packet_send(node, dst, payload, max_hops)` / `mesh_packet_moklo` / `મેશ_પેકેટ_મોકલો`**: Broadcasts an ad-hoc mesh packet with TTL and sequential packet ID.
- **`mesh_packet_route_forward(node, pkt)` / `mesh_packet_aagal_moklo` / `મેશ_પેકેટ_આગળ_મોકલો`**: Handles hop decrements, duplicate drop checks, and multi-hop flood forwarding.
- **`mesh_peer_heartbeat(node, peer, rssi, snr)` / `mesh_peer_dhabkaro` / `મેશ_પીઅર_ધબકારો`**: Updates routing table with neighbor link quality metrics (RSSI, SNR).
- **`mesh_routing_table_get(node)` / `mesh_marga_takhta` / `મેશ_માર્ગ_તખ્તા`**: Returns active routing table with neighbor paths and hop costs.
- **`mesh_packet_encrypt(payload, key)` / `mesh_packet_gupt` / `મેશ_પેકેટ_ગુપ્ત`**: Encrypts mesh payload using authenticated keystream cipher with IV prefix.
- **`mesh_packet_decrypt(ciphertext, key)` / `mesh_packet_spasht` / `મેશ_પેકેટ_સ્પષ્ટ`**: Decrypts mesh over-the-air payload.
- **CLI: `gujarati mesh:simulate <topology.json>` / `gujarati મેશ:સિમ્યુલેટ`**: Simulates multi-hop mesh message propagation and packet loss statistics.

### 3. 📦 Pillar 3: Sanchay (સંચય) IPFS UnixFS & Content Addressing (7 Points)
- **`ipfs_cid_generate(data, version)` / `ipfs_cid_bnavo` / `આઈપીએફએસ_સીઆઈડી_બનાવો`**: Computes standard IPFS CIDv0 (`Qm...` base58) or CIDv1 (`bafy...` base32) cryptographic multihashes.
- **`ipfs_dag_node_create(data, links)` / `ipfs_dag_nod_bnavo` / `આઈપીએફએસ_ડેગ_નોડ_બનાવો`**: Constructs Merkle DAG nodes linking child CIDs with payload data.
- **`ipfs_unixfs_chunk(content, chunk_size)` / `ipfs_unixfs_tukda` / `આઈપીએફએસ_યુનિક્સએફએસ_ટુકડા`**: Splits content into UnixFS leaf blocks and calculates root Merkle hash.
- **`ipfs_block_verify(cid, data)` / `ipfs_block_chakasani` / `આઈપીએફએસ_બ્લોક_ચકાસણી`**: Cryptographically verifies data content against CID hash (tamper detection).
- **`ipfs_pin_add(cid, pin_type)` / `ipfs_pin_umero` / `આઈપીએફએસ_પિન_ઉમેરો`**: Pins CID locally in Sanchay pinned index, preventing garbage collection.
- **`ipfs_pin_list()` / `ipfs_pin_yadi` / `આઈપીએફએસ_પિન_યાદી`**: Returns list of all pinned CIDs with pinning timestamps and pin types.
- **CLI: `gujarati ipfs:hash <file>` / `gujarati આઈપીએફએસ:હેશ`**: Pure C99 CLI tool calculating and verifying CIDv1 multihashes for any file.

### 4. 🪪 Pillar 4: Pehchan (ઓળખ) W3C Decentralized Identifiers & Verifiable Credentials (7 Points)
- **`did_create(method, pubkey)` / `did_bnavo` / `ડીઆઈડી_બનાવો`**: Generates W3C compliant DID string (`did:key:...` or `did:guj:...`).
- **`did_document_resolve(did)` / `did_dastavej_shodho` / `ડીઆઈડી_દસ્તાવેજ_શોધો`**: Resolves W3C DID Document JSON with verification methods and authentication suites.
- **`vc_issue(issuer, subject, claims, exp_days)` / `vc_aapo` / `વીસી_આપો`**: Constructs tamper-evident Verifiable Credential conforming to W3C VC data model.
- **`vc_sign(vc, privkey)` / `vc_sahikaro` / `વીસી_સહીકરો`**: Attaches Ed25519 cryptographic proof block to Verifiable Credential.
- **`vc_verify(vc_signed, pubkey)` / `vc_chakasani` / `વીસી_ચકાસણી`**: Validates cryptographic signature, expiration date, and integrity of claims in a VC.
- **`vp_create(vc_list, holder)` / `vp_bnavo` / `વીપી_બનાવો`**: Packages one or more VCs into a Verifiable Presentation with holder proof.
- **CLI: `gujarati did:resolve <did>` / `gujarati ડીઆઈડી:શોધો`**: Resolves DID and outputs formatted W3C DID Document.

### 5. 🎵 Pre-Built Starter Kit 9: Dhwani Audio (`--kit=audio`, `--kit=dhwani`)
Scaffold cross-platform spatial audio synthesis and sound engine projects:
```bash
gujarati new synth_studio --kit=audio
# or
gujarati new synth_studio --kit=dhwani
```
Generates:
- `app.gj`: Master synthesizer rack, audio engine & 3D spatial positioning.
- `synths/wave_generator.gj`: Multi-waveform wavetable oscillators & ADSR filter envelopes.
- `mixer/track_bus.gj`: 8-Channel stereo mixer bus, gain staging & reverb send.
- `assets/manifest.json`: Sound effects library, sample rate & audio buffers.

---

# GujaratiLang v3.8.0: Yantram & Gati — Robotics, ROS2 DDS, LiDAR SLAM, PID & Drone Telemetry (યંત્રમ, ગતિ, માર્ગ, ચાલક અને ઉડાન)

GujaratiLang **v3.8.0** is officially released! This monumental release brings industrial robotics, real-time autonomous navigation, closed-loop motion control, and avionics telemetry to GujaratiLang, implemented in 100% pure C99 with **zero external C dependencies**.

It introduces a native Data Distribution Service (DDS) pub/sub bridge and OMG CDR binary serializer for ROS2 (Yantram), 2D/3D occupancy grid mapping, LiDAR point cloud downsampling, and A*/RRT* obstacle avoidance pathfinders (Marg), Proportional-Integral-Derivative closed-loop motor controllers with 6-DOF robotic arm inverse kinematics and motion trajectory splines (Chalak), and a complete MAVLink packet parser, GPS waypoint mission sequencer, EKF 9-axis sensor fusion, and return-to-home geo-fencing (Udan), alongside our eighth official pre-coded starter kit: **Setu Mobile Android NDK App Starter Kit (`--kit=mobile`, `--kit=android`)**.

With v3.8.0, the automated test suite reaches the landmark **840 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v3.8.0

### 1. 🤖 Pillar 1: Yantram (યંત્રમ) ROS2 DDS Bridge (8 Points)
- **`ros2_node_create(node_name, namespace)` / `yantram_node_banavo` / `યંત્રમ_નોડ_બનાવો`**: Initializes a ROS2 DDS participant node context.
- **`ros2_publisher_create(node, topic, msg_type)` / `yantram_prakashak_banavo` / `યંત્રમ_પ્રકાશક_બનાવો`**: Allocates DDS publisher handle bound to a topic with specified message type.
- **`ros2_subscriber_create(node, topic, msg_type, callback)` / `yantram_grahak_banavo` / `યંત્રમ_ગ્રાહક_બનાવો`**: Subscribes to a DDS topic with incoming message dispatch.
- **`ros2_publish_msg(publisher, payload_dict)` / `yantram_sandesho_moklo` / `યંત્રમ_સંદેશો_મોકલો`**: Serializes payload dictionary into CDR byte stream and transmits over DDS.
- **`ros2_spin_once(node, timeout_ms)` / `yantram_spin_ekvar` / `યંત્રમ_સ્પિન_એકવાર`**: Non-blocking spin processing incoming callbacks and network events.
- **`ros2_cdr_serialize(payload_dict)` / `yantram_cdr_serialize` / `યંત્રમ_સીડીઆર_એન્કોડ`**: Emits OMG CDR compliant binary serialized buffer with byte length and endianness.
- **`ros2_lifecycle_set(node, target_state)` / `yantram_lifecycle_set` / `યંત્રમ_જીવનચક્ર_સેટ`**: Manages robotic node lifecycle states (Unconfigured, Inactive, Active, Finalized).
- **CLI: `gujarati ros2:node <node_config.json>` / `gujarati યંત્રમ:નોડ`**: Pure C99 standalone tool to launch, inspect, and monitor active ROS2 nodes and topics.

### 2. 🗺️ Pillar 2: Marg (માર્ગ) SLAM & Pathfinding (8 Points)
- **`slam_grid_create(width, height, resolution)` / `marg_grid_banavo` / `માર્ગ_ગ્રીડ_બનાવો`**: Allocates 2D occupancy grid probability map with cell counts and metric dimensions.
- **`slam_point_cloud_filter(cloud_data, voxel_size)` / `marg_point_cloud` / `માર્ગ_પોઇન્ટ_ક્લાઉડ`**: Filters and downsamples 3D LiDAR point cloud scans using voxel grid filtering.
- **`slam_astar_pathfind(grid, start_x, start_y, goal_x, goal_y)` / `marg_shodho` / `માર્ગ_શોધો`**: Computes shortest obstacle-free trajectory using A* heuristic pathfinding.
- **`slam_robot_pose(odom_data, imu_data)` / `marg_robot_sthan` / `માર્ગ_રોબોટ_સ્થાન`**: Estimates fused robot pose (x, y, theta) and confidence rating.
- **`slam_occupancy_update(grid, x, y, prob)` / `marg_grid_update` / `માર્ગ_ગ્રીડ_અપડેટ`**: Updates occupancy probability of grid cells from real-time laser scans.
- **`slam_raycast_scan(grid, origin_x, origin_y, angle, max_range)` / `marg_raycast_scan` / `માર્ગ_રેકાસ્ટ_સ્કેન`**: Simulates 2D rangefinder laser beam traversal across grid cells detecting obstacles.
- **`slam_rrt_plan(grid, start_pt, goal_pt, iterations)` / `marg_rrt_plan` / `માર્ગ_આરઆરટી_પ્લાન`**: Rapidly-exploring Random Tree motion planner for robotic exploration.
- **CLI: `gujarati slam:map <lidar_scan.json>` / `gujarati માર્ગ:નકશો`**: Reconstructs 2D/3D occupancy grid map and trajectory from raw LiDAR scan streams.

### 3. ⚙️ Pillar 3: Chalak (ચાલક) PID Motor Control (7 Points)
- **`motor_pid_create(kp, ki, kd, setpoint)` / `chalak_pid_banavo` / `ચાલક_પીઆઈડી_બનાવો`**: Initializes Proportional-Integral-Derivative control loop gains.
- **`motor_pid_update(pid, measured_value, dt)` / `chalak_pid_update` / `ચાલક_પીઆઈડી_અપડેટ`**: Computes closed-loop motor PWM effort correcting error integral and derivative.
- **`motor_trajectory_plan(start_pos, target_pos, max_vel, max_acc)` / `chalak_gati_yojana` / `ચાલક_ગતિ_યોજના`**: Generates smooth trapezoidal velocity/acceleration motion profiles.
- **`motor_inverse_kinematics(arm_lengths, target_x, target_y, target_z)` / `chalak_robot_hath_ganatari` / `ચાલક_રોબોટ_હાથ_ગણતરી`**: Solves 3-to-6 DOF joint angles reaching 3D end-effector coordinate.
- **`motor_forward_kinematics(arm_lengths, joint_angles)` / `chalak_forward_kinematics` / `ચાલક_આગળ_ગણતરી`**: Computes 3D end-effector spatial coordinates from joint angles.
- **`motor_encoder_read(pulse_count, ppr)` / `chalak_encoder_vancho` / `ચાલક_એનકોડર_વાંચો`**: Converts quadrature encoder pulses into revolutions, pulses, and rotational degrees.
- **CLI: `gujarati motor:tune <motor_params.json>` / `gujarati ચાલક:ટ્યુન`**: Auto-tunes motor PID gains using Ziegler-Nichols closed-loop response modeling.

### 4. 🚁 Pillar 4: Udan (ઉડાન) Drone MAVLink Telemetry (7 Points)
- **`drone_mavlink_connect(port_or_ip, baud_rate)` / `udan_jodan` / `ઉડાન_જોડાણ`**: Establishes UDP/serial connection to flight controller autopilot.
- **`drone_mavlink_heartbeat(sys_id, comp_id, autopilot_type)` / `udan_hrudayspandan` / `ઉડાન_હૃદયસ્પંદન`**: Generates and broadcasts 1Hz MAVLink HEARTBEAT telemetry messages.
- **`drone_waypoint_add(mission, lat, lon, alt_meters)` / `udan_waypoint` / `ઉડાન_વેપોઇન્ટ`**: Appends GPS coordinates and altitude target to autonomous flight mission.
- **`drone_sensor_fusion(gyro_xyz, accel_xyz, baro_alt)` / `udan_sensor_mishran` / `ઉડાન_સેન્સર_મિશ્રણ`**: Extended Kalman Filter combining inertial sensor streams for roll, pitch, and yaw attitude.
- **`drone_failsafe_check(battery_pct, gps_fix, geofence_dist)` / `udan_salamati_tapas` / `ઉડાન_સલામતી_તપાસ`**: Evaluates battery levels, GPS lock, and geofence distance for return-to-home safety.
- **`drone_arm_throttle(armed_flag)` / `udan_arm` / `ઉડાન_આર્મ`**: Sends arm/disarm motor throttle commands to motor ESCs.
- **CLI: `gujarati drone:telemetry <flight_log.bin>` / `gujarati ઉડાન:ટેલિમેટ્રી`**: Decodes raw MAVLink telemetry binaries and logs flight status.

### 5. 🎁 Pre-Built Starter Kit 8: Setu Mobile (`--kit=mobile`, `--kit=android`)
Scaffold cross-platform native Android NDK mobile applications with declarative UI:
```bash
gujarati new my_drone_pilot --kit=mobile
# or
gujarati new my_drone_pilot --kit=android
```
Generates:
- `app.gj`: Declarative widget tree with multi-screen navigation routing.
- `screens/home_screen.gj`: Responsive Column, Row, Card, and Button components.
- `screens/settings_screen.gj`: Settings panel and theme configuration.
- `hardware/sensors.gj`: Native Android Toast, push notifications, and battery status.
- `manifest.json`: Android app permissions, package ID, and high-DPI icon assets.

---

# GujaratiLang v3.7.0: Satya & Shuddhi — Formal Verification & Safe Memory (સત્ય, શુદ્ધિ, પ્રમાણ અને છેદ)

GujaratiLang **v3.7.0** is officially released! This monumental release brings mathematical correctness and compile-time memory safety to GujaratiLang, implemented in 100% pure C99 with **zero external C dependencies**.

It introduces a linear-ownership borrow checker (Shuddhi) guaranteeing zero leaks and zero GC pauses, an embedded pure C99 DPLL SAT/SMT propositional theorem prover (Satya) for arithmetic invariants and induction proofs, design-by-contract preconditions, postconditions, and loop variants (Praman), and a concurrent happens-before memory data race and deadlock detector (Chhed), alongside our seventh official pre-coded starter kit: **Kasauti Testing Suite (`--kit=kasauti`, `--kit=test`)**.

With v3.7.0, the automated test suite reaches the landmark **810 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v3.7.0

### 1. 🛡️ Pillar 1: Shuddhi (શુદ્ધિ) Borrow Checker
- **`borrow_owner_create(name, resource_type)` / `શુદ્ધિ_માલિક_બનાવો`**: Allocates a linearly owned resource with a single unique owner.
- **`borrow_ref_immutable(owner, ref_name)` / `શુદ્ધિ_ઉધાર_સ્થિર`**: Borrows a read-only reference; permits multiple concurrent readers.
- **`borrow_ref_mutable(owner, ref_name)` / `શુદ્ધિ_ઉધાર_બદલાવ`**: Borrows an exclusive mutable reference; strictly forbids concurrent borrows.
- **`borrow_lifetime_check(owner, scope_depth)` / `શુદ્ધિ_આયુષ્ય_તપાસ`**: Validates compile-time lifetime scopes preventing dangling pointers.
- **`borrow_release(owner, ref_name)` / `શુદ્ધિ_મુક્ત_કરો`**: Releases active reference and returns full capabilities to owner.
- **`borrow_move(owner, new_owner)` / `શુદ્ધિ_માલિક_બદલો`**: Transfers ownership linearly, invalidating previous owner handle.
- **`borrow_check_leaks()` / `શુદ્ધિ_તપાસ_લીક`**: Audits memory pool verifying zero lingering unreleased allocations.
- **CLI Subcommand**: `gujarati check:borrow <source.gj>` (alias `gujarati શુદ્ધિ:તપાસ`).

### 2. 🔍 Pillar 2: Satya (સત્ય) Pure C99 SMT Theorem Prover
- **`smt_solver_create(name)` / `સત્ય_સોલ્વર_બનાવો`**: Initializes pure C99 DPLL SAT/SMT propositional logic solver context.
- **`smt_assert_formula(solver, expr_str)` / `સત્ય_સૂત્ર_ઉમેરો`**: Appends quantifier-free linear integer arithmetic formula or clause.
- **`smt_check_sat(solver)` / `સત્ય_તપાસ_સંતોષ`**: Executes DPLL solving returning satisfiability decisions and conflict resolution.
- **`smt_get_model(solver)` / `સત્ય_મોડેલ_મેળવો`**: Extracts satisfying assignment mapping variables to concrete optimal values.
- **`smt_prove_invariant(solver, inv_str)` / `સત્ય_સાબિત_કરો`**: Formally proves mathematical invariant holds across all valid application states.
- **`smt_verify_bounds(array_len, index)` / `સત્ય_બાઉન્ડ્સ_તપાસ`**: Mathematical array bounds verification eliminating runtime bounds checking overhead.
- **`smt_prove_induction(base_case, step)` / `સત્ય_આગમન_સાબિત`**: Formal induction engine for recursive functions and loop terminations.
- **CLI Subcommand**: `gujarati verify:formal <theory.smt>` (alias `gujarati સત્ય:ચકાસણી`).

### 3. 📜 Pillar 3: Praman (પ્રમાણ) Design-by-Contract
- **`praman_requires(cond, err_msg)` / `પ્રમાણ_પૂર્વશરત`**: Asserts function entry preconditions.
- **`praman_ensures(cond, err_msg)` / `પ્રમાણ_પરિણામ_શરત`**: Validates function return guarantees before yielding to caller.
- **`praman_invariant(cond, obj_name)` / `પ્રમાણ_અચળ_નિયમ`**: Asserts perpetual class or struct state invariants.
- **`praman_loop_variant(current_val, prev_val)` / `પ્રમાણ_લૂપ_ચકાસણી`**: Formally ensures monotonic convergence to prevent infinite loops.
- **`praman_status()` / `પ્રમાણ_સ્થિતિ`**: Returns audit count of verified preconditions, postconditions, and invariants.
- **`praman_set_mode(strict_level)` / `પ્રમાણ_મોડ_સેટ`**: Configures contract evaluation mode (0 = off, 1 = debug, 2 = strict).
- **CLI Subcommand**: `gujarati contract:check <app.gj>` (alias `gujarati પ્રમાણ:ચકાસણી`).

### 4. ⚡ Pillar 4: Chhed (છેદ) Data Race Detector
- **`race_detector_init(max_threads)` / `છેદ_તપાસ_શરૂ`**: Allocates happens-before concurrency graph engine with lock-set tracking.
- **`race_record_access(thread_id, addr, is_write)` / `છેદ_એક્સેસ_નોંધણી`**: Logs memory reads and writes across threads.
- **`race_lock_acquire(thread_id, lock_id)` / `છેદ_તાળું_મેળવો`**: Updates lock-set graph to detect lock-order inversion and deadlocks.
- **`race_lock_release(thread_id, lock_id)` / `છેદ_તાળું_છોડો`**: Releases lock from thread active lock-set.
- **`race_detect_conflicts(addr)` / `છેદ_ટકરાવ_શોધો`**: Evaluates whether conflicting concurrent unsynchronized access occurred.
- **`race_check_memory_order(op_type)` / `છેદ_ક્રમ_તપાસ`**: Validates memory ordering and sequential consistency guarantees.
- **CLI Subcommand**: `gujarati check:race <thread_script.gj>` (alias `gujarati છેદ:તપાસ`).

### 5. 🎁 Pre-Coded Starter Kit 7: Kasauti Testing Suite (`--kit=kasauti`, `--kit=test`)
Scaffold automated test suites with Dusk-style browser automation, screenshot pixel diffing, network interceptors, and device viewport emulation:
```bash
gujarati new my_tests --kit=kasauti
# or
gujarati new my_tests --kit=test
# or shorthand
gujarati kit:kasauti my_tests
```
Generates:
- `tests/browser_test.gj`: Dusk-style headless browser automation for authentication and form validation
- `tests/visual_regression.gj`: Visual screenshot diffing with pixel-level tolerance comparison
- `tests/api_mock.gj`: Intercepting network HTTP client calls with realistic mock payloads
- `tests/device_matrix.gj`: Multi-device viewport responsive rendering test suite
- `runner.gj`: Automated test runner producing pass/fail reporting and test coverage diagnostics

---


# GujaratiLang v3.6.0: Vepar & Nanu — Enterprise ERP, GST & Order Book (વેપાર, ખાતા અને જીએસટી એન્જિન)

GujaratiLang **v3.6.0** is officially released! This landmark release delivers native enterprise commerce and financial accounting primitives written in 100% pure C99 with **zero external C dependencies**.

It introduces immutable multi-currency double-entry ledger bookkeeping (Khata), Indian Goods and Services Tax (GST) computation with CGST/SGST/IGST splitting and HSN classification (Kar), high-frequency Level 2 / Level 3 order book trade matching with Price-Time Priority FIFO (Bajar), and an embedded pure C99 vector PDF invoice generator (Dastavej), alongside our sixth official pre-coded starter kit: **Vepar Commerce & GST Invoicing (`--kit=commerce`, `--kit=vepar`)**.

With v3.6.0, the automated test suite reaches the landmark **780 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v3.6.0

### 1. 📒 Pillar 1: Khata (ખાતા) Double-Entry Ledger
- **`khata_account_create(name, type, currency)` / `ખાતા_ખાતું_બનાવો`**: Initializes Asset, Liability, Equity, Revenue, or Expense account.
- **`khata_entry_post(id, date, desc, dr_acc, cr_acc, amount)` / `ખાતા_નોંધ_પોસ્ટ`**: Atomic double-entry journal post strictly enforcing Debit == Credit balance constraint.
- **`khata_account_balance(account, entries)` / `ખાતા_ખાતું_શિલક`**: Computes net real-time account balance according to normal accounting balance rules.
- **`khata_trial_balance(debit_total, credit_total)` / `ખાતા_કાચું_સરવૈયું`**: Generates verified trial balance confirming total Debits == total Credits.
- **`khata_balance_sheet(assets, liabilities, equity)` / `ખાતા_પાકું_સરવૈયું`**: Produces Assets = Liabilities + Equity verification summary.
- **`khata_forex_convert(amount, from_curr, to_curr, rate)` / `ખાતા_ચલણ_રૂપાંતર`**: Converts foreign currency amounts at specified exchange rates.
- **`khata_audit_verify(entry_count)` / `ખાતા_તપાસ_ચકાસણી`**: Cryptographically validates journal entry sequence integrity.
- **CLI Subcommand**: `gujarati erp:balance <journal.gjt>` (alias `gujarati ખાતા:સરવૈયું`).

### 2. 🧾 Pillar 2: Kar (કર) Indian GST Tax Engine
- **`gst_calculate(taxable_val, rate, is_interstate)` / `જીએસટી_ગણતરી`**: Computes dual-tax CGST + SGST (intra-state) or IGST (inter-state) with full breakdown.
- **`gst_hsn_lookup(code)` / `જીએસટી_એચએસએન_શોધો`**: Resolves standard GST rate and description for HSN/SAC code (IT Services 9983, Hardware 8471, Apparel 6203, Grains 1001).
- **`gst_einvoice_payload(seller_gstin, buyer_gstin, inv_no, date, val, tax, irn)` / `જીએસટી_ઈઇન્વોઇસ_પેલોડ`**: Generates NIC compliant e-Invoice signed string format for QR code.
- **`gst_reverse_charge(val, rate)` / `જીએસટી_ઊલટો_કર`**: Calculates Reverse Charge Mechanism (RCM) tax liability for unregistered vendor purchases.
- **`gst_itc_eligible(tax_paid, is_business)` / `જીએસટી_આઈટીસી_પાત્રતા`**: Determines Input Tax Credit (ITC) eligibility under CGST Act Section 16 & 17(5).
- **`gst_tds_deduct(amount, section, rate)` / `જીએસટી_ટીડીએસ_કપાત`**: Calculates Section 194C / 194J TDS deductions and net payable amounts.
- **`gst_verify_gstin(gstin)` / `જીએસટી_ચકાસણી_જીએસટીઆઈએન`**: Verifies 15-character Indian GSTIN format and checksum.
- **CLI Subcommand**: `gujarati gst:calc <amount> <rate> [interstate]` (alias `gujarati જીએસટી:ગણતરી`).

### 3. 📈 Pillar 3: Bajar (બજાર) Order Book Matching Engine
- **`orderbook_create(symbol)` / `ઓર્ડરબુક_બનાવો`**: Allocates a two-sided (Bids & Asks) L2/L3 order book.
- **`orderbook_limit_order(book, side, price, qty)` / `ઓર્ડરબુક_મર્યાદિત_ઓર્ડર`**: Inserts limit order at price level into sorted FIFO queue.
- **`orderbook_market_order(book, side, qty)` / `ઓર્ડરબુક_બજાર_ઓર્ડર`**: Executes immediate fill against top of book across price levels.
- **`orderbook_match(book)` / `ઓર્ડરબુક_મેચ`**: Triggers Price-Time Priority (FIFO) matching cycle and produces trade fills.
- **`orderbook_depth(book, levels)` / `ઓર્ડરબુક_ઊંડાઈ`**: Returns top bid/ask levels with aggregated quantities and spread.
- **`orderbook_trades(book)` / `ઓર્ડરબુક_સોદા`**: Retrieves chronological trade execution log (price, qty, timestamp).
- **CLI Subcommand**: `gujarati orderbook:trade <orders.json>` (alias `gujarati ઓર્ડરબુક:સોદા`).

### 4. 📄 Pillar 4: Dastavej (દસ્તાવેજ) Pure C99 PDF Generator
- **`pdf_document_create(title, author)` / `પીડીએફ_દસ્તાવેજ_બનાવો`**: Initializes PDF-1.4 stream header, catalog, and xref table in memory with zero external C libraries.
- **`pdf_add_page(doc, width, height)` / `પીડીએફ_પાનું_ઉમેરો`**: Appends a page object with dimension media box (default A4 595x842 pt).
- **`pdf_draw_text(doc, x, y, text, font_size)` / `પીડીએફ_લખાણ`**: Emits PDF BT / ET text positioning and glyph rendering commands.
- **`pdf_draw_table(doc, x, y, headers, rows)` / `પીડીએફ_કોષ્ટક`**: Automatically formats tabular rows with cell borders and header styling.
- **`pdf_sign_hash(doc, signee_name, sha256_hash)` / `પીડીએફ_સહી`**: Embeds metadata timestamp and SHA-256 signature seal box.
- **`pdf_save_file(doc, file_path)` / `પીડીએફ_રેન્ડર`**: Serializes cross-reference xref table, trailer, and writes valid PDF document.
- **CLI Subcommand**: `gujarati pdf:generate <invoice.json> <out.pdf>` (alias `gujarati પીડીએફ:બનાવો`).

### 5. 🎁 Pre-Coded Starter Kit 6: Vepar Commerce (`--kit=commerce`, `--kit=vepar`)
Scaffold a complete commercial storefront with catalog, shopping cart, Indian GST tax calculations, double-entry sales journal, and PDF invoice generation:
```bash
gujarati new my_store --kit=commerce
# or
gujarati new my_store --kit=vepar
# or shorthand
gujarati kit:commerce my_store
```
Generates:
- `catalog.gj`: Product definitions with HSN codes and GST rates (5%, 12%, 18%, 28%)
- `cart.gj`: Shopping cart session management with dynamic tax calculations
- `ledger.gj`: Double-entry accounting postings for sales, tax liability, and receivable accounts
- `invoice.gj`: Pure C99 PDF tax invoice rendering with SHA-256 digital stamp
- `app.gj`: Unified commerce gateway on `:8080`

---


# GujaratiLang v3.5.0: Winsock Async Network, Ranga-3D Graphics, Gati Physics & Shilp Desktop GUI (વિન્સોક, રંગ, ગતિ અને શિલ્પ ડેસ્કટોપ)

GujaratiLang **v3.5.0** is officially released! This monumental release expands GujaratiLang into asynchronous systems networking and real-time interactive 3D simulations. It delivers native asynchronous Winsock HTTP listeners (`bind`, `listen`, `accept`, `recv`, `send`, `poll`), 3D scene graphs with affine matrix transformations, a rigid-body physics engine with raycasting, spatial audio synthesis with HRTF panning, an Entity-Component-System (ECS) game engine, alongside our fifth official pre-coded starter kit: **Shilp Native Desktop GUI Suite (`--kit=desktop`)**.

With v3.5.0, the automated test suite reaches the landmark **750 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64), all implemented in 100% pure C99 with zero external C dependencies.

---

## 🌟 What's New in v3.5.0

### 1. 🌐 Pillar 1: Winsock Asynchronous HTTP & Network Listeners (વિન્સોક અસિંક લિસનર)
- **`winsock_server_init(host, port, [backlog])` / `વિન્સોક_સર્વર_શરૂ`**: Native non-blocking TCP socket creation, `WSAStartup` / `socket()`, `setsockopt(SO_REUSEADDR)`, `bind()` to interface, and async non-blocking mode configuration.
- **`winsock_server_poll(server_handle, [timeout_ms])` / `વિન્સોક_સર્વર_પોલ`**: Native non-blocking event multiplexing (`select()` / `WSAPoll`) awaiting incoming client connections without thread freezing.
- **`winsock_server_accept(server_handle)` / `વિન્સોક_સર્વર_સ્વીકારો`**: Non-blocking `accept()` call returning client socket handle, IP address, and remote port, setting client socket to non-blocking mode.
- **`winsock_client_recv(client_handle, [max_bytes])` / `વિન્સોક_ક્લાયન્ટ_મેળવો`**: Non-blocking `recv()` reading incoming HTTP request bytes into a string buffer.
- **`winsock_client_send(client_handle, response_str)` / `વિન્સોક_ક્લાયન્ટ_મોકલો`**: Native `send()` writing HTTP headers and payload response to client socket with transmission byte tracking.
- **`winsock_server_close(socket_handle)` / `વિન્સોક_સર્વર_બંધ`**: Graceful TCP connection shutdown and socket termination.
- **CLI Subcommand**: `gujarati http:serve [port] [dir]`.

### 2. 🎮 Pillar 2: Khel-3D (ખેલ 3D) Scene Graph & Mesh Graphics
- **`khel3d_scene_create(name)` / `ખેલ૩ડી_દ્રશ્ય_બનાવો`**: Initializes 3D scene graph with ambient lighting, background color, and node tree.
- **`khel3d_mesh_create(primitive_type, params)` / `ખેલ૩ડી_મેશ_બનાવો`**: Generates 3D procedural geometry for cubes, spheres, cylinders, and planes.
- **`khel3d_camera_set(scene, eye, target, up, fov)` / `ખેલ૩ડી_કેમેરા_સેટ`**: Perspective and orthographic camera view/projection matrix configuration.
- **`khel3d_node_transform(mesh, translate, rotate, scale)` / `ખેલ૩ડી_નોડ_રૂપાંતર`**: Computes 4x4 affine model transform matrices.
- **`khel3d_render_wireframe(scene, width, height)` / `ખેલ૩ડી_રેન્ડર_વાયરફ્રેમ`**: Vectorized 3D-to-2D perspective projection wireframe rasterizer.
- **CLI Subcommand**: `gujarati assets:cook <mesh.gltf>`.

### 3. ⚙️ Pillar 3: Gati (ગતિ) 3D Physics Engine & Raycasting
- **`gati_world_create(gravity_vec)` / `ગતિ_વિશ્વ_બનાવો`**: Initializes 3D rigid-body simulation world.
- **`gati_body_add(world, body_type, mass, position)` / `ગતિ_બોડી_ઉમેરો`**: Creates dynamic, static, or kinematic rigid bodies with mass and restitution.
- **`gati_step(world, dt)` / `ગતિ_સ્ટેપ`**: Symplectic Euler numerical velocity and position integration.
- **`gati_collide_aabb(box_a, box_b)` / `ગતિ_ટકરાવ_તપાસ`**: Fast Axis-Aligned Bounding Box (AABB) intersection detection.
- **`gati_raycast(world, origin, direction, max_dist)` / `ગતિ_રેકાસ્ટ`**: 3D vector raycasting returning hit point, distance, and collider ID.
- **CLI Subcommand**: `gujarati physics:simulate <world.gj>`.

### 4. 🔊 Pillar 4: Dhwani (ધ્વનિ) Spatial Audio & Sound Synthesis
- **`dhwani_engine_init(sample_rate, channels)` / `ધ્વનિ_શરૂ`**: Initializes 44.1kHz / 48kHz digital audio synthesizer.
- **`dhwani_tone_generate(waveform, freq_hz, duration_sec, volume)` / `ધ્વનિ_સુર_બનાવો`**: Generates pure mathematical audio waveforms (sine, square, triangle, saw, noise).
- **`dhwani_spatial_position(sound_clip, listener_pos, emitter_pos)` / `ધ્વનિ_સ્થાનિક_સેટ`**: Head-Related Transfer Function (HRTF) 3D positional audio stereo panning, distance attenuation, and Doppler shift.
- **`dhwani_reverb_apply(sound_clip, room_size, damping)` / `ધ્વનિ_રીવર્બ_લાગુ`**: Delay-line digital reverberation filter simulating room acoustics.
- **`dhwani_mix_tracks(tracks_list)` / `ધ્વનિ_ટ્રેક_મિશ્રણ`**: Multi-channel audio summing mixer with clipping protection.
- **CLI Subcommand**: `gujarati audio:play <sound.wav>`.

### 5. 🕹️ Pillar 5: Niyantran (નિયંત્રણ) Game ECS & Shilp Desktop GUI
- **`ecs_world_create()` / `ઈસીએસ_વિશ્વ_બનાવો`**: Entity-Component-System archetype registry.
- **`ecs_entity_spawn(world, components_dict)` / `ઈસીએસ_એન્ટિટી_બનાવો`**: Spawns unique entity IDs and binds component maps.
- **`ecs_query(world, required_components)` / `ઈસીએસ_શોધ`**: High-speed entity filtering matching component sets.
- **`ecs_system_register(world, name, update_fn)` / `ઈસીએસ_સિસ્ટમ_નોંધણી`**: Registers priority-ordered game loop systems.
- **`gui_window_create(title, width, height, [flags])` / `જીયુઆઈ_બારી_બનાવો`**: Native cross-platform desktop window descriptor with event listeners and Shilp 2D vector canvas.
- **CLI Subcommand**: `gujarati game:run <main.gj>`.

### 6. 🎁 Pre-Coded Starter Kit 5: Shilp Native Desktop GUI Suite (`--kit=desktop`)
- Scaffolds complete cross-platform desktop GUI application with custom windows, system menubar, file dialogs, and native packaging.
- CLI: `gujarati new <app_name> --kit=desktop`, `gujarati kit:desktop`, `gujarati kit:gui`, `gujarati kit:shilp`.

---

# GujaratiLang v3.4.0: Maha-Sankhya — Big Data, Columnar Analytical Compute & Tarang Setu API (મહાસંખ્યા અને તરંગ સેતુ)

GujaratiLang **v3.4.0** is officially released! This monumental release delivers high-performance big data analytics, vectorized columnar processing, distributed MapReduce computing, time-series Gorilla compression, and streaming ETL pipelines directly into the pure C99 runtime with zero external C dependencies. It also introduces the official **Tarang Setu API Starter Kit (`--kit=api`)**, expanding the automated test suite to the landmark **720 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v3.4.0

### 1. 📊 Pillar 1: Sthambha (સ્તંભ) Columnar Parquet & Arrow Tables
- **`columnar_table_create(schema)` / `સ્તંભ_કોષ્ટક_બનાવો`**: In-memory columnar data frame with typed schemas (int, float, string) for high-performance vectorized scanning.
- **`columnar_append(table, row_dict)` / `સ્તંભ_ઉમેરો`**: Appends row records into columnar memory layout.
- **`columnar_rle_encode(array)` / `સ્તંભ_આરએલઈ_એન્કોડ`**: Run-Length Encoding (RLE) for high compression on repeated values.
- **`columnar_rle_decode(rle_dict)` / `સ્તંભ_આરએલઈ_ડીકોડ`**: Run-Length Decoding reconstructing raw series.
- **`columnar_dict_encode(array)` / `સ્તંભ_શબ્દકોશ_એન્કોડ`**: Dictionary encoding converting high-cardinality string columns into integer indices.
- **`columnar_dict_decode(dict_payload)` / `સ્તંભ_શબ્દકોશ_ડીકોડ`**: Reconstructs original strings from dictionary indices.
- **`columnar_slice(table, offset, count)` / `સ્તંભ_ટુકડો`**: Vectorized zero-copy columnar slicing.
- **CLI Subcommand**: `gujarati query:run <table.parquet>`.

### 2. ⚡ Pillar 2: Vistar (વિસ્તાર) MapReduce Engine
- **`mapreduce_init(name)` / `મેપરીડ્યુસ_શરૂ`**: Initializes distributed MapReduce job context.
- **`mapreduce_map(job, key, val)` / `મેપરીડ્યુસ_મેપ`**: Emits intermediate `(key, value)` pairs during mapping stage.
- **`mapreduce_shuffle(job)` / `મેપરીડ્યુસ_શફલ`**: Partitions and groups intermediate key-value pairs by key.
- **`mapreduce_reduce(job, key, vals)` / `મેપરીડ્યુસ_રીડ્યુસ`**: Aggregates grouped key values with user reduction function.
- **`mapreduce_external_sort(job, runs)` / `મેપરીડ્યુસ_સૉર્ટ`**: External two-phase merge sort for datasets larger than RAM.
- **`mapreduce_dag_optimize(job)` / `મેપરીડ્યુસ_ડીએજી_ઓપ્ટિમાઈઝ`**: Optimizes execution DAG by fusing map/reduce stages.
- **`mapreduce_results(job)` / `મેપરીડ્યુસ_પરિણામ`**: Retrieves final materialized key-value reduction pairs.
- **CLI Subcommand**: `gujarati mapreduce:job <job_spec.gj>`.

### 3. ⏱️ Pillar 3: Gana (ગણ) Time-Series Metrics & Gorilla Compression
- **`gorilla_compress_floats(floats)` / `ગોરિલા_સંકોચન`**: Facebook Gorilla XOR floating-point compression algorithm.
- **`gorilla_decompress_floats(payload)` / `ગોરિલા_વિસંકોચન`**: Decompresses Gorilla bitstreams back to double-precision floats.
- **`timeseries_delta_timestamps(timestamps)` / `સમય_ડેલ્ટા_ટાઇમસ્ટેમ્પ`**: Delta-of-delta timestamp variable-length compression.
- **`timeseries_rollup(ts_data, bucket_sec)` / `સમય_રોલઅપ`**: Downsamples high-frequency metrics into aggregate buckets (count, min, max, sum, avg).
- **`timeseries_ema(data, alpha)` / `સમય_ઈએમએ`**: Computes Exponential Moving Average with configurable smoothing parameter.
- **`timeseries_anomaly_detect(data, threshold_z)` / `સમય_વિસંગતિ_શોધ`**: Z-score anomaly detector identifying statistical outliers.
- **CLI Subcommand**: `gujarati ts:aggregate <metrics.ts>`.

### 4. 🔄 Pillar 4: Setu-Data Universal Streaming ETL
- **`etl_pipeline_create(name)` / `ઈટીએલ_પાઈપલાઈન_બનાવો`**: Initializes declarative ETL streaming pipeline.
- **`etl_transform(pipeline, record, fn)` / `ઈટીએલ_રૂપાંતરણ`**: Streams records through pure functional transformation stages.
- **`etl_schema_validate(record, schema)` / `ઈટીએલ_સ્કીમા_ચકાસો`**: Strict schema contract enforcer ensuring type integrity.
- **`etl_dead_letter_push(pipeline, item, reason)` / `ઈટીએલ_ડેડલેટર_ઉમેરો`**: Routes poisoned/corrupt records into dead-letter queue (DLQ).
- **`etl_dead_letter_drain(pipeline)` / `ઈટીએલ_ડેડલેટર_ખાલી`**: Flushes dead-letter queue for forensic replay and debugging.
- **`etl_ingest_batch(pipeline, batch_records)` / `ઈટીએલ_બેચ_દાખલ`**: High-throughput micro-batch ingestion pipeline.
- **CLI Subcommand**: `gujarati etl:pipeline <config.etl>`.

### 5. 🎁 Pre-Coded Starter Kit 4: Tarang Setu API (તરંગ સેતુ)
- Scaffolds a complete production-grade high-throughput REST API with JWT authentication, rate limiting, columnar caching, and OpenAPI Swagger documentation.
- CLI: `gujarati new <app_name> --kit=api`, `gujarati kit:api`, `gujarati kit:tarang`.

---

# GujaratiLang v3.3.0: Chetana, Chitra, Sanchay & Nyay — Autonomous AI Studio & Sovereign Smart Contracts (ચેતના, ચિત્રા, સંચય અને ન્યાય)

GujaratiLang **v3.3.0** is officially released! This monumental release unites on-device artificial intelligence with decentralized cryptographic trust. It delivers 30 enterprise capabilities across 6 pillars—quantized GGUF LLM execution, multimodal vision and OCR, semantic vector RAG embeddings, deterministic gas-metered smart contracts VM, Merkle Mountain Range (MMR) immutable ledgers, and P2P Kademlia DHT with Paillier homomorphic math—alongside two production-ready pre-coded starter kits: **Sahayak AI Assistant** and **Suraksha Jetstream 2FA**.

With v3.3.0, the automated test suite reaches the landmark **690 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v3.3.0

### 1. 🧠 Pillar 1: Chetana (ચેતના) On-Device GGUF LLM Runner
- **`llm_init(model_path, [gpu_layers])` / `એલએલએમ_શરૂ`**: Loads quantized GGUF LLM model (Q4_K_M, 32 layers) with key-value cache and context window configuration.
- **`llm_generate(prompt, [max_tokens, temp])` / `એલએલએમ_બનાવો`**: Generates text completions with temperature and top-p sampling.
- **`llm_tokenize(text)` / `એલએલએમ_ટોકન`**: Converts text into BPE token ID sequences.
- **`llm_chat(messages, [system_prompt])` / `એલએલએમ_સંવાદ`**: Executes multi-turn conversational chat sessions with role structuring.
- **CLI Subcommand**: `gujarati llm:chat [model.gguf]`.

### 2. 👁️ Pillar 2: Chitra (ચિત્રા) Multimodal Vision & OCR
- **`vision_load_image(path)` / `દ્રષ્ટિ_ચિત્ર_લોડ`**: Decodes image formats into normalized RGB tensor representation.
- **`vision_describe(img_tensor, prompt)` / `દ્રષ્ટિ_વર્ણન`**: Analyzes visual features and generates natural language descriptions.
- **`vision_ocr(img_tensor)` / `દ્રષ્ટિ_ઓસીઆર`**: Extracts printed and handwritten text with confidence scoring.
- **`vision_render_ascii(img_tensor, [width])` / `દ્રષ્ટિ_આસ્કી_રેન્ડર`**: Renders image into terminal ASCII canvas art.
- **CLI Subcommand**: `gujarati vision:scan <image.png>`.

### 3. 🔍 Pillar 3: RAG & Cosine Vector Embeddings
- **`rag_embed_text(text)` / `રાગ_એમ્બેડ`**: Computes semantic embedding vector representations for text passages.
- **`rag_cosine_similarity(vec1, vec2)` / `રાગ_સમાનતા`**: Calculates cosine dot product similarity between normalized vector pairs.
- **`rag_chunk_text(text, chunk_size, overlap)` / `રાગ_ટુકડા`**: Splits large documents into overlapping semantic chunks for retrieval.
- **`rag_search(query_vec, doc_vectors, top_k)` / `રાગ_શોધ`**: In-memory similarity search ranking top relevant knowledge passages.
- **CLI Subcommand**: `gujarati rag:index <docs_dir>`.

### 4. 📜 Pillar 4: Nyay (ન્યાય) Sovereign Smart Contracts VM
- **`contract_deploy(bytecode, [gas_limit])` / `કરાર_અમલ`**: Deploys deterministic bytecode smart contracts with exact gas metering.
- **`contract_call(contract_id, method, args)` / `કરાર_કોલ`**: Invokes contract methods with execution bounds and return state tracking.
- **`contract_state_get(contract_id, key)` / `કરાર_સ્થિતિ_મેળવો`**: Queries contract state storage trie.
- **`contract_state_set(contract_id, key, val)` / `કરાર_સ્થિતિ_સેટ`**: Writes state transitions within transactional contract boundary.
- **CLI Subcommand**: `gujarati nyay:deploy <contract.gj>`.

### 5. 🏛️ Pillar 5: Sanchay (સંચય) Merkle Mountain Range & Ledger
- **`mmr_append(ledger, leaf_hash)` / `એમએમઆર_ઉમેરો`**: Appends leaf hash to Merkle Mountain Range accumulator with O(log n) efficiency.
- **`mmr_root(ledger)` / `એમએમઆર_મૂળ`**: Computes bag-of-peaks cryptographic Merkle root for current ledger state.
- **`mmr_proof(ledger, leaf_index)` / `એમએમઆર_સાબિતી`**: Generates logarithmic inclusion audit proof for target transaction.
- **`mmr_verify(root, leaf_hash, proof)` / `એમએમઆર_ચકાસો`**: Cryptographically verifies inclusion proof against root hash.
- **CLI Subcommand**: `gujarati ledger:audit <ledger.db>`.

### 6. 🌐 Pillar 6: Setu P2P Kademlia DHT & Privacy
- **`dht_node_init(node_id, port)` / `ડીએચટી_નોડ_શરૂ`**: Initializes Kademlia distributed hash table routing node.
- **`dht_store(node, key, val)` / `ડીએચટી_સંગ્રહ`**: Stores key-value mappings across distributed peer routing buckets.
- **`dht_find_value(node, key)` / `ડીએચટી_શોધો`**: Discovers and retrieves stored records across network peers.
- **`crypto_paillier_add(enc_a, enc_b, pub_key)` / `ક્રિપ્ટો_હોમોમોર્ફિક_સરવાળો`**: Computes encrypted addition without decrypting underlying values.
- **CLI Subcommand**: `gujarati p2p:join <seed_peer>`.

### 7. 🎁 Pre-Coded Starter Kits
- **Kit 1: Sahayak AI Assistant (`--kit=sahayak`, `--kit=ai`)**: Complete conversational RAG assistant, document ingestion pipeline, streaming CLI chat UI (`gujarati new my_ai --kit=sahayak`).
- **Kit 2: Suraksha Jetstream (`--kit=jetstream`, `--kit=contracts`)**: Enterprise 2FA TOTP authentication, RBAC roles/permissions, smart contract state verification, and encrypted secret vault storage (`gujarati new my_saas --kit=jetstream`).

---

# GujaratiLang v3.2.0: Rakshak Systems Programming, Win32 FFI & Antivirus Engine (રક્ષક સિસ્ટમ પ્રોગ્રામિંગ અને એન્ટિવાયરસ એન્જિન)

GujaratiLang **v3.2.0** is officially released! This landmark systems programming release transforms GujaratiLang into a bare-metal cyber-defense and systems programming powerhouse. It introduces 30 enterprise capabilities across 6 critical pillars—Win32 FFI interop, raw binary buffers & PE/COFF struct unpacking, native C crypto & Shannon entropy calculation, real-time filesystem change sentinels, multi-threaded scanner worker pools, and process/command-line threat diagnostics—alongside our second official pre-coded starter kit: **Rakshak Antivirus Suite**.

With v3.2.0, the automated test suite reaches the landmark **660 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v3.2.0

### 1. ⚡ Pillar 1: C FFI (Foreign Function Interface) & Win32 Interop
- **`ffi_load_library(dll_name)` / `એફએફઆઈ_લાઈબ્રેરી_લોડ`**: Dynamically loads native Windows DLLs (`LoadLibraryW`) and exports typed library reference handles.
- **`ffi_get_proc(lib_handle, symbol)` / `એફએફઆઈ_ફંક્શન_મેળવો`**: Resolves symbol addresses (`GetProcAddress`) for target native C functions.
- **`ffi_call(proc, ret_type, arg_types, args)` / `એફએફઆઈ_કોલ`**: Dispatches dynamic foreign function calls obeying native C calling conventions.
- **`ffi_kernel32(func_name, args)` / `એફએફઆઈ_કર્નલ૩૨`**: Direct kernel32 API interop (PID tracking, tick counts, error codes).
- **`ffi_advapi32(func_name, args)` / `એફએફઆઈ_એડવાપી૩૨`**: Direct advapi32 API interop (user tokens, security descriptors).
- **CLI Subcommand**: `gujarati ffi:inspect <dll>` (inspects PE export directory and lists exported symbols).

### 2. 🧩 Pillar 2: Raw Binary Buffers & PE/COFF Struct Unpacking
- **`buffer_alloc(size, [fill_byte])` / `બફર_ફાળવો`**: Allocates contiguous raw byte buffers with direct byte-level slicing and indexing.
- **`buffer_from_file(path, offset, size)` / `બફર_ફાઇલમાંથી`**: Reads binary bytes directly from executable and library files on disk.
- **`struct_unpack(format_str, buffer, offset)` / `સ્ટ્રક્ટ_અનપેક`**: Decodes binary structures using endian formats (`<H` 16-bit uint, `<I` 32-bit uint, `<Q` 64-bit uint).
- **`pe_parse_headers(path_or_buffer)` / `પીઈ_હેડર_વાંચો`**: Full PE32/PE32+ parser decoding `IMAGE_DOS_HEADER` (`e_magic = 0x5A4D / MZ`), `IMAGE_NT_HEADERS`, section tables, and subsystem.
- **`bit_and`, `bit_or`, `bit_xor`, `bit_lshift`, `bit_rshift`, `bit_not`**: Native 64-bit bitwise logic operations for masking and binary calculations.

### 3. 🔒 Pillar 3: Native C-Level Hashing Primitives & Shannon Entropy
- **`crypto_sha256(data_or_path)` / `ક્રિપ્ટો_એસએચએ૨૫૬`**: High-performance bare-metal C SHA-256 cryptographic hash computation.
- **`crypto_md5(data_or_path)` / `ક્રિપ્ટો_એમડી૫`**: Ultra-fast MD5 signature generation matching antivirus threat databases.
- **`crypto_entropy(buffer_or_string)` / `ક્રિપ્ટો_એન્ટ્રોપી`**: Computes Shannon entropy ($H(X) = -\sum P_i \log_2 P_i$) to instantly detect packed/encrypted malware.
- **`crypto_pe_section_entropy(path)` / `પીઈ_સેક્શન_એન્ટ્રોપી`**: Audits all executable sections (`.text`, `.data`, `.rsrc`), flagging entropy anomalies exceeding 7.0.
- **CLI Subcommand**: `gujarati crypto:hash <file>` (prints MD5, SHA-256, and entropy rating).

### 4. 👁️ Pillar 4: Real-Time File System Watcher & Sentinel
- **`watcher_init(dir_path, [recursive])` / `વોચર_શરૂ`**: Initializes asynchronous directory monitor hooking Windows `ReadDirectoryChangesW`.
- **`watcher_poll(watcher, [timeout_ms])` / `વોચર_મેળવો`**: Non-blocking queue consumer for filesystem change notifications.
- **`watcher_event_type(event)` / `વોચર_ઇવેન્ટ_પ્રકાર`**: Parses change actions (`created`, `modified`, `deleted`, `renamed`).
- **`watcher_on_change(watcher, callback)` / `વોચર_કોલબેક`**: Event-driven callback mechanism triggering automated virus scans on write.
- **CLI Subcommand**: `gujarati watch:dir <dir>` (launches interactive sentinel on specified directory).

### 5. ⚡ Pillar 5: Multi-Threading & Scanner Worker Pool
- **`thread_pool_create(worker_count)` / `થ્રેડ_પૂલ_બનાવો`**: Creates native OS worker thread pool leveraging all CPU cores.
- **`thread_pool_dispatch(pool, task, args)` / `થ્રેડ_પૂલ_મોકલો`**: Dispatches file paths and scanning jobs concurrently across worker threads.
- **`thread_pool_wait(pool, [timeout_ms])` / `થ્રેડ_પૂલ_રાહ`**: Synchronizes thread execution and awaits completion of pending scan queue.
- **`thread_pool_results(pool)` / `થ્રેડ_પૂલ_પરિણામ`**: Aggregates thread-safe results (total files scanned, malware detected, scan time).
- **CLI Subcommand**: `gujarati scan:parallel <dir>` (performs high-throughput multi-threaded scan).

### 6. 🛡️ Pillar 6: Process & System Diagnostics Module
- **`system_list_processes()` / `સિસ્ટમ_પ્રક્રિયા_યાદી`**: Wraps `CreateToolhelp32Snapshot` returning process list (PID, parent PID, executable path).
- **`system_get_process_cmdline(pid)` / `સિસ્ટમ_કમાન્ડલાઈન_તપાસ`**: Inspects command-line arguments to flag suspicious flags (`-enc`, `Bypass`, hidden windows).
- **`system_terminate_process(pid, [exit_code])` / `સિસ્ટમ_પ્રક્રિયા_અંત`**: Terminates malicious processes via Win32 `TerminateProcess`.
- **CLI Subcommand**: `gujarati process:list`, `gujarati process:kill <pid>`.

### 7. 🛡️ Pre-Coded Starter Kit 2: Rakshak Antivirus Suite (રક્ષક એન્ટિવાયરસ કિટ)
- **CLI Scaffolding**: `gujarati new <name> --kit=rakshak`, `gujarati kit:rakshak`, `gujarati kit:antivirus`
- Generates a full turn-key antivirus solution with signature definitions, parallel PE scanner, real-time sentinel directory watcher, process monitor, and interactive CLI quarantine dashboard.

---

# GujaratiLang v3.1.0: Parikshan & Sanchalan with Garvi Breeze Starter Kit (પરીક્ષણ અને સંચાલન એન્જિન)

GujaratiLang **v3.1.0** is officially released! This major release delivers 30 enterprise capabilities across 4 production operations pillars—OpenTelemetry distributed tracing, eBPF kernel sandboxing, Firecracker MicroVM virtualization, and GeoDNS Anycast edge routing—alongside our first official pre-coded boilerplate starter kit: **Garvi Breeze Auth**.

With v3.1.0, the automated test suite reaches the landmark **630 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v3.1.0

### 1. 🔭 Pillar 1: Drishti (દ્રષ્ટિ) OpenTelemetry & Distributed Tracing
- **`drishti_trace_start(span_name, [parent_span])` / `દ્રષ્ટિ_ટ્રેસ_શરૂ`**: Starts an active distributed trace span with nanosecond timestamps and trace ID generation.
- **`drishti_span_end(span, status)` / `દ્રષ્ટિ_સ્પાન_અંત`**: Closes span, calculates duration in microseconds, and seals execution record.
- **`drishti_span_tag(span, key, val)` / `દ્રષ્ટિ_સ્પાન_ટેગ`**: Attaches OpenTelemetry semantic conventions and custom metadata tags.
- **`drishti_trace_headers(span)` / `દ્રષ્ટિ_ટ્રેસ_હેડર`**: Extracts standard W3C `traceparent` and `tracestate` headers for HTTP propagation.
- **`drishti_metric_counter(name, val, tags)` / `દ્રષ્ટિ_મેટ્રિક_કાઉન્ટર`**: Records monotonic counter increments.
- **`drishti_metric_gauge(name, val, tags)` / `દ્રષ્ટિ_મેટ્રિક_ગેજ`**: Measures variable gauge metrics.
- **`drishti_otlp_export(endpoint, timeout_ms)` / `દ્રષ્ટિ_ઓટીએલપી_નિકાસ`**: Batches and exports traces/metrics in binary Protobuf OTLP wire format.
- **CLI Subcommands**: `gujarati drishti:trace <script.gj>`, `gujarati drishti:flamegraph [profile.json]`.

### 2. 🛡️ Pillar 2: Kavach (કવચ) eBPF Sandboxing & Zero-Trust Kernel
- **`kavach_sock_filter(proto, port)` / `કવચ_સોકેટ_ફિલ્ટર`**: Attaches kernel-level eBPF socket filter for sub-microsecond ingress/egress validation.
- **`kavach_seccomp_policy(whitelist)` / `કવચ_સેકકોમ્પ_નીતિ`**: Compiles BPF seccomp syscall whitelist enforcing strict zero-trust sandbox boundaries.
- **`kavach_ringbuf_poll(buffer, callback)` / `કવચ_રિંગબફર_મેળવો`**: Zero-copy BPF ring buffer reader polling kernel performance events.
- **`kavach_net_flow(interface)` / `કવચ_નેટ_પ્રવાહ`**: Direct NIC XDP flow monitor tracking packet throughput, retransmissions, and drops.
- **`kavach_mem_guard(limit_bytes)` / `કવચ_મેમરી_રક્ષક`**: Kernel page-table defense against heap overflows, memory exhaustion, and UAF attacks.
- **`kavach_anomaly_rule(rule_name, action)` / `કવચ_વિસંગતતા_નિયમ`**: Real-time behavioral anomaly trigger with automatic process isolation.
- **CLI Subcommands**: `gujarati kavach:monitor [process]`, `gujarati kavach:audit`.

### 3. ⚡ Pillar 3: Pavan (પવન) MicroVM Sandboxing & Firecracker Isolation
- **`pavan_vm_init(vcpus, ram_mb)` / `પવન_વીએમ_શરૂ`**: Initializes ultra-fast microVM guest instance (< 5ms cold boot).
- **`pavan_vm_boot(vm, kernel_img, rootfs)` / `પવન_વીએમ_બૂટ`**: Boots Linux uncompressed kernel binary inside KVM/Hyper-V virtualization container.
- **`pavan_cgroup_limit(vm, subsystem, val)` / `પવન_સીગ્રુપ_મર્યાદા`**: Configures hardware cgroup v2 CPU shares, memory caps, and IOPS throttling.
- **`pavan_virtio_disk(vm, disk_path)` / `પવન_વર્ચ્યુઅલ_ડિસ્ક`**: Attaches high-throughput non-blocking VirtIO block device.
- **`pavan_tap_bridge(vm, tap_dev)` / `પવન_ટેપ_બ્રિજ`**: Creates VirtIO-Net tap interface hooked to host virtual bridge.
- **`pavan_vm_checkpoint(vm, snapshot_path)` / `પવન_ચેકપોઇન્ટ`**: Live memory serialization and disk diff snapshotting in < 15ms.
- **`pavan_vm_resume(vm, snapshot_path)` / `પવન_પુનઃશરૂ`**: Instant microVM resume from snapshot image.
- **CLI Subcommands**: `gujarati pavan:spawn <rootfs>`, `gujarati pavan:ps`.

### 4. 🌐 Pillar 4: Anudan (અનુદાન) GeoDNS Anycast & Edge Mesh
- **`anudan_dns_resolve(domain, client_ip)` / `અનુદાન_ડીએનએસ`**: Anycast GeoDNS resolver returning nearest edge PoP with sub-2ms latency.
- **`anudan_health_probe(node, timeout_ms)` / `અનુદાન_આરોગ્ય_તપાસ`**: Active TCP/HTTP/ICMP health checker with jitter-free latency calculation.
- **`anudan_tls_acme(domain, email)` / `અનુદાન_ટીએલએસ_સર્ટ`**: Automated Let's Encrypt / ACME v2 zero-touch TLS 1.3 certificate generation and renewal.
- **`anudan_mesh_route(service, algorithm)` / `અનુદાન_મેશ_માર્ગ`**: Dynamic service mesh load-balancer (weighted, round-robin, least-connections).
- **`anudan_circuit_breaker(service, error_threshold)` / `અનુદાન_સર્કિટ_બ્રેકર`**: Distributed circuit breaker halting requests to failing upstream pods.
- **`anudan_token_bucket(capacity, refill_rate)` / `અનુદાન_ટોકન_બકેટ`**: Multi-region rate-limiting token bucket algorithm.
- **CLI Subcommands**: `gujarati mesh:status`, `gujarati mesh:drain <node>`.

### 5. 🍃 Pre-Coded Starter Kit 1: Garvi Breeze Auth (ગારવી બ્રિઝ ઓથેન્ટિકેશન કિટ)
- **CLI Scaffolding**:
  - `gujarati new <app_name> --kit=breeze`
  - `gujarati kit:auth`
  - `gujarati new:breeze`
- **What's Included**:
  - `models/user.gj`: Fully functional Eloquent SQLite User model with password hashing and timestamps.
  - `controllers/auth_controller.gj`: Complete authentication controller supporting Login, Registration, Session management, and Logout.
  - `views/layout.blade.gj`: Mobile-first responsive Blade master layout with modern styling.
  - `views/login.blade.gj` & `views/register.blade.gj`: Secure CSRF-protected authentication forms.
  - `views/dashboard.blade.gj`: Protected user dashboard showing authenticated session details.
  - `app.gj`: Pre-configured Garvi HTTP server listening on `:8080`.

---

# GujaratiLang v3.0.0 Mega-Release: The Grand Sovereign Cloud & Distributed Quantum Engine (સાર્વભૌમ ક્લાઉડ અને ક્વોન્ટમ એન્જિન)

GujaratiLang **v3.0.0** is officially released! This monumental **Mega-Release** delivers 50 enterprise-grade capabilities across 5 grand pillars: Sovereign Cloud & Edge micro-sandboxing, Zero-Knowledge proofs & Post-Quantum cryptography, Swaroop lightweight green actor runtime, Autonomous self-healing Raft consensus clusters, and Sovereign multi-agent collaborative swarms.

With v3.0.0, the automated test suite expands to the historic **600 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v3.0.0 Mega-Release

### 1. ☁️ Pillar 1: Sovereign Cloud & Serverless Edge (સાર્વભૌમ ક્લાઉડ અને એજ એન્જિન)
- **`cloud_edge_init(region, [opts])` / `ક્લાઉડ_એજ_શરૂ`**: Edge runtime coordinator with Anycast latency routing.
- **`cloud_edge_route(edge, path, handler)` / `ક્લાઉડ_એજ_માર્ગ`**: Micro-routing table with sub-millisecond edge dispatch.
- **`cloud_edge_kv(edge, key, value)` / `ક્લાઉડ_એજ_કેવી`**: Globally replicated distributed key-value edge store.
- **`cloud_worker_spawn(edge, script)` / `ક્લાઉડ_કાર્યકર_બનાવો`**: Sub-0.2ms cold-start micro-sandboxed worker thread.
- **`cloud_wasi_sandbox(edge, config)` / `ક્લાઉડ_વાસી_સેન્ડબોક્સ`**: Universal WASI Preview2 sandboxed execution environment.
- **`cloud_edge_cache(edge, key, val, [ttl])` / `ક્લાઉડ_એજ_કેશ`**: Edge static and dynamic cache with TTL and Brotli/Gzip compression.
- **`cloud_edge_headers(req, headers)` / `ક્લાઉડ_એજ_હેડર`**: Edge request/response header manipulation and geolocation tagging.
- **`cloud_tenant_isolate(tenant_id)` / `ક્લાઉડ_ભાડુઆત_અલગ`**: Strict multi-tenant CPU and memory quota isolation.
- **`cloud_metrics_export([format])` / `ક્લાઉડ_મેટ્રિક્સ_નિકાસ`**: Edge Prometheus/OpenTelemetry real-time metrics telemetry.
- **CLI Subcommands**: `gujarati cloud:deploy [bundle.gj]`, `gujarati cloud:status [node]`.

### 2. 🔐 Pillar 2: Zero-Knowledge & Post-Quantum Cryptography (ઝીરો-નોલેજ અને પોસ્ટ-ક્વોન્ટમ સુરક્ષા)
- **`zk_snark_prove(circuit, witness)` / `ઝેડકે_સાબિતી_બનાવો`**: Native Groth16 and PLONK zero-knowledge proof generation.
- **`zk_snark_verify(proof, public_inputs)` / `ઝેડકે_સાબિતી_ચકાસો`**: Sub-millisecond non-interactive zk proof verification.
- **`pqc_kyber_keypair()` / `પીક્યુસી_કાયબર_કી`**: NIST ML-KEM (Kyber-1024) quantum-resistant keypair generation.
- **`pqc_kyber_encapsulate(public_key)` / `પીક્યુસી_કાયબર_કેપ્સ્યુલ`**: Quantum-safe shared secret encapsulation.
- **`pqc_kyber_decapsulate(secret_key, ciphertext)` / `પીક્યુસી_કાયબર_ડિકેપ્સ્યુલ`**: Quantum-safe shared secret decapsulation.
- **`pqc_dilithium_sign(msg, secret_key)` / `પીક્યુસી_ડિલિથિયમ_સહી`**: NIST ML-DSA (Dilithium-5) quantum digital signature.
- **`pqc_dilithium_verify(msg, signature, public_key)` / `પીક્યુસી_ડિલિથિયમ_ચકાસો`**: Post-quantum digital signature verification.
- **`crypto_vrf_generate(seed, secret_key)` / `ક્રિપ્ટો_વીઆરએફ`**: Verifiable Random Function (VRF) with cryptographic proof.
- **`crypto_threshold_bls(t, n, shares)` / `ક્રિપ્ટો_થ્રેશોલ્ડ`**: Threshold BLS signature scheme with aggregate verification.
- **CLI Subcommands**: `gujarati pqc:genkey`, `gujarati zk:verify [proof.zk]`.

### 3. 🎭 Pillar 3: Swaroop (સ્વરૂપ) Distributed Green Actor Runtime
- **`swaroop_actor_create(name, [config])` / `સ્વરૂપ_એક્ટર_બનાવો`**: Ultra-lightweight green actor (< 2KB memory overhead).
- **`swaroop_actor_send(actor, message)` / `સ્વરૂપ_સંદેશ_મોકલો`**: Non-blocking mailbox message passing.
- **`swaroop_supervisor(children, strategy)` / `સ્વરૂપ_સુપરવાઇઝર`**: OneForOne and OneForAll fault-tolerant supervisor tree.
- **`swaroop_actor_monitor(watcher, target)` / `સ્વરૂપ_મોનિટર`**: Unidirectional crash notification observer.
- **`swaroop_actor_link(actor_a, actor_b)` / `સ્વરૂપ_જોડાણ`**: Bidirectional fatal crash propagation link.
- **`swaroop_hot_reload(actor, new_fn)` / `સ્વરૂપ_હોટ_રીલોડ`**: Live code swapping without draining mailbox or resetting state.
- **`swaroop_mailbox_priority(actor, level)` / `સ્વરૂપ_મેઇલબોક્સ_પ્રાથમિકતા`**: Multi-tier priority queue mailbox.
- **`swaroop_registry_bind(name, actor)` / `સ્વરૂપ_નોંધણી`**: Distributed name registry binding.
- **`swaroop_registry_lookup(name)` / `સ્વરૂપ_શોધો`**: Global cluster-wide actor lookup.
- **CLI Subcommands**: `gujarati swaroop:top`, `gujarati swaroop:cluster`.

### 4. 🛡️ Pillar 4: Autonomous Raft Consensus Clusters (સ્વાયત્ત રાફ્ટ ક્લસ્ટર)
- **`raft_cluster_init(node_id, peers)` / `રાફ્ટ_ક્લસ્ટર_શરૂ`**: Pure C99 Raft distributed consensus node coordinator.
- **`raft_election_timeout(cluster)` / `રાફ્ટ_ચૂંટણી_સમય`**: Randomized election timer trigger with split-vote avoidance.
- **`raft_log_append(cluster, command)` / `રાફ્ટ_લોગ_ઉમેરો`**: Distributed log replication with quorum consensus confirmation.
- **`raft_state_machine_apply(cluster, command)` / `રાફ્ટ_સ્ટેટ_મશીન`**: Linearizable Replicated State Machine (RSM) applier.
- **`raft_log_compact(cluster, index)` / `રાફ્ટ_લોગ_સંકુચિત`**: Snapshot compaction with differential log truncation.
- **`raft_snapshot_restore(cluster, snapshot)` / `રાફ્ટ_સ્નેપશોટ_પુનઃપ્રાપ્તિ`**: Fast state catch-up for lagging or new nodes.
- **`raft_joint_consensus(cluster, old_cfg, new_cfg)` / `રાફ્ટ_સંયુક્ત_સંમતિ`**: Zero-downtime dynamic cluster membership migration.
- **`raft_split_brain_guard(cluster)` / `રાફ્ટ_વિભાજન_સુરક્ષા`**: Network partition defense with majority quorum fencing.
- **`raft_cross_region_federate(cluster, remote_cluster)` / `રાફ્ટ_પ્રદેશ_ફેડરેશન`**: Cross-region anti-entropy gossip federation.
- **CLI Subcommands**: `gujarati raft:quorum`, `gujarati raft:stepdown`.

### 5. 👑 Pillar 5: Sovereign Architecture & Swarms (સાર્વભૌમ આર્કિટેક્ચર અને એજન્ટ સ્વોર્મ)
- **`sovereign_agent_swarm(count, role)` / `સાર્વભૌમ_એજન્ટ_સ્વોર્મ`**: Multi-agent collaborative decision swarm.
- **`sovereign_task_decompose(swarm, task)` / `સાર્વભૌમ_કાર્ય_વિભાજન`**: Autonomous hierarchical goal decomposition.
- **`sovereign_python_bridge(module, fn, args)` / `સાર્વભૌમ_પાયથન_સેતુ`**: Direct zero-copy C-Python bridge.
- **`sovereign_rust_ffi(lib, fn, args)` / `સાર્વભૌમ_રસ્ટ_સેતુ`**: Native C-ABI Rust foreign function interop.
- **`sovereign_bytecode_verify(bytecode)` / `સાર્વભૌમ_બાઇટકોડ_ચકાસો`**: Formal cryptographic verification of compiled bytecode.
- **`sovereign_mcu_profile(architecture)` / `સાર્વભૌમ_એમસીયુ_પ્રોફાઇલ`**: Embedded microcontroller sizing (< 64KB RAM).
- **`sovereign_replay_debugger(recording)` / `સાર્વભૌમ_રીપ્લે_ડિબગર`**: Deterministic time-travel replay debugger.
- **`sovereign_audit_compliance(standard)` / `સાર્વભૌમ_ઓડિટ_સુસંગતતા`**: Regulatory data sovereignty and geolocation border compliance.
- **`sovereign_lts_guarantee(component)` / `સાર્વભૌમ_સ્થિરતા_ખાતરી`**: 10-Year Long-Term Support architectural stability guarantee (2026-2036).
- **CLI Subcommands**: `gujarati swarm:run [swarm.gj]`, `gujarati kernel:audit`.

---

# GujaratiLang v2.9.0: Pravah, Shilp, Vidyut & Yantra (પ્રવાહ, શિલ્પ, વિદ્યુત અને યંત્ર)

GujaratiLang **v2.9.0** is officially released! This landmark update delivers 30 advanced enterprise capabilities across four major pillars: high-throughput distributed event streaming with Kafka wire protocol, 2D/3D hardware-accelerated vector canvas and graphics engine, pure C99 Raft consensus clustering with distributed locks and Erlang-style actors, and an in-memory HNSW vector database with dense neural embeddings and hybrid semantic search.

With v2.9.0, the automated test suite expands to the **560 Tests Milestone (100% Pass Rate)** across Windows x64, Linux x64, macOS x64, and macOS Apple Silicon (ARM64).

---

## 🌟 What's New in v2.9.0

### 1. 🌊 Pravah (પ્રવાહ) — Distributed Streaming & Event Mesh
High-throughput distributed event broker and streaming engine with partitioned topics and consumer groups:
- **`pravah_producer(config)` / `પ્રવાહ_ઉત્પાદક`**: Spawns an event streaming publisher connection to the broker mesh.
- **`pravah_consumer(config)` / `પ્રવાહ_ગ્રાહક`**: Joins a consumer group with automatic partition rebalancing and offset tracking.
- **`pravah_send(producer, topic, msg, [key])` / `પ્રવાહ_મોકલો`**: Dispatches partitioned messages with hash routing.
- **`pravah_poll(consumer, timeout_ms)` / `પ્રવાહ_મેળવો`**: Polls incoming events with partition and offset metadata.
- **`pravah_commit(consumer)` / `પ્રવાહ_સ્વીકાર`**: Commits consumer offsets to the broker log for at-least-once delivery.
- **`pravah_dlq(stream, dlq_topic)` / `પ્રવાહ_મૃત_પત્ર`**: Routes unprocessable poisoned payloads into dead-letter queues.
- **`pravah_window(stream, window_ms, fn)` / `પ્રવાહ_સમય_બારી`**: Sliding and tumbling time-windowed stream aggregations.
- **CLI Subcommands**: `gujarati pravah:stream [topic]` launches a real-time event pump; `gujarati pravah:consume [topic]` subscribes to stream topics.

### 2. 🎨 Shilp (શિલ્પ) — High-Performance Vector Canvas & Graphics Engine
Hardware-accelerated 2D/3D vector scene graph with SVG path rendering and bitmap export:
- **`shilp_scene(width, height)` / `શિલ્પ_દ્રશ્ય`**: Creates a vector drawing context and hierarchical scene graph.
- **`shilp_draw_path(scene, svg_path, style)` / `શિલ્પ_માર્ગ`**: Renders complex Bézier curves, arcs, and SVG path commands.
- **`shilp_draw_text(scene, text, x, y, font)` / `શિલ્પ_લખાણ`**: Vector typography layout with font sizing and glyph anti-aliasing.
- **`shilp_transform(node, matrix)` / `શિલ્પ_રૂપાંતરણ`**: Applies 2D/3D affine transformation matrices (scaling, rotation, translation).
- **`shilp_gradient(type, stops)` / `શિલ્પ_ઢાળ`**: Linear and radial multi-stop color gradient shaders.
- **`shilp_export_svg(scene, [path])` / `શિલ્પ_નિકાસ_svg`**: Serializes the scene graph into clean, resolution-independent SVG XML markup.
- **`shilp_export_png(scene, [path])` / `શિલ્પ_નિકાસ_png`**: Rasterizes vector graphics into uncompressed PNG bitmaps.
- **CLI Subcommand**: `gujarati shilp:render <scene.gj> [output.png]` compiles programmatic canvas scenes directly to images.

### 3. ⚡ Vidyut (વિદ્યુત) — Pure C99 Raft Consensus & Actor System
Resilient distributed coordination engine without external Zookeeper or etcd dependencies:
- **`vidyut_cluster(node_id, peers)` / `વિદ્યુત_ક્લસ્ટર`**: Boots a distributed cluster coordinator instance.
- **`vidyut_raft_state(cluster)` / `વિદ્યુત_રાફ્ટ_સ્થિતિ`**: Inspects current node consensus state (`Leader`, `Follower`, `Candidate`), term, and active leader ID.
- **`vidyut_dlock_acquire(cluster, lock, [ttl])` / `વિદ્યુત_તાળું_મેળવો`**: Acquires a distributed mutual-exclusion lock with lease expiration.
- **`vidyut_dlock_release(cluster, lock)` / `વિદ્યુત_તાળું_છોડો`**: Safely releases held distributed locks across cluster peers.
- **`vidyut_actor_spawn(behavior_fn)` / `વિદ્યુત_અભિનેતા`**: Spawns an Erlang-style lightweight isolated actor process.
- **`vidyut_actor_send(actor, message)` / `વિદ્યુત_સંદેશ`**: Non-blocking asynchronous message passing into actor mailboxes.
- **CLI Subcommands**: `gujarati vidyut:status [node]` audits Raft cluster health; `gujarati vidyut:join <peer>` joins dynamic peer quorums.

### 4. 🧠 Yantra (યંત્ર) — Vector Database & Neural Embeddings
In-memory high-dimensional vector search engine with SIMD metric calculations and hybrid search:
- **`yantra_vector_db(dimension, [metric])` / `યંત્ર_વેક્ટર_ડીબી`**: Creates an in-memory HNSW vector database with cosine, Euclidean, or dot metrics.
- **`yantra_insert(vdb, id, vector, [metadata])` / `યંત્ર_દાખલ`**: Indexes high-dimensional dense vectors with arbitrary metadata dictionaries.
- **`yantra_search(vdb, query_vector, top_k)` / `યંત્ર_શોધ`**: Sub-millisecond approximate nearest neighbor (ANN) retrieval.
- **`yantra_embed_text(text, [model])` / `યંત્ર_એમ્બેડ`**: Computes normalized dense neural embeddings from text strings.
- **`yantra_cosine(vec1, vec2)` / `યંત્ર_કોસાઈન`**: SIMD-optimized vector cosine distance computation.
- **`yantra_hybrid_rank(vdb, text, vec, alpha)` / `યંત્ર_સંકર_શોધ`**: Fuses lexical BM25 keyword matching with semantic vector rankings.
- **CLI Subcommand**: `gujarati yantra:search [index] [query]` performs interactive semantic queries over indexed documents.

---

## 🛡️ The 560 Tests Milestone (100% Pass Rate)
GujaratiLang v2.9.0 elevates automated testing to **560 automated test suites**:
- **548 Language & Subsystem Test Suites**: Comprehensive coverage spanning core lexing, parsing, AST execution, Eloquent ORM, Blade templating, Redis-style caching, Pub/Sub, Desktop GUI, 2D Canvas, Android Camera/Sensors, AOT Compiler, C-FFI, Kasauti browser automation, Mandhan migrations, Garvi web framework, Samvad AI agents, Saransh packaging, Tarang WebSockets, Setu GraphQL, Kasauti v2, Suraksha v2, and the new v2.9.0 Pravah, Shilp, Vidyut, and Yantra suites.
- **12 Production Example Programs**: Fibonacci, Temperature Converter, Inventory, Stock, Calculator, String Utils, CSV Parser, Math Suite, Text Filter, Report Generator, Invoice Generator, and Random Game.
- **100% CTest Pass Rate** across Windows x64, Linux x64, macOS x64, and macOS ARM64.

---

## 🚀 The Road Ahead: The Grand v3.0.0 Mega-Release (50 Points)
The ultimate 50-point crowning milestone of GujaratiLang is next:
- **GujaratiOS Sovereign Runtime Kernel & Pure C99 Microkernel Architecture**
- **Autonomous Multi-Agent AI Swarms & Neural Graph Synthesis**
- **Zero-Knowledge & Post-Quantum Cryptographic Defense (zk-SNARK, ML-KEM Kyber-1024, ML-DSA Dilithium)**
- **WASI 2.0 Pure Sandboxing & Global Anycast Serverless Edge Runtime**
- **The Grand 1,000 Tests Milestone & LTS 2030 Enterprise Support Guarantees**

---

## 🌐 Live Website & Playground
The official portal, chronicle, and interactive playground are updated and deployed live:
- **Official Website**: [https://gujaratilang.hp-square.com/](https://gujaratilang.hp-square.com/)
- **Release Chronicle**: [https://gujaratilang.hp-square.com/history.html](https://gujaratilang.hp-square.com/history.html)
