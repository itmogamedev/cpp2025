cmake_minimum_required(VERSION 3.15)
project(osu)

find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System)

add_executable(${PROJECT_NAME} 
    ../osu/osu.cpp
    ../osu/Game.cpp
    ../osu/UIManager.cpp
)

target_link_libraries(${PROJECT_NAME} 
    SFML::Graphics
    SFML::Window
    SFML::System
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/osu/font.otf"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)