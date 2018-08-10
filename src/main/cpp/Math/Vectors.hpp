#pragma once

namespace MathExtensions
{
    struct Vector2
    {
        float x;
        float y;
    };

    float SquareDistance(MathExtensions::Vector2 a, MathExtensions::Vector2 b);
}