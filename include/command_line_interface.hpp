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

#include <map>

#include "export_comlint_api.hpp"
#include "interface_validator.hpp"
#include "parsed_command.hpp"
#include "command_line_element_type.hpp"
#include "interface_helper.hpp"

namespace comlint {

class PUBLIC_COMLINT_API CommandLineInterface
{
public:
    CommandLineInterface(const int argc, char** argv, const std::string &program_name = "", const std::string &description = "", const bool allow_no_arguments = true);

    /**
     * @brief Method allowing user to add a command which does not take any value.
     * @command_name: Name of the command.
     * @description: Usage help for the command.
     * @allowed_options: Optional argument to specify a list of all options which may be used together with the command. By default (empty list)
     *                   all registered options are allowed.
     * @allowed_flags: Optional argument to specify a list of flags which may be used together with the command. By default (empty list) all
     *                 registered flags are allowed.
     * @required_options: Optional argument to specify a list of options which must be used together with the command. By default (empty list)
     *                    no options are required.
     */
    void AddCommand(const CommandName &command_name, const std::string &description, const OptionNames &allowed_options = {},
                    const FlagNames &allowed_flags = {}, const OptionNames &required_options = {});
    /**
     * @brief Method allowing user to add a command which takes a value.
     * @command_name: Name of the command.
     * @description: Usage help for the command.
     * @allowed_values: List of allowed values which can be used with the command. Empty list means that all values are allowed.
     * @num_of_required_values: Number of required values for the command.
     * @allowed_options: Optional argument to specify a list of all options which may be used together with the command. By default (empty list)
     *                   all registered options are allowed.
     * @allowed_flags: Optional argument to specify a list of flags which may be used together with the command. By default (empty list) all
     *                 registered flags are allowed.
     * @required_options: Optional argument to specify a list of options which must be used together with the command. By default (empty list)
     *                    no options are required.
     */
    void AddCommand(const CommandName &command_name, const std::string &description, const unsigned int num_of_required_values,
                    const CommandValues &allowed_values = {}, const OptionNames &allowed_options = {}, const FlagNames &allowed_flags = {},
                    const OptionNames &required_options = {});
    /**
     * @brief Method allowing user to add an option.
     * @option_name: Name of the option (must be prefixed with a single dash "-").
     * @description: Usage help for the option.
     * @allowed_values: Optional argument to specify list of allowed values for the option.
     */
    void AddOption(const OptionName &option_name, const std::string &description, const OptionValues &allowed_values = {});
    /**
     * @brief: Method allowing user to add a flag.
     * @flag_name: Name of the flag (must be prefixed with a double dash "--").
     * @description: Usage help for the flag.
     */
    void AddFlag(const FlagName &flag_name, const std::string &description);
    /**
     * @brief: Method parses command line input in context of the declared interface elements (commands, options and flags).
     * @return: Structure containing parsed command and its properties.
     */
    ParsedCommand Parse() const;

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