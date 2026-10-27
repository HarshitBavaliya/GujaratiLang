cmake_minimum_required(VERSION 3.16)
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()
project(gujaratilang VERSION 0.7.0 LANGUAGES C)

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
            string_length_ascii
            string_length_gujarati
            string_length_escapes
            string_length_wrong_argument_count
            string_length_type_error
            reserved_string_length
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
            repl_string_length
            warnings_english
            warnings_gujarati
            errors
            fatal_errors
            invalid_condition
            invalid_language
            romanized_keywords
            romanized_keyword_identifier_boundary
            romanized_builtins
            reserved_romanized_builtin
            builtin_sankhya
            builtin_sankhya_error
            builtin_sankhya_type_error
            builtin_lakhan
            builtin_prakar
            reserved_sankhya_lakhan_prakar
            builtin_umero
            builtin_umero_error
            builtin_kapo
            builtin_kapo_error
            builtin_shodho
            builtin_shodho_error
            reserved_umero_kapo_shodho
            builtin_kadho
            builtin_kadho_error
            reserved_kadho
            builtin_case_conversion
            builtin_case_conversion_error
            reserved_case_conversion
            builtin_math_utils
            builtin_math_utils_error
            reserved_math_utils
            romanized_error
            romanized_fatal_error
            lists_and_indexing
            list_index_assignment
            list_index_out_of_range
            list_index_fractional
            non_list_index
            for_list_iteration
            for_numeric_range
            for_empty_range
            for_non_list_error
            module_import_shared_namespace
            nested_relative_module_import
            circular_module_import
            missing_module_import
            import_expected_path
            import_empty_path
            import_missing_semicolon
            empty_list_index_error
            empty_list_assignment_error
            source_context_undefined_variable
            repl_source_reallocation
            nested_list_index_assignment
            gujarati_for_iteration
            romanized_import_alias
            gujarati_import_alias
            cyclic_list_printing)
        add_test(
            NAME ${test_case}
            COMMAND "${CMAKE_COMMAND}"
                "-DPROGRAM=$<TARGET_FILE:gujarati>"
                "-DTEST_CASE=${test_case}"
                "-DTEST_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}/test-work"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/tests/run_test.cmake"
        )
    endforeach()

    foreach(example IN ITEMS fibonacci temperature_converter inventory stock calculator string_utils)
        set(input_file_arg)
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/examples/${example}.stdin")
            set(input_file_arg "-DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/examples/${example}.stdin")
        endif()
        add_test(
            NAME example_${example}
            COMMAND "${CMAKE_COMMAND}"
                "-DPROGRAM=$<TARGET_FILE:gujarati>"
                "-DSOURCE_FILE=${CMAKE_CURRENT_SOURCE_DIR}/examples/${example}.gj"
                "-DEXPECTED_OUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/examples/${example}.stdout"
                ${input_file_arg}
                -P "${CMAKE_CURRENT_SOURCE_DIR}/tests/run_example.cmake"
        )
    endforeach()
endif()
