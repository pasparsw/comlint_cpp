#include <iomanip>
#include <sstream>

#include "interface_helper.hpp"
#include "utils.hpp"

namespace comlint {

static const std::string kHelpCommandName {"help"};
static const std::string kHelpOptionName {"-h"};
static const std::string kHelpFlagName {"--help"};
static const unsigned int kHelpElementHolderWidth {25U};

bool InterfaceHelper::IsHelpRequired(const unsigned int argc, char** argv, const bool allow_no_args)
{
    if (argc == 1U && allow_no_args) {
        return false;
    }
    else if (argc == 1U && !allow_no_args) {
        return true;
    }
    else {
        return argv[1U] == kHelpCommandName || argv[1U] == kHelpOptionName || argv[1U] == kHelpFlagName;
    }
}

std::string InterfaceHelper::GetHelp(const std::string &program_name, const std::string &program_description, const Commands &commands,
                                     const Options &options, const Flags &flags)
{
    std::stringstream help {};

    help << GetHelpHeader(program_name, program_description);
    help << GetCommandsHelp(commands);
    help << GetOptionsHelp(options);
    help << GetFlagsHelp(flags);

    return help.str();
}

std::string InterfaceHelper::GetHint(const std::string &similar_values)
{
    return similar_values.empty() ? "" : " Did you mean:\n" + similar_values;
}

std::string InterfaceHelper::GetHelpHeader(const std::string &program_name, const std::string &program_description)
{
    std::stringstream header;

    header << "Usage of " << program_name << std::endl;
    header << program_description << std::endl << std::endl;

    return header.str();
}

std::string InterfaceHelper::GetCommandsHelp(const Commands &commands)
{
    std::stringstream help;

    help << "COMMANDS:" << std::endl;

    for (const auto &[command_name, command_properties] : commands) {
        help << std::setw(kHelpElementHolderWidth) << std::left << command_name << command_properties.description << std::endl;

        if (!command_properties.allowed_values.empty()) {
            help << std::setw(kHelpElementHolderWidth) << std::left << "  allowed values" << utils::VectorToString(command_properties.allowed_values, ", ", "[", "]") << std::endl;
        }
        if (!command_properties.allowed_options.empty()) {
            help << std::setw(kHelpElementHolderWidth) << std::left << "  allowed options" << utils::VectorToString(command_properties.allowed_options, ", ", "[", "]") << std::endl;
        }
        if (!command_properties.allowed_flags.empty()) {
            help << std::setw(kHelpElementHolderWidth) << std::left << "  allowed flags" << utils::VectorToString(command_properties.allowed_flags, ", ", "[", "]") << std::endl;
        }
        if (!command_properties.required_options.empty()) {
            help << std::setw(kHelpElementHolderWidth) << std::left << "  required options" << utils::VectorToString(command_properties.required_options, ", ", "[", "]") << std::endl;
        }

        help << std::endl;
    }

    return help.str();
}

std::string InterfaceHelper::GetOptionsHelp(const Options &options)
{
    std::stringstream help;

    help << "OPTIONS:" << std::endl;

    for (const auto &[option_name, option_properties] : options) {
        help << std::setw(kHelpElementHolderWidth) << std::left << option_name << option_properties.description << std::endl;

        if (!option_properties.allowed_values.empty()) {
            help << std::setw(kHelpElementHolderWidth) << std::left << "  allowed values" << utils::VectorToString(option_properties.allowed_values, ", ", "[", "]") << std::endl;
        }
    }

    help << std::endl;

    return help.str();
}

std::string InterfaceHelper::GetFlagsHelp(const Flags &flags)
{
    std::stringstream help;
    
    help << "FLAGS:" << std::endl;

    for (const auto &[flag_name, flag_properties] : flags) {
        help << std::setw(kHelpElementHolderWidth) << std::left << flag_name << flag_properties.description << std::endl;
    }

    return help.str();
}

} // comlint