cmake_minimum_required(VERSION 3.30)
project(DataStructs LANGUAGES C)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Werror -Wall -Wpedantic -Wextra -Wconversion -Wno-pointer-arith -Wunused-variable)
endif()

# HACK: Enable assertions.
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O3")
set(CMAKE_C_FLAGS_RELEASE "-O3")

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXECUTABLE_SUFFIX .exe)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
add_subdirectory(deps)
add_subdirectory(src)
