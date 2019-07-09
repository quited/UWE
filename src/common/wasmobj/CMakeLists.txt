cmake_minimum_required(VERSION 2.8)
project(wasmobj)
set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ./bin/)
set(LIBRARY_OUTPUT_PATH ./lib/)

add_library(typeobj typeobj/typeobj.c)
add_library(funcobj typeobj/funcobj/funcobj.c)
add_library(wasmobj wasmobj.c)

target_link_libraries(typeobj funcobj)
target_link_libraries(wasmobj typeobj)
