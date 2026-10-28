# GujaratiLang

GujaratiLang is a small programming language runtime implemented in C, following
the general approach used by languages such as PHP: programs are parsed and run
by an interpreter rather than translated into C source.

New to GujaratiLang? Visit the official website and try the interactive playground at [gujaratilang.hp-square.com](https://gujaratilang.hp-square.com/), or start with the [beginner tutorial](docs/tutorial.md). If
you use Visual Studio Code, install the
[GujaratiLang syntax-highlighting extension](https://marketplace.visualstudio.com/items?itemName=harshitbavaliya.gujarati).

## Current features

The initial interpreter supports:

- Programs delimited by `આવો` (start) and `આવજો` (end)
- UTF-8 source files and the Gujarati `છાપો` (print) keyword
- Numeric literals, parentheses, unary minus, arithmetic with `+`, `-`, `*`,
  `/`, and string concatenation with `+`
- Comparisons: numbers support `==`, `!=`, `<`, `<=`, `>`, and `>=`; strings
  support equality with `==` and `!=`
- Logical operators: `અને` (AND), `અથવા` (OR), and `નહીં` (NOT)
- `જ્યાં સુધી (condition) { ... }` while loops
- Mutable, zero-based lists with nested values, indexed reads and writes, and
  list support in `લંબાઈ`
- `દરેક (item માં list) { ... }` list loops and
  `દરેક (index માં start..end) { ... }` integer ranges with an exclusive end
- `import "module.gj";` with importer-relative paths, one-time execution,
  shared globals, and circular-import detection
- Variables created and assigned with `name = value;`; assigning an existing
  name updates its value
- Functions declared with `કાર્ય name(parameters) { ... }`, called as
  expressions or statements, and returning values with `પરત expression;`
- `વાંચો("prompt")` to display a prompt and read one line of text from standard
  input; the returned value is a string
- `લંબાઈ(value)` to return the number of Unicode code points in a string or
  the number of items in a list
- `સંખ્યા(text)` to parse a numeric string into a number
- `લખાણ(value)` to convert a number, null, or list into its string representation
- `પ્રકાર(value)` to inspect the runtime type of a value (`"number"`, `"string"`, `"list"`, or `"null"`)
- `ઉમેરો(list, item)` to append an item to a list and return the updated list
- `કાપો(string, start[, length])` to extract a substring using Unicode code-point offsets
- `શોધો(string, target[, start])` to find the 0-based code-point index of a substring (or `-1` if not found)
- `કાઢો(list[, index])` to remove and return an item from a list (last item by default)
- `પહેલી_એબીસીડી(text)` to convert a string to uppercase
- `બીજી_એબીસીડી(text)` to convert a string to lowercase
- `મહત્તમ(a, b)` and `ન્યૂનતમ(a, b)` to return the maximum and minimum of two numbers
- `ધન_મૂલ્ય(number)` to return the absolute value of a number
- Romanized Gujarati spellings for all keywords and built-ins, so programs can
  be written using an English keyboard
- Gujarati or English-letter variable names, with digits and underscores
  allowed after the first character
- `જો`, `નહિતર જો`, and `નહિતર` conditional blocks with braces
- The `નકામો` null value; conditions accept numbers (`0` is false, nonzero is
  true) and null (false); strings are not valid conditions. Comparison results
  are numbers (`1` for true and `0` for false)
- Quoted strings with `\"`, `\\`, `\n`, `\r`, and `\t` escapes
- `+` adds two numbers or joins two strings; mixing a string and number is an
  error
- `ચેતવણી "message";` to report a warning and continue
- `ભૂલ "message";` and `ઘાતક ભૂલ "message";` to report an error and stop
- Semicolon-terminated print statements and `//` line comments
- File, line, and column diagnostics with a source-line excerpt and caret
  indicator

Comparisons have lower precedence than arithmetic and produce `1` for true or
`0` for false. Numbers support all comparison operators. Strings support `==`
and `!=`, comparing their decoded text; string-to-number comparisons and
ordering comparisons on strings are errors.
Logical precedence from strongest to weakest is `નહીં`, comparisons, `અને`,
then `અથવા`. Logical operators accept numbers and `નકામો`, return `1` or `0`,
and short-circuit when the result is already known. Strings cannot be used as
logical operands.

The `+` operator adds two numbers or concatenates two strings. It does not
automatically convert between strings and numbers. String equality lets a
program check text values:

```text
નામ = "હર્ષ";
છાપો "નમસ્તે, " + નામ;
જો (નામ == "હર્ષ") { છાપો "ફરીથી સ્વાગત છે!"; }
```

Use `લંબાઈ(text)` to count Unicode code points in text rather than its UTF-8
byte length. Combining marks count as separate code points. For a list,
`લંબાઈ` returns its item count.

```text
છાપો લંબાઈ("Gujarati");
છાપો લંબાઈ("હર્ષ");
```

### Use GujaratiLang with an English keyboard

You do not need to switch to a Gujarati keyboard to write GujaratiLang.
Every Gujarati keyword has a lowercase ASCII spelling (a romanized Gujarati
transliteration). These are alternate spellings of the same keywords, not
English translations. Gujarati spellings continue to work too, and both forms
can be used in the same program. Multi-word spellings use underscores.

| Gujarati keyword | English-keyboard spelling | Meaning |
| --- | --- | --- |
| `આવો` | `aavo` | Start a program |
| `આવજો` | `aavjo` | End a program |
| `છાપો` | `chhapo` | Print |
| `જો` | `jo` | If |
| `નહિતર જો` | `nahitar_jo` | Else if |
| `નહિતર` | `nahitar` | Else |
| `જ્યાં સુધી` | `jya_sudhi` | While loop |
| `દરેક` | `darek` | For loop |
| `માં` | `ma` | For-loop separator |
| `અને` | `ane` | And |
| `અથવા` | `athva` | Or |
| `નહીં` | `nahi` | Not |
| `નકામો` | `nakamo` | Null |
| `કાર્ય` | `kary` | Function |
| `પરત` | `parat` | Return |
| `આયાત` | `aayat` or `import` | Import a module |
| `ચેતવણી` | `chetavani` | Warning |
| `ભૂલ` | `bhul` | Error |
| `ઘાતક ભૂલ` | `ghatak_bhul` | Fatal error |
| `વાંચો(...)` | `vancho(...)` | Read input |
| `લંબાઈ(...)` | `lambai(...)` | Get string or list length |
| `સંખ્યા(...)` | `sankhya(...)` | Convert string to number |
| `લખાણ(...)` | `lakhan(...)` | Convert value to string |
| `પ્રકાર(...)` | `prakar(...)` | Inspect runtime type |
| `ઉમેરો(...)` | `umero(...)` | Append item to list |
| `કાપો(...)` | `kapo(...)` | Slice string |
| `શોધો(...)` | `shodho(...)` | Find substring index |
| `કાઢો(...)` | `kadho(...)` | Remove/pop item from list |
| `પહેલી_એબીસીડી(...)` | `peli_abcd(...)` | Convert string to uppercase |
| `બીજી_એબીસીડી(...)` | `biji_abcd(...)` | Convert string to lowercase |
| `મહત્તમ(...)` | `mahatam(...)` | Return maximum value |
| `ન્યૂનતમ(...)` | `nyunatam(...)` | Return minimum value |
| `ધન_મૂલ્ય(...)` | `dhan_mulya(...)` | Return absolute value |
| `ઉલટાવો(...)` | `ultavo(...)` | Reverse list in-place |
| `ભાગ(...)` | `bhag(...)` | Split string into list by delimiter |
| `જોડો(...)` | `jodo(...)` | Join list into string using separator |
| `સાફ(...)` | `saf(...)` | Trim leading/trailing whitespace |
| `ઘાત(...)` | `ghat(...)` | Return base raised to exponent |
| `મૂળ(...)` | `mul(...)` | Return square root |
| `ગોઠવો(...)` | `gothvo(...)` | Sort list items in-place |
| `બદલો(...)` | `badlo(...)` | Replace occurrences of substring |
| `શરૂઆત_સાથે(...)` | `sharuat_sathe(...)` | Test if string starts with prefix |
| `અંત_સાથે(...)` | `ant_sathe(...)` | Test if string ends with suffix |
| `સમાવે_છે(...)` | `samave_chhe(...)` | Test if list contains item |
| `ગોળ(...)` | `gol(...)` | Round number to nearest whole number |
| `નીચે(...)` | `niche(...)` | Floor number |
| `ઉપર(...)` | `upar(...)` | Ceil number |
| `પુનરાવર્તન(...)` | `punravartan(...)` | Repeat string count times |
| `ટુકડો(...)` | `tukdo(...)` | Extract sub-list slice |
| `સ્થાન(...)` | `sthan(...)` | Find 0-based first index of item in list (-1 if not found) |
| `મૂકો(...)` | `muko(...)` | Insert item into list at index in-place |
| `ડાબે_ભરો(...)` | `dabe_bharo(...)` | Pad string on left to target width |
| `જમણે_ભરો(...)` | `jamne_bharo(...)` | Pad string on right to target width |
| `સીમા(...)` | `sima(...)` | Clamp number between minimum and maximum bounds |
| `યાદચ્છિક(...)` | `yadachhik(...)` | Generate random float in [0.0, 1.0) or random integer in [min, max] |
| `બીજ(...)` | `beej(...)` | Set pseudo-random number generator seed for deterministic output |
| `વિસ્તારો(...)` | `vistaro(...)` | Append all items from another list in-place |
| `પાઈ()` | `pi()` | Mathematical constant pi (~3.14159) |
| `ઈ()` | `e()` | Mathematical constant e (~2.71828) |
| `ચિહ્ન(...)` | `chihna(...)` | Return sign of number (1 for positive, -1 for negative, 0 for zero) |
| `લઘુગણક(...)` | `laghuganak(...)` | Return logarithm (natural log ln(n) or log base(n)) |
| `અક્ષર_કોડ(...)` | `akshar_kod(...)` | Return Unicode codepoint of character at index |
| `કોડ_થી_અક્ષર(...)` | `kod_thi_akshar(...)` | Convert Unicode code point to single-character string |
| `યાદી_ભરો(...)` | `yadi_bharo(...)` | Create a new list filled with count copies of value |
| `સરવાળો_યાદી(...)` | `sarvalo_yadi(...)` | Sum numeric elements in a list |
| `યાદી_ન્યૂનતમ(...)` | `yadi_nyunatam(...)` | Find minimum numeric element in list |
| `યાદી_મહત્તમ(...)` | `yadi_mahatam(...)` | Find maximum numeric element in list |
| `ગણતરી(...)` / `ગણતરી_વસ્તુ(...)` | `ganatari(...)` / `ganatari_vastu(...)` | Count item occurrences in list or substring in string |
| `ડાબે_કાપો(...)` | `dabe_kapo(...)` | Trim leading whitespace from string |
| `જમણે_કાપો(...)` | `jamne_kapo(...)` | Trim trailing whitespace from string |
| `વિભાજન_પંક્તિ(...)` | `vibhaajan_pankti(...)` | Split multi-line string into list of lines |
| `અક્ષરો(...)` | `aksharo(...)` | Split string into list of characters |
| `પર્યાવરણ(...)` | `paryavaran(...)` | Get system environment variable value (or null) |
| `બહાર(...)` | `bahar(...)` | Terminate program immediately with exit code (default 0) |
| `ચકાસો(...)` | `chakaso(...)` | Assert condition is truthy with optional error message |
| `સમાવે_લખાણ(...)` | `samave_lakhan(...)` | Check if string contains substring |
| `ફાઇલ_વાંચો(...)` | `file_vancho(...)` | Read file contents into a string (or null if missing) |
| `ફાઇલ_લખો(...)` | `file_lakho(...)` | Write text content to file (overwrites existing file) |
| `ફાઇલ_ઉમેરો(...)` | `file_umero(...)` | Append text content to file |
| `ફાઇલ_છે(...)` | `file_chhe(...)` | Check if file exists on disk (1.0 or 0.0) |
| `ફાઇલ_કાઢો(...)` / `ફાઇલ_હટાવો(...)` | `file_kadho(...)` / `file_hatao(...)` | Delete file from disk (1.0 on success, 0.0 on failure) |
| `ફાઇલ_કદ(...)` | `file_kad(...)` | Get file size in bytes (or null if missing) |
| `અટકો` | `atko` | Break out of loop immediately |
| `ચાલુ_રાખો` / `આગળ` | `chalu_rakho` / `aagal` | Continue to next loop iteration |
| `પ્રયત્ન` / `પકડો` | `prayatna` / `pakdo` | Try-catch block for error recovery |
| `શબ્દકોશ(...)` / `કોશ(...)` | `shabdakosh(...)` / `kosh(...)` | Create dictionary from key-value pairs |
| `ચાવીઓ(...)` / `ચાવી(...)` | `chavio(...)` / `chavi(...)` | Return list of dictionary keys |
| `મૂલ્યો(...)` | `mulyo(...)` | Return list of dictionary values |
| `દૂર_કરો(...)` / `કોશ_દૂર(...)` | `dur_karo(...)` / `kosh_dur(...)` | Remove key from dictionary (1 on success, 0 if not found) |
| `સમય()` | `samay()` | Current epoch timestamp in seconds |
| `તારીખ([format[, timestamp]])` | `tarikh([format[, timestamp]])` | Format timestamp into date-time string |
| `વર્ષ([timestamp])` | `varsh([timestamp])` | Extract year (e.g. 2026) |
| `મહિનો([timestamp])` | `mahino([timestamp])` | Extract month (1-12) |
| `દિવસ([timestamp])` | `divas([timestamp])` | Extract day of month (1-31) |
| `કલાક([timestamp])` | `kalak([timestamp])` | Extract hour (0-23) |
| `મિનિટ([timestamp])` | `minute([timestamp])` | Extract minute (0-59) |
| `સેકન્ડ([timestamp])` | `second([timestamp])` | Extract second (0-59) |
| `શાંત(...)` / `રાહ_જુઓ(...)` | `shant(...)` / `raah_juo(...)` | Pause execution for milliseconds |
| `ફેંકો(...)` | `phenko(...)` | Throw an error message |
| `અચળ` | `achala` or `const` | Declare immutable constant variable |
| `જેસન_વાંચો(...)` | `json_vancho(...)` | Parse JSON string into native dictionary, list, number, string |
| `જેસન_લખો(...)` | `json_lakho(...)` | Serialize value to standard JSON string |
| `દલીલો()` / `દલીલ_યાદી()` | `daleelo()` / `arg_yadi()` | Get command-line arguments passed to script |
| `દ્વિ_સંખ્યા(...)` | `dvi_sankhya(...)` | Convert integer to binary string representation |
| `દ્વિ_થી_સંખ્યા(...)` | `dvi_thi_sankhya(...)` | Convert binary string to integer number |
| `હેક્સ_લખાણ(...)` | `hex_lakhan(...)` | Convert integer to hex string representation |
| `હેક્સ_થી_સંખ્યા(...)` | `hex_thi_sankhya(...)` | Convert hex string to integer number |
| `ફોલ્ડર_છે(...)` | `folder_chhe(...)` | Check if directory exists on disk |
| `ફોલ્ડર_બનાવો(...)` | `folder_banao(...)` | Create directory on disk |
| `ફોલ્ડર_સૂચિ(...)` | `folder_suchi(...)` | List directory contents as list of strings |
| `કમાન્ડ_ચલાવો(...)` / `સિસ્ટમ(...)` | `command_chalao(...)` / `system_kary(...)` | Run system shell command and return exit code |
| `નકશો_યાદી(...)` | `naksho_yadi(...)` | Map function over list elements and return new list |
| `ગાળો_યાદી(...)` | `gaalo_yadi(...)` | Filter list elements based on predicate function |
| `સમેટો_યાદી(...)` | `sameto_yadi(...)` | Reduce list elements using accumulator function |
| `શોધો_યાદી(...)` | `shodho_yadi(...)` | Find first list element matching predicate |
| `શોધો_સૂચક_યાદી(...)` | `shodho_suchak_yadi(...)` | Find 0-based index of first element matching predicate |
| `ચપટી_યાદી(...)` | `chapti_yadi(...)` | Flatten nested sublists into single flat list |
| `ઝીપ_યાદી(...)` | `zip_yadi(...)` | Zip two lists element-by-element into list of pairs |
| `પેટર્ન_શોધો(...)` | `pattern_shodho(...)` | Wildcard pattern matching (`*` and `?`) |
| `લખાણ_બદલો_દરેક(...)` | `lakhan_badlo_darek(...)` | Replace all occurrences of substring |
| `બેઝ૬૪_કોડ(...)` | `base64_kod(...)` | Encode string to Base64 |
| `બેઝ૬૪_ડીકોડ(...)` | `base64_decode(...)` | Decode Base64 string |
| `શીર્ષક_લખાણ(...)` | `shirshak_lakhan(...)` | Convert string to Title Case |
| `પ્રથમ_મોટી(...)` | `pratham_moti(...)` | Capitalize only the first letter of string |
| `સ્વરૂપ(...)` | `swaroop(...)` | Format string template with `{}` placeholders |
| `લખાણ_અંતર(...)` | `lakhan_antar(...)` | Compute Levenshtein edit distance between two strings |
| `શા૨૫૬_હેશ(...)` | `sha256_hash(...)` | Compute 64-character lowercase SHA-256 hex digest |
| `સાઇન(...)` | `sine(...)` | Sine trigonometric function (radians) |
| `કોસાઇન(...)` | `cosine(...)` | Cosine trigonometric function (radians) |
| `ટેન્જન્ટ(...)` | `tangent(...)` | Tangent trigonometric function (radians) |
| `આર્કસાઇન(...)` | `arcsin(...)` | Inverse sine (arcsin) in radians |
| `આર્કકોસ(...)` | `arccos(...)` | Inverse cosine (arccos) in radians |
| `આર્કટેન(...)` | `arctan(...)` | Inverse tangent (arctan) in radians |
| `ગુરુ_તમ(...)` | `guru_tam(...)` | Greatest Common Divisor (GCD) of two integers |
| `લઘુ_તમ(...)` | `laghu_tam(...)` | Least Common Multiple (LCM) of two integers |
| `અંશ_થી_રેડિયન(...)` | `ansha_thi_radian(...)` | Convert degrees to radians |
| `રેડિયન_થી_અંશ(...)` | `radian_thi_ansha(...)` | Convert radians to degrees |
| `મેટ્રિક્સ_સરવાળો(...)` | `matrix_sarvalo(...)` | Component-wise addition of two 2D numeric matrices |
| `મેટ્રિક્સ_ગુણાકાર(...)` | `matrix_gunakar(...)` | Standard matrix multiplication of two 2D matrices |
| `ભાષા_આવૃત્તિ()` | `bhasha_avrutti()` | Get current interpreter version (`"1.0.0"`) |
| `પ્લેટફોર્મ_નામ()` | `platform_nam()` | Get operating system platform (`"windows"`, `"linux"`, `"macos"`) |
| `પર્યાવરણ(નામ)` | `paryavaran(nam)` | Get environment variable value (`getenv`) |
| `પર્યાવરણ_લખો(નામ, મૂલ્ય)` | `paryavaran_lakho(nam, mulya)` | Set environment variable value |
| `પાથ_જોડો(a, b)` | `path_jodo(a, b)` | Join filesystem paths cross-platform |
| `પાથ_વિસ્તરણ(પાથ)` | `path_vistaran(path)` | Extract file extension (e.g. `".gj"`) |
| `પાથ_મુખ્ય(પાથ)` | `path_mukhya(path)` | Extract basename/filename from path |
| `પાથ_ફોલ્ડર(પાથ)` | `path_folder(path)` | Extract parent directory from path |
| `યુયુઆઈડી_બનાવો()` | `uuid_banao()` | Generate RFC 4122 v4 unique identifier string |
| `યુઆરએલ_કોડ(લખાણ)` | `url_kod(str)` | Percent-encode string for URLs |
| `યુઆરએલ_ડીકોડ(લખાણ)` | `url_decode(str)` | Decode percent-encoded URL string |
| `યાદી_સરવાળો(યાદી)` | `yadi_sarvalo(list)` | Calculate sum of numeric list elements |
| `યાદી_સરેરાશ(યાદી)` | `yadi_sareras(list)` | Calculate arithmetic mean of numeric list |
| `યાદી_મધ્યસ્થ(યાદી)` | `yadi_madhyastha(list)` | Calculate median of numeric list |
| `લેખન_પૂર્ણ_ડાબી(...)` | `lakhan_purn_dabi(...)` | Pad string on the left to target length |
| `લેખન_પૂર્ણ_જમણી(...)` | `lakhan_purn_jamni(...)` | Pad string on the right to target length |
| `બીટ_અને(a, b)` | `bit_ane(a, b)` | Bitwise AND operation |
| `બીટ_અથવા(a, b)` | `bit_athva(a, b)` | Bitwise OR operation |
| `બીટ_એક્સઓર(a, b)` | `bit_xor(a, b)` | Bitwise XOR operation |
| `બીટ_નહિ(a)` | `bit_nahi(a)` | Bitwise NOT operation |
| `બીટ_શિફ્ટ_ડાબી(a, n)` | `bit_shifte_dabi(a, n)` | Bitwise left shift |
| `બીટ_શિફ્ટ_જમણી(a, n)` | `bit_shifte_jamni(a, n)` | Bitwise right shift |
| `યાદી_અનન્ય(યાદી)` | `yadi_ananya(list)` | Return list with duplicate values removed |
| `યાદી_મેળ(l1, l2)` | `yadi_mel(l1, l2)` | Set union of two lists |
| `યાદી_છેદ(l1, l2)` | `yadi_chhed(l1, l2)` | Set intersection of two lists |
| `યાદી_તફાવત(l1, l2)` | `yadi_tavat(l1, l2)` | Set difference of two lists |
| `અક્ષર_કોડ(લખાણ, ક્રમ)` | `akshar_kod(str, idx)` | Get ASCII/Unicode code unit at byte index |
| `કોડ_થી_અક્ષર(કોડ)` | `kod_thi_akshar(code)` | Convert integer code unit to 1-char string |
| `લૉગ_કુદરતી(x)` | `log_kudrati(x)` | Natural logarithm `ln(x)` |
| `લૉગ_૧૦(x)` | `log_10(x)` | Base-10 logarithm `log10(x)` |
| `ઘાત_મૂળ(આધાર, ઘાત)` | `ghat_mul(base, exp)` | Power function `pow(base, exp)` |
| `ઈ_ઘાત(x)` | `e_ghat(x)` | Natural exponential `exp(x)` |
| `યાદી_ઊલટે_ક્રમ(યાદી)` | `yadi_ulte_kram(list)` | Return reversed copy of list |
| `યાદી_ટુકડા(યાદી, કદ)` | `yadi_tukda(list, size)` | Partition list into sublists of size `size` |
| `યાદી_ખીચડી(યાદી)` | `yadi_khichdi(list)` | Randomly shuffle list elements |
| `ચાવી_છે(કોશ, ચાવી)` | `chavi_chhe(dict, key)` | Test if dictionary contains key (1 or 0) |
| `કોશ_જોડો(d1, d2)` | `kosh_jodo(d1, d2)` | Merge two dictionaries into a new dictionary |
| `માઇક્રો_સમય()` | `micro_samay()` | High-resolution microsecond epoch timestamp |
| `લેખન_આવૃત્તિ(લખાણ, ગણતરી)` | `lakhan_aavrutti(str, n)` | Repeat string N times |
| `લેખન_ગણતરી(લખાણ, શોધ)` | `lakhan_ganatari(str, sub)` | Count non-overlapping substring occurrences |
| `લેખન_ટુકડા_યાદી(લખાણ, વિભાજક)` | `lakhan_tukda_yadi(str, delims)` | Split string by any delimiter character in string |
| `ફાઇલ_લાઇન_વાંચો(પાથ)` | `file_line_vancho(path)` | Read file directly into list of string lines |
| `હેક્સ_થી_લેખન(હેક્સ)` | `hex_thi_lakhan(hex)` | Decode hexadecimal string to text |
| `સીએસવી_વાંચો(લખાણ)` | `csv_vancho(csv_text)` | Parse CSV text into 2D list of row lists |
| `સંખ્યા_છે(મૂલ્ય)` | `sankhya_chhe(val)` | Type predicate: 1 if number, 0 otherwise |
| `લેખન_છે(મૂલ્ય)` | `lakhan_chhe(val)` | Type predicate: 1 if string, 0 otherwise |
| `યાદી_છે(મૂલ્ય)` | `yadi_chhe(val)` | Type predicate: 1 if list, 0 otherwise |
| `કોશ_છે(મૂલ્ય)` | `kosh_chhe(val)` | Type predicate: 1 if dict, 0 otherwise |
| `નકામો_છે(મૂલ્ય)` | `nakamo_chhe(val)` | Type predicate: 1 if null, 0 otherwise |

Here is a complete program written using only English-keyboard keyword
spellings:

```text
aavo
kary double(value) { parat value * 2; }
items = [10, 20, 30];
darek (item ma items) {
    chhapo double(item);
}
jo (lambai(items) == 3) {
    chhapo "All three items were processed.";
}
aavjo
```

Save it as `english_keyboard.gj`, then run
`gujarati english_keyboard.gj`. The project also includes the runnable
[`examples/romanized.gj`](examples/romanized.gj) sample.

### Lists, loops, and modules

Lists can contain numbers, strings, `નકામો`, and other lists. Indexes start at
zero; use an indexed assignment to replace an item. `લંબાઈ`/`lambai` accepts
either a string or a list:

```text
items = [10, "twenty", [30, નકામો]];
છાપો items[1];
items[0] = 5;
છાપો items;
છાપો લંબાઈ(items);
```

Use `દરેક` (`darek`) to visit every item in a list, or iterate over an
integer range. The start is included and the end is excluded:

```text
દરેક (item માં items) { છાપો item; }
દરેક (index માં 0..લંબાઈ(items)) { છાપો index; }
```

In English-keyboard code, write the same loop as `darek (item ma items)`.
Use `ma` between the loop variable and either a list (`items`) or a numeric
range (`0..end`).

Import another `.gj` file with `આયાત "helpers.gj";` (`aayat` or `import`).
Import paths are
relative to the importing file. Imported code executes once and shares the
same global variables and functions; circular imports are reported as errors.
See [`examples/modules.gj`](examples/modules.gj),
[`examples/collections.gj`](examples/collections.gj), and the
[`examples/inventory.gj`](examples/inventory.gj) and
[`examples/stock.gj`](examples/stock.gj), and
[`examples/calculator.gj`](examples/calculator.gj), and
[`examples/string_utils.gj`](examples/string_utils.gj),
[`examples/invoice_generator.gj`](examples/invoice_generator.gj), and
[`examples/random_game.gj`](examples/random_game.gj) samples combining modules,
functions, lists, and input.

### Dictionaries (Key-Value Pairs)

GujaratiLang supports dictionary data structures with string keys and arbitrary values:

```text
વિદ્યાર્થી = {"નામ": "હર્ષ", "ગુણ": 95};
છાપો વિદ્યાર્થી["નામ"];
વિદ્યાર્થી["શહેર"] = "અમદાવાદ";
છાપો ચાવીઓ(વિદ્યાર્થી);
છાપો મૂલ્યો(વિદ્યાર્થી);
દરેક (ચાવી માં વિદ્યાર્થી) {
    છાપો ચાવી + ": " + લખાણ(વિદ્યાર્થી[ચાવી]);
}
```

### Loop Control (`અટકો` and `ચાલુ_રાખો`)

Use `અટકો` (`atko` / `break`) to exit a loop early and `ચાલુ_રાખો` (`chalu_rakho` / `aagal` / `continue`) to skip the rest of the current iteration:

```text
સંખ્યા = 0;
જ્યાં સુધી (સંખ્યા < 10) {
    સંખ્યા = સંખ્યા + 1;
    જો (સંખ્યા == 2) { ચાલુ_રાખો; }
    જો (સંખ્યા == 5) { અટકો; }
    છાપો સંખ્યા;
}
```

### Date and Time Utilities

Query timestamps, format localized date/time strings, inspect calendar components, or sleep:

```text
હમણાં = સમય();
છાપો તારીખ("%Y-%m-%d %H:%M:%S", હમણાં);
છાપો વર્ષ(હમણાં);
છાપો મહિનો(હમણાં);
શાંત(100); // 100 મિલિસેકન્ડ વિરામ
```

### Error Recovery (`પ્રયત્ન` and `પકડો`)

Protect against runtime errors (division by zero, file missing, invalid type) or explicitly throw custom errors with `ફેંકો` (`phenko`):

```text
પ્રયત્ન {
    જો (ઇનપુટ < 0) {
        ફેંકો("અનૃણ સંખ્યા અપેક્ષિત છે");
    }
    પરિણામ = 100 / ઇનપુટ;
} પકડો (ભૂલ) {
    છાપો "ભૂલ પકડાઈ: " + ભૂલ;
}
```

Example (`examples/hello.gj`):

```text
આવો
ગણતરી = 3;
ગણતરી = ગણતરી + 2;
છાપો ગણતરી;
છાપો 1 + 2 * (3 + 4);
છાપો -8 / 2;
છાપો 5 >= 5;
જો (ગણતરી > 3) {
    છાપો "શરત સાચી છે";
} નહિતર જો (2 == 3) {
    છાપો "આ શાખા ચાલશે નહીં";
} નહિતર {
    છાપો નકામો;
}
કાર્ય સરવાળો(પહેલું, બીજું) {
    પરત પહેલું + બીજું;
}
છાપો સરવાળો(2, 3);
ચેતવણી "This is a warning; the program will continue";
આવજો
```

Warnings and errors are written to standard error with the source location.
Errors include the relevant source line and a caret under the reported column.
Warnings let the program continue; both error statements stop execution and
return a failure status. Built-in errors and warning labels are English by
default, regardless of the Gujarati keywords used in source. Select Gujarati
diagnostics with the `--language gu` option; use `--language en` to select
English explicitly. Messages supplied by the program remain exactly as written.

```powershell
.\build\gujarati.exe --language gu .\examples\hello.gj
```

Diagnostic messages and printed strings support `\"`, `\\`, `\n`, `\r`, and
`\t` escapes.

Variables can contain numbers, strings, lists, or `નકામો`. Assigning to a name
for the first time creates it; later assignments update it. Reading a name
before its first assignment is an error. Variables first assigned in a
conditional block remain available for the rest of the program.

`વાંચો("prompt")` prints the prompt without a newline, reads one line from
standard input, and returns it as a string. Press Enter to submit an empty
string. Reaching end-of-file before a line is read is an error:

```text
આવો
નામ = વાંચો("તમારું નામ શું છે? ");
છાપો "નમસ્તે";
છાપો નામ;
આવજો
```

Run the interactive example with `./build/gujarati ./examples/input.gj` on
Linux or macOS, or `.\build\Release\gujarati.exe .\examples\input.gj` on
Windows.

### Try commands in the REPL

Start the interactive prompt without a source file:

```powershell
.\build\Release\gujarati.exe --repl
```

On Linux or macOS, run `./build/gujarati --repl`. At the prompt, enter one
complete statement or expression per line. Variables and functions remain
available until you exit; a bare expression prints its result:

```text
GujaratiLang> ગણતરી = 2;
GujaratiLang> ગણતરી + 3
5
GujaratiLang> કાર્ય બમણું(મૂલ્ય) { પરત મૂલ્ય * 2; }
GujaratiLang> બમણું(ગણતરી)
4
```

Use `છાપો` to print a value without automatically printing an expression
result. A syntax or runtime error is reported and the prompt remains available.
Enter Ctrl+Z followed by Enter in PowerShell, or Ctrl+D on Linux/macOS, to exit.
Select Gujarati diagnostics with `--language gu --repl`.

`જ્યાં સુધી` checks its condition before each iteration and repeats the block
while the condition is true:

```text
ગણતરી = 0;
જ્યાં સુધી (ગણતરી < 3) {
    ગણતરી = ગણતરી + 1;
    છાપો ગણતરી;
}
```

Declare a function before calling it. Parameters and newly assigned variables
are local to that call. Assignments to existing names, including globals,
update those variables. Functions can call themselves or other previously
declared functions. A function returns
`નકામો` if it reaches the end or uses `પરત;` without a value:

```text
કાર્ય ગુણાકાર(n) {
    જો (n <= 1) { પરત 1; }
    પરત n * ગુણાકાર(n - 1);
}
છાપો ગુણાકાર(5);
```

## Install, build, and run

### Run a prebuilt release

Prebuilt packages are available for Windows x64, Linux x64, and macOS on both
Intel (x64) and Apple Silicon (arm64). Download the matching package from the
[latest GitHub release](https://github.com/HarshitBavaliya/GujaratiLang/releases/latest).
The release includes SHA-256 checksums for all platform packages.

#### Windows x64

1. Download the latest
   [GujaratiLang Windows 64-bit release](https://github.com/HarshitBavaliya/GujaratiLang/releases/latest/download/gujaratilang-windows-x64.zip).
2. Extract the ZIP file.
3. Optional: add GujaratiLang to your user `PATH` by opening PowerShell in the
   extracted folder and running:

   ```powershell
   powershell -ExecutionPolicy Bypass -File .\install.ps1
   ```

   This installs under your user profile and does not require administrator
   access. Open a new terminal after installation to run `gujarati` from any
   folder. You can also use the executable directly without installing it.
4. Open PowerShell in the extracted folder and run the included example:

   ```powershell
   .\gujarati.exe .\examples\hello.gj
   ```

5. Run your own program by giving its `.gj` file path:

   ```powershell
   .\gujarati.exe C:\path\to\your-program.gj
   ```

#### Linux x64

Download `gujaratilang-linux-x64.tar.gz`, then extract and run it from a
terminal:

```sh
tar -xzf gujaratilang-linux-x64.tar.gz
./gujarati ./examples/hello.gj
./gujarati /path/to/your-program.gj
```

This package is built on Ubuntu 22.04 and requires a compatible glibc-based
Linux distribution. To make `gujarati` available from any folder, move the
extracted files to a directory you own and add that directory to your shell's
`PATH`.

#### macOS Intel and Apple Silicon

Download `gujaratilang-macos-x64.tar.gz` for Intel Macs or
`gujaratilang-macos-arm64.tar.gz` for Apple Silicon Macs. In Terminal, extract
the matching package and run the example:

```sh
tar -xzf gujaratilang-macos-arm64.tar.gz
./gujarati ./examples/hello.gj
./gujarati /path/to/your-program.gj
```

Use the `macos-x64` archive on Intel instead of the `macos-arm64` archive shown
in the extraction command. The macOS binaries are not signed or notarized, so
macOS may display a security warning. The release package contains the
interpreter, examples, and a short `README.txt`.
To run `gujarati` from any folder, move the extracted files to a directory you
own and add that directory to your shell's `PATH`.

To build from source or contribute, follow the developer setup below.

### Build from source

Building requires Git, CMake 3.16 or newer, and a C99 compiler. On Windows,
install Visual Studio or Build Tools with the **Desktop development with C++**
workload. On Debian or Ubuntu, install the tools with
`sudo apt install build-essential cmake git`. On macOS, install Xcode Command
Line Tools and CMake.

Then clone, build, and run the example:

```text
git clone https://github.com/HarshitBavaliya/GujaratiLang.git
cd GujaratiLang
cmake -S . -B build
cmake --build build --config Release
```

On Windows, run
`.\build\Release\gujarati.exe .\examples\hello.gj`. On Linux or macOS, run
`./build/gujarati ./examples/hello.gj`. For a single-configuration CMake
generator, the executable may instead be at `build/gujarati.exe` on Windows.

If PowerShell says `cmake` is not recognized, install CMake, add it to `PATH`,
and open a new PowerShell window.

## Tests

CTest runs the interpreter regression suite after building:

```powershell
ctest --test-dir build --output-on-failure
```

GitHub Actions builds and runs the tests on Windows, Ubuntu, and both Intel and
Apple Silicon macOS runners for pushes and pull requests. Tagged releases
publish prebuilt packages for all four supported platform targets.
The regression suite also runs the shipped Fibonacci, temperature-converter,
inventory, and stock examples and checks their output.

## Project website

The static landing page is in `website/index.html`. It has no build step or
external dependencies. Upload it as `index.html` to the subdomain's web root
using FTPS or SFTP; avoid unencrypted FTP when transferring hosting credentials.
The VS Code FTPS profile in `.vscode/sftp.json` is local-only and excluded from
Git. It leaves the password unset so the SFTP extension can prompt for it.

## Project status

GujaratiLang includes a C interpreter, regression tests, a beginner tutorial,
sample programs, and portable releases for Windows, Linux, and macOS. Future
work will be guided by user feedback and the project's issue tracker.

## Contributing

Bug reports and pull requests are welcome. See [CONTRIBUTING.md](CONTRIBUTING.md)
for build and contribution guidelines. GujaratiLang is licensed under the
[MIT License](LICENSE).
