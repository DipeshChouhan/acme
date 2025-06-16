cmake_minimum_required(VERSION 3.31)

project(Acme DESCRIPTION "i486 emulator" LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(acme src/main.c)

target_include_directories(acme PUBLIC "include/")

set_property(TARGET acme PROPERTY C_STARNDARD_REQUIRED ON)

set_property(TARGET acme PROPERTY C_STANDARD 23)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug build")
    add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release build")
    add_compile_options(-O2)
endif()

