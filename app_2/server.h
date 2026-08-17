#pragma once

#include <cstdint>

#include <arpa/inet.h>

class Server
{
public:
    explicit Server(std::uint16_t port = 1337);
    ~Server();

    Server(const Server &) = delete;
    Server &operator=(const Server &) = delete;

    void openSocket();
    [[nodiscard]] bool receiveAndReview();

private:
    void closeSocket() noexcept;

    std::uint16_t port_;
    int socket_ = -1;
    sockaddr_in address_{};
};
