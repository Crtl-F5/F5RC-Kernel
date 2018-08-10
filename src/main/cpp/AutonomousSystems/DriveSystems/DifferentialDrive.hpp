#pragma once
#include <DriveSystem.hpp>
#include <Vectors.hpp>
#include <PIDController.hpp>
#include <encoder.h>
#include <HardwareConfig.hpp>
#include <GenericMotor>

namespace AutonomousSystems::DriveSystems
{
    
    class DifferentialDrive : public DriveSystem
    {
        public:
        DifferentialDrive();
        ~DifferentialDrive();
        void BaseUpdate(float basePower, float headingPower, float bearingPower);
        void BaseClear();
        Math::Vector2 BaseGetPosition();

        private:
        frc::encoder LHSEncoder;
        frc::encoder RHSEncoder;
        float lastLHSDistance;
        float lastRHSDistance;

        GenericMotor motorLHS;
        GenericMotor motorRHS;

        float distancePerEncoderPulse;
        float wheelSpacing;
    };
}