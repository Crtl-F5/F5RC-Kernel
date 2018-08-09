#pragma once
#include <Vectors.hpp>

namespace Curves::MathExtensions
{
    class Arc : public Curve
    {
        public:
        Arc::Arc(MathExtensions::Vector2 centre, float radius, float startAngle, float endAngle);
        MathExtensions::Vector2 getValue(float t);
        float getValueInverse(MathExtensions::Vector2 point);
        float getDerivative(float t);
        float getNearestPoint(MathExtensions::Vector2 point);

        private:
        MathExtensions::Vector2 centre;
        float radius;
        float startAngle;
        float endAngle;
    };
}