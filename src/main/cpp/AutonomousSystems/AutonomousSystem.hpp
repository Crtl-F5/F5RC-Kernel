#pragma once

namespace AutonomousSystems
{  
    class AutonomousSystem
    {
        public:
        virtual System(){}
        virtual ~System(){}
        virtual void Reconstruct(unsigned char[] data);
        virtual void Update() = 0;
        virtual short GetStatus() = 0;
    };
}