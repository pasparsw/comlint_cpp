#pragma once

#include <map>

#include "types.hpp"
#include "command_properties.hpp"

namespace cli {

using Commands = std::map<CommandName, CommandProperties>;
using Options = std::map<OptionName, OptionValues>;

class InterfaceValidator
{
public:
    static bool IsCommandNameValid(const CommandName &command_name);
    static bool IsOptionNameValid(const OptionName &option_name);
    static bool IsFlagNameValid(const FlagName &flag_name);
};

} // cli