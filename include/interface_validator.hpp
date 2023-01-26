#pragma once

#include <map>

#include "types.hpp"

namespace cli {

class InterfaceValidator
{
public:
    static bool IsCommandNameValid(const CommandName &command_name);
    static bool IsOptionNameValid(const OptionName &option_name);
    static bool IsFlagNameValid(const FlagName &flag_name);
};

} // cli