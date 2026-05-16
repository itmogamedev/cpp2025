cmake_minimum_required(VERSION 3.15)
project(TPtrainer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")

find_package(SFML REQUIRED COMPONENTS Graphics Window System)

add_executable(SFML_App main.cpp typing_trainer.cpp)

target_link_libraries(SFML_App SFML::Graphics SFML::Window SFML::System)