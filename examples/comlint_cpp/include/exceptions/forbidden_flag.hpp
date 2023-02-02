#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class ForbiddenFlag : public ComlintException
{
public:
    ForbiddenFlag(const std::string &message)
    : ComlintException("ForbiddenFlag", message)
    {}
};

} // comlint