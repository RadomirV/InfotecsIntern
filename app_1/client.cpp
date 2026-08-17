#include "client.h"

#include "DataParser.h"

#include <algorithm>
#include <cerrno>
#include <cctype>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <system_error>
#include <thread>
#include <utility>

#include <sys/socket.h>
#include <unistd.h>

Client::Client(std::string serverAddress, const std::uint16_t serverPort)
    : serverAddress_(std::move(serverAddress)), serverPort_(serverPort)
{
}

Client::~Client()
{
    closeSocket();
}

void Client::run()
{
    std::thread inputThread(&Client::readAndPrepareInput, this);
    std::thread processingThread(&Client::processAndSend, this);
    inputThread.join();
    processingThread.join();
}

void Client::openSocket()
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

    destination_.sin_family = AF_INET;
    destination_.sin_port = htons(serverPort_);

    const int parseResult = inet_pton(AF_INET, serverAddress_.c_str(), &destination_.sin_addr);
    if (parseResult != 1)
    {
        const int errorCode = errno;
        closeSocket();
        if (parseResult == 0)
        {
            throw std::invalid_argument("invalid IPv4 address: " + serverAddress_);
        }
        throw std::system_error(errorCode, std::generic_category(), "inet_pton failed");
    }
}

void Client::readAndPrepareInput()
{
    std::string value;
    while (true)
    {
        std::cout << "Enter string:\n";
        if (!std::getline(std::cin, value))
        {
            break;
        }

        if (value.empty() || value.size() > 64 || !std::all_of(value.begin(), value.end(), [](const char symbol)
                                                               { return std::isdigit(static_cast<unsigned char>(symbol)) != 0; }))
        {
            std::cerr << "Invalid input. Enter from 1 to 64 digits.\n";
            continue;
        }

        dataParser::sortAndReplaceEvenDigits(value);
        std::unique_lock<std::mutex> lock(bufferMutex_);
        bufferCondition_.wait(lock, [this]
                              { return !isReady_; });
        buffer_ = std::move(value);
        isReady_ = true;
        lock.unlock();
        bufferCondition_.notify_one();
    }

    std::unique_lock<std::mutex> lock(bufferMutex_);
    bufferCondition_.wait(lock, [this]
                          { return !isReady_; });
    buffer_.clear();
    isReady_ = true;
    lock.unlock();
    bufferCondition_.notify_one();
}

void Client::processAndSend()
{
    while (true)
    {
        std::string value;

        std::unique_lock<std::mutex> lock(bufferMutex_);
        bufferCondition_.wait(lock, [this]
                              { return isReady_; });
        value = std::move(buffer_);
        buffer_.clear();
        isReady_ = false;
        lock.unlock();
        bufferCondition_.notify_one();

        if (value.empty())
        {
            return;
        }

        std::cout << value << '\n';
        const auto sum = dataParser::calculateDigitSum(value);
        std::cout << "Sum: " << sum << '\n';

        try
        {
            sendValue(sum);
        }
        catch (const std::exception &error)
        {
            std::cerr << "Send error: " << error.what() << '\n';
        }
    }
}

void Client::sendValue(const std::uint32_t value)
{
    openSocket();

    const std::uint32_t networkValue = htonl(value);
    const ssize_t sentBytes = sendto(socket_, &networkValue, sizeof(networkValue), 0,
                                     reinterpret_cast<const sockaddr *>(&destination_), sizeof(destination_));

    if (sentBytes == -1)
    {
        throw std::system_error(errno, std::generic_category(), "sendto failed");
    }
    if (static_cast<std::size_t>(sentBytes) != sizeof(networkValue))
    {
        throw std::runtime_error("sendto sent an incomplete UDP datagram");
    }
}

void Client::closeSocket() noexcept
{
    if (socket_ != -1)
    {
        close(socket_);
        socket_ = -1;
    }
}
