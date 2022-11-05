#pragma once
#include <common/token.hpp>
#include <common/errors.hpp>
#include <sclera/scleken.hpp>

namespace iris::sclera::errors
{
    [[nodiscard]] inline bool unrecognized_character(const u64 ln, const u64 ch, const char c)
    {
        db::output_log += iris::errors::entry("sc1", db::sclera_file, ln, ch) + "unrecognized character " + db::sequence + std::string(1ull, c) + db::normal;
        return false;
    }

    [[nodiscard]] inline bool unrecognized_character_precomment(const u64 ln, const u64 ch, const char c)
    {
        db::output_log += iris::errors::entry("sc2", db::sclera_file, ln, ch) + "unrecognized character " + db::sequence + std::string(1ull, c) + db::normal + ", expected " + db::sequence + "`" + db::normal + " or " + db::sequence + "*" + db::normal + " after the pre-comment character";
        return false;
    }

    [[nodiscard]] inline bool unrecognized_keyword(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc3", db::sclera_file, t.ln, t.get_last()) + "unrecognized keyword " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected " + db::sequence + "compiler_version" + db::normal + ", " + db::sequence + "indentation" + db::normal + " or " + db::sequence + "measurement" + db::normal;
        return false;
    }

    [[nodiscard]] inline bool unrecognized_assignment_compiler_version(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc4", db::sclera_file, t.ln, t.get_last()) + "unrecognized " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected " + db::sequence + "=" + db::normal + " to indicate the compiler version assignment";
        return false;
    }

    [[nodiscard]] inline bool unrecognized_numeric_sequence(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc5", db::sclera_file, t.ln, t.get_last()) + "bad format for " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected a numerical sequence";
        return false;
    }

    [[nodiscard]] inline bool empty_cver(const u64 ln, const u64 ch)
    {
        db::output_log += iris::errors::entry("sc6", db::sclera_file, ln, ch) + "empty compiler version before " + db::sequence + ";" + db::normal;
        return false;
    }

    [[nodiscard]] inline bool unrecognized_dot(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc7", db::sclera_file, t.ln, t.get_last()) + "bad format for " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected " + db::sequence + "." + db::normal + " or " + db::sequence + ";" + db::normal;
        return false;
    }

    [[nodiscard]] inline bool unrecognized_cver(const token<scleken>& t, const std::string& cver, const u64 ln, const u64 ch)
    {
        std::string cvers;
        for(const std::string& cv : db::valid_compiler_versions)
            cvers += "\n" + cv;
        db::output_log += iris::errors::entry("sc8", db::sclera_file, t.ln, t.get_last()) + "unrecognized compiler version " + db::sequence + cver + db::normal + iris::errors::starts_at(ln, ch) + ", expected one of the following valid compiler versions:\n" + db::sequence + cvers + db::normal;
        return false;
    }

    [[nodiscard]] inline bool unrecognized_assignment_indentation(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc9", db::sclera_file, t.ln, t.get_last()) + "unrecognized " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected " + db::sequence + "=" + db::normal + " to indicate the indentation assignment";
        return false;
    }

    [[nodiscard]] inline bool empty_indetation(const u64 ln, const u64 ch)
    {
        db::output_log += iris::errors::entry("sc10", db::sclera_file, ln, ch) + "empty indentation before " + db::sequence + ";" + db::normal;
        return false;
    }

    [[nodiscard]] inline bool unrecognized_indentation(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc11", db::sclera_file, t.ln, t.get_last()) + "bad format for indentation, expected a numerical sequence, found " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch);
        return false;
    }

    [[nodiscard]] inline bool unrecognized_indentation_end_of_sentence(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc12", db::sclera_file, t.ln, t.get_last()) + "expected " + db::sequence + ";" + db::normal + " after the indentation assignment, found " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch);
        return false;
    }

    [[nodiscard]] inline bool unrecognized_assignment_measurement(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc13", db::sclera_file, t.ln, t.get_last()) + "unrecognized " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected " + db::sequence + "=" + db::normal + " to indicate the measurement unit assignment";
        return false;
    }

    [[nodiscard]] inline bool unrecognized_measurement_unit(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc14", db::sclera_file, t.ln, t.get_last()) + "unrecognized measurement unit " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected one of the following:\n" + db::sequence + "\nmicroseconds\nmilliseconds\nnanoseconds" + db::normal;
        return false;
    }

    [[nodiscard]] inline bool empty_measurement_unit(const u64 ln, const u64 ch)
    {
        db::output_log += iris::errors::entry("sc15", db::sclera_file, ln, ch) + "empty measurement unit before " + db::sequence + ";" + db::normal;
        return false;
    }

    [[nodiscard]] inline bool unrecognized_measurement_end_of_sentence(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc16", db::sclera_file, t.ln, t.get_last()) + "expected " + db::sequence + ";" + db::normal + " after the assigment of the measurement unit, found " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch);
        return false;
    }

    [[nodiscard]] inline bool unexpected_compiler_version_end_of_file(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc17", db::sclera_file, t.ln, t.get_last()) + "unexpected " + db::sequence + "compiler_version" + db::normal + " before the end of the file";
        return false;
    }

    [[nodiscard]] inline bool expected_compiler_version_end_of_file(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc17", db::sclera_file, t.ln, t.get_last()) + "expected a compiler version assignment after " + db::sequence + "=" + db::normal + " and before the end of the file";
        return false;
    }

    [[nodiscard]] inline bool unexpected_indentation_end_of_file(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc17", db::sclera_file, t.ln, t.get_last()) + "unexpected " + db::sequence + "indentation" + db::normal + " before the end of the file";
        return false;
    }

    [[nodiscard]] inline bool expected_indentation_end_of_file(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc17", db::sclera_file, t.ln, t.get_last()) + "expected a indentation numerical sequence assignment after " + db::sequence + "=" + db::normal + " and before the end of the file";
        return false;
    }

    [[nodiscard]] inline bool unexpected_measure_unit_end_of_file(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc17", db::sclera_file, t.ln, t.get_last()) + "unexpected " + db::sequence + "measurement" + db::normal + " before the end of the file";
        return false;
    }

    [[nodiscard]] inline bool expected_measure_unit_end_of_file(const token<scleken>& t)
    {
        db::output_log += iris::errors::entry("sc17", db::sclera_file, t.ln, t.get_last()) + "expected a measurement unit assignment after " + db::sequence + "=" + db::normal + " and before the end of the file";
        return false;
    }
}