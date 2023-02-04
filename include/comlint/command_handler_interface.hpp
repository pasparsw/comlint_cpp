#pragma once

#include <memory>

#include "types.hpp"

namespace comlint {

class CommandHandlerInterface
{
public:
    virtual ~CommandHandlerInterface() = default;

    virtual void Run(const CommandValues &values, const OptionsMap &options, const FlagsMap &flags) = 0;
};

using CommandHandlerPtr = std::shared_ptr<CommandHandlerInterface>;

} // comlint