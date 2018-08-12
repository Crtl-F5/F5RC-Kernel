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
    void DriveSystem::ReadCommand(unsigned char* data, long* position, unsigned char* memory) //TODO: Add more validation
    {
        clock_t minDuration;
        memcpy(&minDuration, data + *position++, sizeof(clock_t));
        startTime = clock();
        earliestEndTime = startTime + minDuration;
        long oldPosition = position;
        bool lower = true;

        switch (fromBits(data[oldPosition], position, data, &lower).getAbsoluteData(memory).data.b) // Path type
        {
            case None:
                path = nullptr;
                break;

            case Arc:
                Vector2 c;
                c.x = fromBits(data[oldPosition++], position, data, &lower).getAbsoluteData(memory).data.f;
                c.y = fromBits(data[oldPosition], position, data, &lower).getAbsoluteData(memory).data.f;
                path = new Arc(c, fromBits(data[oldPosition++], position, data, &lower).data.f, fromBits(data[oldPosition], position, data, &lower).data.f, fromBits(data[oldPosition++], position, data, &lower).data.f);
                break;
        
            default: // Error handling, should the robot completely halt autonomous mode to prevent damage or log the error and attempt to continue
                cout << "Invalid function arguments at: " << *(position) - 1;
                break;
        }

        switch (fromBits(data[oldPosition], position, data, &lower).getAbsoluteData(memory).data.b) // SpeedMap type
        {
            case None:
                speedMap = nullptr;
                break;

            case Spline:
                speedMap = new Spline(fromBits(data[oldPosition++], position, data, &lower).data.f, fromBits(data[oldPosition++], position, data, &lower).data.f, fromBits(data[oldPosition++], position, data, &lower).data.f, fromBits(data[oldPosition++], position, data, &lower).data.f);
                break;
        
            default: // Error handling, should the robot completely halt autonomous mode to prevent damage or log the error and attempt to continue
                cout << "Invalid function arguments at: " << *(position) - 1;
                break;
        }

        switch (fromBits(data[oldPosition], position, data, &lower).getAbsoluteData(memory).data.b) // bearingMap type
        {
            case None:
                bearingMap = nullptr;
                break;

            case Spline:
                bearingMap = new Spline(fromBits(data[oldPosition++], position, data, &lower).data.f, fromBits(data[oldPosition++], position, data, &lower).data.f, fromBits(data[oldPosition++], position, data, &lower).data.f, fromBits(data[oldPosition++], position, data, &lower).data.f);
                break;
        
            default: // Error handling, should the robot completely halt autonomous mode to prevent damage or log the error and attempt to continue
                cout << "Invalid function arguments at: " << *(position) - 1;
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