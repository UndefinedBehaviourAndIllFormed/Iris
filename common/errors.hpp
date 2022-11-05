#pragma once
#include <common/db.hpp>

namespace iris::errors
{
    [[nodiscard]] inline std::string at(const u64 ln, const u64 ch, const bool last_space = false)
    {
        if(last_space)
            return db::location + std::to_string(ln) + " : " + std::to_string(ch) + db::normal + " ";
        return db::location + std::to_string(ln) + " : " + std::to_string(ch) + db::normal;
    }

    [[nodiscard]] inline std::string starts_at(const u64 ln, const u64 ch, const bool last_space = false)
    {
        if(last_space)
            return " starting at " + db::location + std::to_string(ln) + " : " + std::to_string(ch) + db::normal + " ";
        return " starting at " + db::location + std::to_string(ln) + " : " + std::to_string(ch) + db::normal;
    }

    [[nodiscard]] inline std::string entry(const std::string& code, const std::string& file, const u64 ln, const u64 ch)
    {
        return "\n\n" + db::error + "error(" + code + ")" + db::normal + " at " + db::file + file + db::normal + ", " + db::location + std::to_string(ln) + " : " + std::to_string(ch) + db::normal + " -> ";
    }
}