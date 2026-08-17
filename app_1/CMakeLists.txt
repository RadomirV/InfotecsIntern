find_package(Threads REQUIRED)

add_executable(client
    client.cpp
    main.cpp
)

target_link_libraries(client PRIVATE data_parser Threads::Threads)
target_compile_options(client PRIVATE -Wall -Wextra -Wpedantic)
