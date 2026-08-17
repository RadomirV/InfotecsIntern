#include "DataParser.h"

#include <gtest/gtest.h>

#include <string>

TEST(DataParserTest, TestSortAndReplaceEvenDigits)
{
    std::string value = "123456";

    dataParser::sortAndReplaceEvenDigits(value);

    EXPECT_EQ(value, "KB5KB3KB1");
}

TEST(DataParserTest, TestCalculateDigitSum)
{
    EXPECT_EQ(dataParser::calculateDigitSum("KB5KB3KB1"), 9U);
    EXPECT_EQ(dataParser::calculateDigitSum("KBKB"), 0U);
}

TEST(DataParserTest, TestIsValidSum)
{
    EXPECT_FALSE(dataParser::isValidSum(96));
    EXPECT_FALSE(dataParser::isValidSum(100));
    EXPECT_TRUE(dataParser::isValidSum(128));
    EXPECT_TRUE(dataParser::isValidSum(160));
}
