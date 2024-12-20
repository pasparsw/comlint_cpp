/**
 * Class allowing user to create their own custom command line interfaces which are designed around commands. There are 3 types
 * of interface building blocks which may be added by the user:
 *   - command - keyword specifying an action which should be executed. Command is always placed after executable name and is a
 *               word without any particular prefix or sufix. Command may or may not take a value which details its behavior.
 *               Scheme of usage of command without value:
 *                                      program_name [command_name]
 *               Scheme of usage of command taking value:
 *                                      program_name [command_name] [command_value]
 *               Example of usage of command without value, where "pull" is a command name:
 *                                      git pull
 *               Example of usage of command taking value, where "add" is a command name and "/some/file.txt" is a command value:
 *                                      git add /some/file.txt
 *   - option - keyword providing additional information for the command execution. It is always prefixed with a single dash "-"
 *              and always takes a value.
 *              Scheme of usage of command with a single option:
 *                                      program_name [command_name] [option_name] [option_value]
 *              Scheme of usage of command with multiple options:
 *                                      program_name [command_name] [option_name_1] [option_value_1] [option_name_2] [option_value_2]
 *              Example of usage of command with an option, where "install" is a command name, "-r" is option name and "requirements.txt"
 *              is option value:
 *                                      pip install -r requirements.txt
 *   - flag - keyword enabling or disabling some functionalities during command execution. It is always prefixed with a double dash "--"
 *            and never takes any value.
 *            Scheme of usage of command with a single flag:
 *                                      program_name [command_name] [flag]
 *            Example of usage of command with a single flag, where "pull" is a command name and "--rebase" is a flag:
 *                                      git pull --rebase
 */

#pragma once

#include <functional>

#include "comlint/export_comlint_api.hpp"
#include "comlint/interface_validator.hpp"
#include "comlint/parsed_command.hpp"
#include "comlint/command_line_element_type.hpp"
#include "comlint/interface_helper.hpp"

namespace comlint {

class CommandLineInterface
{
public:
    /**
     * @brief Constructor.
     * @argc: argc from main function.
     * @argv: argv from main function.
     * @program_name: Program name which should be displayed in help prompt.
     * @description: Program description which should be displayed in help prompt.
     * @allow_no_arguments: Setting to true means that program may be ran without providing any command line arguments. Setting to false means that at least
     *                      one command line argument must be provided (otherwise, the help prompt will be displayed).
     */
    PUBLIC_COMLINT_API CommandLineInterface(const int argc, char** argv, const std::string &program_name = "", const std::string &description = "", const bool allow_no_arguments = true);

    /**
     * @brief Method allowing user to add a command which does not take any value.
     * @command_name: Name of the command.
     * @description: Usage help for the command.
     * @allowed_options: Optional argument to specify a list of all options which may be used together with the command. By default (empty list)
     *                   no options are allowed.
     * @allowed_flags: Optional argument to specify a list of flags which may be used together with the command. By default (empty list) no
     *                 flags are allowed.
     * @required_options: Optional argument to specify a list of options which must be used together with the command. By default (empty list)
     *                    no options are required.
     */
    PUBLIC_COMLINT_API void AddCommand(const CommandName &command_name, const std::string &description, const OptionNames &allowed_options = NONE,
                                       const FlagNames &allowed_flags = NONE, const OptionNames &required_options = NONE);
    /**
     * @brief Method allowing user to add a command which takes a value.
     * @command_name: Name of the command.
     * @description: Usage help for the command.
     * @num_of_required_values: Number of required values for the command.
     * @allowed_values: List of allowed values which can be used with the command. By default (empty list) all values are allowed.
     * @allowed_options: Optional argument to specify a list of all options which may be used together with the command. By default (empty list)
     *                   no options are allowed.
     * @allowed_flags: Optional argument to specify a list of flags which may be used together with the command. By default (empty list) no
     *                 flags are allowed.
     * @required_options: Optional argument to specify a list of options which must be used together with the command. By default (empty list)
     *                    no options are required.
     */
    PUBLIC_COMLINT_API void AddCommand(const CommandName &command_name, const std::string &description, const unsigned int num_of_required_values,
                                       const CommandValues &allowed_values = ANY, const OptionNames &allowed_options = NONE, const FlagNames &allowed_flags = NONE,
                                       const OptionNames &required_options = NONE);
    /**
     * @brief Method allowing user to add an option.
     * @option_name: Name of the option (must be prefixed with a single dash "-").
     * @description: Usage help for the option.
     * @allowed_values: Optional argument to specify list of allowed values for the option. By default (empty list) any values are allowed.
     */
    PUBLIC_COMLINT_API void AddOption(const OptionName &option_name, const std::string &description, const OptionValues &allowed_values = ANY);
    /**
     * @brief: Method allowing user to add a flag.
     * @flag_name: Name of the flag (must be prefixed with a double dash "--").
     * @description: Usage help for the flag.
     */
    PUBLIC_COMLINT_API void AddFlag(const FlagName &flag_name, const std::string &description);
    /**
     * @brief: Method parses command line input in context of the declared interface elements (commands, options and flags).
     * @return: Structure containing parsed command and its properties.
     */
    PUBLIC_COMLINT_API ParsedCommand Parse() const;
    /**
     * @brief Method allowing user to register a command handler for the given command name.
     * @command_name: Name of the command.
     * @command_handler: Object containing implementation of all the logic which should be perfomred when specific command is used.
     */
    PUBLIC_COMLINT_API void AddCommandHandler(const CommandName &command_name, CommandHandlerPtr command_handler);
    /**
     * @brief Automatically runs command handler for the corresponding command which was provided by the user in the command line.
     */
    PUBLIC_COMLINT_API void Run();

private:
    CommandLineElementType GetCommandLineElementType(const std::string &input, const unsigned int element_position_index) const;
    CommandValues ParseCommand(const CommandName &command_name, const unsigned int command_index) const;
    std::pair<OptionName, OptionValue> ParseOption(const CommandName &command_name, const OptionName &option_name,
                                                   const unsigned int option_index) const;
    FlagName ParseFlag(const CommandName &command_name, const FlagName &flag_name, const unsigned int flag_index) const;

    const unsigned int argc_;
    char** argv_;
    std::string program_name_;
    std::string description_;
    bool allow_no_arguments_;
    Commands interface_commands_;
    Options interface_options_;
    Flags interface_flags_;
};

} // comlint