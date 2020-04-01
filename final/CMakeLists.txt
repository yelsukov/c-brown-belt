cmake_minimum_required(VERSION 3.14)
project(final)

set(CMAKE_CXX_STANDARD 14)

add_executable(final main.cpp token.cpp token.h condition_parser.cpp condition_parser.h condition_parser_test.cpp node.cpp node.h date.cpp date.h database.cpp database.h)