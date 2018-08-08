#include <cmath>
#include <Arc.hpp>

namespace Curves::MathExtensions
{
    Arc::Arc(Math::Vector2 centre, float radius, float startAngle, float endAngle)
    {
        this->centre = centre;
        this->radius = radius;
        this->startAngle = startAngle;
        this->endAngle = endAngle;
    }

    Math::Vector2 Arc::getValue(float t)
    {
        Math::Vector2 output;
        output.x = cmath::cos(Math::Lerp(startAngle, endAngle, t)) * radius + centre.x;
        output.y = cmath::sin(Math::Lerp(startAngle, endAngle, t)) * radius + centre.y;
        return output;
    }

    float getValueInverse(Math::Vector2 point)
    {
        return (point.y > centre.y) ? Math::LerpInverse(startAngle, endAngle, Math::acos((point.x - centre.x) / radius)) : Math::LerpInverse(startAngle, endAngle, 2 * Math::Pi - Math::acos((point.x - centre.x) / radius));
    }

    float Arc::getDerivative(float t)
    {
        return (Math::Lerp(startAngle, endAngle, t) + 1.5 * Math::Pi) % (2 * Math::Pi);
    }

    float getNearestPoint(Math::Vector2 point)
    {
        return Math::Clamp(0, 1, getValueInverse(point));
    }
}