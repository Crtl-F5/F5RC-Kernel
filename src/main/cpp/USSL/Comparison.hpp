#pragma once
#include <ProgramType.hpp>

namespace USSL
{
    inline void EQL(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[1].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b == args[2].data.b; break;
            case s: *((signed char*)programMemory + args[0].data.i) = args[1].data.s == args[2].data.s; break;
            case i: *((signed char*)programMemory + args[0].data.i) = args[1].data.i == args[2].data.i; break;
            case l: *((signed char*)programMemory + args[0].data.i) = args[1].data.l == args[2].data.l; break;
            case f: *((signed char*)programMemory + args[0].data.i) = args[1].data.f == args[2].data.f; break;
            case d: *((signed char*)programMemory + args[0].data.i) = args[1].data.d == args[2].data.d; break;
        }
    }

     inline void NEQ(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[1].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b != args[2].data.b; break;
            case s: *((signed char*)programMemory + args[0].data.i) = args[1].data.s != args[2].data.s; break;
            case i: *((signed char*)programMemory + args[0].data.i) = args[1].data.i != args[2].data.i; break;
            case l: *((signed char*)programMemory + args[0].data.i) = args[1].data.l != args[2].data.l; break;
            case f: *((signed char*)programMemory + args[0].data.i) = args[1].data.f != args[2].data.f; break;
            case d: *((signed char*)programMemory + args[0].data.i) = args[1].data.d != args[2].data.d; break;
        }
    }

    inline void GTN(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[1].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b > args[2].data.b; break;
            case s: *((signed char*)programMemory + args[0].data.i) = args[1].data.s > args[2].data.s; break;
            case i: *((signed char*)programMemory + args[0].data.i) = args[1].data.i > args[2].data.i; break;
            case l: *((signed char*)programMemory + args[0].data.i) = args[1].data.l > args[2].data.l; break;
            case f: *((signed char*)programMemory + args[0].data.i) = args[1].data.f > args[2].data.f; break;
            case d: *((signed char*)programMemory + args[0].data.i) = args[1].data.d > args[2].data.d; break;
        }
    }

    inline void LTN(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[1].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b < args[2].data.b; break;
            case s: *((signed char*)programMemory + args[0].data.i) = args[1].data.s < args[2].data.s; break;
            case i: *((signed char*)programMemory + args[0].data.i) = args[1].data.i < args[2].data.i; break;
            case l: *((signed char*)programMemory + args[0].data.i) = args[1].data.l < args[2].data.l; break;
            case f: *((signed char*)programMemory + args[0].data.i) = args[1].data.f < args[2].data.f; break;
            case d: *((signed char*)programMemory + args[0].data.i) = args[1].data.d < args[2].data.d; break;
        }
    }

    inline void GTE(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[1].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b >= args[2].data.b; break;
            case s: *((signed char*)programMemory + args[0].data.i) = args[1].data.s >= args[2].data.s; break;
            case i: *((signed char*)programMemory + args[0].data.i) = args[1].data.i >= args[2].data.i; break;
            case l: *((signed char*)programMemory + args[0].data.i) = args[1].data.l >= args[2].data.l; break;
            case f: *((signed char*)programMemory + args[0].data.i) = args[1].data.f >= args[2].data.f; break;
            case d: *((signed char*)programMemory + args[0].data.i) = args[1].data.d >= args[2].data.d; break;
        }
    }

    inline void LTE(ProgramType* args, unsigned char* programMemory, ProgramType* functionArgumentPassBuffer, signed long* stack)
    {
        switch (args[1].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b <= args[2].data.b; break;
            case s: *((signed char*)programMemory + args[0].data.i) = args[1].data.s <= args[2].data.s; break;
            case i: *((signed char*)programMemory + args[0].data.i) = args[1].data.i <= args[2].data.i; break;
            case l: *((signed char*)programMemory + args[0].data.i) = args[1].data.l <= args[2].data.l; break;
            case f: *((signed char*)programMemory + args[0].data.i) = args[1].data.f <= args[2].data.f; break;
            case d: *((signed char*)programMemory + args[0].data.i) = args[1].data.d <= args[2].data.d; break;
        }
    }
}