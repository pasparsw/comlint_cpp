#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class DuplicatedFlag : public ComlintException
{
public:
    DuplicatedFlag(const std::string &message)
    : ComlintException("DuplicatedFlag", message)
    {}
};

} // comlint