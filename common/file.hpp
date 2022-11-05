#pragma once
#include <common/types.hpp>
#include <fstream>
#include <filesystem>

namespace iris::file
{
    std::atomic<bool> r;

    [[nodiscard]] inline bool exists(const std::string& name)
    {
        return std::filesystem::exists(name) and not std::filesystem::is_directory(name);
    }

    [[nodiscard]] inline bool create(const std::string& name)
    {
        std::ofstream(name).close();
        return exists(name);
    }

    [[nodiscard]] inline bool write(const std::string& name, const std::string& content)
    {
        const u64 cs = content.size();
        std::ofstream of(name);
        of.write(content.data(), cs);
        of.close();
        return std::filesystem::file_size(name) == cs
        #if defined(_MSC_VER)
        + std::count(content.begin(), content.end(), '\n')
        #endif
        ;
    }

    [[nodiscard]] inline std::string read(const std::string& name)
    {
        const u64 fs = std::filesystem::file_size(name);
        std::string r(fs, '\0');
        std::ifstream iff(name);
        iff.read(r.data(), fs);
        iff.close();
        r.append(1ull, ' ');
        return r;
    }
}