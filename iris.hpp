#pragma once
#include <sclera/lexer.hpp>
#include <cornea/lexer.hpp>

namespace iris
{
    inline void compile()
    {
        if(sclera::lexer())
        {
            if(db::compiler_version == "0.0.1")
                if(cornea::_0_0_1::lexer())
                    return;
        }
    }
}