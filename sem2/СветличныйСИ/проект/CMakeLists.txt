cmake_minimum_required(VERSION 4.0)
project(ahh)

set(CMAKE_CXX_STANDARD 20)

set(MYLIB_PATH "${CMAKE_SOURCE_DIR}/libs/testlib")

include_directories("${MYLIB_PATH}/include")

if(WIN32)
    add_library(mylib_external SHARED IMPORTED)
    set_target_properties(mylib_external PROPERTIES
            IMPORTED_LOCATION "${MYLIB_PATH}/lib/libc__2.dll"
            IMPORTED_IMPLIB "${MYLIB_PATH}/lib/libc__2.dll.a"
    )
else()
    add_library(mylib_external SHARED IMPORTED)
    set_target_properties(mylib_external PROPERTIES
            IMPORTED_LOCATION "${MYLIB_PATH}/lib/libmylib.so"
    )
endif()

add_executable(ahh_app main.cpp)

target_link_libraries(ahh_app PRIVATE mylib_external)