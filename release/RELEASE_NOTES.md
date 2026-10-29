# GujaratiLang v1.8.0 — High-Performance Data Science, Fast Matrix Math & Distributed Systems 🚀

GujaratiLang **v1.8.0** delivers high-performance numerical computing, statistical modeling, distributed RPC networking, in-memory key-value caching, machine learning classification (K-Means & Decision Trees), and a cron-based recurring task daemon.

This release introduces **30 major features across 6 core pillars**, empowering GujaratiLang developers to run data science, distributed services, and microservices architectures natively with **zero third-party dependencies**.

All **413 test cases** pass with a 100% success rate across Windows, Linux, macOS Apple Silicon, and macOS Intel.

---

## 🌟 What's New in v1.8.0 (The 6 Core Pillars)

### 🧮 1. High-Performance Matrix Math & Linear Algebra (BLAS Primitives)
- **Matrix Operations**:
  - `matrix_dot(m1, m2)` / `મેટ્રિક્સ_ગુણાકાર(મ૧, મ૨)`: High-performance matrix dot product and 2D vector transformations.
  - `matrix_inv(m)` / `મેટ્રિક્સ_ઉલટાવવું(મ)`: Matrix inversion via Gauss-Jordan elimination.
  - `matrix_det(m)` / `મેટ્રિક્સ_નિશ્ચાયક(મ)`: Determinant evaluation of square matrices.
  - `matrix_eigen(m)` / `મેટ્રિક્સ_આઇગન(મ)`: QR algorithm / Power iteration computing eigenvalues and eigenvectors.
  - `matrix_svd(m)` / `મેટ્રિક્સ_એસવીડી(મ)`: Singular Value Decomposition factoring matrices into rank and component vectors.

### 📊 2. Descriptive Statistics & Advanced Distributions
- **Statistical Modeling**:
  - `stat_median(list)` / `આંકડા_મધ્યસ્થ(યાદી)`: Exact median calculation using median-of-medians partition.
  - `stat_stdev(list)` / `આંકડા_પ્રમાણિત_વિચલન(યાદી)`: Sample and population standard deviation calculation.
  - `stat_quartiles(list)` / `આંકડા_ચતુર્થક(યાદી)`: Calculate Q1, Q2 (median), Q3, and IQR (Interquartile Range).
  - `stat_normal_cdf(x, mu, sigma)` / `સામાન્ય_વિતરણ(x, mu, sigma)`: Gaussian / Normal Cumulative Distribution Function.
  - `stat_correlation(list1, list2)` / `સહસંબંધ(યાદી૧, યાદી૨)`: Pearson product-moment correlation coefficient (-1.0 to 1.0).

### 🌐 3. Distributed Remote Procedure Calls (RPC Engine)
- **Microservices & Networking**:
  - `rpc_server_create(port, methods)` / `આરપીસી_સર્વર_બનાવો(પોર્ટ, પદ્ધતિઓ)`: Allocate RPC server socket handling incoming procedures.
  - `rpc_server_listen(server)` / `આરપીસી_સર્વર_સાંભળો(સર્વર)`: Start listening for remote procedure calls.
  - `rpc_client_connect(host, port)` / `આરપીસી_ક્લાયન્ટ_જોડો(યજમાન, પોર્ટ)`: Establish persistent connection to remote RPC server.
  - `rpc_call(client, method, args)` / `આરપીસી_બોલાવો(ક્લાયન્ટ, પદ્ધતિ, દલીલો)`: Dispatch remote method execution over network and await result.
  - `rpc_client_close(client)` / `આરપીસી_ક્લાયન્ટ_બંધ(ક્લાયન્ટ)`: Terminate RPC socket safely.

### 💾 4. In-Memory Key-Value Cache (Distributed Redis-like Primitives)
- **Fast Storage**:
  - `cache_create([ttl_ms])` / `કેશ_બનાવો([સમય_મીલી])`: Initialize thread-safe in-memory key-value cache engine.
  - `cache_set(cache, key, value, [ttl])` / `કેશ_ગોઠવો(કેશ, કી, મૂલ્ય, [સમય])`: Store entry with optional TTL expiration.
  - `cache_get(cache, key)` / `કેશ_મેળવો(કેશ, કી)`: Fetch cached entry with expiration checks.
  - `cache_del(cache, key)` / `કેશ_કાઢી_નાખો(કેશ, કી)`: Invalidate and purge cached keys.
  - `cache_stats(cache)` / `કેશ_આંકડા(કેશ)`: Query hit count, miss count, total keys, and memory consumption.

### 🤖 5. Machine Learning Classifier Suite (K-Means & Decision Trees)
- **Native ML Algorithms**:
  - `kmeans_fit(data, k, [max_iters])` / `કેમીન્સ_ટ્રેન(ડેટા, કે)`: K-Means clustering algorithm computing cluster centroids.
  - `kmeans_predict(model, point)` / `કેમીન્સ_અનુમાન(મોડેલ, બિંદુ)`: Classify new data points to closest cluster center.
  - `dtree_fit(X, y)` / `નિર્ણય_વૃક્ષ_ટ્રેન(ડેટા, લેબલ)`: Train CART decision tree classification model.
  - `dtree_predict(model, X)` / `નિર્ણય_વૃક્ષ_અનુમાન(મોડેલ, ડેટા)`: Predict class labels using trained decision tree.
  - `ml_accuracy_score(y_true, y_pred)` / `ચોકસાઈ_સ્કોર(સાચું, અનુમાન)`: Calculate percentage accuracy score.

### ⏱️ 6. Distributed Task Scheduler & Cron Engine
- **Daemon Workers**:
  - `cron_create(expression, handler)` / `ક્રોન_બનાવો(અભિવ્યક્તિ, કાર્ય)`: Parse 5-field standard cron schedule expression.
  - `cron_start(cron_id)` / `ક્રોન_શરૂ(આઈડી)`: Schedule background recurring task timer.
  - `cron_stop(cron_id)` / `ક્રોન_બંધ(આઈડી)`: Cancel scheduled cron timer.
  - `cron_next_run(cron_id)` / `આગામી_રન(આઈડી)`: Compute next execution timestamp in Unix epoch seconds.
  - `gujarati cron <schedule.gj>`: Run persistent background daemon worker.

---

## 💻 Native Scripts Supported
All 30 new features are available with 100% parity across both **Romanized Gujarati** (`matrix_dot`, `stat_median`, `rpc_server_create`, `cache_create`, `kmeans_fit`, `cron_create`) and **Native Gujarati Script** (`મેટ્રિક્સ_ગુણાકાર`, `આંકડા_મધ્યસ્થ`, `આરપીસી_સર્વર_બનાવો`, `કેશ_બનાવો`, `કેમીન્સ_ટ્રેન`, `ક્રોન_બનાવો`).

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
