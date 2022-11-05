#pragma once
#include <chrono>
#include <common/db.hpp>

namespace iris
{
    using watchdog = const std::chrono::steady_clock::time_point;

    [[nodiscard]] inline watchdog now()
    {
        return std::chrono::steady_clock::now();
    }

    [[nodiscard]] inline std::string result(const watchdog& from, const watchdog& to)
    {
        switch(db::measure_unit)
        {
            case measurement::microseconds:
                return std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(to - from).count()) + " microseconds";
            case measurement::milliseconds:
                return std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(to - from).count()) + " milliseconds";
            case measurement::nanoseconds:
                return std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(to - from).count()) + " nanoseconds";
        }
    }
}