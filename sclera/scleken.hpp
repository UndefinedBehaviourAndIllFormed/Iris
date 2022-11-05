#pragma once
#include <common/types.hpp>

namespace iris
{
    enum class scleken : u8
    {
        unidentified,
        numerical,
        dot,
        end_sentence,
        assignment,
        compiler_version,
        measurement,
        microseconds,
        milliseconds,
        nanoseconds,
        indentation
    };
}