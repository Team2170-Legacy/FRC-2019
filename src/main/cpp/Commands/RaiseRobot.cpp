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
  mRearCmd = Robot::elevator->kRearLiftPos;
  mFwdCmd = Robot::elevator->kFwdLiftPos;
}

/**
 * @brief  Called just before this Command runs the first time
 * 
 * Grab kRearLiftPos and kFwdLiftPos from Elevator class.
 */
RaiseRobot::RaiseRobot(double fwd, double rear) : frc::Command() {
  Requires(Robot::elevator.get());
  bCustomMove = true;         // TODO fix this yuckieness
  mRearCmd = rear;
  mFwdCmd = fwd;
}
// Called just before this Command runs the first time
void RaiseRobot::Initialize() {
  Robot::elevator->RigForClimb();
}

/**
 * @brief Called repeatedly when this Command is scheduled to run
 * 
 * Set the rear elevator position to mRearCmd
 * Set the outer elevator position to mFwdCmd
 */
void RaiseRobot::Execute() {
  Robot::elevator->SetRearPosition(mRearCmd);
  Robot::elevator->SetOuterPosition(mFwdCmd);
}

/**
 * @brief Make this return true when this Command no longer needs to run execute()
 * 
 * Finish this command when the rear and outer elevator is in position (mRearCmd) 
 */
bool RaiseRobot::IsFinished() { 
  return (Robot::elevator->RearAtPosition() && Robot::elevator->OuterAtPosition()); 
}

/**
 * @brief Called once after isFinished returns true
 */
void RaiseRobot::End() {
  printf("Climb Step Complete\n");
}

/**
 * @brief Called when another command which requires one or more of the same subsystems is scheduled to run
 */
void RaiseRobot::Interrupted() {}
