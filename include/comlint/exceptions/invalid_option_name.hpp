#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class InvalidOptionName : public ComlintException
{
public:
    InvalidOptionName(const std::string &message)
    : ComlintException("InvalidOptionName", message)
    {}
};

} // comlint