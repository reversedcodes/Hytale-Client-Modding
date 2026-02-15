project(hytale_header)
add_library(hytale_header INTERFACE)
target_include_directories(hytale_header INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../)
add_library(hytale::header ALIAS hytale_header)