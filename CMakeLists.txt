cmake_minimum_required(VERSION 2.8)
project(UWE)
set(CMAKE_C_STANDARD 11)

include_directories("src")
set(EXECUTABLE_OUTPUT_PATH ./bin/)
set(LIBRARY_OUTPUT_PATH ./lib/)

add_subdirectory(src/common/container)

add_executable(main src/main.c)

add_executable(test_stdlib test/test_stdlib.c)

add_executable(test_container test/test_container.c)
target_link_libraries(test_container container)

add_executable(test_type test/test_type.c)

enable_testing()
add_test(test_stdlib bin/test_stdlib)
add_test(test_container bin/test_container)
add_test(test_type bin/test_type)