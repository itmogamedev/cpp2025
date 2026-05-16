cmake_minimum_required(VERSION 4.0)
project(mathexe)

set(CMAKE_CXX_STANDARD 20)

add_library(mathlib SHARED IMPORTED)
set_target_properties(mathlib PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/libmathlib.dll"
        IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/libs/libmathlib.dll"
)

add_executable(mathexe main.cpp)
target_include_directories(mathexe PRIVATE "${CMAKE_SOURCE_DIR}/libs")
target_link_libraries(mathexe PRIVATE mathlib)

add_custom_command(TARGET mathexe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/libmathlib.dll"
        $<TARGET_FILE_DIR:mathexe>
)