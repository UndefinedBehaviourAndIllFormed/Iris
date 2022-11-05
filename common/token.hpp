#pragma once
#include <string>
#include <common/types.hpp>

namespace iris
{
    template<class t> class token
    {
    public:
        std::string word;

        u64 ln, ch;

        t key;

        [[nodiscard]] inline u64 get_last() &
        {
            return ch + word.size();
        }

        [[nodiscard]] inline u64 get_last() const&
        {
            return ch + word.size();
        }
    };

    [[nodiscard]] inline bool is_numerical(const std::string& str)
    {
        for(const char c : str)
            if(c < '0' || c > '9')
                return false;
        return true;
    }
}