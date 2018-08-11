#pragma once
#include <encoder>

namespace HardwareInterfaces
{
    GenericNonBinarySensor::GenericNonBinarySensor(frc::Encoder nonBinarySensor)
    {
        sensorType = Encoder;
        nonBinarySensor.encoder = nonBinarySensor;
    }

    float GenericNonBinarySensor::getValue()
    {
        switch (sensorType)
        {
            case Encoder:
                return nonBinarySensor.encoder.getValue()
                break;
        }
    }
}