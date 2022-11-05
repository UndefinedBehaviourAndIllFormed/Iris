#pragma once
#include <vector>
#include <common/file.hpp>
#include <common/token.hpp>
#include <sclera/errors.hpp>
#include <sclera/sclede.hpp>
#include <sclera/scleken.hpp>
#include <common/watchdog.hpp>

namespace iris::sclera
{
    inline void tokenize(bool& fc, token<scleken>& t, std::vector<token<scleken>>& ts)
    {
        fc = false;
        t.key = is_numerical(t.word) ? scleken::numerical : t.word == "compiler_version" ? scleken::compiler_version : t.word == "microseconds" ? scleken::microseconds : t.word == "milliseconds" ? scleken::milliseconds : t.word == "nanoseconds" ? scleken::nanoseconds : t.word == "measurement" ? scleken::measurement : t.word == "indentation" ? scleken::indentation : scleken::unidentified;
        ts.push_back(t);
    }

    inline void tokenize(const u64 ln, const u64 ch, const scleken t, const std::string& w, token<scleken>& to, std::vector<token<scleken>>& ts)
    {
        to.ln = ln;
        to.ch = ch;
        to.key = t;
        to.word = w;
        ts.push_back(to);
    }

    [[nodiscard]] inline bool lexer()
    {
        std::vector<token<scleken>> tokens;
        {
            const std::string content = file::read(db::sclera_file);
            token<scleken> t;
            u64 ln = 1ull, ch = 0ull;
            u8 mode = 0u;
            bool fc = false;
            for(const char c : content)
            {
                c == '\n' ? ++ln, ch = 0ull : ++ch;
                switch(mode)
                {
                    case 0u:
                        switch(c)
                        {
                            case alphanumeric:
                                if(!fc)
                                {
                                    fc = true;
                                    t.ln = ln;
                                    t.ch = ch;
                                    t.word = c;
                                }
                                else
                                    t.word.append(1ull, c);
                            break;
                            case '`':
                                mode = 1u;
                                if(fc)
                                    tokenize(fc, t, tokens);
                            break;
                            case ' ':
                            case '\n':
                            //Don't support tabulator here
                                if(fc)
                                    tokenize(fc, t, tokens);
                            break;
                            case ';':
                                if(fc)
                                    tokenize(fc, t, tokens);
                                tokenize(ln, ch, scleken::end_sentence, ";", t, tokens);
                            break;
                            case '=':
                                if(fc)
                                    tokenize(fc, t, tokens);
                                tokenize(ln, ch, scleken::assignment, "=", t, tokens);
                            break;
                            case '.':
                                if(fc)
                                    tokenize(fc, t, tokens);
                                tokenize(ln, ch, scleken::dot, ".", t, tokens);
                            break;
                            default:
                                return errors::unrecognized_character(ln, ch, c);
                        }
                    break;
                    case 1u:
                        switch(c)
                        {
                            case '`':
                                mode = 2u;
                            break;
                            case '*':
                                mode = 3u;
                            break;
                            default:
                                return errors::unrecognized_character_precomment(ln, ch, c);
                        }
                    break;
                    case 2u:
                        if(c == '\n')
                            mode = 0u;
                    break;
                    case 3u:
                        if(c == '*')
                            mode = 4u;
                    break;
                    case 4u:
                        switch(c)
                        {
                            case '`':
                                mode = 0u;
                            break;
                            case '*':
                            break;
                            default:
                                mode = 3u;
                            break;
                        }
                    break;
                }
            }
        }
        if(not tokens.empty())
        {
            std::string data;
            token<scleken>& last = tokens[0];
            u64 ln = 0ull, ch = 0ull;
            sclede mode = sclede::general;
            u8 submode = 0u;
            for(const auto& t : tokens)
                switch(mode)
                {
                    case sclede::general:
                        switch(t.key)
                        {
                            case scleken::compiler_version:
                                mode = sclede::compiler_version;
                            break;
                            case scleken::indentation:
                                mode = sclede::indentation;
                            break;
                            case scleken::measurement:
                                mode = sclede::measurement;
                            break;
                            default:
                                return errors::unrecognized_keyword(t);
                        }
                    break;
                    case sclede::compiler_version:
                        switch(submode)
                        {
                            case 0u:
                                if(t.key == scleken::assignment)
                                    submode = 1u;
                                else
                                    return errors::unrecognized_assignment_compiler_version(t);
                            break;
                            case 1u:
                                switch(t.key)
                                {
                                    case scleken::numerical:
                                        submode = 2u;
                                        ln = t.ln;
                                        ch = t.ch;
                                        last = t;
                                        data = t.word;
                                    break;
                                    case scleken::end_sentence:
                                        return errors::empty_cver(t.ln, t.ch);
                                    default:
                                        return errors::unrecognized_numeric_sequence(t);
                                }
                            break;
                            case 2u:
                                switch(t.key)
                                {
                                    case scleken::dot:
                                        submode = 3u;
                                        data.append(1ull, '.');
                                    break;
                                    case scleken::end_sentence:
                                        if(data.empty())
                                            return errors::empty_cver(t.ln, t.ch);
                                        else
                                        {
                                            mode = sclede::general;
                                            for(const std::string& cv : db::valid_compiler_versions)
                                                if(cv == data)
                                                {
                                                    submode = 0u;
                                                    db::compiler_version = cv;
                                                    break;
                                                }
                                            if(submode)
                                                return errors::unrecognized_cver(last, data, ln, ch);
                                        }
                                    break;
                                    default:
                                        return errors::unrecognized_dot(t);
                                }
                            break;
                            case 3u:
                                if(t.key == scleken::numerical)
                                {
                                    submode = 2u;
                                    last = t;
                                    data += t.word;
                                }
                                else
                                    return errors::unrecognized_numeric_sequence(t);
                            break;
                        }
                    break;
                    case sclede::indentation:
                        switch(submode)
                        {
                            case 0u:
                                if(t.key == scleken::assignment)
                                    submode = 1u;
                                else
                                    return errors::unrecognized_assignment_indentation(t);
                            break;
                            case 1u:
                                switch(t.key)
                                {
                                    case scleken::numerical:
                                        submode = 2u;
                                        data = t.word;
                                    break;
                                    case scleken::end_sentence:
                                        return errors::empty_indetation(t.ln, t.get_last());
                                    default:
                                        return errors::unrecognized_indentation(t);
                                }
                            break;
                            case 2u:
                                if(t.key == scleken::end_sentence)
                                {
                                    mode = sclede::general;
                                    submode = 0u;
                                    db::indentation = std::stoull(data, 0, 0);
                                }
                                else
                                    return errors::unrecognized_indentation_end_of_sentence(t);
                            break;
                        }
                    break;
                    case sclede::measurement:
                        switch(submode)
                        {
                            case 0u:
                                if(t.key == scleken::assignment)
                                    submode = 1u;
                                else
                                    return errors::unrecognized_assignment_measurement(t);
                            break;
                            case 1u:
                                switch(t.key)
                                {
                                    case scleken::microseconds:
                                        submode = 2u;
                                        db::measure_unit = measurement::microseconds;
                                    break;
                                    case scleken::milliseconds:
                                        submode = 2u;
                                        db::measure_unit = measurement::milliseconds;
                                    break;
                                    case scleken::nanoseconds:
                                        submode = 2u;
                                        db::measure_unit = measurement::nanoseconds;
                                    break;
                                    case scleken::end_sentence:
                                        return errors::empty_measurement_unit(t.ln, t.ch);
                                    default:
                                        return errors::unrecognized_measurement_unit(t);
                                }
                            break;
                            case 2u:
                                if(t.key == scleken::end_sentence)
                                {
                                    mode = sclede::general;
                                    submode = 0u;
                                }
                                else
                                    return errors::unrecognized_measurement_end_of_sentence(t);
                            break;
                        }
                    break;
                }
            last = tokens[tokens.size() - 1ull];
            switch(mode)
            {
                case sclede::general:
                    return true;
                case sclede::compiler_version:
                    return submode < 1u ? errors::unexpected_compiler_version_end_of_file(last) : errors::expected_compiler_version_end_of_file(last);
                case sclede::indentation:
                    return submode < 1u ? errors::unexpected_indentation_end_of_file(last) : errors::expected_indentation_end_of_file(last);
                case sclede::measurement:
                    return submode < 1u ? errors::unexpected_measure_unit_end_of_file(last) : errors::expected_measure_unit_end_of_file(last);
            }
        }
        return true;
    }
}