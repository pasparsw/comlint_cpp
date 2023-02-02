#pragma once

#include <map>

#include "types.hpp"

namespace comlint {

class InterfaceValidator
{
public:
    static bool IsCommandNameValid(const CommandName &command_name);
    static bool IsOptionNameValid(const OptionName &option_name);
    static bool IsFlagNameValid(const FlagName &flag_name);
};

} // comlint