#pragma once

#include <iostream>

#include "comlint_exception.hpp"

namespace comlint {

class MissingRequiredOption : public ComlintException
{
public:
    MissingRequiredOption(const std::string &message)
    : ComlintException("MissingRequiredOption", message)
    {}
};

} // comlint