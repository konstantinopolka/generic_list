cmake_minimum_required(VERSION 3.29)
project(generic_list C)

set(CMAKE_C_STANDARD 11)

add_library(generic_list STATIC generic_list.c)
