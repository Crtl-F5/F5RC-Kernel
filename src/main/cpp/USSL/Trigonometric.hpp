#pragma once
#include <ProgramType.hpp>
#include <cmath>
#include <algorithm>

namespace USSL
{
    inline void SIN(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case f: *((float*)programMemory + args[0].data.i) = sin(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = sin(args[1].data.d); break;
        }
    }

    inline void COS(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case f: *((float*)programMemory + args[0].data.i) = cos(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = cos(args[1].data.d); break;
        }
    }

    inline void TAN(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case f: *((float*)programMemory + args[0].data.i) = tan(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = tan(args[1].data.d); break;
        }
    }

    inline void ASN(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case f: *((float*)programMemory + args[0].data.i) = asin(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = asin(args[1].data.d); break;
        }
    }

    inline void ACS(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case f: *((float*)programMemory + args[0].data.i) = acos(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = acos(args[1].data.d); break;
        }
    }

    inline void ATN(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case f: *((float*)programMemory + args[0].data.i) = atan(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = atan(args[1].data.d); break;
        }
    }

    inline void ATT(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case f: *((float*)programMemory + args[0].data.i) = atan2(args[1].data.f), args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = atan2(args[1].data.d, args[2].data.d); break;
        }
    }
}