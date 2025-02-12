#include "DataParser.h"
#include <algorithm>

void DataParser::sortAndInsertKB(std::string &str)
{
    std::sort(str.begin(), str.end(), std::greater<char>());
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (std::isdigit(str[i]) && !(str[i] % 2))
        {
            str.replace(i, 1, "KB");
            ++i;
        }
    }
}

unsigned int DataParser::digitSum(std::string &str)
{
    unsigned int sum = 0;
    for (auto const &i : str)
    {
        if (std::isdigit(i))
        {
            sum += i - '0';
        }
    }
    return sum;
}

bool DataParser::analysis(unsigned int data)
{
    return (data >= 100 && (data & 0x1F) == 0);
}
