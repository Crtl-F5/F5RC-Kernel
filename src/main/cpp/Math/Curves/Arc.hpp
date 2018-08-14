#pragma once
#include <Vectors.hpp>

namespace MathExtensions::Curves
{
    class Arc : public Curve
    {
        public:
        Arc(MathExtensions::Vector2 centre, float radius, float startAngle, float endAngle);
        Arc::Arc(float centreX, float centreY, float radius, float startAngle, float endAngle);
        MathExtensions::Vector2 getValue(float t);
        float getValueInverse(MathExtensions::Vector2 point);
        float getDerivative(float t);
        float getNearestPoint(MathExtensions::Vector2 point);
        float getLength(float t);
        float getCompletion(MathExtensions::Vector2 point, float heading);

        private:
        MathExtensions::Vector2 centre;
        float radius;
        float startAngle;
        float endAngle;
    };
}