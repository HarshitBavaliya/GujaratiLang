cmake_minimum_required(VERSION 3.16)
project(gujaratilang VERSION 0.1.0 LANGUAGES C)

include(CTest)

add_executable(gujarati src/main.c)
target_compile_features(gujarati PRIVATE c_std_99)

if(MSVC)
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
            strings_and_null
            variables
            variable_in_skipped_branch
            duplicate_variable
            undefined_variable
            undefined_variable_gujarati
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
