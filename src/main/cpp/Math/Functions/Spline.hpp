#pragma once

namespace MathExtension::Functions
{
    class Spline : public Function
    {
        public:
        Spline(float startY, float endY, float startD, float endD);
        float getValue(float x);
        float getDerivative(float x);

        private:
        float a;
        float b;
        float c;
        float d;
    }
}