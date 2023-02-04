#pragma once

#include <string>

#include "types.hpp"

namespace comlint {

struct OptionProperties
{
    OptionProperties(const std::string &description, const OptionValues &allowed_values, const OptionValue &default_value)
    : description{description},
      allowed_values{allowed_values},
      default_value{default_value}
    {}

    std::string description;
    OptionValues allowed_values;
    OptionValue default_value;
};

} // comlint