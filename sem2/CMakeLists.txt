cmake_minimum_required(VERSION 3.28)
project(TypingTrainer LANGUAGES CXX)

# Устанавливаем стандарт C++17, обязательный для SFML 3
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Определяем папку для выходных файлов (опционально)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Подключаем модуль FetchContent для автоматической загрузки SFML
include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(SFML)

# Создаём исполняемый файл (без WIN32 — будет и консоль, и графическое окно)
add_executable(typing_trainer
    main.cpp 
    Game.cpp 
    Utils.cpp
)

# Линкуем только модуль Graphics
target_link_libraries(typing_trainer PRIVATE SFML::Graphics)

# Для Windows копируем необходимые DLL SFML в папку с исполняемым файлом
if(WIN32)
    add_custom_command(TARGET typing_trainer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SFML::Graphics>
        $<TARGET_FILE_DIR:typing_trainer>
    )
endif()