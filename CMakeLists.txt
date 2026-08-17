cmake_minimum_required(VERSION 3.16)

project(infotecs VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_subdirectory(lib)
add_subdirectory(app_1)
add_subdirectory(app_2)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

