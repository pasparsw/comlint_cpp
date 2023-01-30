#include <gtest/gtest.h>

#include "command_line_interface.hpp"

using namespace comlint;

TEST(TestNonCommandBasedInterface, InterfaceWithASingleOption)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "-option", "option_value"};

    const CommandName expected_command_name {""};
    const CommandValues expected_command_values {};
    const OptionsMap expected_options {{"-option", "option_value"}};
    const FlagsMap expected_flags {};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);

    cli.AddOption("-option", "Some option");

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestNonCommandBasedInterface, InterfaceWithASingleOptionAndPredefinedOptionValues)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "-option", "option_value_2"};

    const CommandName expected_command_name {""};
    const CommandValues expected_command_values {};
    const OptionsMap expected_options {{"-option", "option_value_2"}};
    const FlagsMap expected_flags {};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);
    const OptionValues allowed_option_values {"option_value_1", "option_value_2"};

    cli.AddOption("-option", "Some option", allowed_option_values);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestNonCommandBasedInterface, InterfaceWithASingleFlag)
{
    const int argc = 2;
    char* argv[] = {"program.exe", "--flag"};

    const CommandName expected_command_name {""};
    const CommandValues expected_command_values {};
    const OptionsMap expected_options {};
    const FlagsMap expected_flags {{"--flag", true}};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);

    cli.AddFlag("--flag", "Some flag");

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestNonCommandBasedInterface, Combo)
{
    const int argc = 7;
    char* argv[] = {"program.exe", "-option_1", "option_value_1", "-option_2", "option_value_2", "--flag_1", "--flag_2"};

    const CommandName expected_command_name {""};
    const CommandValues expected_command_values {};
    const OptionsMap expected_options {{"-option_1", "option_value_1"},
                                       {"-option_2", "option_value_2"}};
    const FlagsMap expected_flags {{"--flag_1", true},
                                   {"--flag_2", true},
                                   {"--flag_3", false}};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);
    const OptionValues option_2_allowed_values {"option_value_2", "option_value_3"};

    cli.AddOption("-option_1", "Some option 1");
    cli.AddOption("-option_2", "Some option 2", option_2_allowed_values);

    cli.AddFlag("--flag_1", "Some flag 1");
    cli.AddFlag("--flag_2", "Some flag 2");
    cli.AddFlag("--flag_3", "Some flag 3");

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}