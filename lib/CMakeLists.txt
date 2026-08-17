add_library(data_parser SHARED DataParser.cpp)

target_include_directories(data_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(data_parser PRIVATE -Wall -Wextra -Wpedantic)
