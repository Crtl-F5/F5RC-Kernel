#pragma once
#include <Spline.hpp>
#include <Function.hpp>

namespace USSL
{
    inline void GEN_FNC_SPL(ProgramType* args, unsigned char* programMemory)
    {
        *((signed long*)programMemory + args[0].data.i) = (signed long)((void*)(new Spline(args[1].data.f, args[2].data.f, args[3].data.f, args[4].data.f)));
    }
}