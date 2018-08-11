#include <Spline>
#include <MathExtensions>

namespace MathExtensions::Functions
{
    Spline::Spline() {}
    Spline::~Spline() {};

    Spline(float startY, float endY, float startD, float endD)
    {
        //TODO: Implement
    }

    float Spline::getValue(float x);
    {
        return a * Cube(x) + b * Square(x) + c * x + d;
    }

    float Spline::getDerivative(float x)
    {
        return 3 * a * Square(x) + 2 * b * x + c;
    }
}