#include "parsed_command.hpp"
#include "utils.hpp"

namespace comlint {

ParsedCommand::ParsedCommand()
: name{},
  values{},
  options{},
  flags{}
{}

ParsedCommand::ParsedCommand(const CommandName &name, const CommandValues &values, const OptionsMap &options, const FlagsMap &flags)
: name{name},
  values{values},
  options{options},
  flags{flags}
{}

bool ParsedCommand::IsOptionUsed(const OptionName &option_name) const
{
    return options.find(option_name) != options.end();

}

bool operator==(const ParsedCommand &lhs, const ParsedCommand &rhs)
{
  return lhs.name == rhs.name && lhs.values == rhs.values && utils::AreMapsEqual<OptionsMap>(lhs.options, rhs.options) && utils::AreMapsEqual<FlagsMap>(lhs.flags, rhs.flags);
}

} // comlint