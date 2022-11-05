#pragma once
#include <string>
#include <vector>
#include <common/measurement.hpp>
#include <cornea/compilation_unit.hpp>

namespace iris::db
{
    std::vector<std::string> valid_compiler_versions = {"0.0.1"};

    const std::string actual_compiler_version("0.0.1"), error("\u001b[31m"), normal("\u001b[37m"), file("\u001b[34m"), location("\u001b[32m"), sequence("\u001b[35m");

    std::string output_log, project_folder, documentation_folder, libraries_folder, output_folder, resource_folder, source_folder, sclera_file, cornea_file, compiler_version("0.0.1");
    
    u64 indentation = 4ull;

    measurement measure_unit = measurement::microseconds;

    namespace _0_0_1
    {
        std::vector<cornea::_0_0_1::compilation_unit> units;

        std::string project_name("project");
    }
}