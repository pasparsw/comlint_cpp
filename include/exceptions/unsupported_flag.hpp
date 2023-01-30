#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class UnsupportedFlag : public ComlintException
{
public:
    UnsupportedFlag(const std::string &message)
    : ComlintException("UnsupportedFlag", message)
    {}
};

} // comlint