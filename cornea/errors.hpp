#pragma once
#include <common/token.hpp>
#include <common/errors.hpp>
#include <cornea/corken.hpp>
#include <cornea/compilation_unit.hpp>

namespace iris::cornea
{
    namespace _0_0_1
    {
        namespace errors
        {
            [[nodiscard]] inline bool unrecognized_character(const u64 ln, const u64 ch, const char c)
            {
                db::output_log += iris::errors::entry("co1", db::cornea_file, ln, ch) + "unrecognized character " + db::sequence + std::string(1ull, c) + db::normal;
                return false;
            }

            [[nodiscard]] inline bool unrecognized_precomment_character(const u64 ln, const u64 ch, const char c)
            {
                db::output_log += iris::errors::entry("co2", db::cornea_file, ln, ch) + "unrecognized pre-comment character " + db::sequence + std::string(1ull, c) + db::normal + ", expected " + db::sequence + "`" + db::normal + " or " + db::sequence + "*" + db::normal;
                return false;
            }

            [[nodiscard]] inline bool numerical_compilation_unit_name(const token<corken>& t)
            {
                db::output_log += iris::errors::entry("co3", db::cornea_file, t.ln, t.get_last()) + "bad format for " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected an alpha-numeric sequence indicating the compilation unit name";
                return false;
            }

            [[nodiscard]] inline bool unrecognized_keyword(const token<corken>& t)
            {
                db::output_log += iris::errors::entry("co4", db::cornea_file, t.ln, t.get_last()) + "unrecognized keyword " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected an alpha-numeric sequence or one of the following keywords:\n" + db::sequence + "\nname\nversion" + db::normal;
                return false;
            }

            [[nodiscard]] inline bool repeated_compilation_unit(const compilation_unit& cu, const u64 oln, const u64 och)
            {
                db::output_log += iris::errors::entry("co5", db::cornea_file, cu.ln, cu.get_last()) + "the compilation unit " + db::sequence + cu.name + db::normal + iris::errors::starts_at(cu.ln, cu.ch) + ", is already declared at " + iris::errors::at(oln, och);
                return false;
            }

            [[nodiscard]] inline bool unrecognized_compilation_unit_start(const token<corken>& t, const compilation_unit& cu)
            {
                db::output_log += iris::errors::entry("co6", db::cornea_file, t.ln, t.get_last()) + "unrecognized start of the compilation unit " + db::sequence + cu.name + db::normal + iris::errors::starts_at(cu.ln, cu.ch) + ", expected " + db::sequence + "{" + db::normal + ", found " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch);
                return false;
            }

            [[nodiscard]] inline bool unrecognized_embedded_compilation_unit(const token<corken>& t, const compilation_unit& cu)
            {
                db::output_log += iris::errors::entry("co7", db::cornea_file, t.ln, t.get_last()) + "unexpected compilation unit " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", it's embedded inside the compilation unit " + db::sequence + cu.name + db::normal + iris::errors::starts_at(cu.ln, cu.ch);
                return false;
            }

            [[nodiscard]] inline bool unrecognized_assignment_global_name(const token<corken>& t)
            {
                db::output_log += iris::errors::entry("co8", db::cornea_file, t.ln, t.get_last()) + "unrecognized " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected " + db::sequence + "=" + db::normal + " to indicate the global project name assignment";
                return false;
            }

            [[nodiscard]] inline bool numerical_global_name(const token<corken>& t)
            {
                db::output_log += iris::errors::entry("co9", db::cornea_file, t.ln, t.get_last()) + "unexpected numerical sequence " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected an alphanumeric sequence for the global project name";
                return false;
            }

            [[nodiscard]] inline bool unrecognized_global_name(const token<corken>& t)
            {
                db::output_log += iris::errors::entry("co10", db::cornea_file, t.ln, t.get_last()) + "unrecognized global project name " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected an alphanumeric sequence";
                return false;
            }

            [[nodiscard]] inline bool unrecognized_end_sentence_global_name(const token<corken>& t)
            {
                db::output_log += iris::errors::entry("co11", db::cornea_file, t.ln, t.get_last()) + "unrecognized end of the global project assignment " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected " + db::sequence + ";" + db::normal;
                return false;
            }

            [[nodiscard]] inline bool unrecognized_assignment_global_version(const token<corken>& t)
            {
                db::output_log += iris::errors::entry("co12", db::cornea_file, t.ln, t.get_last()) + "unrecognized " + db::sequence + t.word + db::normal + iris::errors::starts_at(t.ln, t.ch) + ", expected " + db::sequence + "=" + db::normal + " to indicate the global project version assignment";
                return false;
            }
        }
    }
}