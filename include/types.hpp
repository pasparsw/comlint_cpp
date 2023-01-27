#pragma once

#include <string>
#include <vector>

namespace comlint {

using CommandName = std::string;
using OptionName = std::string;
using FlagName = std::string;

using OptionNames = std::vector<OptionName>;
using FlagNames = std::vector<FlagName>;

using CommandValue = std::string;
using CommandValues = std::vector<CommandValue>;
using OptionValue = std::string;
using OptionValues = std::vector<OptionValue>;
using OptionsMap = std::map<OptionName, OptionValue>;
using FlagsMap = std::map<FlagName, bool>;

} // comlint