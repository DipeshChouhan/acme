cmake_minimum_required(4.0)

project(Acme VERSION 0.0 DESCRIPTION "i486 emulator" LANGUAGES C)

add_executable(acme src/main.c)

target_include_directories(acme PUBLIC include)

set_property(TARGET acme PROPERTY C_STARNDARD_REQUIRED ON)

set_property(TARGET acme PROPERTY C_STANDARD 23)
