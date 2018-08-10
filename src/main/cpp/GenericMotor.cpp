#include <Spark.h>
#include <Talon.h?>

struct GenericMotor
{
    void set(float value)
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
    }
};