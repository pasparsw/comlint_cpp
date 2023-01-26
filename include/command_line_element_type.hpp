#pragma once

namespace cli {

enum class CommandLineElementType
{
    kCommand,
    kOption,
    kFlag,
    kInvalid
};

}