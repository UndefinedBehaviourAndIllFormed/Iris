#pragma once
#include <cornea/corde.hpp>
#include <cornea/errors.hpp>
#include <cornea/compilation_unit.hpp>

namespace iris::cornea
{
    namespace _0_0_1
    {
        inline void tokenize(bool& fc, token<corken>& t, std::vector<token<corken>>& ts)
        {
            fc = false;
            t.key = is_numerical(t.word) ? corken::numerical : t.word == "name" ? corken::name : t.word == "version" ? corken::version : corken::identifier;
            ts.push_back(t);
        }

        inline void tokenize(const u64 ln, const u64 ch, const corken t, const std::string& w, token<corken>& to, std::vector<token<corken>>& ts)
        {
            to.ln = ln;
            to.ch = ch;
            to.key = t;
            to.word = w;
            ts.push_back(to);
        }

        [[nodiscard]] inline bool lexer()
        {
            std::vector<token<corken>> tokens;
            {
                std::string content = file::read(db::cornea_file);
                token<corken> t;
                const u64 inden = db::indentation;
                u64 ln = 1ull, ch = 0ull;
                u8 mode = 0u;
                bool fc = false;
                for(const char c : content)
                {
                    c == '\n' ? ++ln, ch = 0ull : c == '\t' ? ch += inden : ++ch;
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
                                case ' ':
                                case '\n':
                                case '\t':
                                    if(fc)
                                        tokenize(fc, t, tokens);
                                break;
                                case '`':
                                    mode = 1u;
                                    if(fc)
                                        tokenize(fc, t, tokens);
                                break;
                                case '=':
                                    if(fc)
                                        tokenize(fc, t, tokens);
                                    tokenize(ln, ch, corken::assignment, "=", t, tokens);
                                break;
                                case ';':
                                    if(fc)
                                        tokenize(fc, t, tokens);
                                    tokenize(ln, ch, corken::end_sentence, ";", t, tokens);
                                break;
                                case '.':
                                    if(fc)
                                        tokenize(fc, t, tokens);
                                    tokenize(ln, ch, corken::dot, ".", t, tokens);
                                break;
                                case '{':
                                    if(fc)
                                        tokenize(fc, t, tokens);
                                    tokenize(ln, ch, corken::start_node, "{", t, tokens);
                                break;
                                case '}':
                                    if(fc)
                                        tokenize(fc, t, tokens);
                                    tokenize(ln, ch, corken::end_node, "}", t, tokens);
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
                                    return errors::unrecognized_precomment_character(ln, ch, c);
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
                compilation_unit cu;
                std::string data;
                token<corken>& last = tokens[0];
                corde mode = corde::general;
                u8 submode = 0u;
                for(const auto& t : tokens)
                    switch(mode)
                    {
                        case corde::general:
                            if(not submode)
                                switch(t.key)
                                {
                                    case corken::name:
                                        mode = corde::global_name;
                                    break;
                                    case corken::version:
                                        mode = corde::global_version;
                                    break;
                                    case corken::identifier:
                                        submode = 1u;
                                        cu.ln = t.ln;
                                        cu.ch = t.ch;
                                        cu.name = t.word;
                                    break;
                                    case corken::numerical:
                                        return errors::numerical_compilation_unit_name(t);
                                    default:
                                        return errors::unrecognized_keyword(t);
                                }
                            else if(t.key == corken::start_node)
                            {
                                submode = 0u;
                                mode = corde::compilation_unit;
                            }
                            else
                                return errors::unrecognized_compilation_unit_start(t, cu);
                        break;
                        case corde::compilation_unit:
                            switch(t.key)
                            {
                                case corken::name:
                                    mode = corde::local_name;
                                break;
                                case corken::version:
                                    mode = corde::local_version;
                                break;
                                case corken::end_node:
                                    mode = corde::general;
                                    for(const compilation_unit& ocu : db::_0_0_1::units)
                                        if(ocu.name == cu.name)
                                            return errors::repeated_compilation_unit(cu, ocu.ln, ocu.ch);
                                    db::_0_0_1::units.push_back(cu);
                                break;
                                case corken::identifier:
                                    return errors::unrecognized_embedded_compilation_unit(t, cu);
                                default:
                                    return errors::unrecognized_keyword(t);
                            }
                        break;
                        case corde::global_name:
                            switch(submode)
                            {
                                case 0u:
                                    if(t.key == corken::assignment)
                                        submode = 1u;
                                    else
                                        return errors::unrecognized_assignment_global_name(t);
                                break;
                                case 1u:
                                    switch(t.key)
                                    {
                                        case corken::identifier:
                                            submode = 2u;
                                            db::_0_0_1::project_name = t.word;
                                        break;
                                        case corken::numerical:
                                            return errors::numerical_global_name(t);
                                        default:
                                            return errors::unrecognized_global_name(t);
                                    }
                                break;
                                case 2u:
                                    if(t.key == corken::end_sentence)
                                    {
                                        mode = corde::general;
                                        submode = 0u;
                                    }
                                    else
                                        return errors::unrecognized_end_sentence_global_name(t);
                                break;
                            }
                        break;
                        case corde::global_version:
                            switch(submode)
                            {
                                case 0u:
                                    if(t.key == corken::assignment)
                                        submode = 1u;
                                    else
                                        return errors::unrecognized_assignment_global_version(t);
                                break;
                                case 1u:
                                    
                                break;
                                case 2u:
                                break;
                                case 3u:
                                break;
                            }
                        break;
                    }
            }
        }
    }
}