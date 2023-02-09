#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class DuplicatedOption : public ComlintException
{
public:
    DuplicatedOption(const std::string &message)
    : ComlintException("DuplicatedOption", message)
    {}
};

} // comlint