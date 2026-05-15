cmake_minimum_required(VERSION 4.0)
project(client)

set(CMAKE_CXX_STANDARD 20)

# 1️⃣ Сборка DLL из исходников
add_library(vectorLibrary SHARED
        ../library/vectorLibrary.cpp
)

# Экспорт символов DLL
target_compile_definitions(vectorLibrary PRIVATE VECTORLIBRARY_EXPORTS)

# 2️⃣ Сборка клиентского exe
add_executable(client main.cpp)

# 3️⃣ Линковка клиента с DLL
target_link_libraries(client vectorLibrary)

# 4️⃣ Подключение заголовков
target_include_directories(client PRIVATE ../library)