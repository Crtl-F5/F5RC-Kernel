#pragma once
#include <ProgramType.hpp>

namespace USSL
{
    inline void MLC(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[1].type)
        {
            case b: *((unsigned char**)programMemory + args[0].data.i) = new unsigned char[args[1].data.b]; break;
            case s: *((unsigned char**)programMemory + args[0].data.i) = new unsigned char[args[1].data.s]; break;
            case i: *((unsigned char**)programMemory + args[0].data.i) = new unsigned char[args[1].data.i]; break;
        }
    }

    inline void FRE(ProgramType* args, unsigned char* programMemory)
    {
        delete *((unsigned char**)programMemory + args[0].getAbsoluteData(programMemory).i);
    }

    inline void GRF(ProgramType* args, unsigned char* programMemory)
    {
        *((signed long*)programMemory + args[0].data.i) = &args[1].data;
    }

    inline void DRF(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = *((signed char*)args[1].data.i); break;
            case s: *((signed short*)programMemory + args[0].data.i) = *((signed short*)args[1].data.i); break;
            case i: *((signed long*)programMemory + args[0].data.i) = *((signed long*)args[1].data.i); break;
            case l: *((signed long long*)programMemory + args[0].data.i) = *((signed long long*)args[1].data.i); break;
            case f: *((float*)programMemory + args[0].data.i) = *((float*)args[1].data.i); break;
            case d: *((double*)programMemory + args[0].data.i) = *((double*)args[1].data.i); break;
        }
    }
}