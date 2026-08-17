#include "DataParser.h"

#include <algorithm>
#include <cctype>

void dataParser::sortAndReplaceEvenDigits(std::string &value)
{
    std::sort(value.begin(), value.end(), std::greater<char>());
    for (std::size_t index = 0; index < value.size(); ++index)
    {
        const auto symbol = static_cast<unsigned char>(value[index]);
        if (std::isdigit(symbol) != 0 && (value[index] - '0') % 2 == 0)
        {
            value.replace(index, 1, "KB");
            ++index;
        }
    }
}

unsigned int dataParser::calculateDigitSum(const std::string &value)
{
    unsigned int sum = 0;
    for (const char symbol : value)
    {
        if (std::isdigit(static_cast<unsigned char>(symbol)) != 0)
        {
            sum += static_cast<unsigned int>(symbol - '0');
        }
    }
    return sum;
}

bool dataParser::isValidSum(const unsigned int value) noexcept
{
    return value >= 100 && value % 32 == 0;
}
