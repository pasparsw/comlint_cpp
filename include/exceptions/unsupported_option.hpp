#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class UnsupportedOption : public ComlintException
{
public:
    UnsupportedOption(const std::string &message)
    : ComlintException("UnsupportedOption", message)
    {}
};

} // comlint