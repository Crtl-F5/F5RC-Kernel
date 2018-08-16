#pragma once
#include <ProgramType.hpp>

namespace USSL
{
    inline void ADD(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b + args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s + args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i + args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l + args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f + args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d + args[2].data.d; break;
        }
    }

    inline void SUB((ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b - args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s - args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i - args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l - args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f - args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d - args[2].data.d; break;
        }
    }

    inline void MUL(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b * args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s * args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i * args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l * args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f * args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d * args[2].data.d; break;
        }
    }

    inline void DIV(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b / args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s / args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i / args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l / args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f / args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d / args[2].data.d; break;
        }
    }

    inline void MOD(ProgramType* args, unsigned char* memory)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b % args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s % args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i % args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l % args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f % args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d % args[2].data.d; break;
        }
    }
}