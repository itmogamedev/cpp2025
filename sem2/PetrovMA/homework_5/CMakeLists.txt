cmake_minimum_required(VERSION 4.0)
project(mininhwlast)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)


add_executable(mininhwlast main.cpp
        player.h
        player.cpp
        asteroid.h
        asteroid.cpp
        laser.h
        laser.cpp)

target_compile_features(mininhwlast PRIVATE cxx_std_20)
target_link_libraries(mininhwlast PRIVATE SFML::Graphics)
target_link_options(mininhwlast PRIVATE
        -static-libgcc
        -static-libstdc++
        -static
)
