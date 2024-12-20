#include <iostream>

#include "comlint/command_line_interface.hpp"
#include "comlint/exceptions/unsupported_command.hpp"
#include "comlint/exceptions/invalid_command_position.hpp"
#include "comlint/exceptions/missing_command_value.hpp"
#include "comlint/exceptions/unsupported_command_value.hpp"
#include "comlint/exceptions/unsupported_option.hpp"
#include "comlint/exceptions/missing_option_value.hpp"
#include "comlint/exceptions/forbidden_option_value.hpp"
#include "comlint/exceptions/forbidden_option.hpp"
#include "comlint/exceptions/unsupported_flag.hpp"
#include "comlint/exceptions/forbidden_flag.hpp"
#include "comlint/exceptions/missing_required_option.hpp"
#include "comlint/exceptions/invalid_command_handler.hpp"
#include "comlint/exceptions/missing_command_handler.hpp"
#include "comlint/exceptions/invalid_command_name.hpp"
#include "comlint/exceptions/duplicated_command.hpp"
#include "comlint/exceptions/invalid_option_name.hpp"
#include "comlint/exceptions/duplicated_option.hpp"
#include "comlint/exceptions/invalid_flag_name.hpp"
#include "comlint/exceptions/duplicated_flag.hpp"
#include "comlint/utils.hpp"

namespace comlint {

static const std::string kDefaultOptionValue {""};
static const std::string kHelpCommandIndicator {"help"};

CommandLineInterface::CommandLineInterface(const int argc, char** argv, const std::string &program_name, const std::string &description, const bool allow_no_arguments)
: argc_{static_cast<unsigned int>(argc)},
  argv_{argv},
  program_name_{program_name.empty() ? argv[0] : program_name},
  description_{description},
  allow_no_arguments_{allow_no_arguments},
  interface_commands_{},
  interface_options_{},
  interface_flags_{}
{}

void CommandLineInterface::AddCommand(const std::string &command_name, const std::string &description, const OptionNames &allowed_options,
                                      const FlagNames &allowed_flags, const OptionNames &required_options)
{
    AddCommand(command_name, description, 0U, {}, allowed_options, allowed_flags, required_options);
}

void CommandLineInterface::AddCommand(const std::string &command_name, const std::string &description, const unsigned int num_of_required_values,
                                      const CommandValues &allowed_values, const OptionNames &allowed_options, const FlagNames &allowed_flags,
                                      const OptionNames &required_options)
{
    if (!InterfaceValidator::IsCommandNameValid(command_name)) {
        throw InvalidCommandName("Unable to add " + command_name + " command! Name of the command is invalid.");
    }
    if (utils::MapContainsKey(interface_commands_, command_name)) {
        throw DuplicatedCommand("Unable to add " + command_name + " command! Command with the same name is already added.");
    }

    interface_commands_.insert({command_name, CommandProperties(allowed_values, allowed_options, allowed_flags, description,
                                num_of_required_values, required_options)});
}

void CommandLineInterface::AddOption(const OptionName &option_name, const std::string &description, const OptionValues &allowed_values)
{
    if (!InterfaceValidator::IsOptionNameValid(option_name)) {
        throw InvalidOptionName("Unable to add " + option_name + " option! Name of the option is invalid.");
    }
    if (utils::MapContainsKey(interface_options_, option_name)) {
        throw DuplicatedOption("Unable to add " + option_name + " option! Option with the same name is already added.");
    }

    // TODO: implement handling of user defined default option value
    interface_options_.insert({option_name, OptionProperties(description, allowed_values, kDefaultOptionValue)});
}

void CommandLineInterface::AddFlag(const FlagName &flag_name, const std::string &description)
{
    if (!InterfaceValidator::IsFlagNameValid(flag_name)) {
        throw InvalidFlagName("Unable to add " + flag_name + " flag! Name of the flag is invalid.");
    }
    if (utils::MapContainsKey(interface_flags_, flag_name)) {
        throw DuplicatedFlag("Unable to add " + flag_name + " flag! Flag with the same name is already added.");
    }

    interface_flags_.insert({flag_name, FlagProperties(description)});
}

ParsedCommand CommandLineInterface::Parse() const
{
    if (InterfaceHelper::IsHelpRequired(argc_, argv_, allow_no_arguments_)) {
        std::cout << InterfaceHelper::GetHelp(program_name_, description_, interface_commands_, interface_options_, interface_flags_);
        return ParsedCommand(kHelpCommandIndicator, {}, {}, {});
    }

    CommandName command_name {};
    CommandValues command_values {};
    OptionsMap options {};
    FlagsMap flags {};

    for (unsigned int i=1U; i<argc_; i++) {
        const std::string element = argv_[i];
        const CommandLineElementType element_type = GetCommandLineElementType(element, i);

        if (element_type == CommandLineElementType::kCommand) {
            command_name = element;
            command_values = ParseCommand(command_name, i);
        }
        if (element_type == CommandLineElementType::kOption) {
            const std::pair<OptionName, OptionValue> option = ParseOption(command_name, element, i);
            options.insert(option);
        }
        if (element_type == CommandLineElementType::kFlag) {
            const FlagName flag = ParseFlag(command_name, element, i);
            flags.insert({flag, true});
        }
    }

    if (!command_name.empty() && utils::MapContainsKey(interface_commands_, command_name)) {
        for (const auto &required_option : interface_commands_.at(command_name).required_options) {
            if (!utils::MapContainsKey(options, required_option)) {
                throw MissingRequiredOption("Command " + command_name + " requires option " + required_option + ", but such option has not been provided!");
            }
        }
    }

    for (const auto &[flag_name, flag_properties] : interface_flags_) {
        if (!utils::MapContainsKey(flags, flag_name)) {
            flags.insert({flag_name, false});
        }
    }

    return ParsedCommand(command_name, command_values, options, flags);
}

void CommandLineInterface::AddCommandHandler(const CommandName &command_name, CommandHandlerPtr command_handler)
{
    if (!utils::MapContainsKey(interface_commands_, command_name)) {
        throw UnsupportedCommand("Unable to add command handler! Command " + command_name + " is not added to command line interface definition.");
    }
    if (!command_handler) {
        throw InvalidCommandHandler("Provided command handler for " + command_name + " command is a nullptr!");
    }

    interface_commands_.at(command_name).command_handler = command_handler;
}

void CommandLineInterface::Run()
{
    const ParsedCommand parsed_command = Parse();
    
    if (parsed_command.name == kHelpCommandIndicator) {
        return;
    }
    if (!interface_commands_.at(parsed_command.name).command_handler) {
        throw MissingCommandHandler("Unable to run command handler for " + parsed_command.name + " command! No command handler has been added for this command.");
    }

    interface_commands_.at(parsed_command.name).command_handler->Run(parsed_command);
}

CommandLineElementType CommandLineInterface::GetCommandLineElementType(const std::string &input, const unsigned int element_position_index) const
{
    if (InterfaceValidator::IsCommandNameValid(input) && element_position_index == 1U) {
        return CommandLineElementType::kCommand;
    }
    if (InterfaceValidator::IsOptionNameValid(input)) {
        return CommandLineElementType::kOption;
    }
    if (InterfaceValidator::IsFlagNameValid(input)) {
        return CommandLineElementType::kFlag;
    }

    return CommandLineElementType::kCustomValue;
}

CommandValues CommandLineInterface::ParseCommand(const CommandName &command_name, const unsigned int command_index) const
{
    if (!utils::MapContainsKey(interface_commands_, command_name)) {
        const std::string similar_commands = utils::GetSimilarKeys(interface_commands_, command_name, "\n");

        throw UnsupportedCommand("Command " + command_name + " is not supported!" + InterfaceHelper::GetHint(similar_commands));
    }
    if (command_index != 1U) {
        throw InvalidCommandPosition("Detected command " + command_name + " is not directly after program name!");
    }

    if (!interface_commands_.at(command_name).RequiresValue()) {
        return {};
    }
    else if (command_index + interface_commands_.at(command_name).num_of_required_values >= argc_ ||
             GetCommandLineElementType(argv_[command_index + 1U], command_index + 1U) == CommandLineElementType::kOption ||
             GetCommandLineElementType(argv_[command_index + 1U], command_index + 1U) == CommandLineElementType::kFlag) {
        throw MissingCommandValue("Command " + command_name + " requires " + std::to_string(interface_commands_.at(command_name).num_of_required_values) +
                                  " value(s), but they were not provided!");
    }

    CommandValues values {};

    for (unsigned int i=0U; i<interface_commands_.at(command_name).num_of_required_values; i++) {
        const CommandValue command_value = argv_[command_index + i + 1U];

        if (!interface_commands_.at(command_name).allowed_values.empty() &&
            !utils::VectorContainsElement<CommandValues>(interface_commands_.at(command_name).allowed_values, command_value)) {
            const std::string similar_values = utils::GetSimilarValues(interface_commands_.at(command_name).allowed_values, command_value, "\n");

            throw UnsupportedCommandValue("Unsupported value " + command_value + " for " + command_name + " command!" + InterfaceHelper::GetHint(similar_values));
        }

        values.push_back(argv_[command_index + i + 1U]);
    }

    return values;
}

std::pair<OptionName, OptionValue> CommandLineInterface::ParseOption(const CommandName &command_name, const OptionName &option_name,
                                                                     const unsigned int option_index) const
{
    if (!utils::MapContainsKey(interface_options_, option_name)) {
        const std::string similar_options = utils::GetSimilarKeys(interface_options_, option_name, "\n");

        throw UnsupportedOption("Option " + option_name + " is not supported!" + InterfaceHelper::GetHint(similar_options));
    }
    if (option_index + 1U >= argc_) {
        throw MissingOptionValue("Option " + option_name + " requires value, but no value has been provided!");
    }
    if (utils::MapContainsKey(interface_commands_, command_name) &&
        !utils::VectorContainsElement<CommandValues>(interface_commands_.at(command_name).allowed_options, option_name)) {
        throw ForbiddenOption("Option " + option_name + " is not allowed for " + command_name + " command!");
    }

    const OptionValue value = argv_[option_index + 1U];

    if (!interface_options_.at(option_name).allowed_values.empty() &&
        !utils::VectorContainsElement<CommandValues>(interface_options_.at(option_name).allowed_values, value)) {
        const std::string similar_values = utils::GetSimilarValues(interface_options_.at(option_name).allowed_values, value, "\n");

        throw ForbiddenOptionValue("Given value " + value + " for option " + option_name + " is not allowed!" + InterfaceHelper::GetHint(similar_values));
    }

    return std::make_pair(option_name, value);
}

FlagName CommandLineInterface::ParseFlag(const CommandName &command_name, const FlagName &flag_name, const unsigned int flag_index) const
{
    if (!utils::MapContainsKey(interface_flags_, flag_name)) {
        const std::string similar_flags = utils::GetSimilarKeys(interface_flags_, flag_name, "\n");

        throw UnsupportedFlag("Flag " + flag_name + " is not supported!" + InterfaceHelper::GetHint(similar_flags));
    }
    if (utils::MapContainsKey(interface_commands_, command_name) &&
        !utils::VectorContainsElement<CommandValues>(interface_commands_.at(command_name).allowed_flags, flag_name)) {
        throw ForbiddenFlag("Flag " + flag_name + " is not allowed for " + command_name + " command!");
    }

    return argv_[flag_index];
}

} // comlint