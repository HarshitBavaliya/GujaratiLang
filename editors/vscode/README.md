# GujaratiLang Visual Studio Code Extension

Official syntax highlighting, rich autocomplete snippets, and language tooling for GujaratiLang source files (`.gj`, `.gjc`) in Visual Studio Code, updated for **GujaratiLang v4.3.0: Samudra & Hava**.

Highlights Gujarati Unicode keywords, lowercase Romanized Gujarati keywords, and English keywords, comments, strings, numbers, operators, and 2,300+ standard library functions. Includes 250+ starter snippets covering foundational control flow, object-oriented classes, data structures, and all advanced computational domains.

## Features

- 🌈 **Complete Trilingual Parity**: Highlights all language constructs in native Gujarati (`જો`, `નહિતર`, `છાપો`, `કાર્ય`), Romanized Gujarati (`jo`, `nahi_to`, `chhapo`, `kary`), and English (`if`, `else`, `print`, `fn`).
- ⚡ **2,300+ Standard Library Built-ins**: Full syntax recognition for:
  - **Samudra & Hava (v4.3.0)**: Numerical weather prediction, Coriolis frequency, tidal harmonics, seismic geophysics, and Earth climate models.
  - **Parmanu & Shakti (v4.2.0)**: Quantum circuit simulation ($H$, $CNOT$, Bell states), 64-byte aligned SIMD kernels, smart renewable microgrids, and Lattice Boltzmann CFD.
  - **Brahmand & Antariksh (v4.1.0)**: Autodiff tensor engine, SGP4 orbital mechanics, real-time EDF scheduler, and Paillier homomorphic encryption.
  - **Grand Unification (v4.0.0)**: Self-hosting AST inspection, pure C99 WebAssembly compiler, NIST ML-KEM/ML-DSA post-quantum cryptography, and autonomous agent swarms.
  - **Decentralized & Robotics (v3.8-v3.9)**: DTN Delay-Tolerant bundles, LoRaWAN mesh routing, IPFS UnixFS, W3C DID/VC, ROS 2 robotics nodes, SLAM LiDAR navigation, and drone MAVLink telemetry.
  - **Formal Verification & FinTech (v3.6-v3.7)**: Shuddhi borrow checker, Satya SMT solver, Praman Design-by-Contract, double-entry GAAP ledger, Indian GST engine, and OrderBook matching.
  - **Mathematics & Security (v3.0-v3.5)**: Arbitrary precision BigNum arithmetic, 2D game canvas graphics, WinSock TCP/UDP, TLS ACME, Argon2id, and AI LLM prompt/chat integration.
- 💡 **250+ Intelligent Autocomplete Snippets**: Rapid scaffolding for scripts, algorithms, data analysis, neural nets, quantum circuits, and physics simulations.
- 🗂️ **Brace-Aware Folding & Indentation**: Full brace-matching, automatic bracket closing, and comment toggling.

## Install from the Visual Studio Marketplace

Search for **GujaratiLang** in the Extensions view, or install it directly from the
[Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=harshitbavaliya.gujarati):

```powershell
code --install-extension HarshitBavaliya.gujarati
```

## Install a Local Build

To try the extension locally, package it from this directory with:

```powershell
npx @vscode/vsce package --no-git-tag-version
code --install-extension .\gujarati-4.3.0.vsix
```

## Extension Release Workflow

1. Increment `"version"` in [`package.json`](package.json).
2. Add a new release section with changes in [`CHANGELOG.md`](CHANGELOG.md).
3. Package and verify locally:
   ```powershell
   npx @vscode/vsce package --no-git-tag-version
   ```
4. Publish to Visual Studio Marketplace:
   ```powershell
   npx @vscode/vsce publish
   ```
