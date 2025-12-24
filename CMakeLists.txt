cmake_minimum_required(VERSION 3.31)

project(Acme DESCRIPTION "i486 emulator" LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(acme src/main.c)

target_include_directories(acme PUBLIC "include/")

set_property(TARGET acme PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET acme PROPERTY C_STANDARD 17)

target_compile_options(acme PRIVATE
    $<$<CONFIG:Debug>:-g -Wall -Wextra -Wpedantic>
)

