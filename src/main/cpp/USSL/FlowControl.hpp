#pragma once
#include <ProgramType.hpp>

namespace USSL
{
    inline void CAL(ProgramType* args, unsigned char* programMemory, signed long* programStack, short& stackDepth, signed long& programCounter, ProgramType* argumentPassBuffer)
    {
        programStack[stackDepth++] = programCounter;
        programCounter = args[0].getAbsoluteData(programMemory).data.i;
    }

    inline void RET(ProgramType* args, unsigned char* programMemory, signed long* programStack, short* stackDepth, signed long* programCounter, ProgramType* argumentPassBuffer)
    {
        argumentPassBuffer[0] = args[0].getAbsoluteData(programMemory);
        programCounter = programStack[--stackDepth];
    }

    inline void GAR(ProgramType* args, unsigned char* programMemory, signed long* programStack, short* stackDepth, signed long* programCounter, ProgramType* argumentPassBuffer)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = argumentPassBuffer[args[1].data.b].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = argumentPassBuffer[args[1].data.b].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = argumentPassBuffer[args[1].data.b].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = argumentPassBuffer[args[1].data.b].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = argumentPassBuffer[args[1].data.b].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = argumentPassBuffer[args[1].data.b].data.d; break;
        }
    }

    inline void GRT(ProgramType* args, unsigned char* programMemory, signed long* programStack, short* stackDepth, signed long* programCounter, ProgramType* argumentPassBuffer)
    {
        switch (args[0].type)
        {
            case b: *((signed char*)programMemory + args[0].data.i) = argumentPassBuffer[0].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = argumentPassBuffer[0].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = argumentPassBuffer[0].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = argumentPassBuffer[0].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = argumentPassBuffer[0].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = argumentPassBuffer[0].data.d; break;
        }
    }

    inline void SAR(ProgramType* args, unsigned char* programMemory, signed long* programStack, short* stackDepth, signed long* programCounter, ProgramType* argumentPassBuffer)
    {
        argumentPassBuffer[args[0].getAbsoluteData(programMemory).data.b] = args[1];
    }

    inline void GTO(ProgramType* args, unsigned char* programMemory, signed long* programStack, short* stackDepth, signed long* programCounter, ProgramType* argumentPassBuffer)
    {
        programCounter = args[0].getAbsoluteData(programMemory).data.i;
    }
}