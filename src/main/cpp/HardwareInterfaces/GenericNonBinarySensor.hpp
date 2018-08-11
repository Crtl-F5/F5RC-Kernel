#pragma once
#include <encoder.h>

namespace HardwareInterfaces
{
    struct GenericNonBinarySensor
    {
        public:
        GenericNonBinarySensor(frc::Encoder nonBinarySensor);
        float getValue();

        enum { Encoder } sensorType;
        union nonBinarySensor
        {
            frc::Encoder encoder;
        };
    }
}