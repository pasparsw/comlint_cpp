#include <gtest/gtest.h>

#include "command_properties.hpp"

using namespace comlint;

TEST(TestCommandProperties, ConstructorDoesNotThrow)
{
    EXPECT_NO_THROW(CommandProperties(ANY, ANY, ANY, "", 0U, {}));
}

TEST(TestCommandProperties, RequiresValueReturnsTrue)
{
    const unsigned int num_of_required_values {1U};
    CommandProperties command_properties(ANY, ANY, ANY, "", num_of_required_values, {});

    EXPECT_TRUE(command_properties.RequiresValue());
}

TEST(TestCommandProperties, RequiresValueReturnsFalse)
{
    const unsigned int num_of_required_values {0U};
    CommandProperties command_properties(ANY, ANY, ANY, "", num_of_required_values, {});

    EXPECT_FALSE(command_properties.RequiresValue());
}