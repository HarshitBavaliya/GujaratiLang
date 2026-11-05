# Getting Started with GujaratiLang

Welcome to **GujaratiLang (ગુજરાતી લેંગ્વેજ)**! GujaratiLang is a high-performance interpreter, AOT compiler, and full-stack runtime implemented in 100% pure C99 with **zero external dependencies**.

Programs in GujaratiLang can be written interchangeably using:
1. **English Keywords** (e.g. `start`, `print`, `if`, `while`, `function`)
2. **Romanized Gujarati Keywords** (e.g. `aavo`, `chhapo`, `jo`, `jya_sudhi`, `kary`)
3. **Native Gujarati Unicode Keywords** (e.g. `આવો`, `છાપો`, `જો`, `જ્યાં_સુધી`, `કાર્ય`)

All three forms are first-class citizens and execute identically.

---

## 1. Quick Installation

### Option A: Download Pre-Compiled Binaries
Pre-built, standalone binaries are available for Windows, Linux, and macOS on the [GitHub Releases page](https://github.com/HarshitBavaliya/GujaratiLang/releases/latest).

Extract the archive and add the directory to your system's `PATH`:
```bash
# Verify installation
gujarati --version
# Output: 4.3.0
```

### Option B: Build from Source (Any Platform with C99 & CMake)
```bash
git clone https://github.com/HarshitBavaliya/GujaratiLang.git
cd GujaratiLang
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```
The compiled executable will be located in `./build/gujarati` (or `.\build\Release\gujarati.exe` on Windows).

---

## 2. Setting Up Your Editor

### VS Code Extension
GujaratiLang has an official extension published on the Visual Studio Code Marketplace providing syntax highlighting, auto-completion snippets, and bracket matching.

Install it directly from the VS Code command palette (`Ctrl+P` or `Cmd+P`):
```text
ext install HarshitBavaliya.gujarati
```
Or via CLI:
```bash
code --install-extension HarshitBavaliya.gujarati
```

---

## 3. Your First Program in 3 Languages

Create a file named `hello.gj` using whichever syntax style you prefer:

### Style 1: Native Gujarati (માતૃભાષા)
```gujarati
આવો
નામ = "ગુજરાત";
છાપો "નમસ્તે, " + નામ + "!";
આવજો
```

### Style 2: Romanized Gujarati (Phonetic ASCII)
```gujarati
aavo
nam = "Gujarat";
chhapo "Namaste, " + nam + "!";
aavjo
```

### Style 3: English Keywords
```gujarati
start
name = "Gujarat";
print "Namaste, " + name + "!";
end
```

### Running Your Program
```bash
gujarati hello.gj
# Output: Namaste, Gujarat!
```

---

## 4. Interactive REPL

Run `gujarati` with no arguments to enter the interactive Read-Eval-Print Loop:
```text
$ gujarati
=== ગુજરાતીલેંગ્વેજ (GujaratiLang) v4.0.0 Interactive Shell ===
ટાઇપ કરો 'bahar' અથવા 'exit' બહાર નીકળવા માટે.
>> a = 10;
10
>> b = 25;
25
>> chhapo a + b;
35
>> બહાર
```

---

## 5. Built-in Starter Kits (Scaffolding Real Projects)

GujaratiLang comes equipped with 9 pre-coded starter kits to immediately scaffold complete production architectures with a single CLI command:

| Command | Starter Kit | Purpose |
|---|---|---|
| `gujarati new my_app --kit=auth` | **Breeze Auth** | User authentication, password hashing, and session management |
| `gujarati new my_api --kit=api` | **Tarang Setu API** | Dual REST & GraphQL microservice gateway with WebSockets |
| `gujarati new my_gui --kit=desktop` | **Shilp Desktop** | Native 2D vector GUI, windows, menus, and event loops |
| `gujarati new my_mobile --kit=mobile` | **Setu Mobile** | Declarative mobile UI widget tree for Android NDK |
| `gujarati new my_audio --kit=audio` | **Dhwani Audio** | 3D spatial audio synthesizer, wavetable oscillators, mixer |
| `gujarati new my_store --kit=commerce` | **Vepar Commerce** | Shopping cart, Indian GST tax engine, and PDF invoicing |
| `gujarati new my_tests --kit=kasauti` | **Kasauti Testing** | E2E browser automation, pixel diffing, and test runner |
| `gujarati new my_ai --kit=sahayak` | **Sahayak AI** | Local LLM runner, RAG cosine search, and prompt rules |
| `gujarati new my_sec --kit=jetstream` | **Suraksha Vault** | 2FA TOTP generator, RBAC permissions, and audit logs |

Example:
```bash
gujarati new synth_studio --kit=audio
cd synth_studio
gujarati app.gj
```

---

## 6. Language Fundamentals at a Glance

### Variables and Data Types
```gujarati
aavo
// Numbers (IEEE 754 64-bit double)
x = 42;
pi_val = 3.14159;

// Strings (UTF-8 encoded)
msg = "જય શ્રી કૃષ્ણ";

// Dynamic Lists
numbers = [1, 2, 3, 4, 5];
umero(numbers, 6); // Appends 6 to list

// Dictionaries (Hash Tables)
user = {
    "name": "Harshit",
    "role": "Engineer",
    "active": 1
};
chhapo user["name"]; // "Harshit"
aavjo
```

### Conditionals
```gujarati
aavo
marks = 85;

jo (marks >= 90) {
    chhapo "Grade: A+";
} athva (marks >= 80) {
    chhapo "Grade: A";
} nahitar {
    chhapo "Grade: B";
}
aavjo
```

### Loops
```gujarati
aavo
// While loop
i = 0;
jya_sudhi (i < 5) {
    chhapo "Index: " + lakhan(i);
    i = i + 1;
}

// For-in loop
fruits = ["કેરી", "જામફળ", "ચીકુ"];
darek (f ma fruits) {
    chhapo "ફળ: " + f;
}
aavjo
```

### Functions
```gujarati
aavo
kary sarvado(a, b) {
    parat a + b;
}

result = sarvado(15, 27);
chhapo "સરવાળો: " + lakhan(result); // 42
aavjo
```

### Object-Oriented Programming (Classes)
```gujarati
aavo
varg BankAccount {
    rachna(holder, initial_balance) {
        a_pote.holder = holder;
        a_pote.balance = initial_balance;
    }

    deposit(amount) {
        a_pote.balance = a_pote.balance + amount;
        parat a_pote.balance;
    }
}

acc = navu BankAccount("Alice", 1000);
acc.deposit(250);
chhapo acc.balance; // 1250
aavjo
```

---

## 7. Next Steps

- Explore the complete built-in function matrix in [Language Reference](LANGUAGE_REFERENCE.md).
- Understand the interpreter and compiler internals in [Architecture Guide](ARCHITECTURE.md).
- Learn how to contribute new features to the runtime in [Developer Guide](DEVELOPER_GUIDE.md).
- Check out interactive examples in the [`examples/`](../examples/) directory.
