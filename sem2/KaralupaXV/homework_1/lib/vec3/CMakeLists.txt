set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(vec3 SHARED vec3.h)
set_target_properties(vec3 PROPERTIES LINKER_LANGUAGE CXX)