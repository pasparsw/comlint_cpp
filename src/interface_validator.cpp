#include "interface_validator.hpp"
#include <iostream>
namespace cli {

static const std::string kOptionPrefix {"-"};
static const std::string kFlagPrefix {"--"};

bool InterfaceValidator::IsCommandNameValid(const CommandName &command_name)
{
    return !command_name.empty() && std::string(1U, command_name.at(0U)) != kOptionPrefix && 
           (command_name.size() > 1U ? command_name.substr(0U, 2U) != kFlagPrefix : true);
}

bool InterfaceValidator::IsOptionNameValid(const OptionName &option_name)
{
    return !option_name.empty() && option_name.size() > 1U && std::string(1U, option_name.at(0U)) == kOptionPrefix &&
           option_name.substr(0U, 2U) != kFlagPrefix;
}

bool InterfaceValidator::IsFlagNameValid(const FlagName &flag_name)
{
    return !flag_name.empty() && flag_name.size() > 2U && flag_name.substr(0U, 2U) == kFlagPrefix;
}

} // cli