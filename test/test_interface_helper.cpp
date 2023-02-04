#include <gtest/gtest.h>

#include "interface_helper.hpp"

using namespace comlint;

TEST(TestInterfaceHelper, IsHelpRequiredReturnsTrueForNoArgument)
{
    const unsigned int argc = 1;
    char* argv[] = {"program.exe"};

    EXPECT_TRUE(InterfaceHelper::IsHelpRequired(argc, argv, false));
}

TEST(TestInterfaceHelper, IsHelpRequiredReturnsFalseForNoArgumentAndAllowedNoArguments)
{
    const unsigned int argc = 1;
    char* argv[] = {"program.exe"};

    EXPECT_FALSE(InterfaceHelper::IsHelpRequired(argc, argv, true));
}

TEST(TestInterfaceHelper, IsHelpRequiredReturnsTrueForHelpCommand)
{
    const unsigned int argc = 2;
    char* argv[] = {"program.exe", "help"};

    EXPECT_TRUE(InterfaceHelper::IsHelpRequired(argc, argv, false));
}

TEST(TestInterfaceHelper, IsHelpRequiredReturnsTrueForHelpOption)
{
    const unsigned int argc = 2;
    char* argv[] = {"program.exe", "-h"};

    EXPECT_TRUE(InterfaceHelper::IsHelpRequired(argc, argv, false));
}

TEST(TestInterfaceHelper, IsHelpRequiredReturnsTrueForHelpFlag)
{
    const unsigned int argc = 2;
    char* argv[] = {"program.exe", "--help"};

    EXPECT_TRUE(InterfaceHelper::IsHelpRequired(argc, argv, false));
}

TEST(TestInterfaceHelper, IsHelpRequiredReturnsFalseForOtherArguments)
{
    const unsigned int argc = 2;
    char* argv[] = {"program.exe", "some_input"};

    EXPECT_FALSE(InterfaceHelper::IsHelpRequired(argc, argv, false));
}

TEST(TestInterfaceHelper, GetHelpReturnsProperText)
{
    const std::string program_name {"SomeProgram"};
    const std::string program_description {"Some detailed description of the application"};
    const Commands commands {{"command_1", CommandProperties({"allowed_value_1", "allowed_value_2"},
                                                             {"-allowed_option_1", "-allowed_option_2"},
                                                             {"--allowed_flag_1", "--allowed_flag_2"},
                                                             "Description of command_1",
                                                             0U,
                                                             {"-allowed_option_1"})},
                             {"command_2", CommandProperties({"allowed_value_3", "allowed_value_4"},
                                                             {"-allowed_option_3", "-allowed_option_4"},
                                                             {"--allowed_flag_3", "--allowed_flag_4"},
                                                             "Description of command_2",
                                                             0U,
                                                             {})}};
    const Options options {{"-allowed_option_1", OptionProperties("Description of option 1",
                                                                  {"allowed_option_value_1", "allowed_option_value_2"},
                                                                  "")},
                           {"-allowed_option_2", OptionProperties("Description of option 2",
                                                                  {},
                                                                  "")}};
    const Flags flags {{"--allowed_flag_1", FlagProperties("Description of flag 1")},
                       {"--allowed_flag_2", FlagProperties("Description of flag 2")}};
    const std::string expected_help = "Usage of SomeProgram\n"
                                      "Some detailed description of the application\n"
                                      "\n"
                                      "COMMANDS:\n"
                                      "command_1                Description of command_1\n"
                                      "  allowed values         [allowed_value_1, allowed_value_2]\n"
                                      "  allowed options        [-allowed_option_1, -allowed_option_2]\n"
                                      "  allowed flags          [--allowed_flag_1, --allowed_flag_2]\n"
                                      "  required options       [-allowed_option_1]\n"
                                      "\n"
                                      "command_2                Description of command_2\n"
                                      "  allowed values         [allowed_value_3, allowed_value_4]\n"
                                      "  allowed options        [-allowed_option_3, -allowed_option_4]\n"
                                      "  allowed flags          [--allowed_flag_3, --allowed_flag_4]\n"
                                      "\n"
                                      "OPTIONS:\n"
                                      "-allowed_option_1        Description of option 1\n"
                                      "  allowed values         [allowed_option_value_1, allowed_option_value_2]\n"
                                      "-allowed_option_2        Description of option 2\n"
                                      "\n"
                                      "FLAGS:\n"
                                      "--allowed_flag_1         Description of flag 1\n"
                                      "--allowed_flag_2         Description of flag 2\n";
    
    const std::string help = InterfaceHelper::GetHelp(program_name, program_description, commands, options, flags);

    EXPECT_EQ(help, expected_help);
}