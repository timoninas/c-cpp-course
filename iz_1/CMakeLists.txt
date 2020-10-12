cmake_minimum_required(VERSION 3.17)
project(untitled C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(untitled main.c cDate.c cDate.h test.h test.c)