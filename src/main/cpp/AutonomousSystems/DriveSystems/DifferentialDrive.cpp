#pragma once
#include <DriveSystem.hpp>
#include <algorithm>

namespace AutonomousSystems::DriveSystems
{
    DifferentialDrive::DifferentialDrive();
    DifferentialDrive::~DifferentialDrive();

    void DifferentialDrive::BaseUpdate(float basePower, float headingPower, float bearingPower)
    {
        float powerTweak = std::max(1, std::max(abs(basePower + headingPower), abs(basePower - headingPower)));
        motorLHS.set((basePower + headingPower) / powerTweak);
        motorLHS.set((basePower - headingPower) / powerTweak);
        //TODO: Add position and rotation update
    }

    void DifferentialDrive::BaseClear()
    {
        RHSEncoder.reset();
        LHSEncoder.reset();
        lastRHSDistance = 0;
        lastLHSDistance = 0;
    }
}