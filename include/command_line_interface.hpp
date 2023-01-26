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

#include "interface_validator.hpp"

namespace cli {

class CommandLineInterface
{
public:
    CommandLineInterface(const int argc, char** argv, const std::string &program_name = "", const std::string &description = "");

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
    void AddCommand(const CommandName &command_name, std::string &description, const OptionNames &allowed_options = {},
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
    void AddCommand(const CommandName &command_name, std::string &description, const CommandValues &allowed_values,
                    const unsigned int num_of_required_values, const OptionNames &allowed_options = {}, const FlagNames &allowed_flags = {},
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

private:
    bool IsCommandAlreadyAdded(const CommandName &command_name) const;
    bool IsOptionAlreadyAdded(const OptionName &option_name) const;
    bool IsFlagAlreadyAdded(const FlagName &flag_name) const;

    const int argc_;
    char** argv_;
    std::string program_name_;
    std::string description_;
    Commands interface_commands_;
    Options interface_options_;
    FlagNames interface_flags_;
};

} // cli