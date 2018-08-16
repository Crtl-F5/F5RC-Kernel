#pragma once
#include <AutonomousSystem.hpp>
#include <LinkedList.hpp>
#include <DifferentialDrive.hpp>

namespace USSL
{
    inline void SYS_ADD(ProgramType* args, unsigned char* programMemory, LinkedListNode<AutonomousSystem> systems)
    {
        while (systems.payload != nullptr) systems = *systems.next;
        systems.payload = *((AutonomousSystem*)((void*)args[0].getAbsoluteData(programMemory).data.i));
        systems.next = new LinkedListNode<AutonomousSystem>();
    }

    inline void GEN_SYS_DRV_DIF(ProgramType* args, unsigned char* programMemory)
    {
        *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new DifferentialDrive
        (
            (GenericNonBinarySensor*)((void*)args[1].data.i),
            (GenericNonBinarySensor*)((void*)args[2].data.i),
            (GenericMotor*)((void*)args[3].data.i),
            (GenericMotor*)((void*)args[4].data.i),
            args[5].data.f,
            args[6].data.f,
            *((PIDController*)((void*)args[7].data.i)),
            *((PIDController*)((void*)args[8].data.i)),
            *((PIDController*)((void*)args[9].data.i)),
            *((PIDController*)((void*)args[10].data.i))
        )));
    }
}