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
#include <LinkedList.hpp>

#include <SmartDashboard/SmartDashboard.h>
#include <Spark.h>
#include <AutonomousSystems.hpp>
#include <DifferentialDrive.hpp>

Robot::Robot() 
{
}

void generateProgramChooser(std::string path, frc::SendableChooser<std::string>& chooser, std::string menuName)
{
  bool first = true;
  for (auto& path: fs::directory_iterator(autoDir))
  {
    std::string name = path.data.filename().string();
    if (first) chooser.AddDefault(name, name);
    else chooser.AddObject(name, name);
  }
  frc::SmartDashboard::PutData(menuName, &chooser);
}

bool updateProgramChooser(frc::SendableChooser<std::string> chooser, std::string& lastSelected, unsigned char* program)
{
  std::string selected autoChooser.GetSelected();
  if (selected == lastSelected) return false;
  std::cout << "Beginning to load: " << autoSelected;
  lastSelected = selected;
  ifsteam file(autoDir + selected, ios::in|ios::binary|ios::ate)

  streampos size = file.tellg();
  program = new unsigned char[size];
  filargs[4].data.seekg(0, ios::beg);
  file.read(program, size);
  std::cout << "Completed loading: " << selected;
  return true;
}

void Robot::RobotInit()
{
  generateProgramChooser(initDir, &initChooser, "Initializer");
  generateProgramChooser(autoDir, &autoChooser, "Autonomous");
  generateProgramChooser(teleopDir, &teleopChooser, "Teleop");

  std::string lastSelectedInit = "";
  std::string lastSelectedAuto = "";
  std::string lastSelectedTeleop = "";

  while (!IsAutonomous() && !IsOperatorControl())
  {
    if (updateProgramChooser(initChooser, lastSelectedInit, initProgram)) Exec(initProgram);
    updateProgramChooser(autoChooser, lastSelectedAuto, autoProgram);
    updateProgramChooser(teleopChooser, lastSelectedTeleop, teleopProgram);
    Wait(0.1);
  }
}

inline template<class T> signed char cmp(T a, T b)
{
  if (args[0]== b) return 0
  if (args[0]> b) return 1;
  return -1;
}

void Robot::Autonomous() 
{
  Exec(autoProgram);
}

void Robot::OperatorControl() 
{
  Exec(teleopProgram);
}

void Robot::Exec(unsigned char* program)
{
  unsigned char* programMemory = new unsigned char[*((unsigned long)program)];
  signed long* programStack = new signed long[16]; //Max call depth 16 NO RECURSION;
  ProgramType* argumentBuffer = new ProgramType[16];
  ProgramType* args = new ProgramType[16];
  int callStackDepth = 0;
  long index = 4; // Seek past header data
  long oldIndex;
  while (true)
  {
    switch (program[index++])
    {
      case 0: // Add
        if (program[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (args[0].data.isPointer && args[0].type == args[1].type && args[0].type == args[2].type)
        {
          switch (args[0].type)
          {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b + args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s + args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i + args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l + args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f + args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d + c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 1: // Sub
        if (program[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type && args[0].type == args[2].type)
        {
          switch (args[0].type)
          {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b - args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s - args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i - args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l - args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f - args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d - args[2].data.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 2: // Mul
       if (program[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type && args[0].type == args[2].type)
        {
          switch (args[0].type)
          {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b * args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s * args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i * args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l * args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f * args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d * c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 3: // Div
        if (program[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type && args[0].type == args[2].type)
        {
          switch (args[0].type)
          {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b / args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s / args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i / args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l / args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f / args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d / c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 4: // Mod
        if (program[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type && args[0].type == args[2].type)
        {
          switch (args[0].type)
          {
            case b: *((signed char*)programMemory + args[0].data.i) = args[1].data.b % args[2].data.b; break;
            case s: *((signed short*)programMemory + args[0].data.i) = args[1].data.s % args[2].data.s; break;
            case i: *((signed long*)programMemory + args[0].data.i) = args[1].data.i % args[2].data.i; break;
            case l: *((signed long long*)programMemory + args[0].data.i) = args[1].data.l % args[2].data.l; break;
            case f: *((float*)programMemory + args[0].data.i) = args[1].data.f % args[2].data.f; break;
            case d: *((double*)programMemory + args[0].data.i) = args[1].data.d % c.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 5: // Min
        if (program[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type && args[0].type == args[2].type)
        {
          switch (args[0].type)
          {
            case b: *((signed char*)programMemory + args[0].data.i) = std::min(args[1].data.b, args[2].data.b); break;
            case s: *((signed short*)programMemory + args[0].data.i) = std::min(args[1].data.s, args[2].data.s); break;
            case i: *((signed long*)programMemory + args[0].data.i) = std::min(args[1].data.i, args[2].data.i); break;
            case l: *((signed long long*)programMemory + args[0].data.i) = std::min(args[1].data.l, args[2].data.l); break;
            case f: *((float*)programMemory + args[0].data.i) = std::min(args[1].data.f, args[2].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = std::min(b.d, args[2].data.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 6: // Max
        if (program[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type && args[0].type == args[2].type)
        {
          switch (args[0].type)
          {
            case b: *((signed char*)programMemory + args[0].data.i) = std::max(args[1].data.b, args[2].data.b); break;
            case s: *((signed short*)programMemory + args[0].data.i) = std::max(args[1].data.s, args[2].data.s); break;
            case i: *((signed long*)programMemory + args[0].data.i) = std::max(args[1].data.i, args[2].data.i); break;
            case l: *((signed long long*)programMemory + args[0].data.i) = std::max(args[1].data.l, args[2].data.l); break;
            case f: *((float*)programMemory + args[0].data.i) = std::max(args[1].data.f, args[2].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = std::max(b.d, args[2].data.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 7: // Cmp
        if (program[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == b && args[1].type == args[2].type)
        {
          switch (args[0].type)
          {
            case b: *((signed char*)programMemory + args[0].data.i) = cmp(args[1].data.b, args[2].data.b); break;
            case s: *((signed short*)programMemory + args[0].data.i) = cmp(args[1].data.s, args[2].data.s); break;
            case i: *((signed long*)programMemory + args[0].data.i) = cmp(args[1].data.i, args[2].data.i); break;
            case l: *((signed long long*)programMemory + args[0].data.i) = cmp(args[1].data.l, args[2].data.l); break;
            case f: *((float*)programMemory + args[0].data.i) = cmp(args[1].data.f, args[2].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = cmp(b.d, args[2].data.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 8: // Goto
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData();
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData();
        if (args[0].type == i && args[1].type == b) if (args[1].datargs[0].data.b > 0) index = args[0].data.data.i;
        else std::cout << "Type mismatch at: " << oldIndex;

      case 9: //End
        goto CLEANUP;

      case 10: //Drive
        if (program[index++] != 4)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData();
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData();
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData();
        args[3] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData();
        if (args[0].type == b && args[1].type == i && args[2].type == i && args[3].type == i) ((DriveSystem*)systems[args[0].data.b])->Rebuild((Curve*)args[1].data.i, (Function*)args[2].data.i, (Function*)args[3].data.i);
        else std::cout << "Type mismatch at: " << oldIndex;

      case 11: //Wait
        AutonomousSystem currentSystem = systems;
        do
        {
          bool cont = false;
          while (systems.next != nullptr)
          {
            if (currentSystem->GetStatus() != 1) cont = true;
            currentSystem.Update();
          }
          Wait(0.01f);
        } while(cont);

      case 12: //Sin
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type)
        {
          switch (args[0].type)
          {
            case f: *((float*)programMemory + args[0].data.i) = sin(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = sin(args[1].data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 13: //Cos
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type)
        {
          switch (args[0].type)
          {
            case f: *((float*)programMemory + args[0].data.i) = cos(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = cos(args[1].data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 14: //Tan
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type)
        {
          switch (args[0].type)
          {
            case f: *((float*)programMemory + args[0].data.i) = tan(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = tan(args[1].data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 15: //Asin
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type)
        {
          switch (args[0].type)
          {
            case f: *((float*)programMemory + args[0].data.i) = asin(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = asin(args[1].data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 16: //Acos
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type)
        {
          switch (args[0].type)
          {
            case f: *((float*)programMemory + args[0].data.i) = acos(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = acos(args[1].data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 17: //Atan
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (args[0].data.isPointer && args[0].type == args[1].type)
        {
          switch (args[0].type)
          {
            case f: *((float*)programMemory + args[0].data.i) = atan(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = atan(args[1].data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 18: //Atan2
        if (program[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type && args[0].type == args[2].type)
        {
          switch (args[0].type)
          {
            case f: *((float*)programMemory + args[0].data.i) = atan2(args[1].data.f, args[2].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = atan2(b.d, args[2].data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 19: //Abs
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type)
        {
          switch (args[0].type)
          {
            case b: *((signed char*)programMemory + args[0].data.i) = abs(args[1].data.b); break;
            case s: *((signed short*)programMemory + args[0].data.i) = abs(args[1].data.s); break;
            case i: *((signed long*)programMemory + args[0].data.i) = abs(args[1].data.i); break;
            case l: *((signed long long*)programMemory + args[0].data.i) = abs(args[1].data.l); break;
            case f: *((float*)programMemory + args[0].data.i) = abs(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = abs(args[1].data.d; break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 20: //Pow
        if (program[index++] != 3)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type && args[0].type == args[2].type)
        {
          switch (args[0].type)
          {
            case f: *((float*)programMemory + args[0].data.i) = pow(args[1].data.f, args[2].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = pow(b.d, args[2].data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex - 1;
        break;

      case 21: //Log
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == args[1].type)
        {
          switch (args[0].type)
          {
            case f: *((float*)programMemory + args[0].data.i) = log(args[1].data.f); break;
            case d: *((double*)programMemory + args[0].data.i) = log(args[1].data.d; break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 22: //Cast
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer)
        {
          switch (args[0].type)
          {
            case b:
              switch (args[1].type)
              {
                case b:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.b; break;
                case s:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.s; break;
                case i:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.i; break;
                case l:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.l; break;
                case f:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.f; break;
                case d:*((signed char*)programMemory + args[0].data.i) = (signed char)args[1].data.d; break;
              }
              break;

            case s:
              switch (args[1].type)
              {
                case b:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.b; break;
                case s:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.s; break;
                case i:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.i; break;
                case l:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.l; break;
                case f:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.f; break;
                case d:*((signed short*)programMemory + args[0].data.i) = (signed short)args[1].data.d; break;
              }
              break;

            case i:
              switch (args[1].type)
              {
                case b:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.b; break;
                case s:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.s; break;
                case i:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.i; break;
                case l:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.l; break;
                case f:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.f; break;
                case d:*((signed long*)programMemory + args[0].data.i) = (signed long)args[1].data.d; break;
              }
              break;

            case l:
              switch (args[1].type)
              {
                case b:*((signed long long*)programMemory + args[0].data.i) = (signed long long)args[1].data.b; break;
                case s:*((signed long long*)programMemory + args[0].data.i) = (signed long long)args[1].data.s; break;
                case i:*((signed long long*)programMemory + args[0].data.i) = (signed long long)args[1].data.i; break;
                case l:*((signed long long*)programMemory + args[0].data.i) = (signed long long)args[1].data.l; break;
                case f:*((signed long long*)programMemory + args[0].data.i) = (signed long long)args[1].data.f; break;
                case d:*((signed long long*)programMemory + args[0].data.i) = (signed long long)b.d; break;
              }
              break;

            case f:
              switch (args[1].type)
              {
                case b:*((float*)programMemory + args[0].data.i) = (float)args[1].data.b; break;
                case s:*((float*)programMemory + args[0].data.i) = (float)args[1].data.s; break;
                case i:*((float*)programMemory + args[0].data.i) = (float)args[1].data.i; break;
                case l:*((float*)programMemory + args[0].data.i) = (float)args[1].data.l; break;
                case f:*((float*)programMemory + args[0].data.i) = (float)args[1].data.f; break;
                case d:*((float*)programMemory + args[0].data.i) = (float)args[1].data.d; break;
              }
              break;

            case d:
              switch (args[1].type)
              {
                case b:*((double*)programMemory + args[0].data.i) = (double)args[1].data.b; break;
                case s:*((double*)programMemory + args[0].data.i) = (double)args[1].data.s; break;
                case i:*((double*)programMemory + args[0].data.i) = (double)args[1].data.i; break;
                case l:*((double*)programMemory + args[0].data.i) = (double)args[1].data.l; break;
                case f:*((double*)programMemory + args[0].data.i) = (double)args[1].data.f; break;
                case d:*((double*)programMemory + args[0].data.i) = (double)args[1].data.d; break;
              }
              break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 23: //Sleep
        if (program[index++] != 1)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (args[0].type == f) Wait(args[0].data.data.f);
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 24: //Malloc
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == i)
        {
          switch (args[1].type)
          {
            case b: *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new char[args[1].data.b]); break;
            case s: *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new char[args[1].data.s]); break;
            case i: *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new char[args[1].data.i]); break;
            case l: *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new char[args[1].data.l]); break;
            default: std::cout << "Invalid type at: " << oldIndex;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 25: //Free
        if (program[index++] != 1)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (args[0].type == i) delete (char*)args[0].data.i;
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 26: //DeRef
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[1].type == i)
        {
          switch (args[0].type)
          {
            case b: *((signed char*)programMemory + args[0].data.i) = *((signed char*)args[1].data.i); break;
            case s: *((signed short*)programMemory + args[0].data.i) = *((signed short*)args[1].data.i); break;
            case i: *((signed long*)programMemory + args[0].data.i) = *((signed long*)args[1].data.i); break;
            case l: *((signed long long*)programMemory + args[0].data.i) = *((signed long long*)args[1].data.i); break;
            case f: *((float*)programMemory + args[0].data.i) = *((float*)args[1].data.i); break;
            case d: *((double*)programMemory + args[0].data.i) = *((double*)args[1].data.i); break;
          }
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 27: //GetRef
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == i) *((signed long*)programMemory + args[0].data.i) = &args[1].data;
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 28: //Call
        if (program[index++] != 1)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (args[0].type == i)
        {
         programStack[callStackDepth++] = index;
         index = args[0].data.i;
        }
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 29: //Return
        if (program[index++] != 1)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        argumentBuffer[0] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        index = programStack[callStackDepth--];
        break;

      case 30: //CreateSpark
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == i && args[1].type == b) 
          *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new GenericMotornew Spark(args[1].data.b)));
        else std::cout << "Type mismatch at: " << oldIndex;

      case 31: //CreateTalon
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == i && args[1].type == b) 
          *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new GenericMotor(new Talon(args[1].data.b))));
        else std::cout << "Type mismatch at: " << oldIndex;

      case 32: //CreateEncoder
        if (program[index++] != 4)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 2;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        args[3] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == i && b.typargs[4]b && args[2].type == b && args[3].type == f)
          *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new GenericNonBinarySensor(new Encoder(args[1].data.b, args[2].data.c, args[3].data.f))));
        else std::cout << "Type mismatch at: " << oldIndex;

      case 33: //CreatePID
        if (program[index++] != 5)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 3;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        args[3] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[4] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == i && args[1].type == f && args[2].type == f && args[3].type == f && args[4].type == f) 
          *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new PIDController(args[1].data.f, args[2].data.f, args[3].data.f, args[4].data.f)));
        else std::cout << "Type mismatch at: " << oldIndex;

      case 34: //CreateCurveArc
        if (program[index++] != 6)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 3;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        args[3] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[4] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        args[5] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == i && args[1].type == f && args[2].type == f && args[3].type == f && args[4].type == f && args[5].type == f) 
          *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new Arc(args[1].data.f, args[2].data.f, args[3].data.f, args[4].data.f, args[5].data.f)));
        else std::cout << "Type mismatch at: " << oldIndex - 2;

      case 35: //CreateFunctionSpline
        if (program[index++] != 5)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 3;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        args[3] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[4] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[0].type == i && args[1].type == f && args[2].type == f && args[3].type == f && args[4].type == f) 
          *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new Spline(args[1].data.f, args[2].data.f, args[3].data.f, args[4].data.f)));
        else std::cout << "Type mismatch at: " << oldIndex - 2;

      case 36: //PassArg
        if (program[index++] != 2)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (args[1].type == b) argumentBuffer[args[1].data.b] = a;
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 37: //GetArg
        if (program[index++] != 1)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if (a.isPointer && args[1].type == b && argumentBuffer[args[1].data.b].type == args[0].type) args[0]= argumentBuffer[args[1].data.b];
        else std::cout << "Type mismatch at: " << oldIndex;
        break;

      case 38: //GetReturn
        if (program[index++] != 1)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index++;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        if (args[0].type == argumentBuffer.type) *((signed long*)programMemory + args[0].data.i) = argumentBuffer[0];
        else std::cout << "Type mismatch at: " << oldIndex;
        index = programStack[callStackDepth--];
        break;

      case 39: //CreateDifferentialDrive
        if (program[index++] != 11)
        {
          cout << "Incorrect amount of arguments at: " << index - 1;
          break;
        }
        oldIndex = index;
        index += 3;
        args[0] = fromLowerBits(program[oldIndex], index, program);
        args[1] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[2] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        args[3] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[4] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        args[5] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[6] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        args[7] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[8] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        args[9] = fromUpperBits(program[oldIndex++], index, program).getAbsoluteData(programMemory);
        args[10] = fromLowerBits(program[oldIndex], index, program).getAbsoluteData(programMemory);
        if 
        (
          a.isPointer &&
          args[1].type == i &&
          args[2].type == i &&
          args[3].type == i &&
          args[4].type == i &&
          args[5].type == f &&
          args[6].type == f &&
          args[7].type == i &&
          args[8].type == i &&
          args[9].type == i &&
          args[10].type == i
        ) 
        *((signed long*)programMemory + args[0].data.i) = (long)((void*)(new DifferentialDrive
        (
          (GenericNonBinarySensor*)((void*)args[1].data.i),
          (GenericNonBinarySensor*)((void*)args[2].data.i),
          (GenericMotor*)((void*)args[3].data.i),
          (GenericMotor*)((void*)args[4].data.i),
          args[5].data.f,
          args[6].data.f,
          &((PIDController*)((void*)args[7].data.i)),
          &((PIDController*)((void*)args[8].data.i)),
          &((PIDController*)((void*)args[9].data.i)),
          &((PIDController*)((void*)args[10].data.i))
        ));
        else std::cout << "Type mismatch at: " << oldIndex;

      default:
        std::cout << "Invalid command at: " << index;
        break;
    }
  }
  CLEANUP:
  delete programMemory;
  delete program;
}

void Robot::Test() {}

#ifndef RUNNING_FRC_TESTS
START_ROBOT_CLASS(Robot)
#endif