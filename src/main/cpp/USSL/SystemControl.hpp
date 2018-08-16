#pragma once
#include <AutonomousSystem.hpp>
#include <LinkedList.hpp>
#include <DifferentialDrive.hpp>

namespace USSL
{
    inline void SYS_WAT(ProgramType* args, unsigned char* programMemory, LinkedListNode<AutonomousSystem> systems)
    {
        do
        {
          bool cont = false;
          while (systems.payload != nullptr)
          {
            if (currentSystem->GetStatus() != 1) cont = true;
            currentSystem.Update();
          }
          Wait(0.01f);
        } while(cont);
    }

    inline void SYS_DRV(ProgramType* args, unsigned char* programMemory, LinkedListNode<AutonomousSystem> systems)
    {
        ((DriveSystem*)systems[args[0].data.b])->Rebuild((Curve*)args[1].data.i, (Function*)args[2].data.i, (Function*)args[3].data.i);
    }
}