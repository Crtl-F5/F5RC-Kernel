#include <ProgramType.hpp>
#include <string.h>
#define GetBit(i, n) (i >> n) & 1

ProgramTypeData ProgramType::getAbsoluteData(unsigned char* programMemory)
{
    ProgramType ouput;
    ouput.isPointer = isPointer;
    if (isPointer)
    {
        switch type
        {
            case b: ouput.data.b = *((unsigned char*)programMemory + data.i); break;
            case s: ouput.data.s = *((unsigned short*)programMemory + data.i); break;
            case i: ouput.data.i = *((unsigned long*)programMemory + data.i); break;
            case l: ouput.data.l = *((unsigned long long*)programMemory + data.i); break;
            case f: ouput.data.f = *((float*)programMemory + data.i); break;
            case d: ouput.data.d = *((double*)programMemory + data.i); break;
        }
    }
    else ouput.data = data;
    output.type = type;
    return ouput;
}

ProgramType fromBits(unsigned char* typeData, long& index, unsigned char* data, bool& lower)
{
    lower = !lower;
    if (lower) return fromUpperBits(*(typeData++), index, data);
    return fromLowerBits(*typeData, index, data);
}

ProgramType fromLowerBits(unsigned char typeData, long& index, unsigned char* data)
{
    ProgramType output;
    output.isPointer = GetBit(typeData, 0);
    if (ouput.isPointer)
    {
        switch (GetBit(typeData, 1) + GetBit(typeData, 2) * 2 + GetBit(typeData, 3) * 4)
        {
            case 0: ouput.type = b; break;
            case 1: ouput.type = s; break;
            case 2: ouput.type = i; break;
            case 3: ouput.type = l; break;
            case 4: ouput.type = f; break;
            case 5: ouput.type = d; break;
        }
        memcpy(&ouput.data.i, data[index], 4);
        (index) += 4;
    }

    else
    {
        switch (GetBit(typeData, 1) + GetBit(typeData, 2) * 2 + GetBit(typeData, 3) * 4)
        {
            case 0:
                ouput.type = b;
                ouput.data.b = data[(index)++];
                break;

            case 1:
                output.type = s;
                memcpy(&ouput.data.s, data[index], 2);
                (index) += 2;
                break;

            case 2:
                output.type = i;
                memcpy(&ouput.data.i, data[index], 4);
                (index) += 4;
                break;

            case 3:
                output.type = l;
                memcpy(&ouput.data.l, data[index], 8);
                (index) += 8;
                break;

            case 4:
                output.type = f;
                memcpy(&ouput.data.f, data[index], 4)
                (index) += 4;
                break;

            case 5:
                output.type = d;
                memcpy(&ouput.data.d, data[index], 8)
                (index) += 8;
                break;
        }
    }
}

ProgramType fromUpperBits(unsigned char typeData, long& index, unsigned char* data)
{
    ProgramType output;
    output.isPointer = GetBit(typeData, 4);
    if (ouput.isPointer)
    {
        switch (GetBit(typeData, 5) + GetBit(typeData, 6) * 2 + GetBit(typeData, 7) * 4)
        {
            case 0: ouput.type = b; break;
            case 1: ouput.type = s; break;
            case 2: ouput.type = i; break;
            case 3: ouput.type = l; break;
            case 4: ouput.type = f; break;
            case 5: ouput.type = d; break;
        }
        memcpy(&ouput.data.i, data[index], 4);
        (index) += 4;
    }

    else
    {
        switch (GetBit(typeData, 5) + GetBit(typeData, 6) * 2 + GetBit(typeData, 7) * 4)
        {
            case 0:
                ouput.type = b;
                ouput.data.b = data[(index)++];
                break;

            case 1:
                output.type = s;
                memcpy(&ouput.data.s, data[*index], 2);
                (index) += 2;
                break;

            case 2:
                output.type = i;
                memcpy(&ouput.data.i, data[index], 4);
                (index) += 4;
                break;

            case 3:
                output.type = l;
                memcpy(&ouput.data.l, data[index], 8);
                (index) += 8;
                break;

            case 4:
                output.type = f;
                memcpy(&ouput.data.f, data[index], 4)
                (index) += 4;
                break;

            case 5:
                output.type = d;
                memcpy(&ouput.data.d, data[index], 8)
                (index) += 8;
                break;
        }
    }
}