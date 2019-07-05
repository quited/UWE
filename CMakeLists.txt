cmake_minimum_required(VERSION 2.8)
project(UWE)
set(CMAKE_C_STANDARD 11)

include_directories("src")
include_directories("src/common")
include_directories("src/common/container")

set(EXECUTABLE_OUTPUT_PATH ./bin/)
set(LIBRARY_OUTPUT_PATH ./lib/)

add_subdirectory(src/common/container)
add_subdirectory(src/common/spec)

add_executable(UWE src/cmd/UWE/main.c)

option(BUILD_TESTS "option for building test" OFF)

if (BUILD_TESTS)
    include_directories("third_party/Unity/src/")

    add_library(Unity
            third_party/Unity/src/unity.c
            third_party/Unity/src/unity.h
            third_party/Unity/src/unity_internals.h)

    add_executable(test_stdlib test/test_stdlib.c)
    add_executable(test_container test/test_container.c)
    add_executable(test_type test/test_type.c)

    target_link_libraries(test_container container Unity)
    target_link_libraries(test_stdlib Unity)
    target_link_libraries(test_type Unity)

    enable_testing()
    add_test(test_stdlib bin/test_stdlib)
    add_test(test_container bin/test_container)
    add_test(test_type bin/test_type)
else ()
endif ()