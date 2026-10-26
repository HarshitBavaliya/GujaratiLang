set(input_args)
if(DEFINED INPUT_FILE AND EXISTS "${INPUT_FILE}")
    set(input_args INPUT_FILE "${INPUT_FILE}")
endif()

execute_process(
    COMMAND "${PROGRAM}" "${SOURCE_FILE}"
    ${input_args}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE actual_output
    ERROR_VARIABLE actual_error
    ENCODING UTF-8
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR
        "Example ${SOURCE_FILE} failed with exit code ${result}:\n${actual_error}")
endif()

file(READ "${EXPECTED_OUTPUT_FILE}" expected_output)
if(NOT actual_output STREQUAL expected_output)
    message(FATAL_ERROR
        "Unexpected output from ${SOURCE_FILE}.\n"
        "Expected:\n${expected_output}\n"
        "Actual:\n${actual_output}")
endif()

if(NOT actual_error STREQUAL "")
    message(FATAL_ERROR
        "Example ${SOURCE_FILE} wrote unexpected standard error:\n${actual_error}")
endif()
