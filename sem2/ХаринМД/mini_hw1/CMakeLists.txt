cmake_minimum_required(VERSION 3.10)

project(Vec3MathProject)

set(CMAKE_CXX_STANDARD 17)

add_library(Vec3MathLib SHARED
    Vec3MathLib/vec3.cpp
)

target_include_directories(Vec3MathLib PUBLIC
    Vec3MathLib
)

add_executable(Vec3App
    Vec3App/main.cpp
)

target_link_libraries(Vec3App
    Vec3MathLib
)