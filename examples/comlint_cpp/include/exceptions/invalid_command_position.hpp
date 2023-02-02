#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class InvalidCommandPosition : public ComlintException
{
public:
    InvalidCommandPosition(const std::string &message)
    : ComlintException("InvalidCommandPosition", message)
    {}
};

} // comlint