#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class UnsupportedCommand : public ComlintException
{
public:
    UnsupportedCommand(const std::string &message)
    : ComlintException("UnsupportedCommand", message)
    {}
};

} // comlint