cmake_minimum_required(VERSION 4.0)
project(mathlib)

set(CMAKE_CXX_STANDARD 20)

add_library(mathlib SHARED library.cpp)
