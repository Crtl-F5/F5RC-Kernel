#pragma once
#include <ProgramType.hpp>
#include <cmath>
#include <algorithm>

namespace USSL
{
    inline void MIN(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = std::min(args[1].data.b, args[2].data.b); break;
            case s: *((signed short*)programMemory + args[0].data.i) = std::min(args[1].data.s, args[2].data.s); break;
            case i: *((signed long*)programMemory + args[0].data.i) = std::min(args[1].data.i, args[2].data.i); break;
            case l: *((signed long long*)programMemory + args[0].data.i) = std::min(args[1].data.l, args[2].data.l); break;
            case f: *((float*)programMemory + args[0].data.i) = std::min(args[1].data.f, args[2].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = std::min(args[1].data.d, args[2].data.d); break;
        }
    }

    inline void MAX(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = std::max(args[1].data.b, args[2].data.b); break;
            case s: *((signed short*)programMemory + args[0].data.i) = std::max(args[1].data.s, args[2].data.s); break;
            case i: *((signed long*)programMemory + args[0].data.i) = std::max(args[1].data.i, args[2].data.i); break;
            case l: *((signed long long*)programMemory + args[0].data.i) = std::max(args[1].data.l, args[2].data.l); break;
            case f: *((float*)programMemory + args[0].data.i) = std::max(args[1].data.f, args[2].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = std::max(args[1].data.d, args[2].data.d); break;
        }
    }

    inline void POW(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = pow(args[1].data.b, args[2].data.b); break;
            case s: *((signed short*)programMemory + args[0].data.i) = pow(args[1].data.s, args[2].data.s); break;
            case i: *((signed long*)programMemory + args[0].data.i) = pow(args[1].data.i, args[2].data.i); break;
            case l: *((signed long long*)programMemory + args[0].data.i) = pow(args[1].data.l, args[2].data.l); break;
            case f: *((float*)programMemory + args[0].data.i) = pow(args[1].data.f, args[2].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = pow(args[1].data.d, data[2].data.d); break;
        }
    }

    inline void LOG(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = log(args[1].data.b, args[2].data.b); break;
            case s: *((signed short*)programMemory + args[0].data.i) = log(args[1].data.s, args[2].data.s); break;
            case i: *((signed long*)programMemory + args[0].data.i) = log(args[1].data.i, args[2].data.i); break;
            case l: *((signed long long*)programMemory + args[0].data.i) = log(args[1].data.l, args[2].data.l); break;
            case f: *((float*)programMemory + args[0].data.i) = log(args[1].data.f, args[2].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = log(args[1].data.d, data[2].data.d); break;
        }
    }
}