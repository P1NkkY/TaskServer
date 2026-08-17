#include <gtest/gtest.h>

#include "describe_enum.h"

enum class Color { Red, Green, Blue };
BOOST_DESCRIBE_ENUM(Color, Red, Green, Blue)

TEST(DescribeTest, EnumToStringShouldReturnCorrectNameWhenEnumValueExists) {
    EXPECT_STREQ(common::describe::EnumToString(Color::Red), "Red");
}

TEST(DescribeTest, EnumToStringShouldReturnUnknownWhenEnumValueDoesNotExist) {
    Color invalid_color = static_cast<Color>(40);
    EXPECT_STREQ(common::describe::EnumToString(invalid_color), "Unknown");
}

TEST(DescribeTest, EnumFromStringShouldReturnEnumValueWhenCorrectName) {
    std::optional<Color> color = common::describe::EnumFromString<Color>("Red");
    EXPECT_TRUE(color.has_value() && color.value() == Color::Red);
}

TEST(DescribeTest, EnumFromStringShouldReturnNulloptWhenInvalidName) {
    std::optional<Color> color =
        common::describe::EnumFromString<Color>("Pink");
    EXPECT_FALSE(color.has_value());
}