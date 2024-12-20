#pragma once

#include <string>
#include <vector>

#include "comlint/types.hpp"
#include "comlint/command_handler_interface.hpp"

namespace comlint {

/**
 * @brief Structure representing all properties of a single command.
 */
struct CommandProperties
{
    CommandProperties(const CommandValues &allowed_values, const OptionNames &allowed_options, const FlagNames &allowed_flags,
                      const std::string &description, const unsigned int num_of_required_values, const OptionNames &required_options ={})
    : allowed_values{allowed_values},
      allowed_options{allowed_options},
      allowed_flags{allowed_flags},
      description{description},
      num_of_required_values{num_of_required_values},
      required_options{required_options},
      command_handler{nullptr}
    {}

    bool RequiresValue() const { return num_of_required_values > 0U; }

    CommandValues allowed_values;
    OptionNames allowed_options;
    FlagNames allowed_flags;
    std::string description;
    unsigned int num_of_required_values;
    OptionNames required_options;
    CommandHandlerPtr command_handler;
};

} // comlint