add_executable(App main.cpp)
cmake_minimum_required(VERSION 4.0)
target_link_libraries(App MathLib)

target_include_directories(App PRIVATE ${CMAKE_SOURCE_DIR}/mathlib)
