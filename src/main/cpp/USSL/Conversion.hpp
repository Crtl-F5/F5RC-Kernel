#pragma once
#include <ProgramType.hpp>

namespace USSL
{
    inline void VCS(ProgramType* args, unsigned char* programMemory)
    {
        switch (args[0].type)
        {
            case b:
                switch (args[1].type)
                {
                    case b:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.b; break;
                    case s:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.s; break;
                    case i:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.i; break;
                    case l:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.l; break;
                    case f:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.f; break;
                    case d:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.d; break;
                }
                break;

            case s:
                switch (args[1].type)
                {
                    case b:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.b; break;
                    case s:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.s; break;
                    case i:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.i; break;
                    case l:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.l; break;
                    case f:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.f; break;
                    case d:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.d; break;
                }
                break;

            case i:
                switch (args[1].type)
                {
                    case b:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.b; break;
                    case s:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.s; break;
                    case i:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.i; break;
                    case l:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.l; break;
                    case f:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.f; break;
                    case d:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.d; break;
                }
                break;

            case l:
                switch (args[1].type)
                {
                    case b:*((signed long long*)programMemory + args[0].data.i) = (signed long long)args[1].data.b; break;
                    case s:*((signed long long*)programMemory + args[0].data.i) = (signed long long)args[1].data.s; break;
                    case i:*((signed long long*)programMemory + args[0].data.i) = (signed long long)args[1].data.i; break;
                    case l:*((signed long long*)programMemory + args[0].data.i) = (signed long long)args[1].data.l; break;
                    case f:*((signed long long*)programMemory + args[0].data.i) = (signed long long)args[1].data.f; break;
                    case d:*((signed long long*)programMemory + args[0].data.i) = (signed long long)args[1].data.d; break;
                }
                break;

            case f:
                switch (args[1].type)
                {
                    case b:*((float*)programMemory + args[0].data.i) = (float)args[1].data.b; break;
                    case s:*((float*)programMemory + args[0].data.i) = (float)args[1].data.s; break;
                    case i:*((float*)programMemory + args[0].data.i) = (float)args[1].data.i; break;
                    case l:*((float*)programMemory + args[0].data.i) = (float)args[1].data.l; break;
                    case f:*((float*)programMemory + args[0].data.i) = (float)args[1].data.f; break;
                    case d:*((float*)programMemory + args[0].data.i) = (float)args[1].data.d; break;
                }
                break;

            case d:
                switch (args[1].type)
                {
                    case b:*((double*)programMemory + args[0].data.i) = (double)args[1].data.b; break;
                    case s:*((double*)programMemory + args[0].data.i) = (double)args[1].data.s; break;
                    case i:*((double*)programMemory + args[0].data.i) = (double)args[1].data.i; break;
                    case l:*((double*)programMemory + args[0].data.i) = (double)args[1].data.l; break;
                    case f:*((double*)programMemory + args[0].data.i) = (double)args[1].data.f; break;
                    case d:*((double*)programMemory + args[0].data.i) = (double)args[1].data.d; break;
                }
                break;
        }
    }

    inline void BCS(ProgramType* args, unsigned char* programMemory)
    {
        args[0].data.l = 0;
        switch (args[1].type)
        {
            case b:*((unsigned char*)programMemory + args[0].data.i) = args[1].data.b; break;
            case s:*((unsigned short*)programMemory + args[0].data.i) = args[1].data.s; break;
            case i:*((unsigned long*)programMemory + args[0].data.i) = args[1].data.i; break;
            case l:*((unsigned long long*)programMemory + args[0].data.i) = args[1].data.l; break;
            case f:*((float*)programMemory + args[0].data.i) = args[1].data.f; break;
            case d:*((double*)programMemory + args[0].data.i) = args[1].data.d; break;
        }
    }
}