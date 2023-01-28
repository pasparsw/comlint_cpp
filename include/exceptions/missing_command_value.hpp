#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class MissingCommandValue : public ComlintException
{
public:
    MissingCommandValue(const std::string &message)
    : ComlintException("MissingCommandValue", message)
    {}
};

} // comlint