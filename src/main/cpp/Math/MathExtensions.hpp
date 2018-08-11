#pragma once
#define MinorArc false
#define MajorArc true
#define Square(x) x * x
#define Cube(x) x * x * x
typedef ArcType bool;

namespace MathExtensions
{
    template <class T> T Lerp(T a, T b, T t);
    template <class T> T LerpInverse(T a, T b, T v);
    template <class T> T Clamp(T min, T max, T v);
    template <class T> T CircularLerp(T a, T b, T t, T loop);
    template <class T> T CircularLerpInverse(T a, T b, T v, T loop);
    const float PI = 3.14159265359;
}