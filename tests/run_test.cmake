file(MAKE_DIRECTORY "${TEST_BINARY_DIR}")

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
જો (0) { છાપો "wrong"; } અથવા જો (2 > 1) { છાપો "second"; } અથવા { છાપો "wrong"; }
જો (1 < 0) { છાપો "wrong"; } અથવા { છાપો "else"; }
આવજો
]=])
    set(expected_stdout "second\nelse\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "logical_operators")
    set(source [=[આવો
છાપો 1 અને 2 > 1;
છાપો 1 કે 0 અને 0;
છાપો નહીં 1 == 1;
છાપો નહીં 0 == 1;
જો (2 > 1 અને નહીં 0) { છાપો "and and not"; }
જો (0 કે 3 == 3) { છાપો "or"; }
આવજો
]=])
    set(expected_stdout "1\n1\n0\n1\nand and not\nor\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "logical_short_circuit")
    set(source [=[આવો
છાપો 1 કે 1 / 0 == 0;
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
elseif(TEST_CASE STREQUAL "strings_and_null")
    set(source [=[આવો
છાપો નકામો;
છાપો "line\nnext";
આવજો
]=])
    set(expected_stdout "નકામો\nline\nnext\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "variables")
    set(source [=[આવો
રાખો ગણતરી = 3;
ગણતરી = ગણતરી + 2;
રાખો count = ગણતરી * 2;
રાખો item_2 = count + 1;
રાખો છાપોવસ્તુ = item_2 + 1;
છાપો ગણતરી;
છાપો count;
છાપો છાપોવસ્તુ;
રાખો સંદેશ = "Gujarati \nstring";
છાપો સંદેશ;
રાખો નકામું = નકામો;
છાપો નકામું;
જો (ગણતરી == 5) { છાપો "variable condition"; }
આવજો
]=])
    set(expected_stdout "5\n10\n12\nGujarati \nstring\nનકામો\nvariable condition\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "variable_in_skipped_branch")
    set(source [=[આવો
જો (0) { રાખો ખોટું = 1; }
રાખો સાચું = 2;
છાપો સાચું;
આવજો
]=])
    set(expected_stdout "2\n")
    set(expected_stderr "")
    set(expect_failure FALSE)
elseif(TEST_CASE STREQUAL "duplicate_variable")
    set(source [=[આવો
રાખો કિંમત = 1;
રાખો કિંમત = 2;
આવજો
]=])
    set(expected_stdout "")
    set(expected_stderr "variable is already declared")
    set(expect_failure TRUE)
elseif(TEST_CASE STREQUAL "undefined_variable")
    set(source [=[આવો
અજ્ઞાત = 1;
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
else()
    message(FATAL_ERROR "Unknown interpreter test case: ${TEST_CASE}")
endif()

set(source_path "${TEST_BINARY_DIR}/${TEST_CASE}.gj")
set(actual_stdout_path "${TEST_BINARY_DIR}/${TEST_CASE}.stdout")
set(actual_stderr_path "${TEST_BINARY_DIR}/${TEST_CASE}.stderr")
set(expected_stdout_path "${TEST_BINARY_DIR}/${TEST_CASE}.expected-stdout")
set(expected_stderr_path "${TEST_BINARY_DIR}/${TEST_CASE}.expected-stderr")
file(WRITE "${source_path}" "${source}")
file(WRITE "${expected_stdout_path}" "${expected_stdout}")
file(WRITE "${expected_stderr_path}" "${expected_stderr}")

execute_process(
    COMMAND "${PROGRAM}" ${language_args} "${source_path}"
    RESULT_VARIABLE actual_status
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
