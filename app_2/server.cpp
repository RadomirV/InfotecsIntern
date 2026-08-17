#include "server.h"

#include "DataParser.h"

#include <cerrno>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <system_error>

#include <sys/socket.h>
#include <unistd.h>

Server::Server(const std::uint16_t port) : port_(port)
{
}

Server::~Server()
{
    closeSocket();
}

void Server::openSocket()
{
    if (socket_ != -1)
    {
        return;
    }

    socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ == -1)
    {
        throw std::system_error(errno, std::generic_category(), "socket creation failed");
    }

    address_.sin_family = AF_INET;
    address_.sin_addr.s_addr = htonl(INADDR_ANY);
    address_.sin_port = htons(port_);

    if (bind(socket_, reinterpret_cast<const sockaddr *>(&address_), sizeof(address_)) == -1)
    {
        const int errorCode = errno;
        closeSocket();
        throw std::system_error(errorCode, std::generic_category(), "bind failed");
    }
}

bool Server::receiveAndReview()
{
    std::uint32_t networkValue = 0;
    const ssize_t receivedBytes = recv(socket_, &networkValue, sizeof(networkValue), MSG_TRUNC);

    if (receivedBytes == -1)
    {
        throw std::system_error(errno, std::generic_category(), "recv failed");
    }
    if (static_cast<std::size_t>(receivedBytes) != sizeof(networkValue))
    {
        throw std::runtime_error("recv received an invalid UDP datagram size");
    }

    const std::uint32_t value = ntohl(networkValue);
    return dataParser::isValidSum(value);
}

void Server::closeSocket() noexcept
{
    if (socket_ != -1)
    {
        close(socket_);
        socket_ = -1;
    }
}
