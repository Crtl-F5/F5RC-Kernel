#pragma once
#include <Vectors.hpp>
#include <Curve.hpp>
#include <AutonomousSystem.hpp>
#include <MathExtensions>

namespace AutonomousSystems::DriveSystems
{
    class DriveSystem : AutonomousSystem
    {
        public:
        void ReadCommand(unsigned char[] data, int* index);
        void Clear();
        void Update();
        short GetStatus();

        protected:
        virtual void BaseUpdate(float basePower, float headingPower, float bearingPower);
        virtual void BaseClear();

        MathExtensions::Vector2 position;
        float heading;
        private:
        Curve* path;
        Function* speedMap;
        Function* bearingMap;
        
        float completionTolerance;
        MathExtensions::PIDController devianceCorrectionController;
        MathExtensions::PIDController speedController;
        MathExtensions::PIDController headingController;
        MathExtensions::PIDController bearingController;
    };
}