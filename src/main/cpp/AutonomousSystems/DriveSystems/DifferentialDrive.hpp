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
        DifferentialDrive
        (
            HardwareInterfaces::GenericNonBinarySensor* LHSSensor,
            HardwareInterfaces::GenericNonBinarySensor* RHSSensor,
            HardwareInterfaces::GenericMotor* motorLHS,
            HardwareInterfaces::GenericMotor* motorRHS,
            float wheelSpacing,
            float completionTolerance, 
            PIDController devianceCorrectionController, 
            PIDController speedController, 
            PIDController headingController,
            PIDController bearingController
        );
        ~DifferentialDrive();
        void BaseUpdate(float basePower, float headingPower, float bearingPower) override;
        void BaseClear() override;

        private:
        HardwareInterfaces::GenericNonBinarySensor* LHSSensor;
        HardwareInterfaces::GenericNonBinarySensor* RHSSensor;
        float lastLHSDistance;
        float lastRHSDistance;

        HardwareInterfaces::GenericMotor* motorLHS;
        HardwareInterfaces::GenericMotor* motorRHS;

        float wheelSpacing;
    };
}