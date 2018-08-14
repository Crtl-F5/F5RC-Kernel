#include <Vectors.hpp>
#include <Curve.hpp>
#include <Functions.hpp>
#include <DriveSystem.hpp>
#include <iosteam>
#include <MathExtensions>
#include <algorithm>
#include <ctgmath>
#include <ctime>
#include <ProgramType.hpp>

#define None 0
#define Arc 1
#define Spline 2

namespace AutonomousSystems::DriveSystems
{
    DriveSystem::DriveSystem(float completionTolerance, PIDController devianceCorrectionController, PIDController speedController, PIDController headingController, PIDController bearingController)
    {
        this.completionTolerance = completionTolerance;
        this.devianceCorrectionController = devianceCorrectionController;
        this.speedController = speedController;
        this.headingController = headingController;
        this.bearingController = bearingController;
    }

    void DriveSystem::Rebuild(Curve* path, Function* speedMap, Function* bearingMap, long minCompetionTime)
    {
        this.path = path;
        this.speedMap = speedMap;
        this.bearingMap = bearingMap;
        startTime = clock();
        earliestEndTime = startTime + minCompetionTime;
    }

    void DriveSystem::Clear()
    {
        delete path;
        delete speedMap;
        delete bearingMap;
    }

    void DriveSystem::Update()
    {
        float completion = MathExtensions::Lerp(startTime, earliestEndTime, clock());

        if (bearingMap != nullptr) completion = min(completion, MathExtensions.Clamp(MathExtensions::CircularLerpInverse(bearingMap->getValue(0), bearingMap->getValue(1), bearing)));
        if (path != nullptr) completion = min(completion, path->getCompletion(position, heading));

        if (speedMap != nullptr) speedController.target = speedMap->getValue(pathCompletion);
        if (path != nullptr) headingController.target = devianceCorrectionController.Update(MathExtensions::Vector::SquareDistance(currentPosition, path->getValue(pathCompletion))) + path->getDerivative(pathCompletion);
        if (bearingMap != nullptr) bearingController.target =  bearingMap->getValue(pathCompletion);

        lastPosition = position;
        BaseUpdate
        (
            speedMap == nullptr ?: 0 : speedController.Update(sqrt(MathExtensions::Vector::SquareDistance(position, lastPosition))),
            headingController.Update(heading),
            bearingController.Update(bearing)
        );
    }

    short DriveSystem::GetStatus()
    {
        return completion < completionTolerance;
    }
}