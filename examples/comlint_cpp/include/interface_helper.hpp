#pragma once

#include <string>
#include <map>

#include "types.hpp"
#include "command_properties.hpp"
#include "option_properties.hpp"
#include "flag_properties.hpp"

namespace comlint {

using Commands = std::map<CommandName, CommandProperties>;
using Options = std::map<OptionName, OptionProperties>;
using Flags = std::map<FlagName, FlagProperties>;

class InterfaceHelper
{
public:
    static bool IsHelpRequired(const unsigned int argc, char** argv, const bool allow_no_args);
    static std::string GetHelp(const std::string &program_name, const std::string &program_description, const Commands &commands,
                               const Options &options, const Flags &flags);
    static std::string GetHint(const std::string &similar_values);

private:
    static std::string GetHelpHeader(const std::string &program_name, const std::string &program_description);
    static std::string GetCommandsHelp(const Commands &commands);
    static std::string GetOptionsHelp(const Options &options);
    static std::string GetFlagsHelp(const Flags &flags);
};

} // comlint