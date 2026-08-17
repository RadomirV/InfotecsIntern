#pragma once
#include <string>

namespace dataParser
{
    void sortAndReplaceEvenDigits(std::string &value);
    [[nodiscard]] unsigned int calculateDigitSum(const std::string &value);
    [[nodiscard]] bool isValidSum(unsigned int value) noexcept;
}
