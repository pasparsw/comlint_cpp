#include <gtest/gtest.h>

#include "command_line_interface.hpp"

using namespace comlint;

TEST(TestCommandLineInterfaceSingleValueCommands, CommandAcceptingAnyValue)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "open", "/some/file.txt"};
    const ParsedCommand expected_parsed_command("open", {"/some/file.txt"}, {}, {});

    CommandLineInterface cli(argc, argv);
    const CommandValues allowed_values {};
    const unsigned int num_of_req_command_values {1U};

    cli.AddCommand("open", "Command to open file", allowed_values, num_of_req_command_values);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceSingleValueCommands, CommandAceptingPredefinedValues)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "open", "file"};
    const ParsedCommand expected_parsed_command("open", {"file"}, {}, {});

    CommandLineInterface cli(argc, argv);
    const CommandValues allowed_values {"file", "application"};
    const unsigned int num_of_req_command_values {1U};

    cli.AddCommand("open", "Command to open file", allowed_values, num_of_req_command_values);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceSingleValueCommands, CommandWithOneAllowedOption)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "open", "/some/file.txt"};

    const CommandName expected_command_name {"open"};
    const CommandValues expected_command_values {"/some/file.txt"};
    const OptionsMap expected_options {};
    const FlagsMap expected_flags {};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);
    const CommandValues allowed_values {};
    const unsigned int num_of_req_command_values {1U};
    const OptionNames allowed_options {"-allowed_option"};

    cli.AddCommand("open", "Command to open file", {}, num_of_req_command_values, allowed_options);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceSingleValueCommands, CommandWithCoupleAllowedOptionsAndFlags)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "open", "/some/file.txt"};

    const CommandName expected_command_name {"open"};
    const CommandValues expected_command_values {"/some/file.txt"};
    const OptionsMap expected_options {};
    const FlagsMap expected_flags {};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);
    const CommandValues allowed_values {};
    const unsigned int num_of_req_command_values {1U};
    const OptionNames allowed_options {"-allowed_option"};
    const FlagNames allowed_flags {"--allowed_flag"};

    cli.AddCommand("open", "Command to open file", allowed_values, num_of_req_command_values, allowed_options, allowed_flags);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceSingleValueCommands, CommandWithOneRequiredOption)
{
    const int argc = 5;
    char* argv[] = {"program.exe", "open", "/some/file.txt", "-required_option", "required_option_value"};

    const CommandName expected_command_name {"open"};
    const CommandValues expected_command_values {"/some/file.txt"};
    const OptionsMap expected_options {{"-required_option", "required_option_value"}};
    const FlagsMap expected_flags {};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);
    const CommandValues allowed_values {};
    const unsigned int num_of_req_command_values {1U};
    const OptionNames allowed_options {"-required_option"};
    const FlagNames allowed_flags {};
    const OptionNames required_options {"-required_option"};

    cli.AddCommand("open", "Command to open file", allowed_values, num_of_req_command_values, allowed_options, allowed_flags, required_options);
    cli.AddOption("-required_option", "Some required option");

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceSingleValueCommands, Combo)
{
    const int argc = 9;
    char* argv[] = {"program.exe", "open", "/some/file.txt", "-a", "12", "-c", "some_string", "--flag", "--other-flag"};

    const CommandName expected_command_name {"open"};
    const CommandValues expected_command_values {"/some/file.txt"};
    const OptionsMap expected_options {{"-a", "12"},
                                       {"-c", "some_string"}};
    const FlagsMap expected_flags {{"--flag", true},
                                   {"--other-flag", true}};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);
    const CommandValues allowed_values {};
    const unsigned int num_of_req_command_values {1U};
    const OptionNames allowed_options {"-a", "-b", "-c"};
    const FlagNames allowed_flags {"--flag", "--other-flag"};
    const OptionNames required_options {"-a"};

    cli.AddCommand("open", "Command to open file", allowed_values, num_of_req_command_values, allowed_options, allowed_flags, required_options);

    cli.AddOption("-a", "Some required option");
    cli.AddOption("-b", "Some allowed option");
    cli.AddOption("-c", "Some other allowed option");

    cli.AddFlag("--flag", "Some flag");
    cli.AddFlag("--other-flag", "Some other flag");

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}