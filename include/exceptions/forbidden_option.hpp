#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class ForbiddenOption : public ComlintException
{
public:
    ForbiddenOption(const std::string &message)
    : ComlintException("ForbiddenOption", message)
    {}
};

} // comlint