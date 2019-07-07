cmake_minimum_required(VERSION 2.8)
project(util)
set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ./bin/)
set(LIBRARY_OUTPUT_PATH ./lib/)

add_library(util pointer.c pointer.h debugtool.h debugtool.c endian.c endian.h)
