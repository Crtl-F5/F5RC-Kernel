#pragma once
#include <Vectors>

namespace MathExtensions::Vector
{
    float SquareDistance(MathExtensions::Vector2 a, MathExtensions::Vector2 b)
    {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); 
    }
}