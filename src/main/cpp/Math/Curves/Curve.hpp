#pragma once
#include <Vectors.hpp>

namespace MathExtensions::Curves
{
    class Curve
    {
        public:
        virtual Curve(){}
        virtual ~Curve(){}
        virtual MathExtensions::Vector2 getValue(float t) = 0;
        virtual float getValueInverse(MathExtensions::Vector2 point) = 0;
        virtual float getDerivative(float t) = 0;
        virtual float getNearestPoint(MathExtensions::Vector2 point) = 0;
        virtual float getCompletion(MathExtensions::Vector2 point, float heading);
        virtual float getLength(float t) = 0;
    };
}