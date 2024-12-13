#include <gtest/gtest.h>

#include "comlint/command_line_interface.hpp"

using namespace comlint;

TEST(TestCommandLineInterfaceBasicFeatures, DefaultConstructorDoesNotThrow)
{
    int argc = 2;
    char arg_1[] = "a";
    char arg_2[] = "b";
    char* argv[] = {arg_1, arg_2};

    EXPECT_NO_THROW(CommandLineInterface(argc, argv));
}

TEST(TestCommandLineInterfaceBasicFeatures, DefaultConstructorDoesNotThrowWhenArgvEmpty)
{
    int argc = 0;
    char empty_input[] = "";
    char* argv[] = {empty_input};

    EXPECT_NO_THROW(CommandLineInterface(argc, argv));
}

TEST(TestCommandLineInterfaceBasicFeatures, DefaultConstructorDoesNotThrowWhenProvidingCustomProgramName)
{
    int argc = 2;
    char arg_1[] = "a";
    char arg_2[] = "b";
    char* argv[] = {arg_1, arg_2};

    EXPECT_NO_THROW(CommandLineInterface(argc, argv, "custom program name"));
}

TEST(TestCommandLineInterfaceBasicFeatures, DefaultConstructorDoesNotThrowWhenProvidingProgramDescription)
{
    int argc = 2;
    char arg_1[] = "a";
    char arg_2[] = "b";
    char* argv[] = {arg_1, arg_2};

    EXPECT_NO_THROW(CommandLineInterface(argc, argv, "custom program name", "program description"));
}

TEST(TestCommandLineInterfaceBasicFeatures, ParseReturnsEmptyParsedCommandIfInputContainsHelpCommand)
{
    const int argc = 2;
    char program_name[] = "program.exe";
    char help[] = "help";
    char* argv[] = {program_name, help};
    const ParsedCommand expected_parsed_command("help", {}, {}, {});
    CommandLineInterface cli(argc, argv);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceBasicFeatures, ParseReturnsEmptyParsedCommandIfInputContainsHelpOption)
{
    const int argc = 2;
    char program_name[] = "program_name.exe";
    char help_option[] = "-h";
    char* argv[] = {program_name, help_option};
    const ParsedCommand expected_parsed_command("help", {}, {}, {});
    CommandLineInterface cli(argc, argv);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceBasicFeatures, ParseReturnsEmptyParsedCommandIfInputContainsHelpFlag)
{
    const int argc = 2;
    char program_name[] = "program_name.exe";
    char help_flag[] = "--help";
    char* argv[] = {program_name, help_flag};
    const ParsedCommand expected_parsed_command("help", {}, {}, {});
    CommandLineInterface cli(argc, argv);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}