#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class InvalidFlagName : public ComlintException
{
public:
    InvalidFlagName(const std::string &message)
    : ComlintException("InvalidFlagName", message)
    {}
};

} // comlint