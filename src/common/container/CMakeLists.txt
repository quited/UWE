cmake_minimum_required(VERSION 2.8)
project(container)
set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ./bin/)
set(LIBRARY_OUTPUT_PATH ./lib/)

add_library(array array/array.c)
add_library(buffer buffer/buffer.c)
add_library(container container.c)
add_library(deque deque/deque.c)
add_library(list list/list.c)
add_library(set set/set.c)
add_library(stack stack/stack.c)
add_library(vector vector/vector.c)
add_library(byte_buffer byte_buffer/byte_buffer.c byte_buffer/byte_buffer.h)

target_link_libraries(buffer array)
target_link_libraries(stack deque)
link_libraries(byte_buffer buffer)

target_link_libraries(container array buffer deque list set stack vector byte_buffer)
