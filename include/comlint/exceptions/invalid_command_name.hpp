#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class InvalidCommandName : public ComlintException
{
public:
    InvalidCommandName(const std::string &message)
    : ComlintException("InvalidCommandName", message)
    {}
};

} // comlint