#include <gtest/gtest.h>

#include "parsed_command.hpp"

using namespace comlint;

TEST(TestParsedCommand, DefaultConstructorDoesNotThrow)
{
    EXPECT_NO_THROW(ParsedCommand());
}

TEST(TestParsedCommand, ConstructorWithArgumentsDoesNotThrow)
{
    EXPECT_NO_THROW(ParsedCommand("", {}, {}, {}));
}

TEST(TestParsedCommand, IsOptionUsedReturnsTrue)
{
    const CommandName command_name {"command"};
    const CommandValues values {};
    const OptionsMap options {{"-option_name", "option_value"}};
    const FlagsMap flags {};
    const ParsedCommand command(command_name, values, options, flags);

    EXPECT_TRUE(command.IsOptionUsed("-option_name"));
}

TEST(TestParsedCommand, IsOptionUsedReturnsFalse)
{
    const CommandName command_name {"command"};
    const CommandValues values {};
    const OptionsMap options {{"-option_name", "option_value"}};
    const FlagsMap flags {};
    const ParsedCommand command(command_name, values, options, flags);

    EXPECT_FALSE(command.IsOptionUsed("-some_option_name"));
}

TEST(TestParsedCommand, IsFlagUsedReturnsTrue)
{
    const CommandName command_name {"command"};
    const CommandValues values {};
    const OptionsMap options {};
    const FlagsMap flags {{"--flag_name", true}};
    const ParsedCommand command(command_name, values, options, flags);

    EXPECT_TRUE(command.IsFlagUsed("--flag_name"));
}

TEST(TestParsedCommand, IsFlagUsedReturnsFalse)
{
    const CommandName command_name {"command"};
    const CommandValues values {};
    const OptionsMap options {};
    const FlagsMap flags {{"--flag_name", true}};
    const ParsedCommand command(command_name, values, options, flags);

    EXPECT_FALSE(command.IsFlagUsed("--some_flag_name"));
}

TEST(TestParsedCommand, ComparsonOperatorReturnsTrueForIdenticalParsedCommands)
{
    const ParsedCommand parsed_command_1("command",
                                         {"value_1", "value_2"},
                                         {{"-option_name", "option_value"}, {"-other_option_name", "other_option_value"}},
                                         {{"--flag_name", true}, {"--other_flag_name", true}});
    const ParsedCommand parsed_command_2("command",
                                         {"value_1", "value_2"},
                                         {{"-other_option_name", "other_option_value"}, {"-option_name", "option_value"}},
                                         {{"--flag_name", true}, {"--other_flag_name", true}});

    EXPECT_TRUE(parsed_command_1 == parsed_command_2);
}

TEST(TestParsedCommand, ComparsonOperatorReturnsFalseForDifferentParsedCommands)
{
    const ParsedCommand parsed_command_1("command",
                                         {"value_1", "different_value"},
                                         {{"-option_name", "option_value"}, {"-other_option_name", "other_option_value"}},
                                         {{"--flag_name", true}, {"--other_flag_name", true}});
    const ParsedCommand parsed_command_2("command",
                                         {"value_1", "value_2"},
                                         {{"-other_option_name", "other_option_value"}, {"-option_name", "option_value"}},
                                         {{"--flag_name", true}, {"--other_flag_name", true}});

    EXPECT_FALSE(parsed_command_1 == parsed_command_2);
}