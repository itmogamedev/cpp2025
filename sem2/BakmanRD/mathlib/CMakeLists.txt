add_library(MathLib SHARED Vec3.cpp)

cmake_minimum_required(VERSION 4.0)

target_include_directories(MathLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

