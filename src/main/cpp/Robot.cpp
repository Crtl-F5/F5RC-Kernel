/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Robot.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <ProgramType.hpp>
#include <algorithm>

#include <SmartDashboard/SmartDashboard.h>
#include <Spark.h>

Robot::Robot() 
{
}

void Robot::RobotInit()
{
  bool first = true;
  for (auto & path: fs::directory_iterator(autoPathsDir))
  {
    std::string name = path.filename().string();
    if (first) m_chooser.AddDefault(name, name);
    else m_chooser.AddObject(name, name);
  }
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  string lastSelected = "";

  while (!IsAutonomous() && !IsOperatorControl())
  {
    std::string autoSelected = m_chooser.GetSelected();
    if (autoSelected == lastSelected)
    {
      Wait(0.1f);
    }
    else
    {
      std::cout << "Beginning to load autonomous program: " << autoSelected;
      lastSelected = autoSelected;
      ifsteam file(autoPathsDir + autoSelected, ios::in|ios::binary|ios::ate)

      streampos size = file.tellg();
      autoProgram = new unsigned char[size];
      file.seekg(0, ios::beg);
      file.read(autoProgram, size);
      programMemory = new unsigned char[*((long*)autoProgram)];
      std::cout << "Completed loading autonomous program: " << autoSelected;
    }
  }
}

inline template<class T> signed char cmp(T a, T b)
{
  if (a == b) return 0
  if (a > b) return 1;
  return -1;
}

void Robot::Autonomous() 
{
  long index = 4; // Seek past header data
  long oldIndex;
  while (true)
  {
    switch (autoProgram[index++])
    {
      case 0: // Add
        oldIndex = index;
        index += 2;
        ProgramType a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        ProgramTypeData b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        ProgramTypeData c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.i) = b.b + c.b; break;
            case s: *((signed short*)programMemory + a.i) = b.s + c.s; break;
            case i: *((signed long*)programMemory + a.i) = b.i + c.i; break;
            case l: *((signed long long*)programMemory + a.i) = b.l + c.l; break;
            case f: *((float*)programMemory + a.i) = b.f + c.f; break;
            case d: *((double*)programMemory + a.i) = b.d + c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 1: // Sub
        oldIndex = index;
        index += 2;
        ProgramType a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        ProgramTypeData b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        ProgramTypeData c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.i) = b.b - c.b; break;
            case s: *((signed short*)programMemory + a.i) = b.s - c.s; break;
            case i: *((signed long*)programMemory + a.i) = b.i - c.i; break;
            case l: *((signed long long*)programMemory + a.i) = b.l - c.l; break;
            case f: *((float*)programMemory + a.i) = b.f - c.f; break;
            case d: *((double*)programMemory + a.i) = b.d - c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 2: // Mul
        oldIndex = index;
        index += 2;
        ProgramType a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        ProgramTypeData b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        ProgramTypeData c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.i) = b.b * c.b; break;
            case s: *((signed short*)programMemory + a.i) = b.s * c.s; break;
            case i: *((signed long*)programMemory + a.i) = b.i * c.i; break;
            case l: *((signed long long*)programMemory + a.i) = b.l * c.l; break;
            case f: *((float*)programMemory + a.i) = b.f * c.f; break;
            case d: *((double*)programMemory + a.i) = b.d * c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 3: // Div
        oldIndex = index;
        index += 2;
        ProgramType a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        ProgramTypeData b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        ProgramTypeData c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.i) = b.b / c.b; break;
            case s: *((signed short*)programMemory + a.i) = b.s / c.s; break;
            case i: *((signed long*)programMemory + a.i) = b.i / c.i; break;
            case l: *((signed long long*)programMemory + a.i) = b.l / c.l; break;
            case f: *((float*)programMemory + a.i) = b.f / c.f; break;
            case d: *((double*)programMemory + a.i) = b.d / c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 4: // Mod
        oldIndex = index;
        index += 2;
        ProgramType a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        ProgramTypeData b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        ProgramTypeData c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.i) = b.b % c.b; break;
            case s: *((signed short*)programMemory + a.i) = b.s % c.s; break;
            case i: *((signed long*)programMemory + a.i) = b.i % c.i; break;
            case l: *((signed long long*)programMemory + a.i) = b.l % c.l; break;
            case f: *((float*)programMemory + a.i) = b.f % c.f; break;
            case d: *((double*)programMemory + a.i) = b.d % c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 5: // Min
        oldIndex = index;
        index += 2;
        ProgramType a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        ProgramTypeData b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        ProgramTypeData c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.i) = std::min(b.b, c.b); break;
            case s: *((signed short*)programMemory + a.i) = std::min(b.s, c.s); break;
            case i: *((signed long*)programMemory + a.i) = std::min(b.i, c.i); break;
            case l: *((signed long long*)programMemory + a.i) = std::min(b.l, c.l); break;
            case f: *((float*)programMemory + a.i) = std::min(b.f, c.f); break;
            case d: *((double*)programMemory + a.i) = std::min(b.d, c.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 6: // Max
        oldIndex = index;
        index += 2;
        ProgramType a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        ProgramTypeData b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        ProgramTypeData c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.i) = std::max(b.b, c.b); break;
            case s: *((signed short*)programMemory + a.i) = std::max(b.s, c.s); break;
            case i: *((signed long*)programMemory + a.i) = std::max(b.i, c.i); break;
            case l: *((signed long long*)programMemory + a.i) = std::max(b.l, c.l); break;
            case f: *((float*)programMemory + a.i) = std::max(b.f, c.f); break;
            case d: *((double*)programMemory + a.i) = std::max(b.d, c.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 7: // Cmp
        oldIndex = index;
        index += 2;
        ProgramType a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        ProgramTypeData b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        ProgramTypeData c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b && b.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.i) = cmp(b.b, c.b); break;
            case s: *((signed short*)programMemory + a.i) = cmp(b.s, c.s); break;
            case i: *((signed long*)programMemory + a.i) = cmp(b.i, c.i); break;
            case l: *((signed long long*)programMemory + a.i) = cmp(b.l, c.l); break;
            case f: *((float*)programMemory + a.i) = cmp(b.f, c.f); break;
            case d: *((double*)programMemory + a.i) = cmp(b.d, c.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 8: // Goto
        oldIndex = index;
        index++;
        ProgramType a = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData();
        ProgramType b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData();
        if (a.type == i && b.type == b) if (b.data.b > 0) index = a.data.i;
        else std::cout << "Type mismatch at: " << oldIndex - 1;

      case 9: //End
        goto CLEANUP;

      case 10: //Drive
        systems[0]->ReadCommand(autoProgram, index);

      case 11: //Wait
        WAITING:
        for (int i = 0; i < systemCount; i++)
        {
          if (systems[i]->GetStatus() != 1)
          {
            Wait(0.05f);
            goto WAITING;
          }
        }

      default:
        std::cout << "Invalid command at: " << index;
        break;
    }
  }
  CLEANUP:
  delete programMemory;
  delete autoProgram;
}

void Robot::OperatorControl() 
{

}

void Robot::Test() {}

#ifndef RUNNING_FRC_TESTS
START_ROBOT_CLASS(Robot)
#endif
