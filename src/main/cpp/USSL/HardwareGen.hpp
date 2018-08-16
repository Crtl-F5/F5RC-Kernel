#pragma once
#include <spark.h>
#include <talon.h>
#include <encoder.h>

namespace USSL
{
    inline void GEN_MTR_SPK(ProgramType* args, unsigned char* programMemory)
    {
        *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new GenericMotornew(new park(args[1].data.b))));
    }

    inline void GEN_MTR_TLN(ProgramType* args, unsigned char* programMemory)
    {
        *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new GenericMotornew(new Talon(args[1].data.b))));
    }

    inline void GEN_SEN_ENC(ProgramType* args, unsigned char* programMemory)
    {
        *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new GenericNonBinarySensor(new Encoder(args[1].data.b, args[2].data.c, args[3].data.f))));
    }
}