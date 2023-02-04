#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class InvalidCommandHandler : public ComlintException
{
public:
    InvalidCommandHandler(const std::string &message)
    : ComlintException("InvalidCommandHandler", message)
    {}
};

} // comlint