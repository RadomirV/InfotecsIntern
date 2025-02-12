#include "client.h"
#include <iostream>
#include <algorithm>
#include "DataParser.h"

void Client::launchSocket()
{
    if ((sockfd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        throw std::runtime_error("Failed to create socket");
    }

    address_.sin_family = AF_INET;
    address_.sin_addr.s_addr = INADDR_ANY;
    address_.sin_port = htons(1337);
}

Client::~Client()
{
    if (sockfd_ != -1)
    {
        close(sockfd_);
    }
}

void Client::thread_1()
{
    std::string str;
    std::cout << "Enter string: " << '\n';
    std::getline(std::cin, str);

    while ((str.empty()) || (str.size() > 64) || !std::all_of(str.begin(), str.end(), [](const auto &i)
                                                              { return std::isdigit(i); }))
    {
        std::cout << "This string doesn't correct. It has to consist only from digits and with size <= 64.\nEnter msg again: \n";
        std::getline(std::cin, str);
    }

    DataParser::sortAndInsertKB(str);
    std::unique_lock<std::mutex> ul(mtx_);
    buffer_ = str;
    isReady_ = true;
    cond_.notify_one();
}

void Client::thread_2()
{
    std::unique_lock<std::mutex> ul(mtx_);
    cond_.wait(ul, [&]()
               { return isReady_; });
    isReady_ = false;
    std::string data = buffer_;
    buffer_ = "";
    ul.unlock();

    std::cout << data << '\n';
    auto sum = DataParser::digitSum(data);
    std::cout << "Sum: " << sum << '\n';

    launchSocket();
    sendto(sockfd_, &sum, sizeof(sum),
           MSG_CONFIRM, (const struct sockaddr *)&address_,
           sizeof(address_));
}