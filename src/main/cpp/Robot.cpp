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
#include <LinkedList.hpp>
#include <SmartDashboard/SmartDashboard.h>

#include <AdvancedArithmatic.hpp>
#include <BasicArithmatic.hpp>
#include <Bitwise.hpp>
#include <Comparison.hpp>
#include <Conversion.hpp>
#include <CurveGen.hpp>
#include <DynamicMemory.hpp>
#include <FlowControl.hpp>
#include <FunctionGen.hpp>
#include <HardwareGen.hpp>
#include <Logical.hpp>
#include <SystemControl.hpp>
#include <SystemGen.hpp>
#include <Trigonometric.hpp>

using namespace USSL;

Robot::Robot() 
{
}

void generateProgramChooser(std::string path, frc::SendableChooser<std::string>& chooser, std::string menuName)
{
  bool first = true;
  for (auto& path: fs::directory_iterator(autoDir))
  {
    std::string name = path.data.filename().string();
    if (first) { chooser.AddDefault(name, name) first = false };
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
  ProgramType* argumentPassBuffer = new ProgramType[16];
  ProgramType* args = new ProgramType[16];
  int callStackDepth = 0;
  long index = 4; // Seek past header data
  long oldIndex;
  while (true)
  {
    unsigned char command = program[index++];
    int argCount = program[index++];
    bool lowerBits = true;
    oldIndex = index;
    for (int i = 0; i < argCount; i++) args[i] = fromBits(program + oldIndex, index, programMemory, lower);
    for (int i = 1; i < argCount; i++) args[i] = args[i] = args[i].getAbsoluteData(programMemory);

    switch (command)
    {
      case 000: goto CLEANUP;

      case 001: ADD(args, programMemory);
      case 002: SUB(args, programMemory);
      case 003: MUL(args, programMemory);
      case 004: DIV(args, programMemory);
      case 005: MOD(args, programMemory);

      case 006: MIN(args, programMemory);
      case 007: MAX(args, programMemory);
      case 008: POW(args, programMemory);
      case 009: LOG(args, programMemory);
      
      case 010: SIN(args, programMemory);
      case 011: COS(args, programMemory);
      case 012: TAN(args, programMemory);
      case 013: ASN(args, programMemory);
      case 014: ACS(args, programMemory);
      case 015: ATN(args, programMemory);
      case 016: ATT(args, programMemory);
      
      case 017: BAD(args, programMemory);
      case 018: BOR(args, programMemory);
      case 019: BXR(args, programMemory);
      case 020: BNT(args, programMemory);
      case 021: BSL(args, programMemory);
      case 022: BSR(args, programMemory);
      
      case 023: EQL(args, programMemory);
      case 024: NEQ(args, programMemory);
      case 025: GTN(args, programMemory);
      case 026: LTN(args, programMemory);
      case 027: GTE(args, programMemory);
      case 028: LTE(args, programMemory);
      
      case 029: LAD(args, programMemory);
      case 030: LOR(args, programMemory);
      case 031: LXR(args, programMemory);
      case 032: LNT(args, programMemory);

      case 033: CAL(args, programMemory, programStack, callStackDepth, index, argumentPassBuffer);
      case 034: RET(args, programMemory, programStack, callStackDepth, index, argumentPassBuffer);
      case 035: GAR(args, programMemory, programStack, callStackDepth, index, argumentPassBuffer);
      case 036: GRT(args, programMemory, programStack, callStackDepth, index, argumentPassBuffer);
      case 037: SAR(args, programMemory, programStack, callStackDepth, index, argumentPassBuffer);
      case 038: GTO(args, programMemory, programStack, callStackDepth, index, argumentPassBuffer);
      
      case 039: MLC(args, programMemory);
      case 040: FRE(args, programMemory);
      case 041: GRF(args, programMemory);
      case 042: SRF(args, programMemory);
      
      case 043: GEN_CRV_ARC(args, programMemory);

      case 044: GEN_FNC_SPL(args, programMemory);
      
      case 045: GEN_MTR_SPK(args, programMemory);
      case 046: GEN_MTR_TLN(args, programMemory);
      case 047: GEN_SEN_ENC(args, programMemory);

      case 048: SYS_ADD(args, programMemory, systems);
      case 049: GEN_SYS_DRV_DIF(arg, programMemory);

      case 050: SYS_WAT(arg, programMemory, systems);
      case 051: GEN_SYS_DRV_DIF(arg, programMemory, systems);
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