project(ProjectName2)

cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(_sequental STATIC static.c helper_func.c)
add_library(_multiproc SHARED dynamic.c helper_func.c)

add_executable(main.out main.c reader.c reader.h)
target_link_libraries(main.out -ldl)
target_link_libraries(main.out _sequental)
target_link_libraries(main.out _multiproc)

add_executable(test.out test.cpp reader.c reader.h)

target_link_libraries(test.out _sequental)
target_link_libraries(test.out _multiproc)
target_link_libraries(test.out ${GTEST_LIBRARIES} pthread)