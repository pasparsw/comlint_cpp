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
#include "exceptions/invalid_command_handler.hpp"
#include "exceptions/missing_command_handler.hpp"
#include "exceptions/invalid_command_name.hpp"
#include "exceptions/duplicated_command.hpp"
#include "exceptions/invalid_option_name.hpp"
#include "exceptions/duplicated_option.hpp"
#include "exceptions/invalid_flag_name.hpp"
#include "exceptions/duplicated_flag.hpp"
#include "mock_command_handler.hpp"

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
    const FlagNames allowed_flags = NONE;
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
    char* argv[] = {"program.exe", "command_2", "-option_1", "option_value"};
    CommandLineInterface cli(argc, argv);

    const OptionNames command_1_allowed_options {"-option_1"};

    cli.AddCommand("command_1", "Some command 1", command_1_allowed_options);
    cli.AddCommand("command_2", "Some command 2");

    cli.AddOption("-option_1", "Some option 1");

    EXPECT_THROW(cli.Parse(), ForbiddenOption);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsForbiddenOptionForSpecifiedAllowedOptions)
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
    char* argv[] = {"program.exe", "command", "--flag_1"};
    CommandLineInterface cli(argc, argv);

    cli.AddCommand("command", "Some command");
    cli.AddFlag("--flag_1", "Some flag 1");

    EXPECT_THROW(cli.Parse(), ForbiddenFlag);
}

TEST(TestCommandLineInterfaceNegativeCases, ParseThrowsForbiddenFlagForSpecifiedAllowedFlags)
{
    const int argc = 3;
    char* argv[] = {"program.exe", "command", "--flag_2"};
    CommandLineInterface cli(argc, argv);

    const OptionNames allowed_options = NONE;
    const FlagNames allowed_flags {"--flag_1"};

    cli.AddCommand("command", "Some command", allowed_options, allowed_flags);

    cli.AddFlag("--flag_1", "Some flag 1");
    cli.AddFlag("--flag_2", "Some flag 2");

    EXPECT_THROW(cli.Parse(), ForbiddenFlag);
}

TEST(TestCommandLineInterfaceNegativeCases, AddCommandHandlerThrowsUnsupportedCommand)
{
    const int argc = 1;
    char* argv[] = {"program.exe"};
    CommandLineInterface cli(argc, argv);

    cli.AddCommand("command", "Some command");

    EXPECT_THROW(cli.AddCommandHandler("unsupported_command", nullptr), UnsupportedCommand);
}

TEST(TestCommandLineInterfaceNegativeCases, AddCommandHandlerThrowsInvalidCommandHandler)
{
    const int argc = 1;
    char* argv[] = {"program.exe"};
    CommandLineInterface cli(argc, argv);

    cli.AddCommand("command", "Some command");

    EXPECT_THROW(cli.AddCommandHandler("command", nullptr), InvalidCommandHandler);
}

TEST(TestCommandLineInterfaceNegativeCases, AddCommandHandlerThrowsMissingCommandHandler)
{
    const int argc = 2;
    char* argv[] = {"program.exe", "command_2"};
    CommandLineInterface cli(argc, argv);

    cli.AddCommand("command_1", "Some command 1");
    cli.AddCommand("command_2", "Some command 2");

    CommandHandlerPtr command_1_handler = std::make_shared<MockCommandHandler>();

    cli.AddCommandHandler("command_1", command_1_handler);

    EXPECT_THROW(cli.Run(), MissingCommandHandler);
}

TEST(TestCommandLineInterfaceNegativeCases, AddCommandThrowsInvalidCommandName)
{
    const int argc = 2;
    char* argv[] = {"program.exe"};
    CommandLineInterface cli(argc, argv);

    EXPECT_THROW(cli.AddCommand("-command", "Some command"), InvalidCommandName);
}

TEST(TestCommandLineInterfaceNegativeCases, AddCommandThrowsDuplicatedCommand)
{
    const int argc = 2;
    char* argv[] = {"program.exe"};
    CommandLineInterface cli(argc, argv);

    cli.AddCommand("command", "Some command");

    EXPECT_THROW(cli.AddCommand("command", "Some command"), DuplicatedCommand);
}

TEST(TestCommandLineInterfaceNegativeCases, AddOptionThrowsInvalidOptionName)
{
    const int argc = 2;
    char* argv[] = {"program.exe"};
    CommandLineInterface cli(argc, argv);

    EXPECT_THROW(cli.AddOption("option", "Some option"), InvalidOptionName);
}

TEST(TestCommandLineInterfaceNegativeCases, AddOptionThrowsDuplicatedOption)
{
    const int argc = 2;
    char* argv[] = {"program.exe"};
    CommandLineInterface cli(argc, argv);

    cli.AddOption("-option", "Some option");

    EXPECT_THROW(cli.AddOption("-option", "Some option"), DuplicatedOption);
}

TEST(TestCommandLineInterfaceNegativeCases, AddFlagThrowsInvalidFlagName)
{
    const int argc = 2;
    char* argv[] = {"program.exe"};
    CommandLineInterface cli(argc, argv);

    EXPECT_THROW(cli.AddFlag("flag", "Some flag"), InvalidFlagName);
}

TEST(TestCommandLineInterfaceNegativeCases, AddFlagThrowsDuplicatedFlag)
{
    const int argc = 2;
    char* argv[] = {"program.exe"};
    CommandLineInterface cli(argc, argv);

    cli.AddFlag("--flag", "Some flag");

    EXPECT_THROW(cli.AddFlag("--flag", "Some flag"), DuplicatedFlag);
}