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
    set(expected_stderr "expected a string argument for 'લંબાઈ'")
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
કાર્ય જોડો(પહેલું, બીજું) {
    પરત પહેલું + બીજું;
}
છાપો જોડો(2, 3);
આવજો
]=])
    set(expected_stdout "5\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "nested_function_calls")
    set(source [=[આવો
કાર્ય બમણું(કિંમત) { પરત કિંમત * 2; }
કાર્ય ઉમેરો(પહેલું, બીજું) { પરત પહેલું + બીજું; }
છાપો ઉમેરો(બમણું(3), બમણું(4));
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
karya double(value) { parat value * 2; }
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
karya lambai(text) { parat 0; }
aavjo
]=])
    set(expected_stdout "")
    set(expected_stderr "built-in function name cannot be declared")
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
else()
    message(FATAL_ERROR "Unknown interpreter test case: ${TEST_CASE}")
endif()

set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
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
