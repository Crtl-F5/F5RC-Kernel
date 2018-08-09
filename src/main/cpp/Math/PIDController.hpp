#pragma once

namespace MathExtensions
{
    class PIDController
    {
        public:
        PIDController(float P, float I, float D);
        float Update(float value);

        float target;
        float loopLength;
        private:
        float P;
        float I;
        float D;
        float offset;
        float integral;
        float lastError;
        clock_t lastTimeStamp;
    };
}