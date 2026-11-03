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
