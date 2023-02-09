#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class DuplicatedCommand : public ComlintException
{
public:
    DuplicatedCommand(const std::string &message)
    : ComlintException("DuplicatedCommand", message)
    {}
};

} // comlint