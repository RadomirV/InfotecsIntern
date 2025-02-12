#include "server.h"

#include "DataParser.h"
#include <iostream>
#include <unistd.h>

void Server::launchSocket()
{
    if ((sockfd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        throw std::runtime_error("Failed to create socket");
    }

    address_.sin_family = AF_INET;
    address_.sin_addr.s_addr = INADDR_ANY;
    address_.sin_port = htons(1337);

    if (bind(sockfd_, (const struct sockaddr *)&address_, sizeof(address_)) < 0)
    {
        perror("Bind failed");
        throw std::runtime_error("Failed to bind socket");
    }
}

void Server::RunReviewer()
{
    recv(sockfd_, &data_, sizeof(unsigned int), MSG_WAITALL);

    if (DataParser::analysis(data_))
    {
        std::cout << "Data received" << '\n';
    }
    else
    {
        std::cout << "Error with data receiving" << '\n';
    }
}

Server::~Server()
{
    if (sockfd_ != -1)
    {
        close(sockfd_);
    }
}
