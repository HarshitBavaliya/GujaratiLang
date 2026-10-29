file(MAKE_DIRECTORY "${TEST_BINARY_DIR}")
set(input_text "")

if(TEST_CASE STREQUAL "arithmetic_and_comparisons")
    set(source [=[આવો
છાપો 1 + 2 * 3 == 7;
છાપો 1 == 1;
છાપો 1 != 2;
છાપો 1 < 2;
છાપો 2 <= 2;
છાપો 3 > 2;
છાપો 3 >= 3;
આવજો
]=])
    set(expected_stdout "1\n1\n1\n1\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "conditionals")
    set(source [=[આવો
જો (0) { છાપો "wrong"; } નહિતર જો (2 > 1) { છાપો "second"; } નહિતર { છાપો "wrong"; }
જો (1 < 0) { છાપો "wrong"; } નહિતર { છાપો "else"; }
આવજો
]=])
    set(expected_stdout "second\nelse\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "logical_operators")
    set(source [=[આવો
છાપો 1 અને 2 > 1;
છાપો 1 અથવા 0 અને 0;
છાપો નહીં 1 == 1;
છાપો નહીં 0 == 1;
જો (2 > 1 અને નહીં 0) { છાપો "and and not"; }
જો (0 અથવા 3 == 3) { છાપો "or"; }
આવજો
]=])
    set(expected_stdout "1\n1\n0\n1\nand and not\nor\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "logical_short_circuit")
    set(source [=[આવો
છાપો 1 અથવા 1 / 0 == 0;
છાપો 0 અને 1 / 0 == 0;
આવજો
]=])
    set(expected_stdout "1\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "logical_type_error")
    set(source [=[આવો
છાપો "text" અને 1;
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "logical operators require a number or 'નકામો'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "while_loop")
    set(source [=[આવો
ગણતરી = 0;
જ્યાં સુધી (ગણતરી < 3) {
    ગણતરી = ગણતરી + 1;
    હાલનું = ગણતરી;
    છાપો હાલનું;
}
છાપો હાલનું;
આવજો
]=])
    set(expected_stdout "1\n2\n3\n3\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "nested_while_loops")
    set(source [=[આવો
બહાર = 0;
અંદર = 0;
સરવાળો = 0;
જ્યાં સુધી (બહાર < 2) {
    અંદર = 0;
    જ્યાં સુધી (અંદર < 2) {
        સરવાળો = સરવાળો + 1;
        અંદર = અંદર + 1;
    }
    બહાર = બહાર + 1;
}
છાપો સરવાળો;
આવજો
]=])
    set(expected_stdout "4\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "while_false_condition")
    set(source [=[આવો
જ્યાં સુધી (0) { છાપો "wrong"; }
છાપો "after";
આવજો
]=])
    set(expected_stdout "after\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "while_in_skipped_branch")
    set(source [=[આવો
જો (0) { જ્યાં સુધી (1) { છાપો "wrong"; } }
છાપો "after";
આવજો
]=])
    set(expected_stdout "after\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "strings_and_null")
    set(source [=[આવો
છાપો નકામો;
છાપો "line\nnext";
આવજો
]=])
    set(expected_stdout "નકામો\nline\nnext\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "string_concatenation")
    set(source [=[આવો
નામ = "હર્ષ";
સંદેશ = "નમસ્તે, " + નામ + "!";
છાપો સંદેશ;
છાપો "line\n" + "next";
છાપો 1 + 2;
આવજો
]=])
    set(expected_stdout "નમસ્તે, હર્ષ!\nline\nnext\n3\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "string_number_addition_error")
    set(source [=[આવો
છાપો "count: " + 2;
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "arithmetic requires numbers")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "string_equality")
    set(source [=[આવો
છાપો "હર્ષ" == "હર્ષ";
છાપો "હર્ષ" != "હર્ષ";
છાપો "હર્ષ" != "હર્ષભાઈ";
છાપો "line\nnext" == "line\nnext";
છાપો "હર્ષ" + "ભાઈ" == "હર્ષભાઈ";
જો ("હર્ષ" == "હર્ષ") { છાપો "match"; }
આવજો
]=])
    set(expected_stdout "1\n0\n1\n1\n1\nmatch\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "string_equality_input")
    set(source [=[આવો
નામ = વાંચો("Name? ");
જો (નામ == "હર્ષ") { છાપો "welcome"; }
આવજો
]=])
    set(input_text "હર્ષ\n")
    set(expected_stdout "Name? welcome\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "string_equality_type_error")
    set(source [=[આવો
છાપો "1" == 1;
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "comparisons require numbers")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "string_ordering_type_error")
    set(source [=[આવો
છાપો "a" < "b";
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "comparisons require numbers")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "string_length_ascii")
    set(source [=[આવો
છાપો લંબાઈ("");
છાપો લંબાઈ("Gujarati");
આવજો
]=])
    set(expected_stdout "0\n8\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "string_length_gujarati")
    set(source [=[આવો
છાપો લંબાઈ("હર્ષ");
નામ = વાંચો("Name? ");
છાપો લંબાઈ(નામ);
આવજો
]=])
    set(input_text "હર્ષ\n")
    set(expected_stdout "4\nName? 4\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "string_length_escapes")
    set(source [=[આવો
છાપો લંબાઈ("a\n");
છાપો લંબાઈ("ગુ" + "જ");
આવજો
]=])
    set(expected_stdout "2\n3\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "string_length_wrong_argument_count")
    set(source [=[આવો
છાપો લંબાઈ();
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "string_length_type_error")
    set(source [=[આવો
છાપો લંબાઈ(1);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string or list argument for 'લંબાઈ'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_string_length")
    set(source [=[આવો
કાર્ય લંબાઈ(text) { પરત 0; }
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "variables")
    set(source [=[આવો
ગણતરી = 3;
ગણતરી = ગણતરી + 2;
count = ગણતરી * 2;
item_2 = count + 1;
છાપોવસ્તુ = item_2 + 1;
કે = 13;
છાપો ગણતરી;
છાપો count;
છાપો છાપોવસ્તુ;
છાપો કે;
સંદેશ = "Gujarati \nstring";
છાપો સંદેશ;
નકામું = નકામો;
છાપો નકામું;
જો (ગણતરી == 5) { છાપો "variable condition"; }
આવજો
]=])
    set(expected_stdout "5\n10\n12\n13\nGujarati \nstring\nનકામો\nvariable condition\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "variable_in_skipped_branch")
    set(source [=[આવો
જો (0) { ખોટું = 1; }
સાચું = 2;
છાપો સાચું;
આવજો
]=])
    set(expected_stdout "2\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "variable_skipped_not_created")
    set(source [=[આવો
જો (0) { છુપાયેલું = 1; }
છાપો છુપાયેલું;
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "undefined variable")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "variable_reassignment")
    set(source [=[આવો
કિંમત = 1;
કિંમત = 2;
છાપો કિંમત;
આવજો
]=])
    set(expected_stdout "2\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "undefined_variable")
    set(source [=[આવો
જવાબ = અજ્ઞાત;
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "undefined variable")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "undefined_variable_gujarati")
    set(source [=[આવો
છાપો અજ્ઞાત;
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "અવ્યાખ્યાયિત ચલ")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "function_calls")
    set(source [=[આવો
કાર્ય સરવાળો(પહેલું, બીજું) {
    પરત પહેલું + બીજું;
}
છાપો સરવાળો(2, 3);
આવજો
]=])
    set(expected_stdout "5\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "nested_function_calls")
    set(source [=[આવો
કાર્ય બમણું(કિંમત) { પરત કિંમત * 2; }
કાર્ય સરવાળો(પહેલું, બીજું) { પરત પહેલું + બીજું; }
છાપો સરવાળો(બમણું(3), બમણું(4));
આવજો
]=])
    set(expected_stdout "14\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "recursive_function")
    set(source [=[આવો
કાર્ય ગુણાકાર(n) {
    જો (n <= 1) { પરત 1; }
    પરત n * ગુણાકાર(n - 1);
}
છાપો ગુણાકાર(5);
આવજો
]=])
    set(expected_stdout "120\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "function_returns")
    set(source [=[આવો
કાર્ય ખાલી() { }
કાર્ય સ્પષ્ટખાલી() { પરત; }
કાર્ય પહેલા() {
    જ્યાં સુધી (1) { પરત 9; }
    પરત 10;
}
છાપો ખાલી();
છાપો સ્પષ્ટખાલી();
છાપો પહેલા();
આવજો
]=])
    set(expected_stdout "નકામો\nનકામો\n9\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "function_local_and_global_variables")
    set(source [=[આવો
કિંમત = 7;
કાર્ય સ્થાનિક() {
    કિંમત = 3;
    પરત કિંમત;
}
કાર્ય વૈશ્વિકવાંચો() { પરત કિંમત; }
કાર્ય વૈશ્વિકબદલો() { કિંમત = 8; }
કાર્ય નવીસ્થાનિક() {
    અસ્થાયી = 1;
    અસ્થાયી = અસ્થાયી + 1;
    પરત અસ્થાયી;
}
છાપો સ્થાનિક();
છાપો વૈશ્વિકવાંચો();
વૈશ્વિકબદલો();
છાપો વૈશ્વિકવાંચો();
છાપો નવીસ્થાનિક();
છાપો નવીસ્થાનિક();
આવજો
]=])
    set(expected_stdout "3\n3\n8\n2\n2\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "function_undefined")
    set(source [=[આવો
છાપો અજ્ઞાત();
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "undefined function")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "function_wrong_argument_count")
    set(source [=[આવો
કાર્ય ઓળખો(કિંમત) { પરત કિંમત; }
છાપો ઓળખો();
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "function_duplicate")
    set(source [=[આવો
કાર્ય ઓળખો() { પરત 1; }
કાર્ય ઓળખો() { પરત 2; }
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "function is already declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "function_duplicate_parameter")
    set(source [=[આવો
કાર્ય ઓળખો(કિંમત, કિંમત) { પરત કિંમત; }
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "parameter is already declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "return_outside_function")
    set(source [=[આવો
પરત 1;
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'પરત' can only be used inside a function")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "input")
    set(source [=[આવો
કાર્ય પૂછો() { પરત વાંચો("Name? "); }
નામ = પૂછો();
છાપો "Hello, " + નામ;
આવજો
]=])
    set(input_text "હર્ષ\n")
    set(expected_stdout "Name? Hello, હર્ષ\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "input_empty_line")
    set(source [=[આવો
જવાબ = વાંચો("Value: ");
છાપો જવાબ;
આવજો
]=])
    set(input_text "\n")
    set(expected_stdout "Value: \n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "input_long_line")
    string(REPEAT "x" 128 input_text)
    string(APPEND input_text "\n")
    set(source [=[આવો
જવાબ = વાંચો("Long: ");
છાપો જવાબ;
આવજો
]=])
    set(expected_stdout "Long: ${input_text}")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "input_eof")
    set(source [=[આવો
જવાબ = વાંચો("Enter: ");
આવજો
]=])
    set(input_text "")
    set(expected_stdout "Enter: ")
    set(expected_stderr "could not read a line from standard input")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "input_wrong_argument_count")
    set(source [=[આવો
જવાબ = વાંચો();
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "input_prompt_type")
    set(source [=[આવો
જવાબ = વાંચો(1);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string prompt for 'વાંચો'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "input_skipped_branch")
    set(source [=[આવો
જો (0) { છુપાયેલું = વાંચો("Do not ask: "); }
છાપો "after";
આવજો
]=])
    set(input_text "")
    set(expected_stdout "after\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "reserved_input_function")
    set(source [=[આવો
કાર્ય વાંચો(prompt) { પરત prompt; }
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "repl_persistence")
    set(source "")
    set(program_arguments --repl)
    set(input_text [=[count = 2;
count + 3
કાર્ય double(value) { પરત value * 2; }
double(count)
]=])
    set(expected_stdout "GujaratiLang> GujaratiLang> 5\nGujaratiLang> GujaratiLang> 4\nGujaratiLang> ")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "repl_error_recovery")
    set(source "")
    set(program_arguments --repl)
    set(input_text [=[છાપો (1 + );
છાપો 2 + 3;
]=])
    set(expected_stdout "GujaratiLang> GujaratiLang> 5\nGujaratiLang> ")
    set(expected_stderr "expected a number")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "repl_runtime_error_recovery")
    set(source "")
    set(program_arguments --repl)
    set(input_text [=[છાપો unknown;
છાપો 7;
]=])
    set(expected_stdout "GujaratiLang> GujaratiLang> 7\nGujaratiLang> ")
    set(expected_stderr "undefined variable")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "repl_input")
    set(source "")
    set(program_arguments --repl)
    set(input_text [=[name = વાંચો("Name? ");
હર્ષ
છાપો "Hello, " + name;
]=])
    set(expected_stdout "GujaratiLang> Name? GujaratiLang> Hello, હર્ષ\nGujaratiLang> ")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "repl_string_length")
    set(source "")
    set(program_arguments --repl)
    set(input_text [=[લંબાઈ("હર્ષ")
]=])
    set(expected_stdout "GujaratiLang> 4\nGujaratiLang> ")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "warnings_english")
    set(source [=[આવો
ચેતવણી "user warning";
છાપો 1;
આવજો
]=])
    set(expected_stdout "1\n")
    set(expected_stderr "warning: user warning")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "warnings_gujarati")
    set(source [=[આવો
ચેતવણી "user warning";
છાપો 1;
આવજો
]=])
    set(expected_stdout "1\n")
    set(expected_stderr "ચેતવણી: user warning")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "errors")
    set(source [=[આવો
ભૂલ "stop here";
છાપો 99;
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "error: stop here")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "fatal_errors")
    set(source [=[આવો
ઘાતક ભૂલ "stop here";
છાપો 99;
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "fatal error: stop here")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "invalid_condition")
    set(source [=[આવો
છાપો નકામો == 0;
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "comparisons require numbers")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "invalid_language")
    set(source [=[આવો
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "usage:")
    set(expect_failure TRUE)
    set(language_args --language fr)
elseif(TEST_CASE STREQUAL "romanized_keywords")
    set(source [=[aavo
kary double(value) { parat value * 2; }
count = 0;
jya_sudhi (count < 2 ane nahi 0) {
    count = count + 1;
}
jo (count == 2 athva 0) {
    chhapo double(count);
} nahitar_jo (count == 3) {
    chhapo 99;
} nahitar {
    chhapo nakamo;
}
chetavani "romanized warning";
aavjo
]=])
    set(expected_stdout "4\n")
    set(expected_stderr "warning: romanized warning")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "romanized_keyword_identifier_boundary")
    set(source [=[aavo
aavo_count = 3;
chhapo aavo_count;
aavjo
]=])
    set(expected_stdout "3\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "romanized_builtins")
    set(source [=[aavo
name = vancho("Name? ");
chhapo "Hello, " + name;
chhapo lambai(name);
aavjo
]=])
    set(input_text "Harsh\n")
    set(expected_stdout "Name? Hello, Harsh\n5\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "reserved_romanized_builtin")
    set(source [=[aavo
kary lambai(text) { parat 0; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_sankhya")
    set(source [=[aavo
chhapo sankhya("42") + 8;
chhapo sankhya("  -12.5  ") * 2;
chhapo સંખ્યા("100");
aavjo
]=])
    set(expected_stdout "50\n-25\n100\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_sankhya_error")
    set(source [=[aavo
chhapo sankhya("not_a_number");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "could not parse string as a number")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_sankhya_type_error")
    set(source [=[aavo
chhapo sankhya(123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string argument for 'સંખ્યા' or 'sankhya'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_lakhan")
    set(source [=[aavo
chhapo "Val: " + lakhan(42);
chhapo "Pi: " + lakhan(3.14);
chhapo "Null: " + lakhan(nakamo);
chhapo "List: " + lakhan([1, "two", 3]);
chhapo "ગુજરાતી: " + લખાણ(99);
aavjo
]=])
    set(expected_stdout "Val: 42\nPi: 3.14\nNull: નકામો\nList: [1, two, 3]\nગુજરાતી: 99\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_prakar")
    set(source [=[aavo
chhapo prakar(42);
chhapo prakar("hello");
chhapo prakar([1, 2]);
chhapo prakar(nakamo);
chhapo પ્રકાર(100);
aavjo
]=])
    set(expected_stdout "number\nstring\nlist\nnull\nnumber\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "reserved_sankhya_lakhan_prakar")
    set(source [=[aavo
kary lakhan(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_umero")
    set(source [=[aavo
nums = [1, 2];
umero(nums, 3);
chhapo nums;
ઉમેરો(nums, 4);
chhapo nums;
words = [];
umero(words, "apple");
umero(words, "banana");
chhapo words;
nested = [[1]];
umero(nested, [2, 3]);
chhapo nested;
aavjo
]=])
    set(expected_stdout "[1, 2, 3]\n[1, 2, 3, 4]\n[apple, banana]\n[[1], [2, 3]]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_umero_error")
    set(source [=[aavo
umero(42, 10);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a list first argument for 'ઉમેરો' or 'umero'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_kapo")
    set(source [=[aavo
chhapo kapo("hello world", 0, 5);
chhapo kapo("hello world", 6);
chhapo kapo("hello world", 3, 4);
chhapo કાપો("ગુજરાતી", 0, 3);
chhapo kapo("hello", 10, 2);
chhapo kapo("hello", 2, 100);
aavjo
]=])
    set(expected_stdout "hello\nworld\nlo w\nગુજ\n\nllo\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_kapo_error")
    set(source [=[aavo
chhapo kapo(123, 0, 1);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string first argument for 'કાપો' or 'kapo'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_shodho")
    set(source [=[aavo
chhapo shodho("hello world", "world");
chhapo shodho("hello world", "o");
chhapo shodho("hello world", "o", 5);
chhapo shodho("hello world", "xyz");
chhapo shodho("hello", "");
chhapo શોધો("ગુજરાતી", "રા");
chhapo shodho("ગુજરાતી", "નથી");
aavjo
]=])
    set(expected_stdout "6\n4\n7\n-1\n0\n3\n-1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_shodho_error")
    set(source [=[aavo
chhapo shodho("hello", 42);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected string arguments for 'શોધો' or 'shodho'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_umero_kapo_shodho")
    set(source [=[aavo
kary umero(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_kadho")
    set(source [=[aavo
items = [10, 20, 30];
last = kadho(items);
chhapo last;
chhapo items;
first = kadho(items, 0);
chhapo first;
chhapo items;
rem = કાઢો(items);
chhapo rem;
chhapo items;
aavjo
]=])
    set(expected_stdout "30\n[10, 20]\n10\n[20]\n20\n[]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_kadho_error")
    set(source [=[aavo
kadho([]);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "cannot remove item from an empty list")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_kadho")
    set(source [=[aavo
kary kadho(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_case_conversion")
    set(source [=[aavo
chhapo peli_abcd("hello world 123");
chhapo biji_abcd("HELLO WORLD 123");
chhapo પહેલી_એબીસીડી("mixed CASE!");
chhapo બીજી_એબીસીડી("mixed CASE!");
chhapo peli_abcd("ગુજરાતી");
aavjo
]=])
    set(expected_stdout "HELLO WORLD 123\nhello world 123\nMIXED CASE!\nmixed case!\nગુજરાતી\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_case_conversion_error")
    set(source [=[aavo
chhapo peli_abcd(123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string argument for case conversion")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_case_conversion")
    set(source [=[aavo
kary peli_abcd(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_math_utils")
    set(source [=[aavo
chhapo mahatam(10, 25);
chhapo nyunatam(10, 25);
chhapo dhan_mulya(-42.5);
chhapo dhan_mulya(17);
chhapo મહત્તમ(100, 50);
chhapo ન્યૂનતમ(100, 50);
chhapo ધન_મૂલ્ય(-99);
aavjo
]=])
    set(expected_stdout "25\n10\n42.5\n17\n100\n50\n99\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_math_utils_error")
    set(source [=[aavo
chhapo mahatam("10", 20);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected number arguments for math function")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_math_utils")
    set(source [=[aavo
kary mahatam(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_ultavo")
    set(source [=[aavo
items = [1, 2, 3, 4];
ultavo(items);
chhapo items;
chhapo ultavo(["a", "b", "c"]);
chhapo ઉલટાવો([42]);
chhapo ઉલટાવો([]);
aavjo
]=])
    set(expected_stdout "[4, 3, 2, 1]\n[c, b, a]\n[42]\n[]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_ultavo_error")
    set(source [=[aavo
chhapo ultavo("not a list");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a list argument for 'ઉલટાવો' or 'ultavo'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_ultavo")
    set(source [=[aavo
kary ultavo(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_bhag")
    set(source [=[aavo
parts = bhag("red,green,blue", ",");
chhapo parts;
chars = bhag("hello", "");
chhapo chars;
gparts = ભાગ("સફરજન કેળૂ́", " ");
chhapo gparts;
aavjo
]=])
    set(expected_stdout "[red, green, blue]\n[h, e, l, l, o]\n[સફરજન, કેળૂ́]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_bhag_error")
    set(source [=[aavo
chhapo bhag(123, ",");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected string arguments for 'ભાગ' or 'bhag'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_bhag")
    set(source [=[aavo
kary bhag(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_jodo")
    set(source [=[aavo
items = ["one", "two", "three"];
chhapo jodo(items, "-");
chhapo જોડો(["સૂર્ય", "ચંદ્ર"], " અને ");
chhapo jodo([1, 2, 3], ", ");
chhapo jodo([], ",");
aavjo
]=])
    set(expected_stdout "one-two-three\nસૂર્ય અને ચંદ્ર\n1, 2, 3\n\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_jodo_error")
    set(source [=[aavo
chhapo jodo("not a list", ",");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected list and string separator arguments for 'જોડો' or 'jodo'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_jodo")
    set(source [=[aavo
kary jodo(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_saf")
    set(source [=[aavo
chhapo "[" + saf("  hello world  ") + "]";
chhapo "[" + saf("   ") + "]";
chhapo "[" + સાફ("   નમસ્તે ભારત   ") + "]";
aavjo
]=])
    set(expected_stdout "[hello world]\n[]\n[નમસ્તે ભારત]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_saf_error")
    set(source [=[aavo
chhapo saf(123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string argument for 'સાફ' or 'saf'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_saf")
    set(source [=[aavo
kary saf(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_ghat_mul")
    set(source [=[aavo
chhapo ghat(2, 3);
chhapo mul(16);
chhapo ઘાત(3, 2);
chhapo મૂળ(100);
aavjo
]=])
    set(expected_stdout "8\n4\n9\n10\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_ghat_mul_error")
    set(source [=[aavo
chhapo mul(-9);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "cannot calculate square root of a negative number")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_ghat_mul")
    set(source [=[aavo
kary ghat(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_gothvo")
    set(source [=[aavo
nums = [42, 5, 17, 3, 99, 0, -10];
gothvo(nums);
chhapo nums;
words = ["mango", "apple", "banana"];
chhapo gothvo(words);
g_list = ["કેળું", "ચીકુ", "કેરી"];
chhapo ગોઠવો(g_list);
aavjo
]=])
    set(expected_stdout "[-10, 0, 3, 5, 17, 42, 99]\n[apple, banana, mango]\n[કેરી, કેળું, ચીકુ]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_gothvo_error")
    set(source [=[aavo
chhapo gothvo("not a list");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a list argument for 'ગોઠવો' or 'gothvo'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_gothvo")
    set(source [=[aavo
kary gothvo(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_badlo")
    set(source [=[aavo
chhapo badlo("hello world", "world", "gujaratilang");
chhapo badlo("banana", "a", "o");
chhapo બદલો("નમસ્તે ભારત", "ભારત", "ગુજરાત");
aavjo
]=])
    set(expected_stdout "hello gujaratilang\nbonono\nનમસ્તે ગુજરાત\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_badlo_error")
    set(source [=[aavo
chhapo badlo(123, "a", "b");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected string arguments for 'બદલો' or 'badlo'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_badlo")
    set(source [=[aavo
kary badlo(x, y, z) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_prefix_suffix")
    set(source [=[aavo
chhapo sharuat_sathe("gujaratilang", "guj");
chhapo ant_sathe("gujaratilang", "lang");
chhapo શરૂઆત_સાથે("નમસ્તે", "નમ");
chhapo અંત_સાથે("નમસ્તે", "સ્તે");
aavjo
]=])
    set(expected_stdout "1\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_prefix_suffix_error")
    set(source [=[aavo
chhapo sharuat_sathe("abc", 123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected string arguments for prefix/suffix check")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_prefix_suffix")
    set(source [=[aavo
kary sharuat_sathe(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_samave_chhe")
    set(source [=[aavo
items = ["apple", "banana", 42];
chhapo samave_chhe(items, "banana");
chhapo samave_chhe(items, "orange");
chhapo samave_chhe(items, 42);
chhapo સમાવે_છે(["સફરજન", "ચીકુ"], "ચીકુ");
aavjo
]=])
    set(expected_stdout "1\n0\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_samave_chhe_error")
    set(source [=[aavo
chhapo samave_chhe("not a list", 10);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a list first argument for 'સમાવે_છે' or 'samave_chhe'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_samave_chhe")
    set(source [=[aavo
kary samave_chhe(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_round_trunc")
    set(source [=[aavo
chhapo gol(4.6);
chhapo niche(4.9);
chhapo upar(4.1);
chhapo ગોળ(7.5);
chhapo નીચે(7.9);
chhapo ઉપર(7.1);
aavjo
]=])
    set(expected_stdout "5\n4\n5\n8\n7\n8\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_round_trunc_error")
    set(source [=[aavo
chhapo gol("invalid");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected number arguments for math function")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_round_trunc")
    set(source [=[aavo
kary gol(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_punravartan")
    set(source [=[aavo
chhapo punravartan("=", 5);
chhapo punravartan("abc", 2);
chhapo પુનરાવર્તન("જય", 2);
aavjo
]=])
    set(expected_stdout "=====\nabcabc\nજયજય\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_punravartan_error")
    set(source [=[aavo
chhapo punravartan("abc", -2);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "repetition count for 'પુનરાવર્તન' or 'punravartan' must be a non-negative whole number")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_punravartan")
    set(source [=[aavo
kary punravartan(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_tukdo")
    set(source [=[aavo
items = [10, 20, 30, 40, 50];
chhapo tukdo(items, 1, 3);
chhapo tukdo(items, 3);
chhapo ટુકડો(["a", "b", "c"], 0, 2);
aavjo
]=])
    set(expected_stdout "[20, 30, 40]\n[40, 50]\n[a, b]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_tukdo_error")
    set(source [=[aavo
chhapo tukdo("not a list", 0);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a list first argument for 'ટુકડો' or 'tukdo'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_tukdo")
    set(source [=[aavo
kary tukdo(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_sthan")
    set(source [=[aavo
items = [10, 20, 30, 20, 50];
chhapo sthan(items, 20);
chhapo sthan(items, 20, 2);
chhapo sthan(items, 99);
chhapo sthan([], 1);
chhapo સ્થાન(["safarchand", "keri", "kela"], "keri");
chhapo સ્થાન(["safarchand", "keri", "kela"], "draksh");
chhapo સ્થાન([1, nakamo, 2], nakamo);
aavjo
]=])
    set(expected_stdout "1\n3\n-1\n-1\n1\n-1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_sthan_error")
    set(source [=[aavo
chhapo sthan("not a list", 10);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a list first argument for 'સ્થાન' or 'sthan'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_sthan")
    set(source [=[aavo
kary sthan(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_muko")
    set(source [=[aavo
items = [10, 30];
muko(items, 1, 20);
chhapo items;
muko(items, 0, 5);
chhapo items;
muko(items, 4, 40);
chhapo items;
મૂકો(items, 2, "inserted");
chhapo items;
empty = [];
muko(empty, 0, "first");
chhapo empty;
aavjo
]=])
    set(expected_stdout "[10, 20, 30]\n[5, 10, 20, 30]\n[5, 10, 20, 30, 40]\n[5, 10, inserted, 20, 30, 40]\n[first]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_muko_error")
    set(source [=[aavo
muko([1], 5, 1);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "insert index for 'મૂકો' or 'muko' is out of range")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_muko")
    set(source [=[aavo
kary muko(x, y, z) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_padding")
    set(source [=[aavo
chhapo "[" + dabe_bharo("42", 5, "0") + "]";
chhapo "[" + dabe_bharo("hello", 10) + "]";
chhapo "[" + jamne_bharo("hello", 10) + "]";
chhapo "[" + jamne_bharo("item", 10, ".") + "]";
chhapo "[" + dabe_bharo("long string", 5) + "]";
chhapo "[" + ડાબે_ભરો("42", 5, "0") + "]";
chhapo "[" + જમણે_ભરો("નમસ્તે", 10, "-") + "]";
chhapo "[" + jamne_bharo("hi", 6, "=-") + "]";
aavjo
]=])
    set(expected_stdout "[00042]\n[     hello]\n[hello     ]\n[item......]\n[long string]\n[00042]\n[નમસ્તે----]\n[hi=-=-]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_padding_error")
    set(source [=[aavo
chhapo dabe_bharo(123, 5);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string first argument for padding")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_padding")
    set(source [=[aavo
kary dabe_bharo(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_sima")
    set(source [=[aavo
chhapo sima(25, 10, 50);
chhapo sima(5, 10, 50);
chhapo sima(75, 10, 50);
chhapo sima(-20, -10, 10);
chhapo sima(15, -10, 10);
chhapo સીમા(5, 0, 10);
chhapo સીમા(-5, 0, 10);
chhapo સીમા(15, 0, 10);
aavjo
]=])
    set(expected_stdout "25\n10\n50\n-10\n10\n5\n0\n10\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_sima_error")
    set(source [=[aavo
chhapo sima(10, 50, 20);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "minimum bound cannot be greater than maximum bound for 'સીમા' or 'sima'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_sima")
    set(source [=[aavo
kary sima(x, y, z) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadachhik")
    set(source [=[aavo
f1 = yadachhik();
chhapo f1 >= 0.0 ane f1 < 1.0;
f2 = યાદચ્છિક();
chhapo f2 >= 0.0 અને f2 < 1.0;
d1 = yadachhik(1, 6);
chhapo d1 >= 1 ane d1 <= 6;
d2 = યાદચ્છિક(10, 20);
chhapo d2 >= 10 અને d2 <= 20;
chhapo yadachhik(42, 42);
d3 = yadachhik(-10, -5);
chhapo d3 >= -10 ane d3 <= -5;
aavjo
]=])
    set(expected_stdout "1\n1\n1\n1\n42\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_yadachhik_error")
    set(source [=[aavo
chhapo yadachhik(1);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadachhik_bounds_error")
    set(source [=[aavo
chhapo yadachhik(10, 2);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "minimum bound cannot be greater than maximum bound for 'યાદચ્છિક' or 'yadachhik'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadachhik_gujarati_error")
    set(source [=[આવો
છાપો યાદચ્છિક(10, 2);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'યાદચ્છિક' માટે ન્યૂનતમ સીમા મહત્તમ સીમા કરતાં મોટી ન હોઈ શકે")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_yadachhik")
    set(source [=[aavo
kary yadachhik() { parat 0; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_beej")
    set(source [=[aavo
beej(12345);
r1 = yadachhik();
beej(12345);
r2 = yadachhik();
chhapo r1 == r2;
બીજ(999);
g1 = યાદચ્છિક(1, 100);
બીજ(999);
g2 = યાદચ્છિક(1, 100);
chhapo g1 == g2;
aavjo
]=])
    set(expected_stdout "1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_beej_error")
    set(source [=[aavo
beej();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_beej_type_error")
    set(source [=[aavo
beej("invalid");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected number arguments for math function")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_beej")
    set(source [=[aavo
kary beej(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_vistaro")
    set(source [=[aavo
a = [1, 2];
b = [3, 4];
c = vistaro(a, b);
chhapo a;
chhapo c;
vistaro(a, ["five"]);
chhapo a;
d = [10];
vistaro(d, d);
chhapo d;
p = ["x"];
વિસ્તારો(p, ["y", "z"]);
chhapo p;
aavjo
]=])
    set(expected_stdout "[1, 2, 3, 4]\n[1, 2, 3, 4]\n[1, 2, 3, 4, five]\n[10, 10]\n[x, y, z]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_vistaro_error")
    set(source [=[aavo
vistaro([1]);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_vistaro_type_error")
    set(source [=[aavo
vistaro([1, 2], "not_list");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected list arguments for 'વિસ્તારો' or 'vistaro'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_vistaro_gujarati_error")
    set(source [=[આવો
વિસ્તારો(42, [1]);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'વિસ્તારો' માટે બંને દલીલો યાદી હોવી જોઈએ")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_vistaro")
    set(source [=[aavo
kary vistaro(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_pi")
    set(source [=[aavo
p1 = pi();
chhapo gol(p1 * 100);
p2 = પાઈ();
chhapo gol(p2 * 100);
aavjo
]=])
    set(expected_stdout "314\n314\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_pi_error")
    set(source [=[aavo
pi(1);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_pi")
    set(source [=[aavo
kary pi() { parat 0; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_e")
    set(source [=[aavo
val1 = e();
chhapo gol(val1 * 100);
val2 = ઈ();
chhapo gol(val2 * 100);
aavjo
]=])
    set(expected_stdout "272\n272\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_e_error")
    set(source [=[aavo
e(1);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_e")
    set(source [=[aavo
kary e() { parat 0; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_chihna")
    set(source [=[aavo
chhapo chihna(42);
chhapo chihna(-15.5);
chhapo chihna(0);
chhapo ચિહ્ન(100);
chhapo ચિહ્ન(-0.01);
chhapo ચિહ્ન(0);
aavjo
]=])
    set(expected_stdout "1\n-1\n0\n1\n-1\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_chihna_error")
    set(source [=[aavo
chihna();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_chihna_type_error")
    set(source [=[aavo
chihna("not_a_number");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected number arguments for math function")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_chihna")
    set(source [=[aavo
kary chihna(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_laghuganak")
    set(source [=[aavo
chhapo gol(laghuganak(e()));
chhapo gol(laghuganak(100, 10));
chhapo gol(laghuganak(8, 2));
chhapo gol(લઘુગણક(1));
aavjo
]=])
    set(expected_stdout "1\n2\n3\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_laghuganak_error")
    set(source [=[aavo
laghuganak();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_laghuganak_domain_error")
    set(source [=[aavo
laghuganak(0);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "logarithm argument must be greater than zero")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_laghuganak_base_error")
    set(source [=[aavo
laghuganak(10, 1);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "logarithm base must be greater than zero and not equal to one")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_laghuganak_gujarati_error")
    set(source [=[આવો
લઘુગણક(-5);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "લઘુગણક માટે કિંમત શૂન્ય કરતાં મોટી હોવી જોઈએ")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_laghuganak")
    set(source [=[aavo
kary laghuganak(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_akshar_kod")
    set(source [=[aavo
chhapo akshar_kod("A");
chhapo akshar_kod("ABC", 1);
chhapo akshar_kod("ABC", 2);
chhapo akshar_kod("ગુજરાતી", 0);
chhapo અક્ષર_કોડ("ગુજરાતી", 1);
aavjo
]=])
    set(expected_stdout "65\n66\n67\n2711\n2753\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_akshar_kod_error")
    set(source [=[aavo
akshar_kod();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_akshar_kod_type_error")
    set(source [=[aavo
akshar_kod(123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string first argument for 'અક્ષર_કોડ' or 'akshar_kod'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_akshar_kod_range_error")
    set(source [=[aavo
akshar_kod("hi", 5);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "index for 'અક્ષર_કોડ' or 'akshar_kod' is out of range")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "reserved_akshar_kod")
    set(source [=[aavo
kary akshar_kod(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_kod_thi_akshar")
    set(source [=[aavo
chhapo kod_thi_akshar(65);
chhapo kod_thi_akshar(66);
chhapo કોડ_થી_અક્ષર(2711);
chhapo કોડ_થી_અક્ષર(2753);
chhapo akshar_kod(kod_thi_akshar(888));
aavjo
]=])
    set(expected_stdout "A\nB\nગ\nુ\n888\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_kod_thi_akshar_error")
    set(source [=[aavo
kod_thi_akshar();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_kod_thi_akshar_invalid")
    set(source [=[aavo
kod_thi_akshar(-5);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "invalid Unicode code point for 'કોડ_થી_અક્ષર' or 'kod_thi_akshar'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_kod_thi_akshar_gujarati_error")
    set(source [=[આવો
કોડ_થી_અક્ષર(9999999);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'કોડ_થી_અક્ષર' માટે અમાન્ય યુનિકોડ કોડ પોઈન્ટ")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_kod_thi_akshar")
    set(source [=[aavo
kary kod_thi_akshar(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadi_bharo")
    set(source [=[aavo
chhapo yadi_bharo(3, 0);
chhapo yadi_bharo(4, "ha");
chhapo yadi_bharo(0, 10);
chhapo યાદી_ભરો(2, [1, 2]);
aavjo
]=])
    set(expected_stdout "[0, 0, 0]\n[ha, ha, ha, ha]\n[]\n[[1, 2], [1, 2]]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_yadi_bharo_error")
    set(source [=[aavo
yadi_bharo(5);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadi_bharo_count_error")
    set(source [=[aavo
yadi_bharo(-2, 0);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "count for 'યાદી_ભરો' or 'yadi_bharo' must be a non-negative whole number")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadi_bharo_gujarati_error")
    set(source [=[આવો
યાદી_ભરો(1.5, 0);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'યાદી_ભરો' માટે ગણતરી શૂન્ય અથવા ધન પૂર્ણાંક હોવી જોઈએ")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_yadi_bharo")
    set(source [=[aavo
kary yadi_bharo(x, y) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_sarvalo_yadi")
    set(source [=[aavo
chhapo sarvalo_yadi([1, 2, 3, 4]);
chhapo sarvalo_yadi([10.5, -2.5]);
chhapo સરવાળો_યાદી([]);
chhapo સરવાળો_યાદી([100]);
aavjo
]=])
    set(expected_stdout "10\n8\n0\n100\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_sarvalo_yadi_error")
    set(source [=[aavo
sarvalo_yadi();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_sarvalo_yadi_type_error")
    set(source [=[aavo
sarvalo_yadi(123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a list argument for 'સરવાળો_યાદી' or 'sarvalo_yadi'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_sarvalo_yadi_element_error")
    set(source [=[aavo
sarvalo_yadi([1, "two", 3]);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "all list items must be numbers for 'સરવાળો_યાદી' or 'sarvalo_yadi'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_sarvalo_yadi_gujarati_error")
    set(source [=[આવો
સરવાળો_યાદી([1, "ખોટું"]);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'સરવાળો_યાદી' માટે યાદીના તમામ ઘટકો સંખ્યા હોવા જોઈએ")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_sarvalo_yadi")
    set(source [=[aavo
kary sarvalo_yadi(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadi_nyunatam")
    set(source [=[aavo
chhapo yadi_nyunatam([10, 5, 20, 2]);
chhapo yadi_nyunatam([-10, -50, 0]);
chhapo યાદી_ન્યૂનતમ([42]);
aavjo
]=])
    set(expected_stdout "2\n-50\n42\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_yadi_nyunatam_error")
    set(source [=[aavo
yadi_nyunatam();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadi_nyunatam_empty_error")
    set(source [=[aavo
yadi_nyunatam([]);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "cannot find minimum of an empty list")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadi_nyunatam_type_error")
    set(source [=[aavo
yadi_nyunatam([1, "x"]);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "all list items must be numbers for 'યાદી_ન્યૂનતમ' or 'yadi_nyunatam'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadi_nyunatam_gujarati_error")
    set(source [=[આવો
યાદી_ન્યૂનતમ([]);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "ખાલી યાદીમાંથી ન્યૂનતમ શોધી શકાતું નથી")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_yadi_nyunatam")
    set(source [=[aavo
kary yadi_nyunatam(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadi_mahatam")
    set(source [=[aavo
chhapo yadi_mahatam([10, 5, 20, 2]);
chhapo yadi_mahatam([-10, -50, -5]);
chhapo યાદી_મહત્તમ([42]);
aavjo
]=])
    set(expected_stdout "20\n-5\n42\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_yadi_mahatam_error")
    set(source [=[aavo
yadi_mahatam();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadi_mahatam_empty_error")
    set(source [=[aavo
yadi_mahatam([]);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "cannot find maximum of an empty list")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadi_mahatam_type_error")
    set(source [=[aavo
yadi_mahatam([1, "x"]);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "all list items must be numbers for 'યાદી_મહત્તમ' or 'yadi_mahatam'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_yadi_mahatam_gujarati_error")
    set(source [=[આવો
યાદી_મહત્તમ([]);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "ખાલી યાદીમાંથી મહત્તમ શોધી શકાતું નથી")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_yadi_mahatam")
    set(source [=[aavo
kary yadi_mahatam(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_ganatari")
    set(source [=[aavo
sub = [2];
chhapo ganatari([1, 2, 2, 3, 2, 4], 2);
chhapo ganatari(["a", "b", "a", "c"], "a");
chhapo ganatari([1, sub, sub], sub);
chhapo ganatari("banana", "an");
chhapo ganatari("banana", "na");
chhapo ganatari("aaaa", "aa");
chhapo ganatari("hello", "xyz");
chhapo ganatari("hello", "");
chhapo ગણતરી(["સફરજન", "કેળા", "કેળા"], "કેળા");
chhapo ganatari_vastu([5, 5, 5], 5);
aavjo
]=])
    set(expected_stdout "3\n2\n2\n2\n2\n2\n0\n0\n2\n3\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_ganatari_error")
    set(source [=[aavo
ganatari();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_ganatari_type_error")
    set(source [=[aavo
ganatari(123, "a");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a list or string first argument for 'ગણતરી' or 'ganatari'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_ganatari_string_type_error")
    set(source [=[aavo
ganatari("abc", 1);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string second argument when counting in a string")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_ganatari_gujarati_error")
    set(source [=[આવો
ગણતરી(123, "a");
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'ગણતરી' માટે પ્રથમ દલીલ યાદી અથવા લખાણ હોવી જોઈએ")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_ganatari")
    set(source [=[aavo
kary ganatari(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_dabe_kapo")
    set(source [=[aavo
chhapo "[" + dabe_kapo("   hello world   ") + "]";
chhapo "[" + dabe_kapo(" \t\r\ntest") + "]";
chhapo "[" + dabe_kapo("no_spaces") + "]";
chhapo "[" + ડાબે_કાપો("  ગુજરાતી  ") + "]";
chhapo "[" + dabe_saf("   alias   ") + "]";
aavjo
]=])
    set(expected_stdout "[hello world   ]\n[test]\n[no_spaces]\n[ગુજરાતી  ]\n[alias   ]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_dabe_kapo_error")
    set(source [=[aavo
dabe_kapo();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_dabe_kapo_type_error")
    set(source [=[aavo
dabe_kapo(123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string argument for 'ડાબે_કાપો' or 'dabe_kapo'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_dabe_kapo_gujarati_error")
    set(source [=[આવો
ડાબે_કાપો(123);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'ડાબે_કાપો' માટે લખાણ દલીલ અપેક્ષિત છે")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_dabe_kapo")
    set(source [=[aavo
kary dabe_kapo(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_jamne_kapo")
    set(source [=[aavo
chhapo "[" + jamne_kapo("   hello world   ") + "]";
chhapo "[" + jamne_kapo("test\t\r\n ") + "]";
chhapo "[" + jamne_kapo("no_spaces") + "]";
chhapo "[" + જમણે_કાપો("  ગુજરાતી  ") + "]";
chhapo "[" + jamne_saf("   alias   ") + "]";
aavjo
]=])
    set(expected_stdout "[   hello world]\n[test]\n[no_spaces]\n[  ગુજરાતી]\n[   alias]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_jamne_kapo_error")
    set(source [=[aavo
jamne_kapo();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_jamne_kapo_type_error")
    set(source [=[aavo
jamne_kapo(123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string argument for 'જમણે_કાપો' or 'jamne_kapo'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_jamne_kapo_gujarati_error")
    set(source [=[આવો
જમણે_કાપો(123);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'જમણે_કાપો' માટે લખાણ દલીલ અપેક્ષિત છે")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_jamne_kapo")
    set(source [=[aavo
kary jamne_kapo(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_vibhaajan_pankti")
    set(source [=[aavo
chhapo vibhaajan_pankti("one\ntwo\nthree");
chhapo vibhaajan_pankti("first\r\nsecond\r\n");
chhapo vibhaajan_pankti("");
chhapo vibhaajan_pankti("single");
chhapo વિભાજન_પંક્તિ("લાઇન ૧\nલાઇન ૨");
chhapo panktiyo("a\nb");
aavjo
]=])
    set(expected_stdout "[one, two, three]\n[first, second]\n[]\n[single]\n[લાઇન ૧, લાઇન ૨]\n[a, b]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_vibhaajan_pankti_error")
    set(source [=[aavo
vibhaajan_pankti();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_vibhaajan_pankti_type_error")
    set(source [=[aavo
vibhaajan_pankti(123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string argument for 'વિભાજન_પંક્તિ' or 'vibhaajan_pankti'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_vibhaajan_pankti_gujarati_error")
    set(source [=[આવો
વિભાજન_પંક્તિ(123);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'વિભાજન_પંક્તિ' માટે લખાણ દલીલ અપેક્ષિત છે")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_vibhaajan_pankti")
    set(source [=[aavo
kary vibhaajan_pankti(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_aksharo")
    set(source [=[aavo
chhapo aksharo("abc");
chhapo aksharo("");
chhapo અક્ષરો("ગુજરાતી");
aavjo
]=])
    set(expected_stdout "[a, b, c]\n[]\n[ગ, ુ, જ, ર, ા, ત, ી]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_aksharo_error")
    set(source [=[aavo
aksharo();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_aksharo_type_error")
    set(source [=[aavo
aksharo(123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string argument for 'અક્ષરો' or 'aksharo'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_aksharo_gujarati_error")
    set(source [=[આવો
અક્ષરો(123);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'અક્ષરો' માટે લખાણ દલીલ અપેક્ષિત છે")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_aksharo")
    set(source [=[aavo
kary aksharo(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_paryavaran")
    set(source [=[aavo
jo (lambai(paryavaran("PATH")) > 0) {
    chhapo "has path";
}
chhapo paryavaran("NON_EXISTENT_VAR_xyz_12345");
chhapo prakar(paryavaran("NON_EXISTENT_VAR_xyz_12345"));
chhapo prakar(પર્યાવરણ("NON_EXISTENT_VAR_xyz_12345"));
aavjo
]=])
    set(expected_stdout "has path\nનકામો\nnull\nnull\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_paryavaran_error")
    set(source [=[aavo
paryavaran();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_paryavaran_type_error")
    set(source [=[aavo
paryavaran(123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string argument for 'પર્યાવરણ' or 'paryavaran'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_paryavaran_gujarati_error")
    set(source [=[આવો
પર્યાવરણ(123);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'પર્યાવરણ' માટે લખાણ દલીલ અપેક્ષિત છે")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_paryavaran")
    set(source [=[aavo
kary paryavaran(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_bahar")
    set(source [=[aavo
chhapo "before exit";
bahar();
chhapo "after exit should not run";
aavjo
]=])
    set(expected_stdout "before exit\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_bahar_code")
    set(source [=[aavo
chhapo "exiting with 42";
bahar(42);
aavjo
]=])
    set(expected_stdout "exiting with 42\n")
    set(expected_stderr "")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_bahar_unexecuted")
    set(source [=[aavo
jo (0) {
    bahar(1);
}
chhapo "survived";
aavjo
]=])
    set(expected_stdout "survived\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_bahar_type_error")
    set(source [=[aavo
bahar(-1);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "exit code for 'બહાર' or 'bahar' must be a whole number between 0 and 255")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_bahar_gujarati_error")
    set(source [=[આવો
બહાર(999);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'બહાર' માટે એક્ઝિટ કોડ ૦ અને ૨૫૫ વચ્ચેનો પૂર્ણ આંક હોવો જોઈએ")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_bahar")
    set(source [=[aavo
kary bahar(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_chakaso")
    set(source [=[aavo
chakaso(1);
chakaso(5 > 2, "five is greater than two");
ચકાસો(10 == 10);
chhapo "all assertions passed";
aavjo
]=])
    set(expected_stdout "all assertions passed\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_chakaso_fail")
    set(source [=[aavo
chakaso(0);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "assertion failed")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_chakaso_fail_custom")
    set(source [=[aavo
chakaso(0, "custom check failed!");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "custom check failed!")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_chakaso_msg_type_error")
    set(source [=[aavo
chakaso(1, 123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "assertion failure message must be a string")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_chakaso_gujarati_error")
    set(source [=[આવો
ચકાસો(0);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "ચકાસણી નિષ્ફળ ગઈ")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_chakaso")
    set(source [=[aavo
kary chakaso(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_samave_lakhan")
    set(source [=[aavo
chhapo samave_lakhan("hello world", "world");
chhapo samave_lakhan("hello world", "planet");
chhapo samave_lakhan("hello", "");
chhapo સમાવે_લખાણ("નમસ્તે ગુજરાત", "ગુજરાત");
chhapo સમાવે_લખાણ("નમસ્તે ગુજરાત", "ભારત");
aavjo
]=])
    set(expected_stdout "1\n0\n1\n1\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_samave_lakhan_error")
    set(source [=[aavo
samave_lakhan();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_samave_lakhan_type_error")
    set(source [=[aavo
samave_lakhan("hello", 123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected string arguments for 'સમાવે_લખાણ' or 'samave_lakhan'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_samave_lakhan_gujarati_error")
    set(source [=[આવો
સમાવે_લખાણ("hello", 123);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "'સમાવે_લખાણ' માટે લખાણ દલીલો અપેક્ષિત છે")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_samave_lakhan")
    set(source [=[aavo
kary samave_lakhan(x) { parat x; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_file_io")
    set(source [=[aavo
path = "file_io_test_tmp.txt";
file_kadho(path);
chhapo file_chhe(path);
chhapo file_lakho(path, "Hello Gujarat!");
chhapo file_chhe(path);
chhapo file_kad(path);
chhapo file_vancho(path);
chhapo file_umero(path, " and India!");
chhapo file_kad(path);
chhapo file_vancho(path);
chhapo file_kadho(path);
chhapo file_chhe(path);
chhapo prakar(file_vancho(path));
chhapo prakar(file_kad(path));
aavjo
]=])
    set(expected_stdout "0\n1\n1\n14\nHello Gujarat!\n1\n25\nHello Gujarat! and India!\n1\n0\nnull\nnull\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_file_io_gujarati")
    set(source [=[આવો
પાથ = "file_io_gu_tmp.txt";
ફાઇલ_હટાવો(પાથ);
છાપો ફાઇલ_છે(પાથ);
છાપો ફાઇલ_લખો(પાથ, "ગુજરાતી");
છાપો ફાઇલ_છે(પાથ);
છાપો ફાઇલ_વાંચો(પાથ);
છાપો ફાઇલ_કદ(પાથ);
છાપો ફાઇલ_હટાવો(પાથ);
છાપો ફાઇલ_છે(પાથ);
આવજો
]=])
    set(expected_stdout "0\n1\n1\nગુજરાતી\n21\n1\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "builtin_file_io_error_args")
    set(source [=[aavo
file_vancho();
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "incorrect number of function arguments")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_file_io_error_path_type")
    set(source [=[aavo
file_vancho(123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a string file path")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_file_io_error_content_type")
    set(source [=[aavo
file_lakho("file.txt", 123);
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected string content for file operation")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_file_io_gujarati_error")
    set(source [=[આવો
ફાઇલ_વાંચો(123);
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "ફાઇલ પાથ માટે લખાણ હોવું જરૂરી છે")
    set(expect_failure TRUE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "reserved_file_io")
    set(source [=[aavo
kary file_vancho(p) { parat p; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_dict_literals")
    set(source [=[aavo
d = {"a": 10, "b": "hello", "c": [1, 2]};
chhapo d["a"];
chhapo d["b"];
chhapo d["c"];
chhapo prakar(d);
chhapo lambai(d);
chhapo samave_chhe(d, "a");
chhapo samave_chhe(d, "missing");
d["d"] = 99;
chhapo d["d"];
chhapo lambai(d);
d["a"] = 100;
chhapo d["a"];
chhapo dur_karo(d, "b");
chhapo samave_chhe(d, "b");
chhapo lambai(d);
empty = {};
chhapo prakar(empty);
chhapo lambai(empty);
aavjo
]=])
    set(expected_stdout "10\nhello\n[1, 2]\ndict\n3\n1\n0\n99\n4\n100\n1\n0\n3\ndict\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_dict_constructors_and_helpers")
    set(source [=[aavo
d = kosh("name", "Gujarati", "version", 1);
chhapo d["name"];
chhapo d["version"];
chhapo chavio(d);
chhapo mulyo(d);
aavjo
]=])
    set(expected_stdout "Gujarati\n1\n[name, version]\n[Gujarati, 1]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_dict_gujarati")
    set(source [=[આવો
દ = {"નામ": "ગુજરાત", "કોડ": 24};
છાપો દ["નામ"];
છાપો દ["કોડ"];
છાપો પ્રકાર(દ);
છાપો લંબાઈ(દ);
છાપો સમાવે_છે(દ, "નામ");
છાપો દૂર_કરો(દ, "કોડ");
છાપો લંબાઈ(દ);
છાપો ચાવીઓ(દ);
છાપો મૂલ્યો(દ);
આવજો
]=])
    set(expected_stdout "ગુજરાત\n24\ndict\n2\n1\n1\n1\n[નામ]\n[ગુજરાત]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "builtin_dict_for_iteration")
    set(source [=[aavo
scores = {"Alice": 95, "Bob": 80};
darek (k ma scores) {
    chhapo k;
    chhapo scores[k];
}
aavjo
]=])
    set(expected_stdout "Alice\n95\nBob\n80\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_dict_errors")
    set(source [=[aavo
d = kosh("a");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected an even number of key-value arguments for 'શબ્દકોશ' or 'kosh'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "loop_control_while")
    set(source [=[aavo
i = 0;
jya_sudhi (i < 5) {
    i = i + 1;
    jo (i == 2) {
        chalu_rakho;
    }
    jo (i == 4) {
        atko;
    }
    chhapo i;
}
aavjo
]=])
    set(expected_stdout "1\n3\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "loop_control_for")
    set(source [=[aavo
darek (x ma 1..6) {
    jo (x == 2) {
        aagal;
    }
    jo (x == 5) {
        atko;
    }
    chhapo x;
}
aavjo
]=])
    set(expected_stdout "1\n3\n4\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "loop_control_gujarati")
    set(source [=[આવો
સંખ્યા = 0;
જ્યાં સુધી (સંખ્યા < 5) {
    સંખ્યા = સંખ્યા + 1;
    જો (સંખ્યા == 2) {
        ચાલુ_રાખો;
    }
    જો (સંખ્યા == 4) {
        અટકો;
    }
    છાપો સંખ્યા;
}
આવજો
]=])
    set(expected_stdout "1\n3\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "loop_control_outside_loop_error")
    set(source [=[aavo
atko;
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "'અટકો' or 'atko' can only be used inside a loop")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_datetime_ops")
    set(source [=[aavo
ts = 1700000000;
chhapo prakar(samay());
chhapo varsh(ts);
chhapo tarikh("%Y", ts);
chhapo mahino(ts) >= 1;
chhapo divas(ts) >= 1;
chhapo kalak(ts) >= 0;
chhapo minute(ts) >= 0;
chhapo second(ts) >= 0;
chhapo shant(1);
aavjo
]=])
    set(expected_stdout "number\n2023\n2023\n1\n1\n1\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_datetime_gujarati")
    set(source [=[આવો
મુદ્રા = 1700000000;
છાપો પ્રકાર(સમય());
છાપો વર્ષ(મુદ્રા);
છાપો તારીખ("%Y", મુદ્રા);
છાપો મહિનો(મુદ્રા) >= 1;
છાપો દિવસ(મુદ્રા) >= 1;
છાપો કલાક(મુદ્રા) >= 0;
છાપો મિનિટ(મુદ્રા) >= 0;
છાપો સેકન્ડ(મુદ્રા) >= 0;
છાપો શાંત(1);
આવજો
]=])
    set(expected_stdout "number\n2023\n2023\n1\n1\n1\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "builtin_datetime_errors")
    set(source [=[aavo
varsh("not_number");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "timestamp must be a number")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_try_catch_recovery")
    set(source [=[aavo
recovered = 0;
prayatna {
    x = 10 / 0;
    chhapo "not reached";
} pakdo (err) {
    recovered = 1;
    chhapo err;
}
chhapo recovered;
aavjo
]=])
    set(expected_stdout "division by zero\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_try_catch_custom_throw")
    set(source [=[aavo
prayatna {
    phenko("custom error message");
    chhapo "not reached";
} pakdo (msg) {
    chhapo msg;
}
chhapo "after try catch";
aavjo
]=])
    set(expected_stdout "custom error message\nafter try catch\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_try_catch_gujarati")
    set(source [=[આવો
પ્રયત્ન {
    ફેંકો("કસ્ટમ ભૂલ સંદેશ");
    છાપો "અહીં નહીં પહોંચે";
} પકડો (સંદેશ) {
    છાપો સંદેશ;
}
છાપો "પછીનું કાર્ય";
આવજો
]=])
    set(expected_stdout "કસ્ટમ ભૂલ સંદેશ\nપછીનું કાર્ય\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "builtin_try_catch_no_error")
    set(source [=[aavo
prayatna {
    chhapo "all good";
} pakdo (err) {
    chhapo "should not run";
}
chhapo "done";
aavjo
]=])
    set(expected_stdout "all good\ndone\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_try_catch_unhandled_phenko")
    set(source [=[aavo
phenko("fatal failure");
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "fatal failure")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_try_missing_catch_error")
    set(source [=[aavo
prayatna {
    chhapo 1;
}
chhapo 2;
aavjo
]=])
    set(expected_stdout "1\n")
    set(expected_stderr "expected 'પકડો' or 'pakdo' block after 'પ્રયત્ન' or 'prayatna'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "romanized_error")
    set(source [=[aavo
bhul "stop here";
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "error: stop here")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "romanized_fatal_error")
    set(source [=[aavo
ghatak_bhul "stop here";
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "fatal error: stop here")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "lists_and_indexing")
    set(source [=[aavo
items = [1, "two", [3, nakamo]];
chhapo items;
chhapo items[1];
chhapo items[2][0];
chhapo lambai(items);
aavjo
]=])
    set(expected_stdout "[1, two, [3, નકામો]]\ntwo\n3\n3\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "list_index_assignment")
    set(source [=[aavo
items = [1, 2];
items[1] = "updated";
chhapo items[1];
aavjo
]=])
    set(expected_stdout "updated\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "list_index_out_of_range")
    set(source [=[aavo
items = [1];
chhapo items[1];
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "list index is out of range")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "list_index_fractional")
    set(source [=[aavo
items = [1];
chhapo items[0.5];
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "list index must be a non-negative whole number")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "non_list_index")
    set(source [=[aavo
value = 1;
chhapo value[0];
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "cannot index a non-list value")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "for_list_iteration")
    set(source [=[aavo
items = [1, "two", 3];
darek (item ma items) { chhapo item; }
aavjo
]=])
    set(expected_stdout "1\ntwo\n3\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "for_numeric_range")
    set(source [=[aavo
darek (index ma 2..5) { chhapo index; }
aavjo
]=])
    set(expected_stdout "2\n3\n4\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "for_empty_range")
    set(source [=[aavo
darek (index ma 5..2) { chhapo "wrong"; }
chhapo "after";
aavjo
]=])
    set(expected_stdout "after\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "for_non_list_error")
    set(source [=[aavo
darek (item ma 3) { chhapo item; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a list argument for loop")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "module_import_shared_namespace")
    set(module_directory "${TEST_BINARY_DIR}/module-import")
    file(MAKE_DIRECTORY "${module_directory}")
    file(WRITE "${module_directory}/library.gj"
        "aavo\nshared = \"from module\";\nkary get_value() { parat shared; }\nchhapo \"loaded\";\naavjo\n")
    set(source_path "${module_directory}/main.gj")
    set(source [=[aavo
import "library.gj";
import "./nested/../library.gj";
chhapo get_value();
aavjo
]=])
    set(expected_stdout "loaded\nfrom module\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "nested_relative_module_import")
    set(module_directory "${TEST_BINARY_DIR}/nested-modules")
    file(MAKE_DIRECTORY "${module_directory}/sub")
    file(WRITE "${module_directory}/shared.gj"
        "aavo\nshared = 7;\naavjo\n")
    file(WRITE "${module_directory}/sub/child.gj"
        "aavo\nimport \"../shared.gj\";\nshared = shared + 1;\naavjo\n")
    set(source_path "${module_directory}/main.gj")
    set(source [=[aavo
import "sub/child.gj";
chhapo shared;
aavjo
]=])
    set(expected_stdout "8\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "circular_module_import")
    set(module_directory "${TEST_BINARY_DIR}/circular-modules")
    file(MAKE_DIRECTORY "${module_directory}")
    file(WRITE "${module_directory}/first.gj"
        "aavo\nimport \"second.gj\";\naavjo\n")
    file(WRITE "${module_directory}/second.gj"
        "aavo\nimport \"first.gj\";\naavjo\n")
    set(source_path "${module_directory}/main.gj")
    set(source [=[aavo
import "first.gj";
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "circular module import detected")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "missing_module_import")
    set(source [=[aavo
import "missing.gj";
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "could not open file")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "import_expected_path")
    set(source [=[aavo
import 123;
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a quoted module path after 'import'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "import_empty_path")
    set(source [=[aavo
import "";
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected a quoted module path after 'import'")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "import_missing_semicolon")
    set(source [=[aavo
import "helpers.gj"
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "expected ';' after module import")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "empty_list_index_error")
    set(source [=[aavo
items = [];
chhapo items[0];
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "list index is out of range")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "empty_list_assignment_error")
    set(source [=[aavo
items = [];
items[0] = 1;
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "list index is out of range")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "source_context_undefined_variable")
    set(source [=[aavo
chhapo missing;
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "  chhapo missing;\n         ^")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "repl_source_reallocation")
    set(source "")
    set(program_arguments --repl)
    set(input_text [=[message = "persist";
kary get_message() { parat message; }
pad1 = "1234567890123456789012345678901234567890";
pad2 = "1234567890123456789012345678901234567890";
pad3 = "1234567890123456789012345678901234567890";
pad4 = "1234567890123456789012345678901234567890";
pad5 = "1234567890123456789012345678901234567890";
chhapo message;
chhapo get_message();
]=])
    set(expected_stdout "GujaratiLang> GujaratiLang> GujaratiLang> GujaratiLang> GujaratiLang> GujaratiLang> GujaratiLang> GujaratiLang> persist\nGujaratiLang> persist\nGujaratiLang> ")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "nested_list_index_assignment")
    set(source [=[aavo
items = [[1, 2]];
items[0][1] = 9;
chhapo items;
aavjo
]=])
    set(expected_stdout "[[1, 9]]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "gujarati_for_iteration")
    set(source [=[આવો
દરેક (મૂલ્ય માં [4, 5]) { છાપો મૂલ્ય; }
આવજો
]=])
    set(expected_stdout "4\n5\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "romanized_import_alias")
    set(module_directory "${TEST_BINARY_DIR}/romanized-import")
    file(MAKE_DIRECTORY "${module_directory}")
    file(WRITE "${module_directory}/helper.gj"
        "aavo\nshared = 9;\naavjo\n")
    set(source_path "${module_directory}/main.gj")
    set(source [=[aavo
aayat "helper.gj";
chhapo shared;
aavjo
]=])
    set(expected_stdout "9\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "gujarati_import_alias")
    set(module_directory "${TEST_BINARY_DIR}/gujarati-import")
    file(MAKE_DIRECTORY "${module_directory}")
    file(WRITE "${module_directory}/helper.gj"
        "આવો\nshared = 11;\nઆવજો\n")
    set(source_path "${module_directory}/main.gj")
    set(source [=[આવો
આયાત "helper.gj";
છાપો shared;
આવજો
]=])
    set(expected_stdout "11\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "cyclic_list_printing")
    set(source [=[aavo
items = [0];
items[0] = items;
chhapo items;
aavjo
]=])
    set(expected_stdout "[<cycle>]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_json")
    set(source [=[aavo
data = {"name": "test", "val": 42};
json_str = json_lakho(data);
chhapo json_str;
parsed = json_vancho(json_str);
chhapo parsed["name"];
chhapo parsed["val"];
aavjo
]=])
    set(expected_stdout "{\"name\": \"test\", \"val\": 42}\ntest\n42\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_radix")
    set(source [=[aavo
b = dvi_sankhya(10);
chhapo b;
chhapo dvi_thi_sankhya(b);
h = hex_lakhan(255);
chhapo h;
chhapo hex_thi_sankhya(h);
aavjo
]=])
    set(expected_stdout "1010\n10\nff\n255\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_folder")
    set(source [=[aavo
chhapo folder_banao("test_dir");
chhapo folder_chhe("test_dir");
files = folder_suchi("test_dir");
chhapo lambai(files);
aavjo
]=])
    set(expected_stdout "1\n1\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_functional_list")
    set(source [=[aavo
kary double_it(n) {
    parat n * 2;
}
kary is_even(n) {
    parat (n % 2 == 0);
}
kary add_two(a, b) {
    parat a + b;
}
nums = [1, 2, 3, 4];
doubled = naksho_yadi(nums, "double_it");
chhapo doubled;
evens = gaalo_yadi(nums, "is_even");
chhapo evens;
sum = sameto_yadi(nums, "add_two", 0);
chhapo sum;
first_even = shodho_yadi(nums, "is_even");
chhapo first_even;
first_even_idx = shodho_suchak_yadi(nums, "is_even");
chhapo first_even_idx;
aavjo
]=])
    set(expected_stdout "[2, 4, 6, 8]\n[2, 4]\n10\n2\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_list_flatten_zip")
    set(source [=[aavo
nested = [[1, 2], [3, 4], 5];
flat = chapti_yadi(nested);
chhapo flat;
names = ["a", "b"];
scores = [10, 20];
zipped = zip_yadi(names, scores);
chhapo zipped;
aavjo
]=])
    set(expected_stdout "[1, 2, 3, 4, 5]\n[[a, 10], [b, 20]]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_pattern_and_replace")
    set(source [=[aavo
chhapo pattern_shodho("hello world", "h*ld");
chhapo pattern_shodho("apple", "b*");
txt = "foo bar foo baz foo";
rep = lakhan_badlo_darek(txt, "foo", "qux");
chhapo rep;
aavjo
]=])
    set(expected_stdout "1\n0\nqux bar qux baz qux\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_base64")
    set(source [=[aavo
enc = base64_kod("GujaratiLang");
chhapo enc;
dec = base64_decode(enc);
chhapo dec;
aavjo
]=])
    set(expected_stdout "R3VqYXJhdGlMYW5n\nGujaratiLang\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_string_case")
    set(source [=[aavo
chhapo shirshak_lakhan("hello world of gujarati");
chhapo pratham_moti("developer");
aavjo
]=])
    set(expected_stdout "Hello World Of Gujarati\nDeveloper\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_swaroop")
    set(source [=[aavo
msg = swaroop("Namaste, {}! You scored {} points.", "Harshit", 100);
chhapo msg;
aavjo
]=])
    set(expected_stdout "Namaste, Harshit! You scored 100 points.\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_distance")
    set(source [=[aavo
dist = lakhan_antar("kitten", "sitting");
chhapo dist;
chhapo lakhan_antar("same", "same");
aavjo
]=])
    set(expected_stdout "3\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_sha256")
    set(source [=[aavo
h1 = sha256_hash("");
chhapo h1;
h2 = sha256_hash("hello");
chhapo h2;
aavjo
]=])
    set(expected_stdout "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\n2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_trigonometry")
    set(source [=[aavo
s0 = sine(0);
c0 = cosine(0);
t0 = tangent(0);
chhapo s0;
chhapo c0;
chhapo t0;
chhapo arcsin(0);
chhapo arccos(1);
chhapo arctan(0);
aavjo
]=])
    set(expected_stdout "0\n1\n0\n0\n0\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_gcd_lcm")
    set(source [=[aavo
chhapo guru_tam(48, 18);
chhapo laghu_tam(4, 6);
aavjo
]=])
    set(expected_stdout "6\n12\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_angle_conversions")
    set(source [=[aavo
r = ansha_thi_radian(180);
chhapo gol(r);
d = radian_thi_ansha(pi());
chhapo gol(d);
aavjo
]=])
    set(expected_stdout "3\n180\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_matrix")
    set(source [=[aavo
m1 = [[1, 2], [3, 4]];
m2 = [[5, 6], [7, 8]];
sum_m = matrix_sarvalo(m1, m2);
chhapo sum_m;
prod_m = matrix_gunakar(m1, [[2, 0], [1, 2]]);
chhapo prod_m;
aavjo
]=])
    set(expected_stdout "[[6, 8], [10, 12]]\n[[4, 4], [10, 8]]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "ternary_operator")
    set(source [=[aavo
x = 10;
res = x > 5 ? "high" : "low";
chhapo res;
res2 = x < 5 ? 100 : (x == 10 ? 200 : 300);
chhapo res2;
aavjo
]=])
    set(expected_stdout "high\n200\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "compound_assignment")
    set(source [=[aavo
x = 10;
x += 5;
chhapo x;
x -= 3;
chhapo x;
x *= 2;
chhapo x;
x /= 4;
chhapo x;
x %= 5;
chhapo x;
str = "Hello";
str += " World";
chhapo str;
aavjo
]=])
    set(expected_stdout "15\n12\n24\n6\n1\nHello World\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "constant_variables")
    set(source [=[aavo
achala MAX_LIMIT = 500;
chhapo MAX_LIMIT;
aavjo
]=])
    set(expected_stdout "500\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "constant_reassign_error")
    set(source [=[aavo
achala FIXED = 42;
FIXED = 100;
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "cannot reassign constant variable")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "builtin_version_platform")
    set(source [=[aavo
chhapo bhasha_avrutti();
p = platform_nam();
chhapo (p == "windows" || p == "linux" || p == "macos");
aavjo
]=])
    set(expected_stdout "1.1.0\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_env")
    set(source [=[aavo
paryavaran_lakho("GJ_TEST_VAR", "hello_env");
chhapo paryavaran("GJ_TEST_VAR");
aavjo
]=])
    set(expected_stdout "hello_env\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_path_utils")
    set(source [=[aavo
chhapo path_jodo("foo/bar", "baz.txt");
chhapo path_vistaran("my/dir/file.gj");
chhapo path_mukhya("my/dir/file.gj");
chhapo path_folder("my/dir/file.gj");
aavjo
]=])
    set(expected_stdout "foo/bar/baz.txt\n.gj\nfile.gj\nmy/dir\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_uuid")
    set(source [=[aavo
u = uuid_banao();
chhapo lambai(u);
aavjo
]=])
    set(expected_stdout "36\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_url")
    set(source [=[aavo
enc = url_kod("hello world & foo=bar");
chhapo enc;
dec = url_decode(enc);
chhapo dec;
aavjo
]=])
    set(expected_stdout "hello%20world%20%26%20foo%3Dbar\nhello world & foo=bar\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_statistics")
    set(source [=[aavo
l = [10, 20, 30, 40, 50];
chhapo yadi_sarvalo(l);
chhapo yadi_sareras(l);
chhapo yadi_madhyastha(l);
aavjo
]=])
    set(expected_stdout "150\n30\n30\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_lakhan_padding")
    set(source [=[aavo
chhapo lakhan_purn_dabi("42", 5, "0");
chhapo lakhan_purn_jamni("hi", 5, ".");
aavjo
]=])
    set(expected_stdout "00042\nhi...\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_bitwise")
    set(source [=[aavo
chhapo bit_ane(12, 10);
chhapo bit_athva(12, 10);
chhapo bit_xor(12, 10);
chhapo bit_shifte_dabi(1, 4);
chhapo bit_shifte_jamni(16, 2);
aavjo
]=])
    set(expected_stdout "8\n14\n6\n16\n4\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_list_sets")
    set(source [=[aavo
l1 = [1, 2, 2, 3];
chhapo yadi_ananya(l1);
l2 = [3, 4, 5];
chhapo yadi_mel(l1, l2);
chhapo yadi_chhed(l1, l2);
chhapo yadi_tavat(l1, l2);
aavjo
]=])
    set(expected_stdout "[1, 2, 3]\n[1, 2, 3, 4, 5]\n[3]\n[1, 2]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_char_code")
    set(source [=[aavo
c = akshar_kod("ABC", 1);
chhapo c;
s = kod_thi_akshar(65);
chhapo s;
aavjo
]=])
    set(expected_stdout "66\nA\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_exp_log")
    set(source [=[aavo
chhapo log_10(100);
chhapo ghat_mul(2, 8);
aavjo
]=])
    set(expected_stdout "2\n256\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_list_reverse")
    set(source [=[aavo
l = [10, 20, 30];
chhapo yadi_ulte_kram(l);
aavjo
]=])
    set(expected_stdout "[30, 20, 10]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_list_chunk")
    set(source [=[aavo
l = [1, 2, 3, 4, 5];
chhapo yadi_tukda(l, 2);
aavjo
]=])
    set(expected_stdout "[[1, 2], [3, 4], [5]]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_dict_utils")
    set(source [=[aavo
d1 = { "a": 1, "b": 2 };
chhapo chavi_chhe(d1, "a");
chhapo chavi_chhe(d1, "z");
d2 = { "b": 20, "c": 30 };
d3 = kosh_jodo(d1, d2);
chhapo d3["b"];
chhapo d3["c"];
aavjo
]=])
    set(expected_stdout "1\n0\n20\n30\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_micro_samay")
    set(source [=[aavo
t = micro_samay();
chhapo t > 0;
aavjo
]=])
    set(expected_stdout "1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_repeat_count")
    set(source [=[aavo
chhapo lakhan_aavrutti("abc", 3);
chhapo lakhan_ganatari("banana", "an");
aavjo
]=])
    set(expected_stdout "abcabcabc\n2\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_split_delim")
    set(source [=[aavo
res = lakhan_tukda_yadi("apple,banana;cherry:date", ",;:");
chhapo res;
aavjo
]=])
    set(expected_stdout "[apple, banana, cherry, date]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_file_lines")
    set(source [=[aavo
file_lakho("test_lines_tmp.txt", "line1\nline2\nline3\n");
lines = file_line_vancho("test_lines_tmp.txt");
chhapo lines;
file_kadho("test_lines_tmp.txt");
aavjo
]=])
    set(expected_stdout "[line1, line2, line3]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_hex_to_string")
    set(source [=[aavo
txt = hex_thi_lakhan("47756a61726174");
chhapo txt;
aavjo
]=])
    set(expected_stdout "Gujarat\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_csv")
    set(source [=[aavo
csv = "name,age,city\nAlice,30,Ahmedabad\nBob,25,\"Surat, City\"";
table = csv_vancho(csv);
chhapo table;
aavjo
]=])
    set(expected_stdout "[[name, age, city], [Alice, 30, Ahmedabad], [Bob, 25, Surat, City]]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_type_predicates")
    set(source [=[aavo
chhapo sankhya_chhe(42);
chhapo lakhan_chhe("hello");
chhapo yadi_chhe([1, 2]);
chhapo kosh_chhe({ "a": 1 });
chhapo nakamo_chhe(nakamo);
aavjo
]=])
    set(expected_stdout "1\n1\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "oop_class_and_methods")
    set(source [=[aavo
varg Person {
    rachna(name, age) {
        a_pote.name = name;
        a_pote.age = age;
    }
    kary greet() {
        chhapo a_pote.name;
        chhapo a_pote.age;
    }
}
p = navu Person("Harsh", 24);
p.greet();
aavjo
]=])
    set(expected_stdout "Harsh\n24\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "oop_inheritance")
    set(source [=[aavo
varg Animal {
    rachna(name) {
        a_pote.name = name;
    }
    kary speak() {
        chhapo a_pote.name;
    }
}
varg Dog anukaran Animal {
    rachna(name, breed) {
        a_pote.name = name;
        a_pote.breed = breed;
    }
    kary bark() {
        chhapo a_pote.breed;
    }
}
d = navu Dog("Buddy", "Golden");
d.speak();
d.bark();
aavjo
]=])
    set(expected_stdout "Buddy\nGolden\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "oop_gujarati_syntax")
    set(language_args "--language" "gu")
    set(source [=[આવો
વર્ગ બિલાડી {
    રચના(નામ) {
        આ_પોતે.નામ = નામ;
    }
    કાર્ય અવાજ() {
        છાપો આ_પોતે.નામ;
    }
}
બ = નવું બિલાડી("મીની");
બ.અવાજ();
આવજો
]=])
    set(expected_stdout "મીની\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_sleep_exit_cwd")
    set(source [=[aavo
suvo(1);
folder = sthanak_folder();
chhapo lakhan_chhe(folder);
ok = folder_badlo(folder);
chhapo ok;
aavjo
]=])
    set(expected_stdout "1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_sangrah")
    set(source [=[aavo
sangrah_lakho("test_store.json", "theme", "dark");
val = sangrah_vancho("test_store.json", "theme");
chhapo val;
sangrah_lakho("test_store.json", "count", 42);
chhapo sangrah_vancho("test_store.json", "count");
aavjo
]=])
    set(expected_stdout "dark\n42\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_ini")
    set(source [=[aavo
ini_text = "[app]\nname = GujaratiLang\nversion = 1.1\n[db]\nport = 5432";
cfg = ini_vancho(ini_text);
chhapo cfg["app"]["name"];
chhapo cfg["app"]["version"];
chhapo cfg["db"]["port"];
aavjo
]=])
    set(expected_stdout "GujaratiLang\n1.1\n5432\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_env_expand")
    set(source [=[aavo
paryavaran_lakho("GJ_TEST_VAR", "Antigravity");
msg = paryavaran_vistaran("Hello ${GJ_TEST_VAR}!");
chhapo msg;
aavjo
]=])
    set(expected_stdout "Hello Antigravity!\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_url_prashno")
    set(source [=[aavo
params = url_prashno("https://example.com/api?search=gujarati&page=2");
chhapo params["search"];
chhapo params["page"];
aavjo
]=])
    set(expected_stdout "gujarati\n2\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_vector_math")
    set(source [=[aavo
v1 = [1, 2, 3];
v2 = [4, 5, 6];
chhapo vector_bindu(v1, v2);
chhapo vector_maan([3, 4]);
chhapo antar_euclidean([0, 0], [3, 4]);
chhapo (cosine_samanata([1, 0], [1, 0]) > 0.99);
aavjo
]=])
    set(expected_stdout "32\n5\n5\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_ml_primitives")
    set(source [=[aavo
x = [1, 2, 3, 4, 5];
y = [2, 4, 6, 8, 10];
reg = ml_rekhiya_sambandh(x, y);
chhapo reg["dhal"];
chhapo reg["antarched"];
chhapo reg["r2"];
chhapo ml_relu(-10);
chhapo ml_relu(15);
chhapo (ml_sigmoid(0) > 0.49 && ml_sigmoid(0) < 0.51);
aavjo
]=])
    set(expected_stdout "2\n0\n1\n0\n15\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_ml_advanced")
    set(source [=[aavo
chhapo ml_mse([1, 2, 3], [1, 2, 3]);
chhapo ml_mse([1, 2], [2, 4]);
scaled = ml_minmax_scaling([10, 20, 30]);
chhapo scaled[0];
chhapo scaled[2];
data = [1.0, 2.0, 10.0, 11.0];
km = ml_kmeans(data, 2, 10);
chhapo yadi_chhe(km["clusters"]);
chhapo yadi_chhe(km["centroids"]);
aavjo
]=])
    set(expected_stdout "0\n2.5\n0\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_binary_search_fuzzy")
    set(source [=[aavo
arr = [10, 20, 30, 40, 50];
chhapo shodho_dvimukhi(arr, 30);
chhapo shodho_dvimukhi(arr, 99);
f = shodho_sarshu("apple", ["apply", "banana", "orange"]);
chhapo f["match"];
chhapo (f["score"] > 0.7);
aavjo
]=])
    set(expected_stdout "2\n-1\napply\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "builtin_safe_casts")
    set(source [=[aavo
chhapo sankhya_rupantar("123.45", 0);
chhapo sankhya_rupantar("invalid", 999);
chhapo lakhan_rupantar(100);
chhapo lakhan_rupantar([1, 2]);
aavjo
]=])
    set(expected_stdout "123.45\n999\n100\n[1, 2]\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "cli_tooling")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[aavo
chhapo 42;
aavjo
]=])
    set(program_arguments "--ast" "${source_path}")
    set(expected_stdout "Program: ${source_path}\n  ProgramStart (line 1)\n  PrintStatement (line 2)\n  ProgramEnd (line 3)\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
else()
    message(FATAL_ERROR "Unknown interpreter test case: ${TEST_CASE}")
endif()

if(NOT DEFINED source_path)
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
endif()
set(actual_stdout_path "${TEST_BINARY_DIR}/${TEST_CASE}.stdout")
set(actual_stderr_path "${TEST_BINARY_DIR}/${TEST_CASE}.stderr")
set(input_path "${TEST_BINARY_DIR}/${TEST_CASE}.input")
set(expected_stdout_path "${TEST_BINARY_DIR}/${TEST_CASE}.expected-stdout")
set(expected_stderr_path "${TEST_BINARY_DIR}/${TEST_CASE}.expected-stderr")
file(WRITE "${source_path}" "${source}")
file(WRITE "${input_path}" "${input_text}")
file(WRITE "${expected_stdout_path}" "${expected_stdout}")
file(WRITE "${expected_stderr_path}" "${expected_stderr}")

if(NOT DEFINED program_arguments)
    set(program_arguments ${language_args} "${source_path}")
endif()
execute_process(
    COMMAND "${PROGRAM}" ${program_arguments}
    RESULT_VARIABLE actual_status
    INPUT_FILE "${input_path}"
    OUTPUT_FILE "${actual_stdout_path}"
    ERROR_FILE "${actual_stderr_path}"
)

if(expect_failure)
    if(actual_status STREQUAL "0")
        message(FATAL_ERROR "${TEST_CASE}: expected failure, got exit code 0")
    endif()
elseif(NOT actual_status STREQUAL "0")
    file(READ "${actual_stderr_path}" actual_stderr)
    message(FATAL_ERROR "${TEST_CASE}: expected success, got ${actual_status}\n${actual_stderr}")
endif()

file(READ "${actual_stdout_path}" actual_stdout_hex HEX)
file(READ "${expected_stdout_path}" expected_stdout_hex HEX)
if(NOT actual_stdout_hex STREQUAL expected_stdout_hex)
    message(FATAL_ERROR
        "${TEST_CASE}: stdout bytes did not match\nExpected: ${expected_stdout_hex}\nActual:   ${actual_stdout_hex}")
endif()

if(NOT expected_stderr STREQUAL "")
    file(READ "${actual_stderr_path}" actual_stderr_hex HEX)
    file(READ "${expected_stderr_path}" expected_stderr_hex HEX)
    string(FIND "${actual_stderr_hex}" "${expected_stderr_hex}" stderr_match)
    if(stderr_match EQUAL -1)
        message(FATAL_ERROR
            "${TEST_CASE}: stderr did not contain expected bytes ${expected_stderr_hex}\nActual: ${actual_stderr_hex}")
    endif()
endif()
