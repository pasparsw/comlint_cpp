#pragma once

#include <string>
#include <vector>

namespace cli {

using CommandName = std::string;
using OptionName = std::string;
using FlagName = std::string;

using OptionNames = std::vector<OptionName>;
using FlagNames = std::vector<FlagName>;

using CommandValues = std::vector<std::string>;
using OptionValues = std::vector<std::string>;

} // cli