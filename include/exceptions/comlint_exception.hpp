#pragma once

#include <iostream>

namespace comlint {

class ComlintException : public std::exception
{
public:
    ComlintException(const std::string &exception_name, const std::string &message)
    : full_message_{exception_name + ": " + message}
    {}

    const char* what() const
    {
        return full_message_.c_str();
    }

private:
    const std::string full_message_;
};

} // comlint