# GujaratiLang beginner tutorial

This tutorial walks through a first program, then introduces variables,
functions, conditions, loops, lists, and modules. GujaratiLang accepts both
Gujarati keywords and romanized spellings, so you can use a Gujarati or an
English keyboard.

## 1. Get GujaratiLang

Download a package for your operating system from the
[latest release](https://github.com/HarshitBavaliya/GujaratiLang/releases/latest),
or [build it from source](../README.md#build-from-source). The release package
contains the `gujarati` interpreter and runnable examples.

Open a terminal in the extracted package directory. Run the included example:

```powershell
.\gujarati.exe .\examples\hello.gj
```

On Linux or macOS:

```sh
./gujarati ./examples/hello.gj
```

## 2. Write your first program

Create a text file named `hello.gj`:

```text
aavo
name = "Harshit";
chhapo "Hello, " + name + "!";
aavjo
```

Run it from the directory where you saved the file:

```powershell
.\gujarati.exe .\hello.gj
```

The output is:

```text
Hello, Harshit!
```

`aavo` starts a program and `aavjo` ends it. `chhapo` prints a value.
Statements end with semicolons. Strings use double quotes, and `+` joins two
strings. The same program can use Gujarati spellings:

```text
આવો
નામ = "હર્ષિત";
છાપો "નમસ્તે, " + નામ + "!";
આવજો
```

## 3. Use variables and calculations

Assign a value to a name, then use that name in an expression:

```text
aavo
price = 12;
quantity = 3;
chhapo price * quantity;
aavjo
```

GujaratiLang supports numbers, strings, lists, and the `nakamo` null value.
Reassigning a variable updates its value. Arithmetic operators are `+`, `-`,
`*`, and `/`; comparisons include `==`, `!=`, `<`, `<=`, `>`, and `>=`.

## 4. Define and call a function

Use `kary` to declare a function and `parat` to return a value:

```text
aavo
kary double(value) {
    parat value * 2;
}
chhapo double(21);
aavjo
```

This prints `42`. Gujarati equivalents are `કાર્ય` and `પરત`. Function
parameters and newly assigned variables are local to the call.

## 5. Make decisions and repeat work

`jo` and `nahitar` choose between branches. A `jya_sudhi` loop repeats while
its condition is true:

```text
aavo
count = 0;
jya_sudhi (count < 3) {
    count = count + 1;
    jo (count == 2) {
        chhapo "Two";
    } nahitar {
        chhapo count;
    }
}
aavjo
```

For a list or integer range, use `darek` with `ma`:

```text
aavo
colors = ["red", "green", "blue"];
darek (color ma colors) {
    chhapo color;
}
darek (number ma 1..4) {
    chhapo number;
}
aavjo
```

The range includes its start and excludes its end. Gujarati spellings include
`જો`, `નહિતર`, `જ્યાં સુધી`, `દરેક`, and `માં`.

## 6. Work with lists and imports

Lists use square brackets and zero-based indexes. They can contain nested
lists:

```text
aavo
scores = [10, 20, [30, 40]];
chhapo scores[1];
scores[0] = 15;
chhapo lambai(scores);
chhapo prakar(scores);
chhapo "Score: " + lakhan(scores[0]);
aavjo
```

Built-in functions also include `sankhya(text)` / `સંખ્યા(...)` to parse numbers from
input strings, `lakhan(value)` / `લખાણ(...)` to convert values to strings, and
`prakar(value)` / `પ્રકાર(...)` to check runtime types, `umero(list, item)` / `ઉમેરો(...)`
to append items dynamically to lists, `kapo(string, start[, length])` / `કાપો(...)`
to slice strings using Unicode codepoints, and `shodho(string, target[, start])` / `શોધો(...)`
to search for substrings, `kadho(list[, index])` / `કાઢો(...)` to pop elements,
`peli_abcd(str)` / `પહેલી_એબીસીડી(...)` and `biji_abcd(str)` / `બીજી_એબીસીડી(...)` for uppercase and lowercase conversion,
math helpers `mahatam` / `મહત્તમ`, `nyunatam` / `ન્યૂનતમ`, `dhan_mulya` / `ધન_મૂલ્ય`, power `ghat` / `ઘાત`, square root `mul` / `મૂળ`, list reverse `ultavo(list)` / `ઉલટાવો(...)`, string split `bhag(string, delimiter)` / `ભાગ(...)`, list join `jodo(list, separator)` / `જોડો(...)`, whitespace trim `saf(string)` / `સાફ(...)`, and in-place list sorting `gothvo(list)` / `ગોઠવો(...)`.

Use `import "helpers.gj";` to load another `.gj` file. The path is relative to
the file containing the import; imported functions and variables share the
program's global namespace. See
[`examples/modules.gj`](../examples/modules.gj) and
[`examples/modules_helpers.gj`](../examples/modules_helpers.gj).

## 7. Try the REPL and more examples

Start the interactive prompt:

```powershell
.\gujarati.exe --repl
```

Enter one statement or expression per line. Variables and functions remain
available until you exit. Use Ctrl+Z then Enter in PowerShell, or Ctrl+D on
Linux/macOS, to exit.

The [`examples`](../examples) folder also contains complete programs,
including a [Fibonacci sequence](../examples/fibonacci.gj), a
[temperature converter](../examples/temperature_converter.gj), an
[inventory manager](../examples/inventory.gj), and a native Gujarati-script
[stock manager](../examples/stock.gj). The full
[language guide](../README.md) lists all keywords, diagnostics, and runtime
details.
