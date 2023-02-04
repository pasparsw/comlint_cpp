#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class UnsupportedCommandValue : public ComlintException
{
public:
    UnsupportedCommandValue(const std::string &message)
    : ComlintException("UnsupportedCommandValue", message)
    {}
};

} // comlint