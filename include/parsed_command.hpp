#pragma once

#include <map>

#include "types.hpp"

namespace cli {

struct ParsedCommand
{
    ParsedCommand()
    : name{},
      values{},
      options{},
      flags{}
    {}
    ParsedCommand(const CommandName &name, const CommandValues &values, const OptionsMap &options, const FlagsMap &flags)
    : name{name},
      values{values},
      options{options},
      flags{flags}
    {}

    bool IsOptionUsed(const OptionName &option_name) const { return options.find(option_name) != options.end(); }
    bool IsFlagUsed(const FlagName &flag_name) const { return flags.find(flag_name) != flags.end(); }

    CommandName name;
    CommandValues values;
    OptionsMap options;
    FlagsMap flags;
};

} // cli