cmake_minimum_required(VERSION 2.8)
project(spec)
set(CMAKE_C_STANDARD 11)

add_library(spec spec.c opcode.h magic.h section_id.h LEB128/leb128.c LEB128/leb128.h)
