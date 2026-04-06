include_directories("${PROJECT_SOURCE_DIR}/lib/vec3")
add_executable(main main.cpp)
target_link_libraries(main vec3)