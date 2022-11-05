#pragma once
#include <common/types.hpp>

namespace iris
{
    template<bool reversed> class alignas(2ull) bytes2
    {
    public:
        u8 a, b;
    };

    template<> class alignas(2ull) bytes2<true>
    {
    public:
        u8 b, a;
    };

    template<bool reversed> class alignas(4ull) bytes4
    {
    public:
        u8 a, b, c, d;
    };

    template<> class alignas(4ull) bytes4<true>
    {
    public:
        u8 d, c, b, a;
    };

    template<bool reversed> class alignas(8ull) bytes8
    {
    public:
        u8 a, b, c, d, e, f, g, h;
    };

    template<> class alignas(8ull) bytes8<true>
    {
    public:
        u8 h, g, f, e, d, c, b, a;
    };

    template<bool little_endian = true> [[nodiscard]] inline auto u16_to_bytes(const u16 value)
    {
        union
        {
            bytes2<little_endian> b;
            u16 u;
        };
        u = value;
        return b;
    }

    template<bool little_endian = true> [[nodiscard]] inline auto u32_to_bytes(const u32 value)
    {
        union
        {
            bytes4<little_endian> b;
            u32 u;
        };
        u = value;
        return b;
    }

    template<bool little_endian = true> [[nodiscard]] inline auto u64_to_bytes(const u64 value)
    {
        union
        {
            bytes8<little_endian> b;
            u64 u;
        };
        u = value;
        return b;
    }

    template<bool little_endian> [[nodiscard]] inline u16 bytes_to_u16(const bytes2<little_endian>& bytes)
    {
        union
        {
            bytes2<little_endian> b;
            u16 u;
        };
        b = bytes;
        return u;
    }

    template<bool little_endian> [[nodiscard]] inline u32 bytes_to_u32(const bytes4<little_endian>& bytes)
    {
        union
        {
            bytes4<little_endian> b;
            u32 u;
        };
        b = bytes;
        return u;
    }

    template<bool little_endian> [[nodiscard]] inline u64 bytes_to_u64(const bytes8<little_endian>& bytes)
    {
        union
        {
            bytes8<little_endian> b;
            u64 u;
        };
        b = bytes;
        return u;
    }
}