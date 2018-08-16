#pragma once
#include <ProgramType.hpp>

namespace USSL
{
    inline void LAD(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        *((signed char*)programMemory + args[0].data.i) = args[1].data.b && args[2].data.b;
    }

    inline void LOR(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {   
        *((signed char*)programMemory + args[0].data.i) = args[1].data.b || args[2].data.b;
    }

    inline void LXR(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        *((signed char*)programMemory + args[0].data.i) = !args[1].data.b != !args[2].data.b;
    }

    inline void LNT(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        *((signed char*)programMemory + args[0].data.i) = !args[1].data.b;
    }
}