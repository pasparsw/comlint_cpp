#include <gtest/gtest.h>

#include "command_line_interface.hpp"

using namespace comlint;

TEST(TestCommandLineInterfaceBasicFeatures, DefaultConstructorDoesNotThrow)
{
    int argc = 2;
    char* argv = "a b";

    EXPECT_NO_THROW(CommandLineInterface(argc, &argv));
}

TEST(TestCommandLineInterfaceBasicFeatures, DefaultConstructorDoesNotThrowWhenArgvEmpty)
{
    int argc = 0;
    char* argv = "";

    EXPECT_NO_THROW(CommandLineInterface(argc, &argv));
}

TEST(TestCommandLineInterfaceBasicFeatures, DefaultConstructorDoesNotThrowWhenProvidingCustomProgramName)
{
    int argc = 2;
    char* argv = "a b";

    EXPECT_NO_THROW(CommandLineInterface(argc, &argv, "custom program name"));
}

TEST(TestCommandLineInterfaceBasicFeatures, DefaultConstructorDoesNotThrowWhenProvidingProgramDescription)
{
    int argc = 2;
    char* argv = "a b";

    EXPECT_NO_THROW(CommandLineInterface(argc, &argv, "custom program name", "program description"));
}

TEST(TestCommandLineInterfaceBasicFeatures, ParseReturnsEmptyParsedCommandIfInputContainsHelpCommand)
{
    const int argc = 2;
    char* argv[] = {"program.exe", "help"};
    const ParsedCommand expected_parsed_command("help", {}, {}, {});
    CommandLineInterface cli(argc, argv);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceBasicFeatures, ParseReturnsEmptyParsedCommandIfInputContainsHelpOption)
{
    const int argc = 2;
    char* argv[] = {"program.exe", "-h"};
    const ParsedCommand expected_parsed_command("help", {}, {}, {});
    CommandLineInterface cli(argc, argv);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceBasicFeatures, ParseReturnsEmptyParsedCommandIfInputContainsHelpFlag)
{
    const int argc = 2;
    char* argv[] = {"program.exe", "--help"};
    const ParsedCommand expected_parsed_command("help", {}, {}, {});
    CommandLineInterface cli(argc, argv);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}