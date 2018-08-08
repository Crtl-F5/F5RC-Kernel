#include <Vectors.hpp>
#include <Curve.hpp>
#include <AutonomousSystem.hpp>

namespace AutonomousSystems::DriveSystems
{
    class DriveSystem : AutonomousSystem
    {
        public:
        void Reconstruct(unsigned char[] data, int* position);
        void Update();
        short GetStatus();

        protected:
        void BaseUpdate();
        void BaseDeconstruct();
        Math::Vector2 GetPosition();

        private:
        Curve* path;
        Function* speedMap;
    };
}