#pragma once

namespace AutonomousSystems
{  
    class AutonomousSystem
    {
        public:
        virtual System(){}
        virtual ~System(){}
        virtual void ReadCommand(unsigned char[] data, long* index);
        virtual void Clear();
        virtual void Update() = 0;
        virtual short GetStatus() = 0;
    };
}