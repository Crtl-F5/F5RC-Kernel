#include <cmath>
#include <cstdlib>
#include <Arc.hpp>
#include <MathExtensions.hpp>

namespace Curves::MathExtensions
{
    Arc::Arc() {}
    Arc::~Arc() {}

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

    float getValueInverse(MathExtensions::Vector2 point)
    {
        return (point.y > centre.y) ? MathExtensions::LerpInverse(startAngle, endAngle, Math::acos((point.x - centre.x) / radius)) : MathExtensions::LerpInverse(startAngle, endAngle, 2 * Math::Pi - Math::acos((point.x - centre.x) / radius));
    }

    float Arc::getDerivative(float t)
    {
        return (MathExtensions::Lerp(startAngle, endAngle, t) + 1.5 * Math::Pi) % (2 * Math::Pi);
    }

    float Arc::getNearestPoint(MathExtensions::Vector2 point)
    {
        return MathExtensions::Clamp(0, 1, getValueInverse(point));
    }

    float Arc::getLength(float t)
    {
        return (endAngle - startAngle) * radius; 
    }

    float Arc::getCompletion(MathExtensions::Vector2 position, float heading)
    {
        return getNearestPoint(position);
    }
}