#include <Vectors.hpp>
#include <Curve.hpp>
#include <Functions.hpp>
#include <DriveSystem.hpp>

namespace AutonomousSystems::DriveSystems
{
    void DriveSystem::ReadCommand(unsigned char[] data, int* position)
    {
        //TODO: Implement this
    }

    void DriveSystem::Clear()
    {
        delete path;
        delete speedMap;
        delete bearingMap;
    }

    void DriveSystem::Update()
    {
        //TODO: Change based on what side of line bot is on
        MathExtensions::Vector2 currentPosition = BaseGetPosition();
        float pathCompletion = path->getNearestPoint(currentPosition);
        BaseUpdate
        (
            speedController::Update(speedMap->getValue(pathCompletion)),
            headingController::Update(MathExtensions::Vector::SquareDistance(currentPosition, path->getValue(pathCompletion)) + path->getDerivative(pathCompletion)), 
            bearingController::Update(bearingMap == nullptr :? 0 : bearingMap->getValue(pathCompletion))
        );
    }

    short DriveSystem::GetStatus()
    {
        return completionTolerance > BaseGetPosition();
    }
}