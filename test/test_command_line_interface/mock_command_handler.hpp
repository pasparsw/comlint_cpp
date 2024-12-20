#include <gmock/gmock.h>

#include "comlint/command_handler_interface.hpp"

using namespace comlint;

class MockCommandHandler : public CommandHandlerInterface
{
public:
    MOCK_METHOD(void, Run, (const ParsedCommand &command), (override));
};