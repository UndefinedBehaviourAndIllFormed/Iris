#pragma once
#include <string>
#include <common/types.hpp>

namespace iris::cornea
{
    namespace _0_0_1
    {
        class compilation_unit
        {
        public:
            std::string name;

            u64 ln, ch;

            [[nodiscard]] inline u64 get_last() &
            {
                return name.size() + ch;
            }

            [[nodiscard]] inline u64 get_last() const&
            {
                return name.size() + ch;
            }
        };
    }
}