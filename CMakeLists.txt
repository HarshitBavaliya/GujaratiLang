cmake_minimum_required(VERSION 3.16)
project(gujaratilang VERSION 0.1.0 LANGUAGES C)

add_executable(gujarati src/main.c)
target_compile_features(gujarati PRIVATE c_std_99)

if(MSVC)
    target_compile_options(gujarati PRIVATE /W4 /utf-8)
else()
    target_compile_options(gujarati PRIVATE -Wall -Wextra -Wpedantic)
endif()
