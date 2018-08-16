#pragma once
#include <ProgramType.hpp>

namespace USSL
{
    inline void BAD(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b & args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s & args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i & args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l & args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f & args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d & c.d; break;
        }
    }

    inline void BOR(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b | args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s | args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i | args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l | args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f | args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d | c.d; break;
        }
    }

    inline void BXR(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b ^ args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s ^ args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i ^ args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l ^ args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f ^ args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d ^ c.d; break;
        }
    }

    inline void BNT(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = ~args[1].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = ~args[1].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = ~args[1].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = ~args[1].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = ~args[1].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = ~args[1].data.d; break;
        }
    }

    inline void BSL(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b << args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s << args[2].data.b; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i << args[2].data.b; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l << args[2].data.b; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f << args[2].data.b; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d << c.b; break;
        }
    }

    inline void BSR(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b >> args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s >> args[2].data.b; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i >> args[2].data.b; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l >> args[2].data.b; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f >> args[2].data.b; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d >> c.b; break;
        }
    }
}