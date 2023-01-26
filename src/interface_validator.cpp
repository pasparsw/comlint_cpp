#include "interface_validator.hpp"
#include <iostream>
namespace cli {

static const char kOptionPrefix {'-'};
static const std::string kFlagPrefix {"--"};
static const unsigned int kMinCommandNameLength {1U};
static const unsigned int kMinOptionNameLength {2U};
static const unsigned int kMinFlagNameLength {3U};

bool InterfaceValidator::IsCommandNameValid(const CommandName &command_name)
{
    return command_name.size() >= kMinCommandNameLength && command_name.at(0U) != kOptionPrefix;
}

bool InterfaceValidator::IsOptionNameValid(const OptionName &option_name)
{
    return option_name.size() >= kMinOptionNameLength && option_name.at(0U) == kOptionPrefix &&
           option_name.substr(0U, 2U) != kFlagPrefix;
}

bool InterfaceValidator::IsFlagNameValid(const FlagName &flag_name)
{
    return flag_name.size() >= kMinFlagNameLength && flag_name.substr(0U, 2U) == kFlagPrefix;
}

} // cli