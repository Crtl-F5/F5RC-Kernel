#pragma once

ProgramType fromLowerBits(unsigned char typeData, long* index, unsigned char* data);
ProgramType fromUpperBits(unsigned char typeData, long* index, unsigned char* data);

struct ProgramType
{
    public:
    ProgramTypeData getAbsoluteData(unsigned char* programMemory);
    bool isPointer;
    enum { b, s, i, l, f, f} type;
    ProgramTypeData data;
};

union ProgramTypeData
{
    signed char b;
    signed short s;
    signed long i;
    signed long long l;
    float f;
    double d;
};