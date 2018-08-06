#include <cmath>

namespace Curves::Math
{
    class Arc : public Curve
    {
        public:
        Math::Vector2 getValue(float t);
        float getValueInverse(Math::Vector2 point);
        float getDerivative(float t);
        float getNearestPoint(Math::Vector2 point);

        private:
        Math::Vector2 centre;
        float radius;
        float startAngle;
        float endAngle;
    };

    Math::Vector2 Arc::getValue(float t)
    {
        Math::Vector2 output;
        output.x = cmath::cos(Math::Lerp(startAngle, endAngle, t)) * radius + centre.x;
        output.y = cmath::sin(Math::Lerp(startAngle, endAngle, t)) * radius + centre.y;
        return output;
    }

    float getValueInverse(Math::Vector2 point)
    {
        if (point.y > centre.y) 
        {
            return Math::LerpInverse(startAngle, endAngle, Math::acos((point.x - centre.x) / radius));
        }

        else 
        {
            return Math::LerpInverse(startAngle, endAngle, 2 * Math::Pi - Math::acos((point.x - centre.x) / radius));
        }
    }

    float Arc::getDerivative(float t)
    {
        return (Math::Lerp(startAngle, endAngle, t) + 1.5 * Math::Pi) % (2 * Math::Pi);
    }

    float getNearestPoint(Math::Vector2 point)
    {
    }
}