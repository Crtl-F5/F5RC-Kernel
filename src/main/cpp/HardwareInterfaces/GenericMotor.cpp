#include <Spark.h>
#include <Talon.h>
#include <GenericMotor.hpp>

namespace HardwareInterfaces
{
    GenericMotor::GenericMotor(Spark motor)
    {
        motorType = Spark;
        motor.spark = motor;
    }

    GenericMotor::GenericMotor(Talon motor)
    {
        motorType = Talon;
        motor.talon = motor;
    }

    void GenericMotor::set(float value)
    {   
        switch (motorType)
        {
            case Spark:
                motor.spark.set(value);
                break;

            case Talon:
                motor.talon.set(value);
                break;
        }
    };
}