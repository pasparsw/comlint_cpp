#include <gtest/gtest.h>

#include "command_line_interface.hpp"
#include "exceptions/unsupported_command.hpp"
#include "exceptions/missing_command_value.hpp"
#include "exceptions/unsupported_command_value.hpp"
#include "exceptions/unsupported_option.hpp"
#include "exceptions/missing_option_value.hpp"
#include "exceptions/forbidden_option.hpp"
#include "exceptions/forbidden_option_value.hpp"
#include "exceptions/unsupported_flag.hpp"
#include "exceptions/forbidden_flag.hpp"
#include "exceptions/missing_required_option.hpp"

using namespace comlint;

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsUnsupportedCommand)
{
    const int argc = 2;
    char* argv[] = {"program.exe", "unsupported_command"};
    CommandLineInterface cli(argc, argv);

    cli.AddCommand("supported_command", "Some supported command");

    EXPECT_THROW(cli.Parse(), UnsupportedCommand);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsMissingCommandValue)
{
    const int argc = 2;
    char* argv[] = {"program.exe", "supported_command"};
    CommandLineInterface cli(argc, argv);

    const unsigned int num_of_required_values {1U};

    cli.AddCommand("supported_command", "Some supported command", num_of_required_values);

    EXPECT_THROW(cli.Parse(), MissingCommandValue);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsMissingCommandValueWhenOptionFollowsCommand)
{
    const int argc = 4;
    char* argv[] = {"program.exe", "supported_command", "-option", "option_value"};
    CommandLineInterface cli(argc, argv);

    const unsigned int num_of_required_values {1U};

    cli.AddCommand("supported_command", "Some supported command", num_of_required_values);
    cli.AddOption("-option", "Some option");

    EXPECT_THROW(cli.Parse(), MissingCommandValue);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsMissingCommandValueWhenFlagFollowsCommand)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "supported_command", "--flag"};
    CommandLineInterface cli(argc, argv);

    const unsigned int num_of_required_values {1U};

    cli.AddCommand("supported_command", "Some supported command", num_of_required_values);
    cli.AddFlag("--flag", "Some flag");

    EXPECT_THROW(cli.Parse(), MissingCommandValue);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsUnsupportedCommandValue)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "supported_command", "unsupported_value"};
    CommandLineInterface cli(argc, argv);

    const CommandValues allowed_values {"supported_value"};
    const unsigned int num_of_required_values {1U};

    cli.AddCommand("supported_command", "Some supported command", num_of_required_values, allowed_values);

    EXPECT_THROW(cli.Parse(), UnsupportedCommandValue);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsUnsupportedOption)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "supported_command", "-unsupported_option"};
    CommandLineInterface cli(argc, argv);

    cli.AddCommand("supported_command", "Some supported command");

    EXPECT_THROW(cli.Parse(), UnsupportedOption);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsMissingRequiredOption)
{
    const int argc = 4;
    char* argv[] = {"program.exe", "supported_command", "-allowed_option", "some_value"};
    CommandLineInterface cli(argc, argv);
    const OptionNames allowed_options {"-allowed_option", "-required_option"};
    const FlagNames allowed_flags {};
    const OptionNames required_options {"-required_option"};

    cli.AddCommand("supported_command", "Some supported command", allowed_options, allowed_flags, required_options);

    cli.AddOption("-allowed_option", "Some allowed option");
    cli.AddOption("-required_option", "Some required option");

    EXPECT_THROW(cli.Parse(), MissingRequiredOption);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsMissingOptionValue)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "command", "-option_name"};
    CommandLineInterface cli(argc, argv);

    cli.AddCommand("command", "Some command");
    cli.AddOption("-option_name", "Some option");

    EXPECT_THROW(cli.Parse(), MissingOptionValue);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsForbiddenOption)
{
    const int argc = 4;
    char* argv[] = {"program.exe", "command_1", "-option_2", "option_value"};
    CommandLineInterface cli(argc, argv);

    const OptionNames command_1_allowed_options {"-option_1"};
    const OptionNames command_2_allowed_options {"-option_2"};

    cli.AddCommand("command_1", "Some command 1", command_1_allowed_options);
    cli.AddCommand("command_2", "Some command 2", command_2_allowed_options);

    cli.AddOption("-option_1", "Some option 1");
    cli.AddOption("-option_2", "Some option 2");

    EXPECT_THROW(cli.Parse(), ForbiddenOption);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsForbiddenOptionValue)
{
    const int argc = 4;
    char* argv[] = {"program.exe", "command", "-option", "forbidden_option_value"};
    CommandLineInterface cli(argc, argv);

    const OptionNames command_allowed_options {"-option"};
    const OptionValues option_allowed_values {"allowed_option_value_1", "allowed_option_value_2"};

    cli.AddCommand("command", "Some command", command_allowed_options);

    cli.AddOption("-option", "Some option", option_allowed_values);

    EXPECT_THROW(cli.Parse(), ForbiddenOptionValue);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsUnsupportedFlag)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "command", "--unsupported_flag"};
    CommandLineInterface cli(argc, argv);

    cli.AddCommand("command", "Some command");

    EXPECT_THROW(cli.Parse(), UnsupportedFlag);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsForbiddenFlag)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "command", "--flag_2"};
    CommandLineInterface cli(argc, argv);

    const OptionNames allowed_options {};
    const FlagNames allowed_flags {"--flag_1"};

    cli.AddCommand("command", "Some command", allowed_options, allowed_flags);

    cli.AddFlag("--flag_1", "Some flag 1");
    cli.AddFlag("--flag_2", "Some flag 2");

    EXPECT_THROW(cli.Parse(), ForbiddenFlag);
}