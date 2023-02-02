#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class MissingOptionValue : public ComlintException
{
public:
    MissingOptionValue(const std::string &message)
    : ComlintException("MissingOptionValue", message)
    {}
};

} // comlint