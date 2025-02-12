cmake_minimum_required(VERSION 3.16)
project(infotecs)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)


set(APP_1_SOURCES app_1/client.cpp
    app_1/main.cpp)
set(APP_1_HEADERS app_1/client.h)

set(APP_2_SOURCES app_2/server.cpp
    app_2/main.cpp)
set(APP_2_HEADERS app_2/server.h)

set(DLL_DATAPARSER_SOURCES lib/DataParser.cpp)
set(DLL_DATAPARSER_HEADERS lib/DataParser.h )

add_library(DATAPARSER_LIB SHARED ${DLL_DATAPARSER_SOURCES} ${DLL_DATAPARSER_HEADERS})
target_include_directories(DATAPARSER_LIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)


add_executable(client ${APP_1_SOURCES} ${APP_1_HEADERS})
add_executable(server ${APP_2_SOURCES} ${APP_2_HEADERS})

target_link_libraries(client PRIVATE Threads::Threads DATAPARSER_LIB)
target_link_libraries(server PRIVATE DATAPARSER_LIB)

