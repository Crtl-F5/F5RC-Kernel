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
        void Reconstruct(unsigned char[] data, int* position);
        void Update();
        short GetStatus();

        protected:
        virtual void BaseUpdate(float speed, float turnPower, float targetHeading);
        virtual void BaseDeconstruct();
        virtual Math::Vector2 BaseGetPosition();

        private:
        Curve* path;
        Function* speedMap;
        Function* bearingMap;

        MathExtensions::PIDController devianceCorrection;
    };
}