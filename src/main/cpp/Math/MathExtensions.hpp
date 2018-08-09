#pragma once
#define MinorArc false
#define MajorArc true
typedef ArcType bool;

namespace MathExtensions
{
    float Lerp(float a, float b, float t);
    float LerpInverse(float a, float b, float v);
    float Clamp(float min, float max, float v);
    float CircularLerp(float a, float b, float t, float loop);
    const float PI = 3.14159265359;
}