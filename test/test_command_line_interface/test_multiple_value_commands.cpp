#include <gtest/gtest.h>

#include "command_line_interface.hpp"

using namespace comlint;

TEST(TestCommandLineInterfaceMultipleValuesCommands, CommandAcceptingAnyTwoValues)
{
    const int argc = 4;
    char* argv[] = {"program.exe", "copy", "/dst/from", "/dst/to"};
    const ParsedCommand expected_parsed_command("copy", {"/dst/from", "/dst/to"}, {}, {});

    CommandLineInterface cli(argc, argv);
    const CommandValues allowed_values {};
    const unsigned int num_of_req_command_values {2U};

    cli.AddCommand("copy", "Command to copy folders", allowed_values, num_of_req_command_values);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceMultipleValuesCommands, CommandAcceptingPredefinedTwoValues)
{
    const int argc = 4;
    char* argv[] = {"program.exe", "list_files", "txt", "pdf"};
    const ParsedCommand expected_parsed_command("list_files", {"txt", "pdf"}, {}, {});

    CommandLineInterface cli(argc, argv);
    const CommandValues allowed_values {"txt", "pdf", "zip", "jpg", "gif"};
    const unsigned int num_of_req_command_values {2U};

    cli.AddCommand("list_files", "Command to list all files of a given type (max two types allowed)", allowed_values, num_of_req_command_values);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}