#pragma once
#include <DriveSystem.hpp>
#include <algorithm>
#include <math.h>

namespace AutonomousSystems::DriveSystems
{
    DifferentialDrive::DifferentialDrive
    (
        HardwareInterfaces::GenericNonBinarySensor* LHSSensor,
        HardwareInterfaces::GenericNonBinarySensor* RHSSensor,
        HardwareInterfaces::GenericMotor* motorLHS,
        HardwareInterfaces::GenericMotor* motorRHS,
        float wheelSpacing
    )
    {
        this.LHSSensor = LHSSensor;
        this.RHSSensor = RHSSensor;
        this.lastLHSDistance = 0;
        this.lastRHSDistance = 0;
        this.motorLHS = motorLHS;
        this.motorRHS = motorRHS;
        this.wheelSpacing = wheelSpacing;
    }

    void DifferentialDrive::BaseUpdate(float basePower, float headingPower, float bearingPower)
    {
        float powerTweak = std::max(1, std::max(abs(basePower + headingPower), abs(basePower - headingPower)));
        motorLHS.set((basePower + headingPower) / powerTweak);
        motorRHS.set((basePower - headingPower) / powerTweak);
        float theta = (LHSSensor.Value() - lastLHSDistance - RHSSensor.getValue() + lastRHSDistance) / wheelSpacing;
        float diagonalDistance = ((LHSSensor.getValue() - lastLHSDistance) / theta - wheelSpacing / 2) * sqrt(2 * (1 - cos(theta)));
        float phi = theta / 2 - rotation;

        rotation -= theta;
        position.x += diagonalDistance * cos(phi);
        position.y += diagonalDistance * sin(phi);

        lastLHSDistance = LHSSensor.getValue();
        lastRHSDistance = RHSSensor.getValue();
    }

    void DifferentialDrive::BaseClear()
    {
        RHSSensor.reset();
        LHSSensor.reset();
        lastRHSDistance = 0;
        lastLHSDistance = 0;
    }
}