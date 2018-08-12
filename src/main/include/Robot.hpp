/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <GenericMotor.hpp>
#include <GenericNonBinarySensor.hpp>
#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>

class Robot : public frc::SampleRobot 
{
  public:
  Robot();

  void RobotInit() override;
  void Autonomous() override;
  void OperatorControl() override;
  void Test() override;

  private:
  HardwareInterfaces::GenericMotor MotorLHS;
  HardwareInterfaces::GenericMotor MotorRHS;

  HardwareInterfaces::GenericNonBinarySensor DistanceSensorLHS;
  HardwareInterfaces::GenericNonBinarySensor DistanceSensorRHS;

  AutonomousSystem** systems;
  int systemCount;

  frc::SendableChooser<std::string> m_chooser;
  const std::string autoPathsDir = "/U/AutoPaths/";
  unsigned char* autoProgram;
  unsigned char* programMemory;
  signed long* programStack;
};