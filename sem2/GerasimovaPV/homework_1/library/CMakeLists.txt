cmake_minimum_required(VERSION 4.0)
project(library)

set(CMAKE_CXX_STANDARD 20)

add_library(library SHARED library.cpp
        vectorLibrary.h
        vectorLibrary.cpp
)
