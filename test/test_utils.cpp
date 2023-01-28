#include <map>

#include <gtest/gtest.h>

#include "utils.hpp"

using namespace comlint;

TEST(TestUtils, VectorToStringReturnsProperValue)
{
    const std::vector<std::string> vector {"one", "two", "three"};
    const std::string expected_outptut {"onetwothree"};

    const std::string output = utils::VectorToString(vector);

    EXPECT_EQ(output, expected_outptut);
}

TEST(TestUtils, VectorToStringReturnsProperValueWhenEmptyVectorProvided)
{
    const std::vector<std::string> vector {};
    const std::string expected_outptut {""};

    const std::string output = utils::VectorToString(vector);

    EXPECT_EQ(output, expected_outptut);
}

TEST(TestUtils, VectorToStringReturnsProperValueWhenDelimiterProvided)
{
    const std::vector<std::string> vector {"one", "two", "three"};
    const std::string expected_outptut {"one, two, three"};
    const std::string delimiter {", "};

    const std::string output = utils::VectorToString(vector, delimiter);

    EXPECT_EQ(output, expected_outptut);
}

TEST(TestUtils, VectorToStringReturnsProperValueWhenOpeningStringProvided)
{
    const std::vector<std::string> vector {"one", "two", "three"};
    const std::string expected_outptut {"[one, two, three"};
    const std::string delimiter {", "};
    const std::string opening_string {"["};

    const std::string output = utils::VectorToString(vector, delimiter, opening_string);

    EXPECT_EQ(output, expected_outptut);
}

TEST(TestUtils, VectorToStringReturnsProperValueWhenOpeningAndClosingStringProvided)
{
    const std::vector<std::string> vector {"one", "two", "three"};
    const std::string expected_outptut {"[one, two, three]"};
    const std::string delimiter {", "};
    const std::string opening_string {"["};
    const std::string closing_string {"]"};

    const std::string output = utils::VectorToString(vector, delimiter, opening_string, closing_string);

    EXPECT_EQ(output, expected_outptut);
}

TEST(TestUtils, AreMapsEqualReturnsTrueForEqualMaps)
{
    using MapType = std::map<std::string, std::string>;

    const MapType lhs_map {{"key_1", "value_1"},
                           {"key_2", "value_2"}};
    const MapType rhs_map {{"key_2", "value_2"},
                           {"key_1", "value_1"}};
    
    EXPECT_TRUE(utils::AreMapsEqual<MapType>(lhs_map, rhs_map));
}

TEST(TestUtils, AreMapsEqualReturnsFalseForDifferentMaps)
{
    using MapType = std::map<std::string, std::string>;

    const MapType lhs_map {{"key_1", "value_1"},
                           {"key_2", "value_2"}};
    const MapType rhs_map {{"key_1", "value_1"},
                           {"key_2", "different_value"}};
    
    EXPECT_FALSE(utils::AreMapsEqual<MapType>(lhs_map, rhs_map));
}

TEST(TestUtils, MapContainsKeyReturnsTrue)
{
    using MapType = std::map<std::string, std::string>;

    const MapType map {{"key_1", "value_1"},
                       {"key_2", "value_2"}};

    EXPECT_TRUE(utils::MapContainsKey<MapType>(map, "key_2"));
}

TEST(TestUtils, MapContainsKeyReturnsFalse)
{
    using MapType = std::map<std::string, std::string>;

    const MapType map {{"key_1", "value_1"},
                       {"key_2", "value_2"}};

    EXPECT_FALSE(utils::MapContainsKey<MapType>(map, "key_3"));
}

TEST(TestUtils, VectorContainsElementReturnsTrue)
{
    using VectorType = std::vector<std::string>;

    const VectorType vector {"element_1", "element_2"};

    EXPECT_TRUE(utils::VectorContainsElement<VectorType>(vector, "element_2"));
}

TEST(TestUtils, VectorContainsElementReturnsFalse)
{
    using VectorType = std::vector<std::string>;

    const VectorType vector {"element_1", "element_2"};

    EXPECT_FALSE(utils::VectorContainsElement<VectorType>(vector, "element_3"));
}