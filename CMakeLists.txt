cmake_minimum_required(VERSION 3.30)
project(DataStructs LANGUAGES C)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Werror -Wall -Wpedantic -Wextra -Wconversion -Wno-pointer-arith)
endif()

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXECUTABLE_SUFFIX .exe)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(singly src/singly.c)
add_executable(doubly src/doubly.c)
