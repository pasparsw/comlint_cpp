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
    CommandLineInterface cli(argc, argv);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, ParsedCommand());
}

TEST(TestCommandLineInterfaceBasicFeatures, ParseReturnsEmptyParsedCommandIfInputContainsHelpOption)
{
    const int argc = 2;
    char* argv[] = {"program.exe", "-h"};
    CommandLineInterface cli(argc, argv);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, ParsedCommand());
}

TEST(TestCommandLineInterfaceBasicFeatures, ParseReturnsEmptyParsedCommandIfInputContainsHelpFlag)
{
    const int argc = 2;
    char* argv[] = {"program.exe", "--help"};
    CommandLineInterface cli(argc, argv);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, ParsedCommand());
}