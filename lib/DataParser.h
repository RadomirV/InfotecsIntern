#pragma once
#include <string>

#define DATA_API __attribute__((visibility("default")))

class DATA_API DataParser
{
public:
    static void sortAndInsertKB(std::string &str);
    static unsigned int digitSum(std::string &str);
    static bool analysis(unsigned int data);
};
