cmake_minimum_required(VERSION 3.10)
project(miniDZ_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем, что используем статическую SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(BUILD_SHARED_LIBS FALSE)

# Находим SFML
find_package(SFML 2.6 COMPONENTS graphics window system audio network REQUIRED)

# Собираем исходные файлы
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Линковка (автоматически выберет статические версии)
target_link_libraries(${PROJECT_NAME} 
    sfml-graphics
    sfml-window
    sfml-system
)

# Для Windows добавляем системные библиотеки
if(WIN32)
    target_link_libraries(${PROJECT_NAME} winmm gdi32 opengl32)
endif()