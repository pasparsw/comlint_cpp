#pragma once

namespace comlint {

enum class CommandLineElementType
{
    kCommand,
    kOption,
    kFlag,
    kCustomValue
};

} // comlint