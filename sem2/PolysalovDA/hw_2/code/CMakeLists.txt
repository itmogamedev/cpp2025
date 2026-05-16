cmake_minimum_required(VERSION 3.15)
project(osu_at_home)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)

include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
)

set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
set(SFML_ENABLE_NETWORK ON)
set(SFML_ENABLE_AUDIO ON)

FetchContent_MakeAvailable(sfml)

add_executable(${PROJECT_NAME} 
    main.cpp
    Circle.cpp
    CircleSystem.cpp
    Game.cpp
    InputHandler.cpp
    Renderer.cpp
    UI.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    sfml-network
)

# Копирование DLL для Windows
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE:sfml-audio>
            $<TARGET_FILE:sfml-network>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()