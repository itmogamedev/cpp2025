cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(DLL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/DLL/)

include_directories(${DLL_PATH})

add_executable(MyApp main.cpp)

target_link_libraries(MyApp PRIVATE ${DLL_PATH}/MathLib.lib)

add_custom_command(TARGET MyApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLL_PATH}/MathLib.dll
        $<TARGET_FILE_DIR:MyApp>
)