#pragma once
#include <Spark.h>
#include <Talon.h?>

struct GenericMotor
{
    void set(float value);

    enum { Spark, Talon } motorType;
    
    union motor
    {
        frc::Spark spark;
        frc::Talon talon;
    };
};