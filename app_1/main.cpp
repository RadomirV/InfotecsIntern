#include "client.h"

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
        const std::string address = argc > 1 ? argv[1] : "127.0.0.1";
        const std::uint16_t port = argc > 2 ? parsePort(argv[2]) : 1337;
        Client client(address, port);
        client.run();
    }
    catch (const std::exception &error)
    {
        std::cerr << "Client error: " << error.what() << '\n';
        return 1;
    }
}
