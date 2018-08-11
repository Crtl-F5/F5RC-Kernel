#pragma once
#include <DriveSystem.hpp>
#include <Vectors.hpp>
#include <PIDController.hpp>
#include <HardwareConfig.hpp>
#include <GenericMotor.hpp>
#include <GenericNonBinarySensor.hpp>

namespace AutonomousSystems::DriveSystems
{
    
    class DifferentialDrive : public DriveSystem
    {
        public:
        DifferentialDrive();
        ~DifferentialDrive();
        void BaseUpdate(float basePower, float headingPower, float bearingPower) override;
        void BaseClear() override;

        private:
        HardwareInterfaces::GenericNonBinarySensor* LHSEncoder;
        HardwareInterfaces::GenericNonBinarySensor* RHSEncoder;
        float lastLHSDistance;
        float lastRHSDistance;

        HardwareInterfaces::GenericMotor* motorLHS;
        HardwareInterfaces::GenericMotor* motorRHS;

        float wheelSpacing;
    };
}