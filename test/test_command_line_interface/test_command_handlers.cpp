#include <gtest/gtest.h>

#include "comlint/command_line_interface.hpp"
#include "mock_command_handler.hpp"

using namespace comlint;

TEST(TestCommandLineInterfaceCommandHandlers, ProperCommandHandlerIsRan)
{
    using ::testing::_;

    const int argc = 2;
    char program_name[] = "program.exe";
    char command[] = "command_2";
    char* argv[] = {program_name, command};
    CommandLineInterface cli(argc, argv);

    std::shared_ptr<MockCommandHandler> command_1_handler = std::make_shared<MockCommandHandler>();
    std::shared_ptr<MockCommandHandler> command_2_handler = std::make_shared<MockCommandHandler>();
    std::shared_ptr<MockCommandHandler> command_3_handler = std::make_shared<MockCommandHandler>();

    cli.AddCommand("command_1", "Some command 1");
    cli.AddCommand("command_2", "Some command 2");
    cli.AddCommand("command_3", "Some command 3");

    cli.AddCommandHandler("command_1", command_1_handler);
    cli.AddCommandHandler("command_2", command_2_handler);
    cli.AddCommandHandler("command_3", command_3_handler);

    EXPECT_CALL(*command_2_handler, Run(_)).Times(1);

    cli.Run();
}

TEST(TestCommandLineInterfaceCommandHandlers, ProperCommandHandlerIsRanWithProperArguments)
{
    const int argc = 10;
    char program_name[] = "program.exe";
    char command[] = "command_2";
    char value_1[] = "value_1";
    char value_2[] = "value_2";
    char option_1[] = "-option_1";
    char option_1_value[] = "option_value_1";
    char option_2[] = "-option_2";
    char option_2_value[] = "option_value_2";
    char flag_1[] = "--flag_1";
    char flag_2[] = "--flag_2";
    char* argv[] = {program_name, command, value_1, value_2, option_1, option_1_value,
                    option_2, option_2_value, flag_1, flag_2};
    CommandLineInterface cli(argc, argv);

    std::shared_ptr<MockCommandHandler> command_1_handler = std::make_shared<MockCommandHandler>();
    std::shared_ptr<MockCommandHandler> command_2_handler = std::make_shared<MockCommandHandler>();
    std::shared_ptr<MockCommandHandler> command_3_handler = std::make_shared<MockCommandHandler>();

    const CommandValues expected_command_values {"value_1", "value_2"};
    const OptionsMap expected_options {{"-option_1", "option_value_1"},
                                       {"-option_2", "option_value_2"}};
    const FlagsMap expected_flags {{"--flag_1", true},
                                   {"--flag_2", true},
                                   {"--flag_3", false}};
    const ParsedCommand expected_parsed_command("command_2", expected_command_values, expected_options, expected_flags);

    cli.AddCommand("command_1", "Some command 1", {"-option_1", "-option_2"}, {"--flag_1", "--flag_2", "--flag_3"});
    cli.AddCommand("command_2", "Some command 2", 2U, {}, {"-option_1", "-option_2"}, {"--flag_1", "--flag_2", "--flag_3"});
    cli.AddCommand("command_3", "Some command 3", {"-option_1", "-option_2"}, {"--flag_1", "--flag_2", "--flag_3"});

    cli.AddOption("-option_1", "Some option 1");
    cli.AddOption("-option_2", "Some option 2");

    cli.AddFlag("--flag_1", "Some flag 1");
    cli.AddFlag("--flag_2", "Some flag 2");
    cli.AddFlag("--flag_3", "Some flag 3");

    cli.AddCommandHandler("command_1", command_1_handler);
    cli.AddCommandHandler("command_2", command_2_handler);
    cli.AddCommandHandler("command_3", command_3_handler);

    EXPECT_CALL(*command_2_handler, Run(expected_parsed_command)).Times(1);

    cli.Run();
}