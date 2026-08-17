#include "server.h"

#include <cstdint>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

std::uint16_t parsePort(const std::string &text)
{
    std::size_t processedCharacters = 0;
    unsigned long value = std::stoul(text, &processedCharacters);
    if (processedCharacters != text.size() || value == 0 ||
        value > std::numeric_limits<std::uint16_t>::max())
    {
        throw std::out_of_range("port must be in the range 1..65535");
    }
    return static_cast<std::uint16_t>(value);
}

int main(const int argc, char *argv[])
{
    try
    {
        const std::uint16_t port = argc > 1 ? parsePort(argv[1]) : 1337;
        Server server(port);
        server.openSocket();
        std::cout << "Listening on UDP port " << port << '\n';

        while (true)
        {
            bool isValid = server.receiveAndReview();
            if (isValid)
            {
                std::cout << "Data received" << '\n';
            }
            else
            {
                std::cout << "Invalid data received" << '\n';
            }
        }
    }
    catch (const std::exception &error)
    {
        std::cerr << "Server error: " << error.what() << '\n';
        return 1;
    }
}
