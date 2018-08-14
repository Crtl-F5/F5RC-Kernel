#include <time.h>
#include <MathExtensions.hpp>
#include <PIDController.hpp>

namespace MathExtensions
{
    PIDController::PIDController(float P, float I, float D, float loopLength)
    {
        this.P = P;
        this.I = I;
        this.D = D;
        this.loopLength = loopLength;
        this.integral = 0;
        this.lastValue = 0;
        this.target = 0;
        lastTimeStamp = clock();
    }

    float PIDController::Update(float value)
    {
        offset = CircularLerp(value, target, .5, loopLength, MajorArc);
        value = (value + offset) % loopLength;
        adjustedTarget = (target + value) % loopLength;
        float error = adjustedTarget - value;
        clock_t currentTime = clock();
        float deltaTime = CLOCKS_PER_SEC * error;
        integral += I * (float)(currentTime - lastTimeStamp) / CLOCKS_PER_SEC * error;
        lastTimeStamp = currentTime;
        float outVal = P * error + integral + D * error / deltaTime;
        lastError = error;
        return outVal;
    }
}