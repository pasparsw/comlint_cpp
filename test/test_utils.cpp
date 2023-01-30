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

TEST(TestUtils, MapKeysToStringReturnsProperValue)
{
    using MapType = std::map<std::string, int>;

    const MapType map {{"key_1", 1}, {"key_2", 2}, {"key_3", 3}};

    EXPECT_EQ(utils::MapKeysToString(map), "key_1key_2key_3");
}
TEST(TestUtils, MapKeysToStringReturnsProperValueWhenSpecifyingDelimiter)
{
    using MapType = std::map<std::string, int>;

    const MapType map {{"key_1", 1}, {"key_2", 2}, {"key_3", 3}};

    EXPECT_EQ(utils::MapKeysToString(map, ", "), "key_1, key_2, key_3");
}

TEST(TestUtils, MapKeysToStringReturnsProperValueWhenDelimiterIsEscapedCharacter)
{
    using MapType = std::map<std::string, int>;

    const MapType map {{"key_1", 1}, {"key_2", 2}, {"key_3", 3}};

    EXPECT_EQ(utils::MapKeysToString(map, "\n"), "key_1\nkey_2\nkey_3");
}

TEST(TestUtils, GetSimilarValuesReturnsProperValues)
{
    const std::vector<std::string> vector {"open_file", "open_folder", "close_file", "close_folder"};

    EXPECT_EQ(utils::GetSimilarValues(vector, "open", ", "), "open_file, open_folder");
    EXPECT_EQ(utils::GetSimilarValues(vector, "file", ", "), "open_file, close_file");
    EXPECT_EQ(utils::GetSimilarValues(vector, "run_open_file", ", "), "open_file");
    EXPECT_EQ(utils::GetSimilarValues(vector, "abcdef", ", "), "");
}

TEST(TestUtils, GetSimilarKeysReturnsProperValues)
{
    const std::map<std::string, int> map {{"open_file", 1},
                                          {"open_folder", 2},
                                          {"close_file", 3},
                                          {"close_folder", 4}};

    const std::string similar_values_1 = utils::GetSimilarKeys(map, "open", ", ");
    const std::string similar_values_2 = utils::GetSimilarKeys(map, "file", ", ");
    const std::string similar_values_3 = utils::GetSimilarKeys(map, "run_open_file", ", ");
    const std::string similar_values_4 = utils::GetSimilarKeys(map, "abcdef", ", ");

    const std::string expected_values_1 {"open_file, open_folder"};
    const std::string expected_values_2 {"open_file, close_file"};
    const std::string expected_values_3 {"open_file"};

    EXPECT_EQ(similar_values_1.size(), expected_values_1.size());
    EXPECT_TRUE(similar_values_1.find("open_file") != std::string::npos);
    EXPECT_TRUE(similar_values_1.find("open_folder") != std::string::npos);

    EXPECT_EQ(similar_values_2.size(), expected_values_2.size());
    EXPECT_TRUE(similar_values_2.find("open_file") != std::string::npos);
    EXPECT_TRUE(similar_values_2.find("close_file") != std::string::npos);

    EXPECT_EQ(similar_values_3.size(), expected_values_3.size());
    EXPECT_TRUE(similar_values_3.find("open_file") != std::string::npos);

    EXPECT_TRUE(similar_values_4.empty());
}