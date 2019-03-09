/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/RaiseRobot.h"

RaiseRobot::RaiseRobot() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
}

/**
 * @brief  Called just before this Command runs the first time
 * 
 * Grab kRearLiftPos and kFwdLiftPos from Elevator class.
 */
void RaiseRobot::Initialize() {
  mRearCmd = Robot::elevator->kRearLiftPos;
  mFwdCmd = Robot::elevator->kFwdLiftPos;
}

/**
 * @brief Called repeatedly when this Command is scheduled to run
 * 
 * Set the rear elevator position to mRearCmd
 * Set the outer elevator position to mFwdCmd
 */
void RaiseRobot::Execute() {}

/**
 * @brief Make this return true when this Command no longer needs to run execute()
 * 
 * Finish this command when the rear and outer elevator is in position (mRearCmd) 
 */
bool RaiseRobot::IsFinished() { 
  return (Robot::elevator->RearAtPosition()); 
}

/**
 * @brief Called once after isFinished returns true
 */
void RaiseRobot::End() {}

/**
 * @brief Called when another command which requires one or more of the same subsystems is scheduled to run
 */
void RaiseRobot::Interrupted() {}
