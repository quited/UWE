cmake_minimum_required(VERSION 2.8)
project(executor)
set(CMAKE_C_STANDARD 11)

add_library(vm vm/vm.h vm/vm.c)