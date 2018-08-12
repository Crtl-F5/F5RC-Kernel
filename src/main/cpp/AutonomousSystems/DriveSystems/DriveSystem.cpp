#include <Vectors.hpp>
#include <Curve.hpp>
#include <Functions.hpp>
#include <DriveSystem.hpp>
#include <iosteam>
#include <MathExtensions>
#include <algorithm>
#include <ctgmath>
#include <ctime>

#define None 0
#define Arc 1
#define Spline 1

namespace AutonomousSystems::DriveSystems
{
    void DriveSystem::ReadCommand(unsigned char[] data, long* position) // Commands compiled from a human readable format
    {
        clock_t minDuration;
        memcpy(&minDuration, data + *position++, sizeof(clock_t));
        startTime = clock();
        earliestEndTime = startTime + minDuration;

        switch (data[*(position)++]) // Path type
        {
            case None:
                path = nullptr;
                break;

            case Arc:
                path = new Arc();
                memcpy(path, data + *position, sizeof(Arc));
                (*position) += sizeof(Arc);
                break;
        
            default: // Error handling, should the robot completely halt autonomous mode to prevent damage or log the error and attempt to continue
                cout << data[*(position) - 1] << " is not a valid curve type code. Index: " << *(position) - 1;
                break;
        }

        switch (data[*(position)++]) // SpeedMap type
        {
            case None:
                path = nullptr;
                break;

            case Spline:
                path = new Spline();
                memcpy(path, data + *position, sizeof(Spline));
                (*position) += sizeof(Spline);
                break;
        
            default: // Error handling, should the robot completely halt autonomous mode to prevent damage or log the error and attempt to continue
                cout << data[*(position) - 1] << " is not a valid function type code. Index: " << *(position) - 1;
                break;
        }

        switch (data[*(position)++]) // HeadingMap type
        {
            case None:
                path = nullptr;
                break;

            case Spline:
                path = new Spline();
                memcpy(path, data + *position, sizeof(Spline));
                (*position) += sizeof(Spline);
                break;
        
            default: // Error handling, should the robot completely halt autonomous mode to prevent damage or log the error and attempt to continue
                cout << data[*(position) - 1] << " is not a valid function type code. Index: " << *(position) - 1;
                break;
        }
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