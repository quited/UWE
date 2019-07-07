cmake_minimum_required(VERSION 2.8)
project(leb128)
set(CMAKE_C_STANDARD 11)

add_library(leb128 leb128.c leb128.h)