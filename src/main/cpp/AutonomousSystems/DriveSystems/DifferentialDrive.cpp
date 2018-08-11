#pragma once
#include <DriveSystem.hpp>
#include <algorithm>
#include <math.h>

namespace AutonomousSystems::DriveSystems
{
    DifferentialDrive::DifferentialDrive();
    DifferentialDrive::~DifferentialDrive();

    void DifferentialDrive::BaseUpdate(float basePower, float headingPower, float bearingPower)
    {
        float powerTweak = std::max(1, std::max(abs(basePower + headingPower), abs(basePower - headingPower)));
        motorLHS.set((basePower + headingPower) / powerTweak);
        motorRHS.set((basePower - headingPower) / powerTweak);
        float theta = (LHSEncoder.getDistance() - lastLHSDistance - RHSEncoder.getDistance() + lastRHSDistance) / wheelSpacing;
        float diagonalDistance = ((LHSEncoder.getDistance() - lastLHSDistance) / theta - wheelSpacing / 2) * sqrt(2 * (1 - cos(theta)));
        float phi = theta / 2 - rotation;

        rotation -= theta;
        position.x += diagonalDistance * cos(phi);
        position.y += diagonalDistance * sin(phi);
    }

    void DifferentialDrive::BaseClear()
    {
        RHSEncoder.reset();
        LHSEncoder.reset();
        lastRHSDistance = 0;
        lastLHSDistance = 0;
    }
}