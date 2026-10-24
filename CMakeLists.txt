cmake_minimum_required(VERSION 3.16)
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()
project(gujaratilang VERSION 0.5.0 LANGUAGES C)

include(CTest)

add_executable(gujarati src/main.c)
target_compile_features(gujarati PRIVATE c_std_99)

if(MSVC)
    set_property(TARGET gujarati PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    target_compile_options(gujarati PRIVATE /W4 /utf-8)
else()
    target_compile_options(gujarati PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(BUILD_TESTING)
    foreach(test_case IN ITEMS
            arithmetic_and_comparisons
            conditionals
            logical_operators
            logical_short_circuit
            logical_type_error
            while_loop
            nested_while_loops
            while_false_condition
            while_in_skipped_branch
            strings_and_null
            string_concatenation
            string_number_addition_error
            string_equality
            string_equality_input
            string_equality_type_error
            string_ordering_type_error
            variables
            variable_in_skipped_branch
            variable_skipped_not_created
            variable_reassignment
            undefined_variable
            undefined_variable_gujarati
            function_calls
            nested_function_calls
            recursive_function
            function_returns
            function_local_and_global_variables
            function_undefined
            function_wrong_argument_count
            function_duplicate
            function_duplicate_parameter
            return_outside_function
            input
            input_empty_line
            input_long_line
            input_eof
            input_wrong_argument_count
            input_prompt_type
            input_skipped_branch
            reserved_input_function
            repl_persistence
            repl_error_recovery
            repl_runtime_error_recovery
            repl_input
            warnings_english
            warnings_gujarati
            errors
            fatal_errors
            invalid_condition
            invalid_language)
        add_test(
            NAME ${test_case}
            COMMAND "${CMAKE_COMMAND}"
                "-DPROGRAM=$<TARGET_FILE:gujarati>"
                "-DTEST_CASE=${test_case}"
                "-DTEST_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}/test-work"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/tests/run_test.cmake"
        )
    endforeach()
endif()
