#pragma once

#include <map>

#include "types.hpp"

namespace comlint {

struct ParsedCommand
{
    ParsedCommand();
    ParsedCommand(const CommandName &name, const CommandValues &values, const OptionsMap &options, const FlagsMap &flags);

    bool IsOptionUsed(const OptionName &option_name) const;

    CommandName name;
    CommandValues values;
    OptionsMap options;
    FlagsMap flags;
};

bool operator==(const ParsedCommand &lhs, const ParsedCommand &rhs);

} // comlint