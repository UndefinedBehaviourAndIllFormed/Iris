#pragma once
#include <filesystem>

namespace iris::folder
{
    [[nodiscard]] inline bool create(const std::string& name)
    {
        return std::filesystem::create_directory(name);
    }

    [[nodiscard]] inline bool exists(const std::string& name)
    {
        return std::filesystem::exists(name) and std::filesystem::is_directory(name);
    }
}