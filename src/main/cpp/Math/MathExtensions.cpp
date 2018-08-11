#pragma once
#include <cstdlib>
#include <Math>
#include <MathExtensions.hpp>

namespace MathExtensions
{
    template <class T> Lerp T (T a, T b, T t);
    {
        return a + t * (b - a);
    }

    template <class T> T LerpInverse(T a, T b, T v)
    {
        return (v - a) / (b - a);
    }

    template <class T> T Clamp(T min, T max, T v)
    {
        return (v > max) ? max : ((v < min) ? min : v);
    }

    template <class T> T CircularLerp(T a, T b, T t, T loop)
    {
        if (!(arcType && abs(a - b) > abs(a - loop - b)))
        {
            return Lerp(a, b, t);
        }
        else
        {
            return Lerp(a, b + loop, t) % loop;
        }
        
    }

    float GetInvalid()
    {
        long a = 0x7f800001;
        return *((float*)&a);
    }

    const float Pi = 3.1415;
}