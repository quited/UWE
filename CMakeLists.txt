cmake_minimum_required(VERSION 2.8)
project(UWE)
set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(src/common)
include_directories(src/common/container)
include_directories(third_party/pt)

set(EXECUTABLE_OUTPUT_PATH ./bin/)
set(LIBRARY_OUTPUT_PATH ./lib/)

add_subdirectory(src/common/container)
<<<<<<< HEAD
add_subdirectory(src/common/wasmspec)
=======
add_subdirectory(src/common/wasmpec)
>>>>>>> 5feb8bd7465bb32850edda0b489cee9c5b20e53d
add_subdirectory(src/common/wasmobj)
add_subdirectory(src/common/LEB128)
add_subdirectory(src/parser)
add_subdirectory(src/common/util)

link_libraries(wasmobj container spec)
link_libraries(parser wasmobj)

add_executable(UWE src/cmd/UWE/main.c)
add_library(pt third_party/pt_mock.c third_party/pt/pt.h)

target_link_libraries(UWE container spec parser util)

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

    add_executable(test_pt third_party/pt/pt_test.c third_party/pt/pt.h)

    enable_testing()
    add_test(test_stdlib bin/test_stdlib)
    add_test(test_container bin/test_container)
    add_test(test_type bin/test_type)
    add_test(test_pt bin/test_pt)
else ()
endif ()