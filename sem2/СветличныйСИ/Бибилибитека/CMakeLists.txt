cmake_minimum_required(VERSION 4.0)
project(c__2)

set(CMAKE_CXX_STANDARD 20)

add_library(c__2 SHARED library.cpp)

set_target_properties(c__2 PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
)

if(WIN32)
    target_compile_definitions(c__2 PRIVATE MYLIB_EXPORTS)
endif()