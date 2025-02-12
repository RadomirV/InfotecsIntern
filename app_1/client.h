#pragma once

#include <string>
#include <mutex>
#include <condition_variable>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class Client
{

public:
    void thread_1();
    void thread_2();
    ~Client();

private:
    std::string buffer_;
    std::mutex mtx_;
    std::condition_variable cond_;
    bool isReady_ = false;
    int sockfd_;
    struct sockaddr_in address_{};

    void launchSocket();
    

};

