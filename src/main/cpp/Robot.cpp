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
#include <math.h>
#include <cstdlib>

#include <SmartDashboard/SmartDashboard.h>
#include <Spark.h>
#include <AutonomousSystems.hpp>
#include <DifferentialDrive.hpp>

Robot::Robot() 
{
  systemCount = 1;
  systems = new AutonomousSystem*[systemCount];
  systems[0] = new DifferentialDrive(&DistanceSensorLHS, &DistanceSensorRHS, &motorLHS, &motorRHS, 100);
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
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
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
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
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
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
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
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
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
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
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
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
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
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
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
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData();
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData();
        if (a.type == i && b.type == b) if (b.data.b > 0) index = a.data.i;
        else std::cout << "Type mismatch at: " << oldIndex;

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

      case 12: //Sin
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.i) = sin(b.f); break;
            case d: *((double*)programMemory + a.i) = sin(b.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 13: //Cos
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.i) = cos(b.f); break;
            case d: *((double*)programMemory + a.i) = cos(b.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 14: //Tan
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.i) = tan(b.f); break;
            case d: *((double*)programMemory + a.i) = tan(b.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 15: //Asin
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.i) = asin(b.f); break;
            case d: *((double*)programMemory + a.i) = asin(b.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 16: //Acos
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.i) = acos(b.f); break;
            case d: *((double*)programMemory + a.i) = acos(b.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 17: //Atan
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.i) = atan(b.f); break;
            case d: *((double*)programMemory + a.i) = atan(b.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 18: //Atan2
        oldIndex = index;
        index += 2;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.i) = atan2(b.f, c.f); break;
            case d: *((double*)programMemory + a.i) = atan2(b.d, c.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 19: //Abs
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.i) = abs(b.b); break;
            case s: *((signed short*)programMemory + a.i) = abs(b.s); break;
            case i: *((signed long*)programMemory + a.i) = abs(b.i); break;
            case l: *((signed long long*)programMemory + a.i) = abs(b.l); break;
            case f: *((float*)programMemory + a.i) = abs(b.f); break;
            case d: *((double*)programMemory + a.i) = abs(b.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 20: //Pow
        oldIndex = index;
        index += 2;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.i) = pow(b.f, c.f); break;
            case d: *((double*)programMemory + a.i) = pow(b.d, c.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 21: //Log
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.i) = log(b.f); break;
            case d: *((double*)programMemory + a.i) = log(b.d); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 22: //Cast
      oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer)
        {
          switch (a.type)
          {
            case b:
              switch (b.type)
              {
                case b:*((signed char*)programMemory + a.i) = (signed char)b.b; break;
                case s:*((signed char*)programMemory + a.i) = (signed char)b.s; break;
                case i:*((signed char*)programMemory + a.i) = (signed char)b.i; break;
                case l:*((signed char*)programMemory + a.i) = (signed char)b.l; break;
                case f:*((signed char*)programMemory + a.i) = (signed char)b.f; break;
                case d:*((signed char*)programMemory + a.i) = (signed char)b.d; break;
              }
              break;

            case s:
              switch (b.type)
              {
                case b:*((signed short*)programMemory + a.i) = (signed short)b.b; break;
                case s:*((signed short*)programMemory + a.i) = (signed short)b.s; break;
                case i:*((signed short*)programMemory + a.i) = (signed short)b.i; break;
                case l:*((signed short*)programMemory + a.i) = (signed short)b.l; break;
                case f:*((signed short*)programMemory + a.i) = (signed short)b.f; break;
                case d:*((signed short*)programMemory + a.i) = (signed short)b.d; break;
              }
              break;

            case i:
              switch (b.type)
              {
                case b:*((signed long*)programMemory + a.i) = (signed long)b.b; break;
                case s:*((signed long*)programMemory + a.i) = (signed long)b.s; break;
                case i:*((signed long*)programMemory + a.i) = (signed long)b.i; break;
                case l:*((signed long*)programMemory + a.i) = (signed long)b.l; break;
                case f:*((signed long*)programMemory + a.i) = (signed long)b.f; break;
                case d:*((signed long*)programMemory + a.i) = (signed long)b.d; break;
              }
              break;

            case l:
              switch (b.type)
              {
                case b:*((signed long long*)programMemory + a.i) = (signed long long)b.b; break;
                case s:*((signed long long*)programMemory + a.i) = (signed long long)b.s; break;
                case i:*((signed long long*)programMemory + a.i) = (signed long long)b.i; break;
                case l:*((signed long long*)programMemory + a.i) = (signed long long)b.l; break;
                case f:*((signed long long*)programMemory + a.i) = (signed long long)b.f; break;
                case d:*((signed long long*)programMemory + a.i) = (signed long long)b.d; break;
              }
              break;

            case f:
              switch (b.type)
              {
                case b:*((float*)programMemory + a.i) = (float)b.b; break;
                case s:*((float*)programMemory + a.i) = (float)b.s; break;
                case i:*((float*)programMemory + a.i) = (float)b.i; break;
                case l:*((float*)programMemory + a.i) = (float)b.l; break;
                case f:*((float*)programMemory + a.i) = (float)b.f; break;
                case d:*((float*)programMemory + a.i) = (float)b.d; break;
              }
              break;

            case d:
              switch (b.type)
              {
                case b:*((double*)programMemory + a.i) = (double)b.b; break;
                case s:*((double*)programMemory + a.i) = (double)b.s; break;
                case i:*((double*)programMemory + a.i) = (double)b.i; break;
                case l:*((double*)programMemory + a.i) = (double)b.l; break;
                case f:*((double*)programMemory + a.i) = (double)b.f; break;
                case d:*((double*)programMemory + a.i) = (double)b.d; break;
              }
              break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

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
