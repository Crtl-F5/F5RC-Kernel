#pragma once
#include <Spark.h>
#include <Talon.h?>


namespace HardwareInterfaces
{
    struct GenericMotor
    {
        public:
        GenericMotor(frc::Spark motor);
        GenericMotor(frc::Talon motor);
        void set(float value);

        enum { Spark, Talon } motorType;
        union motor
        {
            frc::Spark spark;
            frc::Talon talon;
        };
    };
}