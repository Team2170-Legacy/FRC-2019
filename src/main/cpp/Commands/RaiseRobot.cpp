/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/RaiseRobot.h"

RaiseRobot::RaiseRobot() : frc::Command() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
}

RaiseRobot::RaiseRobot(double fwd, double rear) : frc::Command() {
Requires(Robot::elevator.get());
bCustomMove = true;         // TODO fix this yuckieness
mRearCmd = rear;
mFwdCmd = fwd;
}
// Called just before this Command runs the first time
void RaiseRobot::Initialize() {
  Robot::elevator->RigForClimb();
  if (!bCustomMove) {
    mRearCmd = Robot::elevator->kRearLiftPos;
    mFwdCmd = Robot::elevator->kFwdLiftPos;
  }
}

// Called repeatedly when this Command is scheduled to run
void RaiseRobot::Execute() {
  Robot::elevator->SetRearPosition(mRearCmd);
  Robot::elevator->SetOuterPosition(mFwdCmd);
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseRobot::IsFinished() { 
  return (Robot::elevator->RearAtPosition() && Robot::elevator->OuterAtPosition()); 
}

// Called once after isFinished returns true
void RaiseRobot::End() {
  printf("Climb Step Complete\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseRobot::Interrupted() {}
