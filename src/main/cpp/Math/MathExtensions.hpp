#pragma once
#define MinorArc false
#define MajorArc true
typedef ArcType bool;

namespace MathExtensions
{
    template <class T> Lerp T (T a, T b, T t);
    template <class T> T LerpInverse(T a, T b, T v);
    template <class T> T Clamp(T min, T max, T v);
    template <class T> T CircularLerp(T a, T b, T t, T loop);
    const float PI = 3.14159265359;
}