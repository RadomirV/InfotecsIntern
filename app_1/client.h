#pragma once

#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <string>

#include <arpa/inet.h>

class Client
{
public:
    explicit Client(std::string serverAddress = "127.0.0.1",
                    std::uint16_t serverPort = 1337);
    ~Client();

    Client(const Client &) = delete;
    Client &operator=(const Client &) = delete;

    void run();

private:
    void openSocket();
    void closeSocket() noexcept;
    void readAndPrepareInput();
    void processAndSend();
    void sendValue(std::uint32_t value);

    std::string serverAddress_;
    std::uint16_t serverPort_;
    std::string buffer_;
    std::mutex bufferMutex_;
    std::condition_variable bufferCondition_;
    bool isReady_ = false;
    int socket_ = -1;
    sockaddr_in destination_{};
};
