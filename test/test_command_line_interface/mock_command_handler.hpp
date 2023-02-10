#include <gmock/gmock.h>

#include "command_handler_interface.hpp"

using namespace comlint;

class MockCommandHandler : public CommandHandlerInterface
{
public:
    MOCK_METHOD(void, Run, (const ParsedCommand &command), (override));
};