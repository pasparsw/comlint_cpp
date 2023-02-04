#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class MissingCommandHandler : public ComlintException
{
public:
    MissingCommandHandler(const std::string &message)
    : ComlintException("MissingCommandHandler", message)
    {}
};

} // comlint