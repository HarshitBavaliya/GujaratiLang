# GujaratiLang Complete Language Reference

This reference document catalogs the syntax, keywords, operators, and built-in functions of **GujaratiLang (ગુજરાતી લેંગ્વેજ)**.

---

## 1. Trilingual Keyword Equivalence Matrix

GujaratiLang allows writing programs in **English**, **Romanized Gujarati**, or **Native Gujarati Unicode**. The table below shows the exact equivalents:

| English Keyword | Romanized Gujarati | Native Gujarati Unicode | Description |
|---|---|---|---|
| `start` | `aavo` | `આવો` | Marks the beginning of a program block |
| `end` | `aavjo` | `આવજો` | Marks the conclusion of a program block |
| `print` | `chhapo` | `છાપો` | Prints a value or expression to stdout with newline |
| `if` | `jo` | `જો` | Conditional branch condition |
| `else if` | `athva` / `nahitar_jo` | `અથવા` / `નહિતર_જો` | Alternative conditional branch |
| `else` | `nahitar` | `નહિતર` | Default fallback conditional branch |
| `while` | `jya_sudhi` | `જ્યાં_સુધી` | While loop repeating while condition is truthy |
| `for` | `darek` | `દરેક` | For-in loop iterating over lists or dictionaries |
| `in` | `ma` | `માં` / `મા` | Membership selector in `for-in` loop |
| `break` | `atko` | `અટકો` | Immediately terminates the nearest loop |
| `continue` | `chalu_rakho` | `ચાલુ_રાખો` | Skips to the next iteration of the nearest loop |
| `function` | `kary` | `કાર્ય` | Declares a named function |
| `return` | `parat` | `પરત` | Returns a value from a function |
| `class` | `varg` | `વર્ગ` | Declares an object-oriented class |
| `new` | `navu` | `નવું` | Instantiates a class instance |
| `this` / `self` | `a_pote` | `આ_પોતે` | Refers to the current class instance |
| `constructor` | `rachna` | `રચના` | Class constructor method |
| `import` | `aayat` | `આયાત` | Imports another `.gj` module |
| `as` | `tarike` | `તરીકે` | Renames an imported module alias |
| `null` | `nakamo` | `નકામો` | Represents empty/null reference |
| `and` | `ane` | `અને` | Logical boolean AND (`&&` or `ane`) |
| `or` | `athva` | `અથવા` | Logical boolean OR (`\|\|` or `athva`) |
| `not` | `nathi` | `નથી` | Logical boolean NOT (`!` or `nathi`) |

---

## 2. Program Structure

Every program begins with `start` (`aavo` / `આવો`) and concludes with `end` (`aavjo` / `આવજો`). Statements are separated by semicolons (`;`).

```gujarati
// Single line comments begin with double slashes
/* Multi-line comments
   are enclosed like C */

aavo
chhapo "હેલ્લો વર્લ્ડ!";
aavjo
```

---

## 3. Data Types & Literals

GujaratiLang provides 5 primary runtime data types:

| Data Type | Description | Example Literals |
|---|---|---|
| **Number** | 64-bit IEEE 754 floating point | `42`, `-17.5`, `0.003`, `1e6` |
| **String** | UTF-8 encoded text string | `"નમસ્તે"`, `"Hello"`, `"Value: \n"` |
| **List** | Dynamic resizable array | `[1, 2, "three", [4, 5]]` |
| **Dictionary** | Key-value associative hash table | `{"name": "Alice", "age": 30}` |
| **Null** | Represents absence of a value | `nakamo` / `નકામો` / `null` |

---

## 4. Operators

### Arithmetic Operators
- `+` : Addition (numbers) or concatenation (strings)
- `-` : Subtraction
- `*` : Multiplication
- `/` : Division (with divide-by-zero runtime protection)
- `%` : Modulo (remainder)

### Comparison Operators
- `==` : Value equality
- `!=` : Value inequality
- `<`  : Less than
- `<=` : Less than or equal to
- `>`  : Greater than
- `>=` : Greater than or equal to

### Logical Operators
- `ane` / `&&` : Short-circuit logical AND
- `athva` / `||` : Short-circuit logical OR
- `nathi` / `!` : Logical negation

---

## 5. Control Flow

### If / Else Conditions
```gujarati
aavo
temp = 32;

jo (temp > 35) {
    chhapo "ગરમી છે (Hot)";
} athva (temp < 15) {
    chhapo "ઠંડી છે (Cold)";
} nahitar {
    chhapo "હવામાન સારું છે (Pleasant)";
}
aavjo
```

### While Loops
```gujarati
aavo
count = 1;
jya_sudhi (count <= 5) {
    chhapo "ગણતરી: " + lakhan(count);
    count = count + 1;
}
aavjo
```

### For-In Loops
```gujarati
aavo
names = ["અમદાવાદ", "સુરત", "વડોદરા", "રાજકોટ"];
darek (city ma names) {
    chhapo "શહેર: " + city;
}
aavjo
```

### Loop Interruption (`atko` and `chalu_rakho`)
```gujarati
aavo
i = 0;
jya_sudhi (i < 10) {
    i = i + 1;
    jo (i == 3) { chalu_rakho; } // skip 3
    jo (i == 7) { atko; }        // break at 7
    chhapo i;
}
aavjo
```

---

## 6. Functions

Functions are defined with `kary` (or `function` / `કાર્ય`) and can accept parameters and return values:

```gujarati
aavo
kary factorial(n) {
    jo (n <= 1) {
        parat 1;
    }
    parat n * factorial(n - 1);
}

chhapo factorial(5); // 120
aavjo
```

---

## 7. Classes and Objects

```gujarati
aavo
varg Gadi {
    rachna(brand, speed) {
        a_pote.brand = brand;
        a_pote.speed = speed;
    }

    accelerate(amount) {
        a_pote.speed = a_pote.speed + amount;
        parat a_pote.speed;
    }
}

car = navu Gadi("Tesla", 80);
car.accelerate(40);
chhapo car.speed; // 120
aavjo
```

---

## 8. Standard Library Primitives (By Category)

### String Functions
| English Built-in | Romanized Gujarati | Native Gujarati Unicode | Description |
|---|---|---|---|
| `lambai(str)` | `lambai(str)` | `લંબાઈ` | Codepoint length of string or list count |
| `kapo(str, start, len)` | `kapo` | `કાપો` | Slices a string |
| `shodho(haystack, needle)`| `shodho` | `શોધો` | Finds substring index (-1 if absent) |
| `bhag(str, delim)` | `bhag` | `ભાગ` | Splits string into list of tokens |
| `jodo(list, delim)` | `jodo` | `જોડો` | Joins list of strings into one string |
| `saf(str)` | `saf` | `સાફ` | Trims leading/trailing whitespace |
| `badlo(str, old, new)` | `badlo` | `બદલો` | Replaces occurrences of a substring |
| `peli_abcd(str)` | `peli_abcd` | `પહેલી_એબીસીડી` | Converts string to uppercase |
| `biji_abcd(str)` | `biji_abcd` | `બીજી_એબીસીડી` | Converts string to lowercase |

### List & Dictionary Functions
| English Built-in | Romanized Gujarati | Native Gujarati Unicode | Description |
|---|---|---|---|
| `umero(list, item)` | `umero` | `ઉમેરો` | Appends item to list in-place |
| `kadho(list[, idx])` | `kadho` | `કાઢો` | Removes and returns item from list |
| `gothvo(list)` | `gothvo` | `ગોઠવો` | Sorts list elements in ascending order |
| `ultavo(list)` | `ultavo` | `ઉલટાવો` | Reverses list in-place |
| `samave_chhe(col, item)`| `samave_chhe` | `સમાવે_છે` | Returns 1 if collection contains item, 0 otherwise |
| `chavio(dict)` | `chavio` | `ચાવીઓ` | Returns list of dictionary keys |
| `mulyo(dict)` | `mulyo` | `મૂલ્યો` | Returns list of dictionary values |

### Math Functions
| English Built-in | Romanized Gujarati | Native Gujarati Unicode | Description |
|---|---|---|---|
| `dhan_mulya(n)` | `dhan_mulya` | `ધન_મૂલ્ય` | Absolute value of a number |
| `mul(n)` | `mul` | `મૂળ` | Square root of number |
| `ghat(b, e)` | `ghat` | `ઘાત` | Calculates $b^e$ (power) |
| `gol(n)` | `gol` | `ગોળ` | Rounds to nearest whole number |
| `pi()` | `pi` | `પાઈ` | Mathematical constant $\pi \approx 3.14159265$ |
| `e()` | `e` | `ઈ` | Mathematical constant $e \approx 2.71828182$ |
| `yadachhik(min, max)` | `yadachhik` | `યાદચ્છિક` | Generates pseudo-random number in range |

### System & Networking
| English Built-in | Romanized Gujarati | Native Gujarati Unicode | Description |
|---|---|---|---|
| `vancho(prompt)` | `vancho` | `વાંચો` | Reads a line of text from standard input |
| `paryavaran(name)` | `paryavaran` | `પર્યાવરણ` | Gets system environment variable |
| `bahar(code)` | `bahar` | `બહાર` | Exits the program with return code |
| `file_vancho(path)` | `file_vancho` | `ફાઇલ_વાંચો` | Reads entire file contents as string |
| `file_lakho(path, text)` | `file_lakho` | `ફાઇલ_લખો` | Writes string content to file path |
| `http_get(url)` | `http_get` | `નેટ_મેળવો` | Executes HTTP GET request |
| `http_post(url, body)` | `http_post` | `નેટ_મોકલો` | Executes HTTP POST request |

### Decentralized & Planetary Networking (v3.9.0)
| English Built-in | Romanized Gujarati | Native Gujarati Unicode | Description |
|---|---|---|---|
| `dtn_bundle_create(...)` | `dtn_bundle_bnavo` | `ડીટીએન_બંડલ_બનાવો` | RFC 5050 DTN bundle creation |
| `mesh_packet_send(...)` | `mesh_packet_moklo` | `મેશ_પેકેટ_મોકલો` | Sub-GHz ad-hoc mesh packet broadcaster |
| `ipfs_cid_generate(...)` | `ipfs_cid_bnavo` | `આઈપીએફએસ_સીઆઈડી_બનાવો` | Computes CIDv0/v1 IPFS multihash |
| `did_create(...)` | `did_bnavo` | `ડીઆઈડી_બનાવો` | W3C DID generator (`did:key`, `did:guj`) |
| `vc_issue(...)` | `vc_aapo` | `વીસી_આપો` | W3C Verifiable Credential issuer |
| `vc_sign(...)` | `vc_sahikaro` | `વીસી_સહીકરો` | Cryptographic proof signer |
| `vc_verify(...)` | `vc_chakasani` | `વીસી_ચકાસણી` | Signature & claim validator |


### 7. Self-Hosting AST, Wasm, Post-Quantum & Multi-Agent (v4.0.0 Grand Unification)

| English Function | Romanized Gujarati | Native Gujarati Unicode | Description |
|---|---|---|---|
| `ast_parse(source)` | `ast_vancho` | `એએસટી_વાંચો` | Parses source code into an in-memory AST dictionary |
| `ast_dump(node)` | `ast_nikas` | `એએસટી_નિકાસ` | Serializes an AST node hierarchy into S-expression text |
| `ast_node_type(node)` | `ast_nod_prakar` | `એએસટી_નોડ_પ્રકાર` | Returns syntax categorization of an AST node |
| `ast_walk(node, visitor)` | `ast_chalo` | `એએસટી_ચાલો` | Traverses AST tree calculating metrics & visiting nodes |
| `ast_transform(node, rule)` | `ast_badlo` | `એએસટી_બદલો` | In-memory AST tree rewriting and macro expansions |
| `ast_eval(node[, env])` | `ast_mulyankan` | `એએસટી_મૂલ્યાંકન` | Dynamically evaluates an in-memory AST subtree |
| `ast_validate_syntax(code)` | `ast_chakasani` | `એએસટી_ચકાસણી` | Validates syntax without raising runtime errors |
| `wasm_module_create(name)` | `wasm_module_bnavo` | `વાસ્મ_મોડ્યુલ_બનાવો` | Initializes a binary WebAssembly module builder |
| `wasm_func_add(m, n, p, r, b)` | `wasm_kary_umero` | `વાસ્મ_કાર્ય_ઉમેરો` | Emits a WebAssembly function with bytecode instructions |
| `wasm_memory_define(m, min, max)` | `wasm_smruti_bnavo` | `વાસ્મ_સ્મૃતિ_બનાવો` | Configures WebAssembly linear memory bounds |
| `wasm_export_symbol(m, i, e, k)` | `wasm_nikas_chinha` | `વાસ્મ_નિકાસ_ચિહ્ન` | Exports a symbol (function, memory, global) |
| `wasm_emit_binary(module)` | `wasm_binary_kramit` | `વાસ્મ_બાઈનરી_ક્રમિત` | Compiles module into standard `.wasm` bytecode binary |
| `wasm_validate(bytes)` | `wasm_chakasani` | `વાસ્મ_ચકાસણી` | Validates binary WebAssembly magic bytes & sections |
| `wasm_disassemble(bytes)` | `wasm_vigathan` | `વાસ્મ_વિઘટન` | Disassembles `.wasm` binary into WebAssembly Text (WAT) |
| `pqc_mlkem_keypair()` | `pqc_mlkem_jodi` | `પીક્યુસી_એમએલકેઈએમ_જોડી` | Generates NIST FIPS 203 ML-KEM-768 lattice keypair |
| `pqc_mlkem_encap(pubkey)` | `pqc_mlkem_bandho` | `પીક્યુસી_એમએલકેઈએમ_બાંધો` | Encapsulates 256-bit symmetric shared key |
| `pqc_mlkem_decap(ct, privkey)` | `pqc_mlkem_kholo` | `પીક્યુસી_એમએલકેઈએમ_ખોલો` | Decapsulates and verifies shared secret in constant-time |
| `pqc_mldsa_keypair()` | `pqc_mldsa_jodi` | `પીક્યુસી_એમએલડીએસએ_જોડી` | Generates NIST FIPS 204 ML-DSA-65 signature keypair |
| `pqc_mldsa_sign(msg, privkey)` | `pqc_mldsa_sahi` | `પીક્યુસી_એમએલડીએસએ_સહી` | Signs payload with lattice polynomial vector proofs |
| `pqc_mldsa_verify(msg, sig, pub)` | `pqc_mldsa_chakasani` | `પીક્યુસી_એમએલડીએસએ_ચકાસણી` | Verifies post-quantum digital signature |
| `swarm_init(swarm, node, q)` | `sangh_saruaat` | `સંઘ_શરૂઆત` | Initializes autonomous agent swarm coordinator |
| `swarm_peer_register(s, p, caps)` | `sangh_sathi_umero` | `સંઘ_સાથી_ઉમેરો` | Registers swarm peers and capability tags |
| `swarm_proposal_submit(s, id, p)` | `sangh_prastav_aapo` | `સંઘ_પ્રસ્તાવ_આપો` | Submits distributed proposal to swarm |
| `swarm_vote_cast(s, id, vote, sig)` | `sangh_mat_aapo` | `સંઘ_મત_આપો` | Casts authenticated vote on proposal |
| `swarm_consensus_check(s, id)` | `sangh_sammat_chakasani` | `સંઘ_સંમત_ચકાસણી` | Checks BFT supermajority quorum threshold |
| `swarm_task_auction(s, task, bids)` | `sangh_kam_haraji` | `સંઘ_કામ_હરાજી` | Conducts second-price distributed task allocation |

### 9. Parmanu & Shakti: Pure C99 Quantum Circuit Simulator, SIMD Vectorization, Smart Energy Grid & Lattice Boltzmann CFD (v4.2.0)

GujaratiLang v4.2.0 introduces quantum circuits, high-throughput SIMD vector operations, smart renewable microgrids, and 2D Lattice Boltzmann fluid dynamics.

#### 1. Parmanu Quantum Circuit Simulation
```gujarati
start
// Create a 2-qubit quantum circuit register
c = quantum_circuit_create(2);

// Apply Hadamard gate to create superposition on qubit 0
quantum_gate_apply(c, "H", 0);

// Apply CNOT gate (control=0, target=1) to create Bell state
quantum_gate_apply(c, "CNOT", 0, 1);

// Measure the quantum statevector (1024 shots)
m = quantum_measure(c, 1024);
print m["shots"];

// Compute von Neumann entanglement entropy
s = quantum_entropy(c);
print s;
end
```

#### 2. Gati-SIMD Vector Operations
```gujarati
start
v1 = simd_vector_create([1.0, 2.0, 3.0, 4.0]);
v2 = simd_vector_create([5.0, 6.0, 7.0, 8.0]);

// SIMD 4-way unrolled vector add
v_sum = simd_vector_add(v1, v2);

// Kahan-compensated dot product
dot = simd_vector_dot(v1, v2);
print dot;

// Euclidean norm & tree reduction
norm = simd_vector_norm(v1);
total = simd_parallel_reduce(v1, "sum");
print total;
end
```

#### 3. Shakti Smart Grid & Energy Dispatch
```gujarati
start
buses = [
    {"id": 1, "type": "slack", "voltage": 1.0, "angle": 0.0},
    {"id": 2, "type": "pq", "voltage": 0.98, "angle": -0.05}
];
branches = [{"from": 1, "to": 2, "r": 0.01, "x": 0.05}];

// Solve multi-bus power flow
pf = grid_power_flow_solve(buses, branches, 10, 0.0001);

// Update BESS state of charge
soc = battery_soc_update(85.0, 15.0, 1.0, 50.0, 0.95);

// Calculate solar irradiance (DNI / GHI)
irr = solar_irradiance_calc(23.0, 72.5, 12.0, 0.8);
print irr["dni_w_m2"];
end
```

#### 4. Taral Lattice Boltzmann CFD Simulation
```gujarati
start
// Create 2D D2Q9 lattice mesh (width=100, height=40, tau=0.6)
lat = lbm_lattice_create(100, 40, 0.6);

// Perform BGK collision and streaming step
step = lbm_collide_and_stream(lat);

// Apply no-slip bounceback boundary at obstacle (x=15, y=20)
lbm_boundary_bounceback(lat, 15, 20);

// Extract velocity field and calculate Reynolds number
vf = lbm_velocity_field(lat);
re = lbm_reynolds_number(0.1, 10.0, 0.02);
print re;
end
```

### 8. Brahmand & Antariksh: Tensor Autodiff, Satellite Mechanics, Deterministic RTOS & Homomorphic Encryption (v4.1.0)

| English Function | Romanized Gujarati | Native Gujarati Unicode | Description |
|---|---|---|---|
| `tensor_create(shape, data)` | `tensor_bnavo` | `ટેન્સર_બનાવો` | Creates N-dimensional autodiff tensor with shape descriptor and gradient tracking |
| `tensor_matmul(a, b)` | `tensor_gunakar` | `ટેન્સર_ગુણાકાર` | BLAS-grade 2D matrix multiplication with computational graph stitching |
| `tensor_backward(tensor)` | `tensor_pachhad` | `ટેન્સર_પાછળ` | Reverse-mode automatic differentiation backpropagation over computational graph |
| `tensor_grad(tensor)` | `tensor_dhal` | `ટેન્સર_ઢાળ` | Retrieves partial derivatives/gradient vector for parameter updates |
| `nn_dense(in_dim, out_dim, act)` | `nn_sthar_ghat` | `ચેતાતંત્ર_સ્તર` | Constructs fully-connected neural layer with Xavier initialization & activations |
| `nn_forward(layer, x)` | `nn_aagal` | `ચેતાતંત્ર_આગળ` | Evaluates forward inference pass ($y = \sigma(W \cdot x + b)$) |
| `nn_train_step(layer, x, y, lr)` | `nn_talim_paglu` | `ચેતાતંત્ર_તાલીમ_પગલું` | Computes MSE loss, backprop pass, and SGD/Adam parameter update |
| `orbit_sgp4_propagate(tle1, tle2, t)` | `kaksha_sgp4_ganatri` | `કક્ષા_ગણતરી` | SGP4 orbital propagator calculating sub-satellite coordinates and orbital velocity |
| `ground_station_pass(lat, lon, ...)` | `station_sampark` | `સ્ટેશન_સંપર્ક` | Computes ground station AOS/LOS passes, elevation angle, and line-of-sight duration |
| `ccsds_packet_encode(hdr, payload)` | `ccsds_packet_kod` | `સીસીએસડીએસ_પેકેટ_કોડ` | Encodes CCSDS 133.0-B-2 space telemetry packet with APID, sequence counter & CRC-16 |
| `ccsds_packet_decode(packet_hex)` | `ccsds_packet_khulaso` | `સીસીએસડીએસ_પેકેટ_ખુલાસો` | Decodes raw space telemetry hex stream, verifying CRC checksum integrity |
| `doppler_shift_calc(freq, rate)` | `doppler_ganatri` | `ડોપ્લર_ગણતરી` | Computes relativistic Doppler shift frequency corrections for RF transceivers |
| `quaternion_slerp(q1, q2, t)` | `quaternion_antarvesh` | `ચતુષ્કોણ_અંતર્વેશન` | Spherical Linear Interpolation (SLERP) for satellite attitude quaternion steering |
| `sched_task_periodic(name, p, d, fn)` | `samay_kary_aavartak` | `સમય_કાર્ય_આવર્તક` | Registers real-time task with Period ($T$), Worst-Case Execution Time ($C$), and Deadline ($D$) |
| `sched_dispatch_edf()` | `samay_chalak_edf` | `સમય_ચાલક_ઈડીએફ` | Executes provably optimal Earliest Deadline First (EDF) dynamic priority real-time scheduler |
| `sched_deadline_check()` | `samay_maryada_tapas` | `સમય_મર્યાદા_તપાસ` | Evaluates system schedulability guarantees ($U \le 1.0$), ensuring 0 deadline overruns |
| `timer_monotonic_micros()` | `sukshma_samay` | `સૂક્ષ્મ_સમય` | High-resolution microsecond monotonic hardware timer |
| `ringbuffer_bounded(capacity)` | `chakriya_bafar` | `ચક્રીય_બફર` | Lock-free bounded circular ringbuffer for deterministic telemetry ingestion |
| `ringbuffer_push(rb, item)` | `chakriya_mukvo` | `ચક્રીય_મૂકવો` | Thread-safe push operation into circular ringbuffers with overflow protection |
| `paillier_keygen(key_bits)` | `paillier_jodi` | `પેલિયર_જોડી` | Generates Paillier additive homomorphic cryptosystem public and private keys |
| `paillier_encrypt(val, pubkey)` | `paillier_gupt` | `પેલિયર_ગુપ્ત` | Encrypts numbers into homomorphic ciphertexts ($c = g^m \cdot r^n \pmod{n^2}$) |
| `paillier_add_ciphertexts(c1, c2, pub)` | `paillier_sarvalo` | `પેલિયર_સરવાળો` | Computes encrypted addition homomorphically without decryption |
| `paillier_decrypt(ct, privkey)` | `paillier_kholo` | `પેલિયર_ખોલો` | Recovers exact plaintexts from ciphertexts using L-function inversion |
| `zk_range_proof_generate(sec, min, max)` | `shunya_gnan_sabiti` | `શૂન્ય_જ્ઞાન_સાબિતી` | Generates zero-knowledge Pedersen commitment range proofs verifying $x \in [	ext{min}, 	ext{max}]$ |

