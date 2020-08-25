get_filename_component(lib_vstr
        ${CMAKE_CURRENT_SOURCE_DIR} NAME)
cmake_minimum_required(VERSION 3.12)
project(${lib_vstr}
        LANGUAGES           C
        VERSION             1.1.2
        DESCRIPTION         "A C string library")

set(flags "-Wall -Wextra -Wpedantic -Wunreachable-code -Wredundant-decls")
set(properties
        C_STANDARD          11
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS        ON
        C_FLAGS             "${CMAKE_C_FLAGS} ${flags}"
        C_FLAGS_DEBUG       "${CMAKE_C_FLAGS} -Og -ggdb3 -fsanitize=undefined"
        C_FLAGS_RELEASE     "${CMAKE_C_FLAGS} -O2 -march=native")

include_directories(include)
include_directories(include/vstr)

set(cwd ${CMAKE_CURRENT_SOURCE_DIR})
set(lib_h
        ${cwd}/include/vstr/vstr.h)
add_executable(${lib_vstr} example.c ${lib_h})
set_target_properties(${lib_vstr} PROPERTIES ${properties})

