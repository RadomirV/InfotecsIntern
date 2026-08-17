add_executable(server
    server.cpp
    main.cpp
)

target_link_libraries(server PRIVATE data_parser)
target_compile_options(server PRIVATE -Wall -Wextra -Wpedantic)
