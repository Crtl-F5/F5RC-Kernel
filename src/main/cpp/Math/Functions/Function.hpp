#pragma once

namespace MathExtensions::Functions
{
    class Function
    {
        public:
        virtual Function(){}
        virtual ~Function(){}
        virtual float getValue(float x) = 0;
        virtual float getDerivative(float x) = 0;
    };
}