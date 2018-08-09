#include <Spline>

namespace MathExtensions::Functions
{
    Spline(float startY, float endY, float startD, float endD)
    {
        //TODO: Implement
    }

    float getValue(float x);
    {
        return a * x * x * x + b * x * x + c * x + d;
    }

    float getDerivative(float x)
    {
        return 3 * a * x * x + 2 * b * x + c;
    }
}