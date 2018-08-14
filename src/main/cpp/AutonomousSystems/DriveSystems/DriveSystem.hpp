#pragma once
#include <Vectors.hpp>
#include <Curve.hpp>
#include <AutonomousSystem.hpp>
#include <MathExtensions>
#include <time.h>

namespace AutonomousSystems::DriveSystems
{
    class DriveSystem : AutonomousSystem
    {
        public:
        DriveSystem(float completionTolerance, PIDController devianceCorrectionController, PIDController speedController, PIDController headingController, PIDController bearingController);
        void Rebuild(Curve* path, Function* speedMap, Function* bearingMap, long minCompletionTime);
        void Clear() override;
        void Update() override;
        short GetStatus() override;

        protected:
        virtual void BaseUpdate(float basePower, float headingPower, float bearingPower);
        virtual void BaseClear();

        MathExtensions::Vector2 position;
        MathExtensions::Vector2 lastPostion;
        float heading;
        float bearing;
        private:
        float completion;
        clock_t startTime;
        clock_t earliestEndTime;
        
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