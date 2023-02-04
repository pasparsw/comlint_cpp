#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class ForbiddenOptionValue : public ComlintException
{
public:
    ForbiddenOptionValue(const std::string &message)
    : ComlintException("ForbiddenOptionValue", message)
    {}
};

} // comlint