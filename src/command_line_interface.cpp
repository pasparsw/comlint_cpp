#include <iostream>
#include <algorithm>

#include "command_line_interface.hpp"

namespace cli {



CommandLineInterface::CommandLineInterface(const int argc, char** argv, const std::string &program_name, const std::string &description)
: argc_{argc},
  argv_{argv},
  program_name_{program_name.empty() ? argv[0] : program_name},
  description_{description}
{}

void CommandLineInterface::AddCommand(const std::string &command_name, std::string &description, const OptionNames &allowed_options,
                                      const FlagNames &allowed_flags, const OptionNames &required_options)
{
    AddCommand(command_name, description, {}, 0U, allowed_options, allowed_flags, required_options);
}

void CommandLineInterface::AddCommand(const std::string &command_name, std::string &description, const CommandValues &allowed_values,
                                      const unsigned int num_of_required_values, const OptionNames &allowed_options, const FlagNames &allowed_flags,
                                      const OptionNames &required_options)
{
    if (!InterfaceValidator::IsCommandNameValid(command_name)) {
        std::cerr << "Unable to add command " << command_name << " - command name invalid" << std::endl;
        return;
    }
    if (IsCommandAlreadyAdded(command_name)) {
        std::cerr << "Unable to add command " << command_name << " - command with the same name already added" << std::endl;
        return;
    }

    interface_commands_.insert({command_name, CommandProperties(allowed_values, allowed_options, allowed_flags, description,
                                num_of_required_values, required_options)});
}

void CommandLineInterface::AddOption(const OptionName &option_name, const std::string &description, const OptionValues &allowed_values)
{
    if (!InterfaceValidator::IsOptionNameValid(option_name)) {
        std::cerr << "Unable to add option " << option_name << " - option name invalid" << std::endl;
    }
    if (IsOptionAlreadyAdded(option_name)) {
        std::cerr << "Unable to add option " << option_name << " - option with the same name already added" << std::endl;
    }

    interface_options_.insert({option_name, allowed_values});
}

void CommandLineInterface::AddFlag(const FlagName &flag_name, const std::string &description)
{
    if (!InterfaceValidator::IsFlagNameValid(flag_name)) {
        std::cerr << "Unable to add flag " << flag_name << " - flag name invalid" << std::endl;
    }
    if (IsFlagAlreadyAdded(flag_name)) {
        std::cerr << "Unable to add flag " << flag_name << " - flag with the same name already added" << std::endl;
    }

    interface_flags_.push_back(flag_name);
}

bool CommandLineInterface::IsCommandAlreadyAdded(const CommandName &command_name) const
{
    return interface_commands_.find(command_name) != interface_commands_.end();
}

bool CommandLineInterface::IsOptionAlreadyAdded(const OptionName &option_name) const
{
    return interface_options_.find(option_name) != interface_options_.end();
}

bool CommandLineInterface::IsFlagAlreadyAdded(const FlagName &flag_name) const
{
    return std::find(interface_flags_.begin(), interface_flags_.end(), flag_name) != interface_flags_.end();
}

}