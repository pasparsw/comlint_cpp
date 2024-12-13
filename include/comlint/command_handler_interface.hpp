#pragma once

#include <memory>

#include "comlint/parsed_command.hpp"

namespace comlint {

class CommandHandlerInterface
{
public:
    virtual ~CommandHandlerInterface() = default;

    virtual void Run(const ParsedCommand &command) = 0;
};

using CommandHandlerPtr = std::shared_ptr<CommandHandlerInterface>;

} // comlint