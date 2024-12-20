#pragma once

#include <string>

#include "comlint/types.hpp"

namespace comlint {

struct FlagProperties
{
    FlagProperties(const std::string &description)
    : description{description}
    {}

    std::string description;
};

} // comlint