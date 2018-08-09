#include <Vectors.hpp>
#include <Curve.hpp>
#include <Functions.hpp>
#include <DriveSystem.hpp>

namespace AutonomousSystems::DriveSystems
{
    DriveSystem::Update()
    {
        //TODO: Change based on what side of line bot is on
        MathExtensions::Vector2 currentPosition = BaseGetPosition();
        float pathCompletion = path->getNearestPoint(currentPosition);
        BaseUpdate
        (
            devianceCorrection.Update(speedMap->getValue(pathCompletion),
            MathExtensions::Vector::SquareDistance(currentPosition, path->getValue(pathCompletion)), 
            bearingMap->getValue(pathCompletion)
        );
    }
}