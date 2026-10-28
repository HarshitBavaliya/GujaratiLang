# Changelog

## 1.0.0

- Major 30-Point Milestone Release for GujaratiLang:
  - JSON serialization & parsing: `json_lakho` (`જેસન_લખો`), `json_vancho` (`જેસન_વાંચો`)
  - Command-line arguments: `daleelo` (`દલીલો`), `arg_yadi` (`દલીલ_યાદી`)
  - Radix integer & string conversions: `dvi_sankhya` (`દ્વિ_સંખ્યા`), `dvi_thi_sankhya` (`દ્વિ_થી_સંખ્યા`), `hex_lakhan` (`હેક્સ_લખાણ`), `hex_thi_sankhya` (`હેક્સ_થી_સંખ્યા`)
  - Directory & folder utilities: `folder_chhe` (`ફોલ્ડર_છે`), `folder_banao` (`ફોલ્ડર_બનાવો`), `folder_suchi` (`ફોલ્ડર_સૂચિ`)
  - System shell command execution: `command_chalao` (`કમાન્ડ_ચલાવો`), `system_kary` (`સિસ્ટમ`)
  - Functional list operations: `naksho_yadi` (`નકશો_યાદી` - map), `gaalo_yadi` (`ગાળો_યાદી` - filter), `sameto_yadi` (`સમેટો_યાદી` - reduce), `shodho_yadi` (`શોધો_યાદી` - find), `shodho_suchak_yadi` (`શોધો_સૂચક_યાદી`)
  - List manipulation: `chapti_yadi` (`ચપટી_યાદી` - flatten), `zip_yadi` (`ઝીપ_યાદી`)
  - Wildcard pattern matching & global replace: `pattern_shodho` (`પેટર્ન_શોધો`), `lakhan_badlo_darek` (`લખાણ_બદલો_દરેક`)
  - Base64 encoding and decoding: `base64_kod` (`બેઝ૬૪_કોડ`), `base64_decode` (`બેઝ૬૪_ડીકોડ`)
  - String case utilities: `shirshak_lakhan` (`શીર્ષક_લખાણ`), `pratham_moti` (`પ્રથમ_મોટી`)
  - String template formatting: `swaroop` (`સ્વરૂપ`)
  - Levenshtein edit distance: `lakhan_antar` (`લખાણ_અંતર`)
  - SHA-256 cryptographic hashing: `sha256_hash` (`શા૨૫૬_હેશ`)
  - Trigonometry: `sine` (`સાઇન`), `cosine` (`કોસાઇન`), `tangent` (`ટેન્જન્ટ`), `arcsin` (`આર્કસાઇન`), `arccos` (`આર્કકોસ`), `arctan` (`આર્કટેન`)
  - Number theory & angle conversions: `guru_tam` (`ગુરુ_તમ`), `laghu_tam` (`લઘુ_તમ`), `ansha_thi_radian` (`અંશ_થી_રેડિયન`), `radian_thi_ansha` (`રેડિયન_થી_અંશ`)
  - Matrix 2D math: `matrix_sarvalo` (`મેટ્રિક્સ_સરવાળો`), `matrix_gunakar` (`મેટ્રિક્સ_ગુણાકાર`)
  - Syntax extensions: Ternary conditional `? :`, compound assignments `+=`, `-=`, `*=`, `/=`, `%=`, modulo operator `%`, and constant variable declarations with `achala` (`અચળ`) / `const`
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
