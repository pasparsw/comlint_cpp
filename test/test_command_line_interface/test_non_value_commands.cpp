#include <gtest/gtest.h>

#include "comlint/command_line_interface.hpp"

using namespace comlint;

TEST(TestCommandLineInterfaceNonValueCommands, CommandWithDefaultProperties)
{
    const int argc = 2;
    char program_name[] = "program.exe";
    char open[] = "open";
    char* argv[] = {program_name, open};
    CommandLineInterface cli(argc, argv);
    const ParsedCommand expected_parsed_command("open", {}, {}, {});

    cli.AddCommand("open", "Command to open file");

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceNonValueCommands, CommandWithOneAllowedOption)
{
    const int argc = 2;
    char program_name[] = "program.exe";
    char open[] = "open";
    char* argv[] = {program_name, open};

    const CommandName expected_command_name {"open"};
    const CommandValues expected_command_values {};
    const OptionsMap expected_options {};
    const FlagsMap expected_flags {};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);
    const OptionNames allowed_options {"-allowed_option"};

    cli.AddCommand("open", "Command to open file", allowed_options);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceNonValueCommands, CommandWithCoupleAllowedOptionsAndFlags)
{
    const int argc = 2;
    char program_name[] = "program.exe";
    char open[] = "open";
    char* argv[] = {program_name, open};

    const CommandName expected_command_name {"open"};
    const CommandValues expected_command_values {};
    const OptionsMap expected_options {};
    const FlagsMap expected_flags {};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);
    const OptionNames allowed_options {"-allowed_option"};
    const FlagNames allowed_flags {"--allowed_flag"};

    cli.AddCommand("open", "Command to open file", allowed_options, allowed_flags);

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceNonValueCommands, CommandWithOneRequiredOption)
{
    const int argc = 4;
    char program_name[] = "program.exe";
    char open[] = "open";
    char required_option[] = "-required_option";
    char required_option_value[] = "required_option_value";
    char* argv[] = {program_name, open, required_option, required_option_value};

    const CommandName expected_command_name {"open"};
    const CommandValues expected_command_values {};
    const OptionsMap expected_options {{"-required_option", "required_option_value"}};
    const FlagsMap expected_flags {};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);
    const OptionNames allowed_options {"-required_option"};
    const FlagNames allowed_flags = NONE;
    const OptionNames required_options {"-required_option"};

    cli.AddCommand("open", "Command to open file", allowed_options, allowed_flags, required_options);
    cli.AddOption("-required_option", "Some required option");

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}

TEST(TestCommandLineInterfaceNonValueCommands, Combo)
{
    const int argc = 8;
    char program_name[] = "program.exe";
    char open[] = "open";
    char option_a[] = "-a";
    char option_a_value[] = "12";
    char option_c[] = "-c";
    char option_c_value[] = "some_string";
    char flag_1[] = "--flag_1";
    char flag_2[] = "--flag_2";
    char* argv[] = {program_name, open, option_a, option_a_value, option_c, option_c_value, flag_1, flag_2};

    const CommandName expected_command_name {"open"};
    const CommandValues expected_command_values {};
    const OptionsMap expected_options {{"-a", "12"},
                                       {"-c", "some_string"}};
    const FlagsMap expected_flags {{"--flag_1", true},
                                   {"--flag_2", true},
                                   {"--flag_3", false}};
    const ParsedCommand expected_parsed_command(expected_command_name, expected_command_values, expected_options, expected_flags);

    CommandLineInterface cli(argc, argv);
    const OptionNames allowed_options {"-a", "-b", "-c"};
    const FlagNames allowed_flags {"--flag_1", "--flag_2", "--flag_3"};
    const OptionNames required_options {"-a"};

    cli.AddCommand("open", "Command to open file", allowed_options, allowed_flags, required_options);

    cli.AddOption("-a", "Some required option");
    cli.AddOption("-b", "Some allowed option");
    cli.AddOption("-c", "Some other allowed option");

    cli.AddFlag("--flag_1", "Some flag 1");
    cli.AddFlag("--flag_2", "Some flag 2");
    cli.AddFlag("--flag_3", "Some flag 3");

    const ParsedCommand parsed_command = cli.Parse();

    EXPECT_EQ(parsed_command, expected_parsed_command);
}