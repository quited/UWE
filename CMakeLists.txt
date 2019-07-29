cmake_minimum_required(VERSION 2.8)
project(UWE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ./bin/)
set(LIBRARY_OUTPUT_PATH ./lib/)

add_library(common
        src/common/io.h
        src/common/errors.h
        src/common/stringer.h
        src/common/panic.h
        src/common/config.h
        src/common/std.h
        src/common/types.h
        src/common/append.h
        #        src/common/buffer.h
        src/common/common.cc
        )