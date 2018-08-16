#pragma once
#include <Arc.hpp>
#include <Curve.hpp>

namespace USSL
{
    inline void GEN_CRV_ARC(ProgramType* args, unsigned char* programMemory)
    {
        *((signed long*)programMemory + args[0].data.i) = (signed long)((void*)(new Arc(args[1].data.f, args[2].data.f, args[3].data.f, args[4].data.f, args[5].data.f)));
    }
}