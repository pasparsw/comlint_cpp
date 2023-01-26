#pragma once

#include <string>
#include <vector>

#include "types.hpp"

namespace cli {

/**
 * @brief Structure representing all properties of a single command.
 */
struct CommandProperties
{
public:
    CommandProperties(const CommandValues &allowed_values, const OptionNames &allowed_options, const FlagNames &allowed_flags,
                      const std::string &description, const unsigned int num_of_required_values, const OptionNames &required_options ={})
    : command_values{command_values},
      allowed_options{allowed_options},
      allowed_flags{allowed_flags},
      description{description},
      num_of_required_values{num_of_required_values},
      required_options{required_options}
    {}

    bool RequiresValue() const { return num_of_required_values > 0U; }

    CommandValues command_values;
    OptionNames allowed_options;
    FlagNames allowed_flags;
    std::string description;
    unsigned int num_of_required_values;
    OptionNames required_options;
};

}