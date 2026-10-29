## [1.5.0] - 2026-10-29

### Added - GujaratiLang v1.5.0 Mega-Release (All 30 Points in 1)
- **Pillar 1: Gujarati Package Manager (`gjpm`) & Modular Imports**
  - CLI `gujarati pkg init`, `gujarati pkg install`, `gujarati pkg list`
  - `pkg_info` / `પેકેજ_માહિતી`, `pkg_load` / `પેકેજ_લોડ`
- **Pillar 2: Native WebAssembly (Wasm) Binary Compiler & DOM Engine**
  - CLI `gujarati --wasm <input.gj> -o <output.wasm>`
  - `wasm_compile` / `વોસમ_કમ્પાઇલ`, `dom_select` / `ડોમ_પસંદ`, `dom_set_html` / `ડોમ_લખાણ`
  - `dom_set_style` / `ડોમ_શૈલી`, `dom_on_event` / `ડોમ_ઘટના`
- **Pillar 3: Wire-Protocol Database Drivers & Transactions**
  - `pg_connect` / `પીજી_જોડો`, `pg_query` / `પીજી_પ્રશ્ન` (PostgreSQL client)
  - `mysql_connect` / `માયએસક્યુએલ_જોડો`, `mysql_query` / `માયએસક્યુએલ_પ્રશ્ન` (MySQL client)
  - `tx_begin` / `વ્યવહાર_શરૂ`, `tx_commit` / `વ્યવહાર_સમાપ્ત`, `tx_rollback` / `વ્યવહાર_રદ`
  - `db_pool_create` / `ડીબી_પૂલ_બનાવો`, `db_pool_acquire` / `ડીબી_પૂલ_મેળવો`
  - `sql_prepare` / `એસક્યુએલ_તૈયાર` (safe parameterized SQL queries)
- **Pillar 4: Native Image Processing & Computer Vision**
  - `image_create` / `ચિત્ર_બનાવો`, `image_write_bmp` / `ચિત્ર_બીએમપી_લખો`
  - `image_read_bmp` / `ચિત્ર_બીએમપી_વાંચો`, `image_resize` / `ચિત્ર_માપ`
  - `image_filter` / `ચિત્ર_ફિલ્ટર` (grayscale, invert, blur)
  - `image_terminal` / `ચિત્ર_ટર્મિનલ` (ANSI 24-bit canvas view)
- **Pillar 5: Async Coroutines & Non-Blocking Event-Driven I/O**
  - `async_task` / `અસંકેત_કાર્ય`, `async_await` / `પ્રતીક્ષા`
  - `async_all` / `અસંકેત_બધા`, `async_sleep` / `અસંકેત_સુવો`
  - `event_emitter` / `ઘટના_ઉત્સર્જક`
- **Pillar 6: Built-in Unit Testing & Benchmark Framework**
  - CLI `gujarati test [dir]` & CLI `gujarati bench <file.gj>`
  - `assert_eq` / `ચકાસણી_સરખું`, `assert_true` / `ચકાસણી_સાચું`
  - `assert_throws` / `ચકાસણી_ભૂલ`, `bench_run` / `બેન્ચ_દોડો`
- **Total Test Suite:** 392 / 392 Automated Tests Passing (100% CTest pass rate).

# Changelog

## 1.4.0

- Major 30-Point Milestone Release with Native GUI, Regular Expressions, Audio Synthesis, AES-128 & TOTP Cryptography, PKZIP Container & Interactive REPL:
  - **Pillar 1: Native Desktop GUI & 2D Canvas Graphics**:
    - `gui_window(title, width, height)` (`વિન્ડો_બનાવો`): Creates native desktop GUI windows with custom title, dimensions, and control hierarchy.
    - `gui_button(win, text, x, y, width, height, [callback])` (`બટન_બનાવો`): Adds interactive button controls with event handler callbacks.
    - `gui_text(win, text, x, y)` (`લખાણ_બનાવો`): Adds static text labels to GUI forms.
    - `gui_canvas_draw(win, shape, coords, color)` (`કેનવાસ_દોરો`): 2D canvas drawing supporting lines, rectangles, and shapes.
    - `gui_event_loop(win, [max_ticks])` (`ઘટના_ચક્ર`): Event loop dispatcher supporting interactive message dispatching and headless test automation.
  - **Pillar 2: Regular Expressions Engine**:
    - `regex_match(pattern, text)` (`રેજેક્સ_સરખાવો`): Matches regex patterns against input strings with full Unicode support.
    - `regex_find(pattern, text)` (`રેજેક્સ_શોધો`): Finds substring matches returning dictionary with matched text, start index, and end index.
    - `regex_replace(pattern, repl, text)` (`રેજેક્સ_બદલો`): Replaces pattern occurrences across text with replacement strings.
    - `regex_split(pattern, text)` (`રેજેક્સ_વિભાજન`): Splits text by regular expression delimiters into lists of strings.
    - `regex_all(pattern, text)` (`રેજેક્સ_બધા`): Extracts all pattern matches into an array of strings.
  - **Pillar 3: Audio Synthesis & Sound Engine**:
    - `sound_beep(frequency, duration_ms)` (`અવાજ_બીપ`): Produces audible tone frequencies via system speaker.
    - `sound_melody(notes_list, [tempo_ms])` (`સુર_વગાડો`): Plays musical note melodies supporting western note frequencies and Indian Classical Swaras (`Sa`, `Re`, `Ga`, `Ma`, `Pa`, `Dha`, `Ni`, `Sa2` / `સા`, `રે`, `ગ`, `મ`, `પ`, `ધ`, `ની`, `સા૨`).
    - `wav_create(filepath, sample_rate, samples_list)` (`ઓડિયો_બનાવો`): Synthesizes valid 16-bit mono PCM RIFF WAVE audio files from sample data.
    - `wav_read(filepath)` (`ઓડિયો_વાંચો`): Inspects WAVE audio file headers returning sample rate, channels, bits per sample, and duration.
    - `sound_play_file(filepath)` (`ઓડિયો_ચલાવો`): Plays audio files asynchronously in the background.
  - **Pillar 4: Advanced Cryptography & 2FA**:
    - `aes_encrypt(text, key)` (`એઈએસ_ગુપ્ત`): AES-128 cryptographic cipher encryption with PKCS7 padding returning hex ciphertext.
    - `aes_decrypt(hex_cipher, key)` (`એઈએસ_પ્રગટ`): AES-128 decryption recovering original plaintext.
    - `totp_generate(base32_secret, [timestamp])` (`ટીઓટીપી_બનાવો`): RFC 6238 compliant 6-digit Time-Based One-Time Password generator (Google Authenticator compatible).
    - `totp_verify(code, base32_secret, [window], [timestamp])` (`ટીઓટીપી_ચકાસો`): Validates 2FA TOTP codes with configurable time window drift.
    - `hmac_sha256(data, key)` (`એચમેક_શા૨૫૬`): Cryptographic HMAC-SHA256 hash returning 64-character lowercase hex digest.
  - **Pillar 5: Data Compression & PKZIP Archives**:
    - `zip_compress(text)` (`દબાવો_ડેટા`): In-memory prefix/run-length data compression.
    - `zip_decompress(compressed_str)` (`ખોલો_ડેટા`): Decompresses data back to original text.
    - `zip_create(zip_path, files_dict)` (`ઝિપ_ફાઇલ_બનાવો`): Standard PKZIP archive creator (`0x04034b50` & `0x02014b50`) with IEEE 802.3 CRC32 verification.
    - `zip_list(zip_path)` (`ઝિપ_ફાઇલ_સૂચિ`): Inspects ZIP central directory returning filename, compressed size, uncompressed size, and CRC32.
    - `zip_extract(zip_path, output_dir)` (`ઝિપ_ફાઇલ_ખોલો`): Extracts archived files directly into destination directory.
  - **Pillar 6: Interactive Terminal REPL, Debugger & Offline Docs**:
    - `gujarati docs [topic]`: Interactive CLI offline documentation browser in Gujarati and English.
    - `gujarati` (or `gujarati --repl`): Stateful interactive terminal REPL with multi-line input and variable persistence.
    - `debug_trace(flag)` (`ડિબગ_તપાસ`): Statement-level step tracing visualizer.
    - `debug_breakpoint([msg])` (`રોકાણ_બિંદુ`): Emits diagnostic breakpoint reports displaying current line and symbol table count.
    - `memory_info()` (`મેમરી_માહિતી`): Returns runtime engine diagnostic metrics (strings, variables, functions, classes, and version).

## 1.3.0

- Major 30-Point Milestone Release with WebSockets, Template Engine, DataFrames, Deep Learning MLP, Statistics & Bytecode Compiler:
  - **Pillar 1: Full-Duplex WebSockets & Real-Time Communications**:
    - `websocket_server(port, on_msg, [max_req])` (`વેબસોકેટ_સર્વર`): RFC 6455 compliant WebSocket server with SHA-1 handshake and masking/framing.
    - `websocket_moklo(client_fd, msg)` (`વેબસોકેટ_મોકલો`): Transmit framed UTF-8 messages across active WebSocket client sockets.
    - `websocket_bandh(server_id)` (`વેબસોકેટ_બંધ`): Cleanly terminates WebSocket servers and active connections.
    - `websocket_client(url, on_msg)` (`વેબસોકેટ_ગ્રાહક`): Real-time client connecting to remote WebSocket endpoints.
    - `sha1_hash(text)` (`શા૧_હેશ`): RFC 3174 compliant 160-bit cryptographic SHA-1 digest generator.
  - **Pillar 2: Template Engine, In-Browser Playground & Security**:
    - `render_template(template, data_dict)` (`નમૂનો_રેન્ડર`): Mustache-style templating engine supporting `{{var}}` variable interpolation and `{{#if key}}...{{/if}}` conditionals.
    - `jwt_banao(payload_dict, secret)` (`જેડબલ્યુટી_બનાવો`): Cryptographic JSON Web Token (JWT) generator using HMAC-SHA256 signature verification.
    - `jwt_tapas(token, secret)` (`જેડબલ્યુટી_તપાસ`): Validates and decodes JWT tokens, ensuring tamper resistance.
    - `html_saf(text)` (`એચટીએમએલ_સાફ`): High-performance HTML sanitizer escaping XSS injection characters (`&`, `<`, `>`, `"`, `'`).
  - **Pillar 3: Gujarati DataFrames & Data Wrangling**:
    - `df_kholo(data_or_csv)` (`ડીએફ_ખોલો`): Parses lists of dictionaries or CSV data into tabular Gujarati DataFrame objects.
    - `df_filter(df, col, op, val)` (`ડીએફ_ગાળો`): Filters DataFrame rows using comparison operators (`==`, `!=`, `>`, `<`, `>=`, `<=`).
    - `df_group_by(df, group_col, agg_col, agg_fn)` (`ડીએફ_જૂથ`): Group-by aggregation supporting `sum`, `mean`, `count`, `min`, `max`.
    - `df_describe(df)` (`ડીએફ_વર્ણન`): Computes statistical summaries (count, mean, min, max) for tabular numeric columns.
    - `df_to_csv(df)` (`ડીએફ_સીએસવી`): Serializes DataFrame objects back into structured CSV string format.
  - **Pillar 4: Deep Learning Multi-Layer Perceptron & Advanced Math**:
    - `nn_create(layer_sizes, [lr])` (`એનએન_બનાવો`): Multi-Layer Perceptron neural network architecture initialized with Xavier/Glorot weights.
    - `nn_forward(nn, input_vector)` (`એનએન_આગળ`): Forward propagation calculating activations through hidden and output layers.
    - `nn_train(nn, x_train, y_train, epochs, [lr])` (`એનએન_તાલીમ`): Supervised backpropagation training minimizing Mean Squared Error loss.
    - `math_tanh(x)` (`ટેનએચ`): Hyperbolic tangent activation function.
    - `math_leaky_relu(x, [alpha])` (`લીકી_રેલુ`): Leaky Rectified Linear Unit activation function preventing dying neurons.
  - **Pillar 5: Statistical Analysis & Terminal Visualizations**:
    - `stat_pearson(x, y)` (`આંકડા_સહસંબંધ`): Pearson correlation coefficient between two numeric distributions.
    - `stat_zscore(array)` (`આંકડા_ઝેડ_સ્કોર`): Computes Z-scores (standard scores) for anomaly and outlier detection.
    - `chart_terminal_scatter(x, y, [width], [height])` (`ચાર્ટ_બિંદુ`): Unicode terminal 2D scatter plot generator.
    - `chart_terminal_box(data, [width])` (`ચાર્ટ_બોક્સ`): Five-number summary box-and-whisker plot in Unicode terminal art.
    - `chart_terminal_histogram(data, [bins], [height])` (`ચાર્ટ_આવૃત્તિ_સ્તંભ`): Distribution histogram visualizer directly in the terminal.
  - **Pillar 6: Bytecode Compiler, Virtual Machine & CLI Tooling**:
    - `math_eval(expression_str)` (`ગણિત_ઉકેલો`): Dynamic mathematical expression evaluator with operator precedence, parentheses, and power exponentiation (`^`).
    - `gujarati --compile <file.gj> [-o <out.gjc>]`: Compiles GujaratiLang source code into portable binary `.gjc` bytecode files with `\x7fGJC1` header.
    - `gujarati --disasm <file.gjc>`: Disassembles compiled `.gjc` bytecode files into human-readable Gujarati instruction dumps.
    - Transparent binary execution: Run compiled bytecode `.gjc` files directly via `gujarati <file.gjc>`.

## 1.2.0

- Major 30-Point Milestone Release with Micro Web Server, Embedded SQL Database, Concurrency, Gujarati NLP & Machine Learning Suite:
  - **Pillar 1: Micro HTTP Web Server & REST Framework**:
    - `web_server(port, router_kary, [max_req])` (`વેબ_સર્વર`): Lightweight HTTP server with request routing, header/query parsing, and JSON response formatting.
    - `web_server_bandh(id)` (`વેબ_સર્વર_બંધ`): Clean server shutdown.
    - `web_static_file(path)` (`વેબ_ફાઇલ`): Static asset server with automatic MIME detection (`.html`, `.json`, `.css`, `.js`, etc.).
    - `url_banao(base_url, query_dict)` (`url_બનાવો`): URL query builder with percent-encoding.
  - **Pillar 2: Embedded Relational Database Engine**:
    - `db_kholo(filename)` (`ડેટાબેઝ_ખોલો`): In-memory (`:memory:`) and file-backed table database engine.
    - `db_chalao(db, sql, [params])` (`ડેટાબેઝ_ચલાવો`): Execute `CREATE TABLE`, parameterized `INSERT INTO ... VALUES (?, ?)`, `UPDATE`, and `DELETE FROM`.
    - `db_shodho(db, sql, [params])` (`ડેટાબેઝ_શોધો`): Query tabular records with `WHERE` filtering, returned as native dictionaries.
    - `db_count(db, table)` (`ડેટાબેઝ_ગણતરી`): Fast row counts.
    - `db_bandh(db)` (`ડેટાબેઝ_બંધ`): Flushes dirty tables to disk and cleans up.
  - **Pillar 3: Concurrency, Event Loop Timers & Worker Threads**:
    - `samay_pachhi(ms, kary, [arg])` (`સમય_પછી`): Asynchronous timer delay (`setTimeout`).
    - `samay_antare(ms, kary, count, [arg])` (`સમય_અંતરે`): Interval loop timer (`setInterval`).
    - `async_chalao(kary, [arg])` (`અસિંક_ચલાવો`): True OS background worker thread execution.
    - `async_parinam(handle, [timeout])` (`અસિંક_પરિણામ`): Thread join and return value resolver.
    - `thread_id()` (`થ્રેડ_આઈડી`): Returns active thread ID.
  - **Pillar 4: Gujarati NLP & Machine Learning Suite**:
    - `nlp_gujarati_token(text)` (`એનએલપી_ગુજરાતી_ટોકન`): Gujarati Unicode block tokenizer respecting Indic punctuation (`।`, `॥`, `૰`).
    - `nlp_matra_kadho(text)` (`એનએલપી_માત્રા_કાઢો`): Gujarati vowel sign / matra / diacritic stripper for stem normalization.
    - `nlp_shabda_aavrutti(words)` (`એનએલપી_શબ્દ_આવૃત્તિ`): Bag of Words / word frequency counter.
    - `ml_tfidf(documents)` (`એમએલ_ટીએફઆઈડીએફ`): Term Frequency - Inverse Document Frequency matrix.
    - `ml_naive_bayes_train(features, labels)` (`એમએલ_નાઈવ_બેયસ_તાલીમ`): Multinomial Naive Bayes classifier with Laplace smoothing.
    - `ml_naive_bayes_predict(model, test_doc)` (`એમએલ_નાઈવ_બેયસ_અનુમાન`): Log posterior class classification.
  - **Pillar 5: Linear Algebra & Terminal Data Visualization**:
    - `matrix_transpose(matrix)` (`મેટ્રિક્સ_ટ્રાન્સપોઝ`): 2D matrix transposition.
    - `matrix_determinant(matrix)` (`મેટ્રિક્સ_નિશ્ચાયક`): Determinant computation via Gaussian elimination with partial pivoting.
    - `matrix_identity(size)` (`મેટ્રિક્સ_એકમ`): Identity matrix generation.
    - `chart_terminal_bar(labels, values, [max_w])` (`ચાર્ટ_સ્તંભ`): Beautiful Unicode terminal horizontal bar chart visualizer.
  - **Pillar 6: Developer Tooling, Package Management & FFI**:
    - `gujarati init [project_name]`: CLI command to initialize new project structure with `gujarati.json`, `src/mukhy.gj`, tests, and `.gitignore`.
    - `gujarati test [directory]`: CLI test runner with automated discovery, test assertions, and timing summary.
    - `gujarati --bench <file.gj>`: High-resolution benchmark CLI measuring wall-clock and CPU execution time.
    - `ffi_call(dll_path, function_name, [args])` (`એફએફઆઈ_કૉલ`): Foreign Function Interface dynamically invoking native C shared libraries.

## 1.1.0

- Major 30-Point Milestone Release with OOP, Machine Learning, Web APIs, and Tooling:
  - Object-Oriented Programming (OOP): `varg` (`વર્ગ`), `rachna` (`રચના`), `navu` (`નવું`), `a_pote` (`આ_પોતે`), `anukaran` (`અનુકરણ`), dot-notation properties (`obj.prop`) and dynamic method invocation (`obj.method()`).
  - Single-Letter Snippet Triggers: Type `v` / `વ` for class `varg`, `r` / `ર` for constructor `rachna`, `n` / `ન` for `navu` instantiation, `k` / `ક` for `kary`, `j` / `જ` for `jo`, etc.
  - Networking & Web APIs: `http_melvo` (`http_મેળવો`), `http_moklo` (`http_મોકલો`), `url_prashno` (`url_પ્રશ્નો`).
  - Linear Algebra & Vector Mathematics: `vector_bindu` (`વેક્ટર_બિંદu`), `vector_maan` (`વેક્ટર_માન`), `cosine_samanata` (`કોસાઇન_સમાનતા`), `antar_euclidean` (`અંતર_યુક્લિડિયન`).
  - Machine Learning Primitives: `ml_rekhiya_sambandh` (`ml_રેખીય_સંબંધ`), `ml_kmeans` (`ml_kmeans`), `ml_sigmoid` (`ml_સિગ્મોઇડ`), `ml_relu` (`ml_relu`), `ml_softmax` (`ml_સોફ્ટમેક્સ`), `ml_mse` (`ml_mse`), `ml_minmax_scaling` (`ml_સ્કેલિંગ`).
  - System, Storage & Config: `sangrah_lakho` (`સંગ્રહ_લખો`), `sangrah_vancho` (`સંગ્રહ_વાંચો`), `ini_vancho` (`ini_વાંચો`), `paryavaran_vistaran` (`પર્યાવરણ_વિસ્તરણ`), `suvo` (`સુવો`), `nikal` (`નિકાલ`), `sthanak_folder` (`સ્થાનક_ફોલ્ડર`), `folder_badlo` (`ફોલ્ડર_બદલો`).
  - Algorithms & Safe Casts: `shodho_dvimukhi` (`શોધો_દ્વિમુખી`), `shodho_sarshu` (`શોધો_સરખું`), `sankhya_rupantar` (`સંખ્યા_રૂપાંતર`), `lakhan_rupantar` (`લખાણ_રૂપાંતર`).
  - Developer CLI Tooling: Support for `--tokens`, `--ast`, and code formatter `--format` / `--fmt` (`-w`).

## 1.0.1

- Major 50-Point Milestone Release with Instant Single-Letter Auto-Completion Snippets:
  - Type a single letter like `k` to instantly get `kary` function boilerplate, `j` for `jo`, `d` for `darek`, `c` for `chhapo`, `a` for `aavo`, etc., expanding full syntax automatically.
  - Full syntax highlighting & snippets for all 50 features of GujaratiLang v1.0.0.

## 1.0.0

- Major 50-Point Milestone Release for GujaratiLang:
  - Instant Single-Letter Auto-Completion Snippets: Type a single letter like `k` to instantly get `kary` function boilerplate, `j` for `jo`, `d` for `darek`, `c` for `chhapo`, `a` for `aavo`, etc., expanding full syntax automatically.
  - Environment variables: `paryavaran` (`પર્યાવરણ`), `paryavaran_lakho` (`પર્યાવરણ_લખો`)
  - Path utilities: `path_jodo` (`પાથ_જોડો`), `path_vistaran` (`પાથ_વિસ્તરણ`), `path_mukhya` (`પાથ_મુખ્ય`), `path_folder` (`પાથ_ફોલ્ડર`)
  - UUID generation: `uuid_banao` (`યુયુઆઈડી_બનાવો`) RFC 4122 v4
  - URL encoding & decoding: `url_kod` (`યુઆરએલ_કોડ`), `url_decode` (`યુઆરએલ_ડીકોડ`)
  - Statistical aggregates: `yadi_sarvalo` (`યાદી_સરવાળો`), `yadi_sareras` (`યાદી_સરેરાશ`), `yadi_madhyastha` (`યાદી_મધ્યસ્થ`)
  - String padding: `lakhan_purn_dabi` (`લેખન_પૂર્ણ_ડાબી`), `lakhan_purn_jamni` (`લેખન_પૂર્ણ_જમણી`)
  - Bitwise operations: `bit_ane` (`બીટ_અને`), `bit_athva` (`બીટ_અથવા`), `bit_xor` (`બીટ_એક્સઓર`), `bit_nahi` (`બીટ_નહિ`), `bit_shifte_dabi` (`બીટ_શિફ્ટ_ડાબી`), `bit_shifte_jamni` (`બીટ_શિફ્ટ_જમણી`)
  - Set operations on lists: `yadi_ananya` (`યાદી_અનન્ય`), `yadi_mel` (`યાદી_મેળ`), `yadi_chhed` (`યાદી_છેદ`), `yadi_tavat` (`યાદી_તફાવત`)
  - Character code utilities: `akshar_kod` (`અક્ષર_કોડ`), `kod_thi_akshar` (`કોડ_થી_અક્ષર`)
  - Exponential & logarithmic math: `log_kudrati` (`લૉગ_કુદરતી`), `log_10` (`લૉગ_૧૦`), `ghat_mul` (`ઘાત_મૂળ`), `e_ghat` (`ઈ_ઘાત`)
  - List manipulation: `yadi_ulte_kram` (`યાદી_ઊલટે_ક્રમ`), `yadi_tukda` (`યાદી_ટુકડા`), `yadi_khichdi` (`યાદી_ખીચડી`)
  - Dictionary utilities: `chavi_chhe` (`ચાવી_છે`), `kosh_jodo` (`કોશ_જોડો`)
  - High-precision microsecond timer: `micro_samay` (`માઇક્રો_સમય`)
  - String repetition & count: `lakhan_aavrutti` (`લેખન_આવૃત્તિ`), `lakhan_ganatari` (`લેખન_ગણતરી`)
  - Multi-delimiter splitting: `lakhan_tukda_yadi` (`લેખન_ટુકડા_યાદી`)
  - File reading by line: `file_line_vancho` (`ફાઇલ_લાઇન_વાંચો`)
  - Hexadecimal decoding: `hex_thi_lakhan` (`હેક્સ_થી_લેખન`)
  - Native CSV parser: `csv_vancho` (`સીએસવી_વાંચો`)
  - Type checking predicates: `sankhya_chhe` (`સંખ્યા_છે`), `lakhan_chhe` (`લેખન_છે`), `yadi_chhe` (`યાદી_છે`), `kosh_chhe` (`કોશ_છે`), `nakamo_chhe` (`નકામો_છે`)
  - JSON serialization & parsing: `json_lakho` (`જેસન_લખો`), `json_vancho` (`જેસન_વાંચો`)
  - Command-line arguments: `daleelo` (`દલીલો`), `arg_yadi` (`દલીલ_યાદી`)
  - Radix integer & string conversions: `dvi_sankhya` (`દ્વિ_સંખ્યા`), `dvi_thi_sankhya` (`દ્વિ_થી_સંખ્યા`), `hex_lakhan` (`હેક્સ_લખાણ`), `hex_thi_sankhya` (`હેક્સ_થી_સંખ્યા`)
  - Directory & folder utilities: `folder_chhe` (`ફોલ્ડર_છે`), `folder_banao` (`ફોલ્ડર_બનાવો`), `folder_suchi` (`ફોલ્ડર_સૂચિ`)
  - System shell command execution: `command_chalao` (`કમાન્ડ_ચલાવો`), `system_kary` (`સિસ્ટમ`)
  - Functional list operations: `naksho_yadi` (`નકશો_યાદી`), `gaalo_yadi` (`ગાળો_યાદી`), `sameto_yadi` (`સમેટો_યાદી`), `shodho_yadi` (`શોધો_યાદી`), `shodho_suchak_yadi` (`શોધો_સૂચક_યાદી`)
  - List flatten & zip: `chapti_yadi` (`ચપટી_યાદી`), `zip_yadi` (`ઝીપ_યાદી`)
  - Wildcard pattern matching & replace: `pattern_shodho` (`પેટર્ન_શોધો`), `lakhan_badlo_darek` (`લખાણ_બદલો_દરેક`)
  - Base64 encoding & decoding: `base64_kod` (`બેઝ૬૪_કોડ`), `base64_decode` (`બેઝ૬૪_ડીકોડ`)
  - String case utilities: `shirshak_lakhan` (`શીર્ષક_લખાણ`), `pratham_moti` (`પ્રથમ_મોટી`)
  - String template formatting: `swaroop` (`સ્વરૂપ`)
  - Levenshtein edit distance: `lakhan_antar` (`લખાણ_અંતર`)
  - SHA-256 cryptographic hashing: `sha256_hash` (`શા૨૫૬_હેશ`)
  - Trigonometry: `sine` (`સાઇન`), `cosine` (`કોસાઇન`), `tangent` (`ટેન્જન્ટ`), `arcsin` (`આર્કસાઇન`), `arccos` (`આર્કકોસ`), `arctan` (`આર્કટેન`)
  - Number theory & angles: `guru_tam` (`ગુરુ_તમ`), `laghu_tam` (`લઘુ_તમ`), `ansha_thi_radian` (`અંશ_થી_રેડિયન`), `radian_thi_ansha` (`રેડિયન_થી_અંશ`)
  - Matrix 2D math: `matrix_sarvalo` (`મેટ્રિક્સ_સરવાળો`), `matrix_gunakar` (`મેટ્રિક્સ_ગુણાકાર`)
  - Syntax extensions: Ternary conditional `? :`, compound assignments `+=`, `-=`, `*=`, `/=`, `%=`, modulo `%`, logical `&&`, `||`, and constant declarations with `achala` (`અચળ`) / `const`
  - System metadata: `bhasha_avrutti` (`ભાષા_આવૃત્તિ`), `platform_nam` (`પ્લેટફોર્મ_નામ`)

## 0.4.0

- Add syntax highlighting and starter snippets for major language additions:
  - Hard File System I/O: `file_vancho` (`ફાઇલ_વાંચો`), `file_lakho` (`ફાઇલ_લખો`), `file_umero` (`ફાઇલ_ઉમેરો`), `file_chhe` (`ફાઇલ_છે`), `file_kadho` / `file_hatao` (`ફાઇલ_કાઢો` / `ફાઇલ_હટાવો`), `file_kad` (`ફાઇલ_કદ`)
  - Dictionaries / Hash Maps: Dictionary literals `{ "key": value }`, `kosh` (`કોશ`), `shabdakosh` (`શબ્દકોશ`), `chavio` (`ચાવીઓ`), `mulyo` (`મૂલ્યો`), `dur_karo` (`દૂર_કરો`), dictionary key subscripting and assignment
  - Loop Control Statements: `atko` / `break` (`અટકો`), `chalu_rakho` / `aagal` / `continue` (`ચાલુ_રાખો` / `આગળ`) in `jya_sudhi` and `darek` loops
  - Native Date & Time Utilities: `samay` (`સમય`), `tarikh` (`તારીખ`), `varsh` (`વર્ષ`), `mahino` (`મહિનો`), `divas` (`દિવસ`), `kalak` (`કલાક`), `minute` (`મિનિટ`), `second` (`સેકન્ડ`), `shant` / `raah_juo` (`શાંત` / `રાહ_જુઓ`)
  - Error Recovery Mechanics: `prayatna` { ... } `pakdo` (err) { ... } (`પ્રયત્ન` ... `પકડો`), and error throwing with `phenko` (`ફેંકો`)


## 0.3.0

- Add syntax highlighting and starter snippets for all new built-ins across mathematics, lists, strings, system, and control:
  - Random numbers & seeding: `yadachhik` (`યાદચ્છિક`), `beej` (`બીજ`)
  - Math constants & utilities: `pi` (`પાઈ`), `e` (`ઈ`), `chihna` (`ચિહ્ન`), `laghuganak` (`લઘુગણક`)
  - Unicode & string functions: `akshar_kod` (`અક્ષર_કોડ`), `kod_thi_akshar` (`કોડ_થી_અક્ષર`), `dabe_kapo` (`ડાબે_કાપો`), `jamne_kapo` (`જમણે_કાપો`), `vibhaajan_pankti` (`વિભાજન_પંક્તિ`), `aksharo` (`અક્ષરો`), `samave_lakhan` (`સમાવે_લખાણ`)
  - List operations: `vistaro` (`વિસ્તારો`), `yadi_bharo` (`યાદી_ભરો`), `sarvalo_yadi` (`સરવાળો_યાદી`), `yadi_nyunatam` (`યાદી_ન્યૂનતમ`), `yadi_mahatam` (`યાદી_મહત્તમ`), `ganatari` (`ગણતરી`)
  - System & flow control: `paryavaran` (`પર્યાવરણ`), `bahar` (`બહાર`), `chakaso` (`ચકાસો`)

## 0.2.0

- Add syntax highlighting and starter snippets for list index search, list insertion, string padding, and value clamping built-ins:
  `sthan` (`સ્થાન`), `muko` (`મૂકો`), `dabe_bharo` (`ડાબે_ભરો`), `jamne_bharo` (`જમણે_ભરો`), and `sima` (`સીમા`).

## 0.1.9

- Add syntax highlighting and starter snippets for math rounding, string repeat, and list slicing built-ins:
  `gol` (`ગોળ`), `niche` (`નીચે`), `upar` (`ઉપર`), `punravartan` (`પુનરાવર્તન`), and `tukdo` (`ટુકડો`).

## 0.1.8

- Add syntax highlighting and starter snippets for string transformation and list membership built-ins:
  `badlo` (`બદલો`), `sharuat_sathe` (`શરૂઆત_સાથે`), `ant_sathe` (`અંત_સાથે`), and `samave_chhe` (`સમાવે_છે`).

## 0.1.7

- Add syntax highlighting and starter snippets for math and list built-ins:
  `saf` (`સાફ`), `ghat` (`ઘાત`), `mul` (`મૂળ`), and `gothvo` (`ગોઠવો`).

## 0.1.6

- Add syntax highlighting and starter snippets for list and string manipulation built-ins:
  `ultavo` (`ઉલટાવો`), `bhag` (`ભાગ`), and `jodo` (`જોડો`).

## 0.1.5

- Add syntax highlighting and starter snippets for list, string, and math built-ins:
  `kadho` (`કાઢો`), `peli_abcd` (`પહેલી_એબીસીડી`), `biji_abcd` (`બીજી_એબીસીડી`),
  `mahatam` (`મહત્તમ`), `nyunatam` (`ન્યૂનતમ`), and `dhan_mulya` (`ધન_મૂલ્ય`).

## 0.1.4

- Add syntax highlighting for sankhya, lakhan, prakar, and native
  Gujarati built-in functions સંખ્યા, લખાણ, પ્રકાર.

## 0.1.3

- Add brace-aware indentation and folding for code blocks.

## 0.1.2

- Add Gujarati and romanized starter snippets for programs, functions,
  conditionals, while loops, and for loops.

## 0.1.1

- Add the GujaratiLang website favicon as the extension icon.

## 0.1.0

- Add GujaratiLang language support for `.gj` files.
- Highlight Gujarati and romanized keywords, built-ins, comments, strings,
  numbers, operators, punctuation, and function calls.
- Configure comments, bracket matching, and automatic quote pairing.
