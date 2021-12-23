cmake_minimum_required(VERSION 3.20)
set(LIB_NAME supportlib)

project(${LIB_NAME})

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(_UNICODE UNICODE)
add_link_options(
        /SUBSYSTEM:WINDOWS
        /DYNAMICBASE
        /MACHINE:X64
)

INCLUDE_DIRECTORIES(include)

add_library(
        ${LIB_NAME}
        include/supportlib/Support.h
        src/Support.cpp
)

target_include_directories(${LIB_NAME} PUBLIC include)
target_link_options(${LIB_NAME} PUBLIC "/INCREMENTAL")