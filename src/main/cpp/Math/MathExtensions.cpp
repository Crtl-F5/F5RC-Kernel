#include <cstdlib>
#include <Math>
#include <MathExtensions.hpp>

namespace MathExtensions
{
    float Lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    float LerpInverse(float a, float b, float v)
    {
        return (v - a) / (b - a);
    }

    float Clamp(float min, float max, float v)
    {
        return (v > max) ? max : ((v < min) ? min : v);
    }

    float CircularLerp(float a, float b, float t, float loop, ArcType arcType)
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

    const float Pi = 3.1415;
}