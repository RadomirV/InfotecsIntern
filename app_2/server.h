#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class Server
{
public:
    void launchSocket();
    void RunReviewer();
    ~Server();

private:
    int data_;
    int sockfd_;
    struct sockaddr_in address_{};
};