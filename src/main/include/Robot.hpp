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
  void Exec();

  private:
  LinkedListNode<AutonomousSystem> systems;

  frc::SendableChooser<std::string> initChooser;
  frc::SendableChooser<std::string> autoChooser;
  frc::SendableChooser<std::string> teleopChooser;
  const std::string initDir = "/U/Init/";
  const std::string autoDir = "/U/Auto/";
  const std::string teleopDir = "/U/Teleop/";
  unsigned char* initProgram;
  unsigned char* autoProgram;
  unsigned char* teleopProgram;
};