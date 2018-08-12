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
    std::string name = path.data.filename().string();
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
      file.data.seekg(0, ios::beg);
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
        if (autoProgram[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        ProgramType a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        ProgramType b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        ProgramType c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.data.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.data.i) = b.data.b + c.data.b; break;
            case s: *((signed short*)programMemory + a.data.i) = b.data.s + c.data.s; break;
            case i: *((signed long*)programMemory + a.data.i) = b.data.i + c.data.i; break;
            case l: *((signed long long*)programMemory + a.data.i) = b.data.l + c.data.l; break;
            case f: *((float*)programMemory + a.data.i) = b.data.f + c.data.f; break;
            case d: *((double*)programMemory + a.data.i) = b.data.d + c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 1: // Sub
        if (autoProgram[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.data.i) = b.data.b - c.data.b; break;
            case s: *((signed short*)programMemory + a.data.i) = b.data.s - c.data.s; break;
            case i: *((signed long*)programMemory + a.data.i) = b.data.i - c.data.i; break;
            case l: *((signed long long*)programMemory + a.data.i) = b.data.l - c.data.l; break;
            case f: *((float*)programMemory + a.data.i) = b.data.f - c.data.f; break;
            case d: *((double*)programMemory + a.data.i) = b.data.d - c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 2: // Mul
       if (autoProgram[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.data.i) = b.data.b * c.data.b; break;
            case s: *((signed short*)programMemory + a.data.i) = b.data.s * c.data.s; break;
            case i: *((signed long*)programMemory + a.data.i) = b.data.i * c.data.i; break;
            case l: *((signed long long*)programMemory + a.data.i) = b.data.l * c.data.l; break;
            case f: *((float*)programMemory + a.data.i) = b.data.f * c.data.f; break;
            case d: *((double*)programMemory + a.data.i) = b.data.d * c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 3: // Div
        if (autoProgram[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.data.i) = b.data.b / c.data.b; break;
            case s: *((signed short*)programMemory + a.data.i) = b.data.s / c.data.s; break;
            case i: *((signed long*)programMemory + a.data.i) = b.data.i / c.data.i; break;
            case l: *((signed long long*)programMemory + a.data.i) = b.data.l / c.data.l; break;
            case f: *((float*)programMemory + a.data.i) = b.data.f / c.data.f; break;
            case d: *((double*)programMemory + a.data.i) = b.data.d / c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 4: // Mod
        if (autoProgram[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.data.i) = b.data.b % c.data.b; break;
            case s: *((signed short*)programMemory + a.data.i) = b.data.s % c.data.s; break;
            case i: *((signed long*)programMemory + a.data.i) = b.data.i % c.data.i; break;
            case l: *((signed long long*)programMemory + a.data.i) = b.data.l % c.data.l; break;
            case f: *((float*)programMemory + a.data.i) = b.data.f % c.data.f; break;
            case d: *((double*)programMemory + a.data.i) = b.data.d % c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 5: // Min
        if (autoProgram[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.data.i) = std::min(b.data.b, c.data.b); break;
            case s: *((signed short*)programMemory + a.data.i) = std::min(b.data.s, c.data.s); break;
            case i: *((signed long*)programMemory + a.data.i) = std::min(b.data.i, c.data.i); break;
            case l: *((signed long long*)programMemory + a.data.i) = std::min(b.data.l, c.data.l); break;
            case f: *((float*)programMemory + a.data.i) = std::min(b.data.f, c.data.f); break;
            case d: *((double*)programMemory + a.data.i) = std::min(b.d, c.data.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 6: // Max
        if (autoProgram[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.data.i) = std::max(b.data.b, c.data.b); break;
            case s: *((signed short*)programMemory + a.data.i) = std::max(b.data.s, c.data.s); break;
            case i: *((signed long*)programMemory + a.data.i) = std::max(b.data.i, c.data.i); break;
            case l: *((signed long long*)programMemory + a.data.i) = std::max(b.data.l, c.data.l); break;
            case f: *((float*)programMemory + a.data.i) = std::max(b.data.f, c.data.f); break;
            case d: *((double*)programMemory + a.data.i) = std::max(b.d, c.data.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 7: // Cmp
        if (autoProgram[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b && b.type == c.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.data.i) = cmp(b.data.b, c.data.b); break;
            case s: *((signed short*)programMemory + a.data.i) = cmp(b.data.s, c.data.s); break;
            case i: *((signed long*)programMemory + a.data.i) = cmp(b.data.i, c.data.i); break;
            case l: *((signed long long*)programMemory + a.data.i) = cmp(b.data.l, c.data.l); break;
            case f: *((float*)programMemory + a.data.i) = cmp(b.data.f, c.data.f); break;
            case d: *((double*)programMemory + a.data.i) = cmp(b.d, c.data.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 8: // Goto
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData();
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData();
        if (a.type == i && b.type == b) if (b.data.data.b > 0) index = a.data.data.i;
        else std::cout << "Type mismatch at: " << oldIndex;

      case 9: //End
        goto CLEANUP;

      case 10: //Drive
        systems[0]->ReadCommand(autoProgram, index, programMemory);

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
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.data.i) = sin(b.data.f); break;
            case d: *((double*)programMemory + a.data.i) = sin(b.data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 13: //Cos
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.data.i) = cos(b.data.f); break;
            case d: *((double*)programMemory + a.data.i) = cos(b.data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 14: //Tan
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.data.i) = tan(b.data.f); break;
            case d: *((double*)programMemory + a.data.i) = tan(b.data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 15: //Asin
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.data.i) = asin(b.data.f); break;
            case d: *((double*)programMemory + a.data.i) = asin(b.data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 16: //Acos
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.data.i) = acos(b.data.f); break;
            case d: *((double*)programMemory + a.data.i) = acos(b.data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 17: //Atan
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.data.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.data.i) = atan(b.data.f); break;
            case d: *((double*)programMemory + a.data.i) = atan(b.data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 18: //Atan2
        if (autoProgram[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.data.i) = atan2(b.data.f, c.data.f); break;
            case d: *((double*)programMemory + a.data.i) = atan2(b.d, c.data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 19: //Abs
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.data.i) = abs(b.data.b); break;
            case s: *((signed short*)programMemory + a.data.i) = abs(b.data.s); break;
            case i: *((signed long*)programMemory + a.data.i) = abs(b.data.i); break;
            case l: *((signed long long*)programMemory + a.data.i) = abs(b.data.l); break;
            case f: *((float*)programMemory + a.data.i) = abs(b.data.f); break;
            case d: *((double*)programMemory + a.data.i) = abs(b.data.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 20: //Pow
        if (autoProgram[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex++], index, autoProgram).getAbsoluteData(programMemory);
        c = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type && a.type == c.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.data.i) = pow(b.data.f, c.data.f); break;
            case d: *((double*)programMemory + a.data.i) = pow(b.d, c.data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 21: //Log
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == b.type)
        {
          switch (a.type)
          {
            case f: *((float*)programMemory + a.data.i) = log(b.data.f); break;
            case d: *((double*)programMemory + a.data.i) = log(b.data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 22: //Cast
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
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
                case b:*((signed char*)programMemory + a.data.i) = (signed char)b.data.b; break;
                case s:*((signed char*)programMemory + a.data.i) = (signed char)b.data.s; break;
                case i:*((signed char*)programMemory + a.data.i) = (signed char)b.data.i; break;
                case l:*((signed char*)programMemory + a.data.i) = (signed char)b.data.l; break;
                case f:*((signed char*)programMemory + a.data.i) = (signed char)b.data.f; break;
                case d:*((signed char*)programMemory + a.data.i) = (signed char)b.data.d; break;
              }
              break;

            case s:
              switch (b.type)
              {
                case b:*((signed short*)programMemory + a.data.i) = (signed short)b.data.b; break;
                case s:*((signed short*)programMemory + a.data.i) = (signed short)b.data.s; break;
                case i:*((signed short*)programMemory + a.data.i) = (signed short)b.data.i; break;
                case l:*((signed short*)programMemory + a.data.i) = (signed short)b.data.l; break;
                case f:*((signed short*)programMemory + a.data.i) = (signed short)b.data.f; break;
                case d:*((signed short*)programMemory + a.data.i) = (signed short)b.data.d; break;
              }
              break;

            case i:
              switch (b.type)
              {
                case b:*((signed long*)programMemory + a.data.i) = (signed long)b.data.b; break;
                case s:*((signed long*)programMemory + a.data.i) = (signed long)b.data.s; break;
                case i:*((signed long*)programMemory + a.data.i) = (signed long)b.data.i; break;
                case l:*((signed long*)programMemory + a.data.i) = (signed long)b.data.l; break;
                case f:*((signed long*)programMemory + a.data.i) = (signed long)b.data.f; break;
                case d:*((signed long*)programMemory + a.data.i) = (signed long)b.data.d; break;
              }
              break;

            case l:
              switch (b.type)
              {
                case b:*((signed long long*)programMemory + a.data.i) = (signed long long)b.data.b; break;
                case s:*((signed long long*)programMemory + a.data.i) = (signed long long)b.data.s; break;
                case i:*((signed long long*)programMemory + a.data.i) = (signed long long)b.data.i; break;
                case l:*((signed long long*)programMemory + a.data.i) = (signed long long)b.data.l; break;
                case f:*((signed long long*)programMemory + a.data.i) = (signed long long)b.data.f; break;
                case d:*((signed long long*)programMemory + a.data.i) = (signed long long)b.d; break;
              }
              break;

            case f:
              switch (b.type)
              {
                case b:*((float*)programMemory + a.data.i) = (float)b.data.b; break;
                case s:*((float*)programMemory + a.data.i) = (float)b.data.s; break;
                case i:*((float*)programMemory + a.data.i) = (float)b.data.i; break;
                case l:*((float*)programMemory + a.data.i) = (float)b.data.l; break;
                case f:*((float*)programMemory + a.data.i) = (float)b.data.f; break;
                case d:*((float*)programMemory + a.data.i) = (float)b.data.d; break;
              }
              break;

            case d:
              switch (b.type)
              {
                case b:*((double*)programMemory + a.data.i) = (double)b.data.b; break;
                case s:*((double*)programMemory + a.data.i) = (double)b.data.s; break;
                case i:*((double*)programMemory + a.data.i) = (double)b.data.i; break;
                case l:*((double*)programMemory + a.data.i) = (double)b.data.l; break;
                case f:*((double*)programMemory + a.data.i) = (double)b.data.f; break;
                case d:*((double*)programMemory + a.data.i) = (double)b.data.d; break;
              }
              break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 23: //Sleep
        if (autoProgram[index++] != 1)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.type == f) Wait(a.data.data.f);
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 24: //Malloc
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == i)
        {
          switch (b.type)
          {
            case b: *((signed long*)programMemory + a.data.i) = new char[b.data.b]; break;
            case s: *((signed long*)programMemory + a.data.i) = new char[b.data.s]; break;
            case i: *((signed long*)programMemory + a.data.i) = new char[b.data.i]; break;
            case l: *((signed long*)programMemory + a.data.i) = new char[b.data.l]; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 25: //Free
        if (autoProgram[index++] != 1)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.type == i) delete (char*)a.data.i;
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 26: //DeRef
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && b.type == i)
        {
          switch (a.type)
          {
            case b: *((signed char*)programMemory + a.data.i) = *((signed char*)b.data.i); break;
            case s: *((signed short*)programMemory + a.data.i) = *((signed short*)b.data.i); break;
            case i: *((signed long*)programMemory + a.data.i) = *((signed long*)b.data.i); break;
            case l: *((signed long long*)programMemory + a.data.i) = *((signed long long*)b.data.i); break;
            case f: *((float*)programMemory + a.data.i) = *((float*)b.data.i); break;
            case d: *((double*)programMemory + a.data.i) = *((double*)b.data.i); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 27: //GetRef
        if (autoProgram[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        a = fromLowerBits(autoProgram[oldIndex], index, autoProgram);
        b = fromUpperBits(autoProgram[oldIndex], index, autoProgram).getAbsoluteData(programMemory);
        if (a.isPointer && a.type == i) *((signed long*)programMemory + a.data.i) = &b.data;
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