cmake_minimum_required(VERSION 3.10)
project(TypingTrainer)

set(CMAKE_CXX_STANDARD 17)

# Поиск SFML 3.0
find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

add_executable(TypingTrainer main.cpp)

# Линковка компонентов SFML
target_link_libraries(TypingTrainer SFML::Graphics SFML::Window SFML::System)