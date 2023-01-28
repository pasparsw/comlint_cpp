#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>

#include "command_line_interface.hpp"
#include "exceptions/unsupported_command.hpp"
#include "exceptions/invalid_command_position.hpp"
#include "exceptions/missing_command_value.hpp"
#include "exceptions/unsupported_command_value.hpp"
#include "exceptions/unsupported_option.hpp"
#include "exceptions/missing_option_value.hpp"
#include "exceptions/forbidden_option_value.hpp"
#include "exceptions/forbidden_option.hpp"
#include "exceptions/unsupported_flag.hpp"
#include "exceptions/forbidden_flag.hpp"

namespace comlint {

static const std::string kHelpCommandName {"help"};
static const std::string kHelpOptionName {"-h"};
static const std::string kHelpFlagName {"--help"};
static const unsigned int kHelpElementHolderWidth {25U};

CommandLineInterface::CommandLineInterface(const int argc, char** argv, const std::string &program_name, const std::string &description)
: argc_{static_cast<unsigned int>(argc)},
  argv_{argv},
  program_name_{program_name.empty() ? argv[0] : program_name},
  description_{description},
  interface_commands_{},
  interface_options_{},
  interface_flags_{}
{}

void CommandLineInterface::AddCommand(const std::string &command_name, const std::string &description, const OptionNames &allowed_options,
                                      const FlagNames &allowed_flags, const OptionNames &required_options)
{
    AddCommand(command_name, description, {}, 0U, allowed_options, allowed_flags, required_options);
}

void CommandLineInterface::AddCommand(const std::string &command_name, const std::string &description, const CommandValues &allowed_values,
                                      const unsigned int num_of_required_values, const OptionNames &allowed_options, const FlagNames &allowed_flags,
                                      const OptionNames &required_options)
{
    if (!InterfaceValidator::IsCommandNameValid(command_name)) {
        std::cerr << "Unable to add command " << command_name << " - command name invalid" << std::endl;
        return;
    }
    if (IsCommandAdded(command_name)) {
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
    if (IsOptionAdded(option_name)) {
        std::cerr << "Unable to add option " << option_name << " - option with the same name already added" << std::endl;
    }

    interface_options_.insert({option_name, allowed_values});
}

void CommandLineInterface::AddFlag(const FlagName &flag_name, const std::string &description)
{
    if (!InterfaceValidator::IsFlagNameValid(flag_name)) {
        std::cerr << "Unable to add flag " << flag_name << " - flag name invalid" << std::endl;
    }
    if (IsFlagAdded(flag_name)) {
        std::cerr << "Unable to add flag " << flag_name << " - flag with the same name already added" << std::endl;
    }

    interface_flags_.push_back(flag_name);
}

ParsedCommand CommandLineInterface::Parse() const
{
    if (argc_ == 0U || argv_[1U] == kHelpCommandName || argv_[1U] == kHelpOptionName || argv_[1U] == kHelpFlagName) {
        PrintHelp();
        return ParsedCommand();
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

    return ParsedCommand(command_name, command_values, options, flags);
}

bool CommandLineInterface::IsCommandAdded(const CommandName &command_name) const
{
    return interface_commands_.find(command_name) != interface_commands_.end();
}

bool CommandLineInterface::IsOptionAdded(const OptionName &option_name) const
{
    return interface_options_.find(option_name) != interface_options_.end();
}

bool CommandLineInterface::IsFlagAdded(const FlagName &flag_name) const
{
    return std::find(interface_flags_.begin(), interface_flags_.end(), flag_name) != interface_flags_.end();
}

CommandLineElementType CommandLineInterface::GetCommandLineElementType(const std::string &input, const unsigned int element_position_index) const
{
    if (InterfaceValidator::IsCommandNameValid(input) && argv_[element_position_index - 1U] == program_name_) {
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

    if (!IsCommandAdded(command_name)) {
        throw UnsupportedCommand("Command " + command_name + " is not supported!");
    }
    if (command_index != 1U) {
        throw InvalidCommandPosition("Detected command " + command_name + " is not directly after program name!");
    }

    if (!interface_commands_.at(command_name).RequiresValue()) {
        return {};
    }
    else if (command_index + interface_commands_.at(command_name).num_of_required_values >= argc_) {
        throw MissingCommandValue("Command " + command_name + " requires " + std::to_string(interface_commands_.at(command_name).num_of_required_values) +
                                  " value(s), but they were not provided!");
    }

    CommandValues values {};

    for (unsigned int i=0U; i<interface_commands_.at(command_name).num_of_required_values; i++) {
        const CommandValue command_value = argv_[command_index + i + 1U];

        if (!interface_commands_.at(command_name).allowed_values.empty() &&
            std::find(interface_commands_.at(command_name).allowed_values.begin(), interface_commands_.at(command_name).allowed_values.end(), command_value) == interface_commands_.at(command_name).allowed_values.end()) {
            throw UnsupportedCommandValue("Unsupported value " + command_value + " for " + command_name + " command!");
        }

        values.push_back(argv_[command_index + i + 1U]);
    }

    return values;
}

std::pair<OptionName, OptionValue> CommandLineInterface::ParseOption(const CommandName &command_name, const OptionName &option_name,
                                                                     const unsigned int option_index) const
{
    if (!IsOptionAdded(option_name)) {
        throw UnsupportedOption("Option " + option_name + " is not supported!");
    }
    if (option_index + 1U >= argc_) {
        throw MissingOptionValue("Option " + option_name + " requires value, but no value has been provided!");
    }
    if (!interface_commands_.at(command_name).allowed_options.empty() &&
        std::find(interface_commands_.at(command_name).allowed_options.begin(), interface_commands_.at(command_name).allowed_options.end(), option_name) == interface_commands_.at(command_name).allowed_options.end()) {
        throw ForbiddenOption("Option " + option_name + " is not allowed for " + command_name + " command!");
    }

    const OptionValue value = argv_[option_index + 1U];

    if (!interface_options_.at(option_name).empty() &&
        std::find(interface_options_.at(option_name).begin(), interface_options_.at(option_name).end(), value) == interface_options_.at(option_name).end()) {
        throw ForbiddenOptionValue("Given value " + value + " for option " + option_name + " is not allowed!");
    }

    return std::make_pair(option_name, value);
}

FlagName CommandLineInterface::ParseFlag(const CommandName &command_name, const FlagName &flag_name, const unsigned int flag_index) const
{
    if (!IsFlagAdded(flag_name)) {
        throw UnsupportedFlag("Flag " + flag_name + " is not supported!");
    }
    if (!interface_commands_.at(command_name).allowed_flags.empty() &&
        std::find(interface_commands_.at(command_name).allowed_flags.begin(), interface_commands_.at(command_name).allowed_flags.end(), flag_name) == interface_commands_.at(command_name).allowed_flags.end()) {
        throw ForbiddenFlag("Flag " + flag_name + " is not allowed for " + command_name + " command!");
    }

    return argv_[flag_index];
}

void CommandLineInterface::PrintHelp() const
{
    std::cout << "Usage of " << program_name_ << std::endl;
    std::cout << description_ << std::endl << std::endl;

    for (const auto &[command_name, command_properties] : interface_commands_) {
        std::cout << std::setw(kHelpElementHolderWidth) << std::left << command_name << ":" << command_properties.description << std::endl;

        if (!command_properties.allowed_values.empty()) {
            std::cout << std::setw(kHelpElementHolderWidth) << std::left << "allowed values: " << VectorToString(command_properties.allowed_values) << std::endl;
        }
        if (!command_properties.allowed_options.empty()) {
            std::cout << std::setw(kHelpElementHolderWidth) << std::left << "allowed options: " << VectorToString(command_properties.allowed_options) << std::endl;
        }
        if (!command_properties.allowed_flags.empty()) {
            std::cout << std::setw(kHelpElementHolderWidth) << std::left << "allowed flags: " << VectorToString(command_properties.allowed_flags) << std::endl;
        }
        if (!command_properties.required_options.empty()) {
            std::cout << std::setw(kHelpElementHolderWidth) << std::left << "required options: " << VectorToString(command_properties.required_options) << std::endl;
        }

        std::cout << std::endl << std::endl;
    }

    std::cout << std::endl;
}

std::string CommandLineInterface::VectorToString(const std::vector<std::string> &vector) const
{
    const std::string text = std::accumulate(vector.begin(), vector.end(), std::string(), [](const std::string &a, const std::string &b){
        return a + (a.size() > 0U ? ", " : "") + b;
    });

    return "[" + text + "]";
}

} // comlint