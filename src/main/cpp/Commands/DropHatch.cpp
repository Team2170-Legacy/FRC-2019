/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/DropHatch.h"

DropHatch::DropHatch() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
}

/**
 * @brief Called just before this Command runs the first time
 * 
 * Set the new inner elevator position to 3 inches below current position
 * in order to release grip on the hatch.
 */
void DropHatch::Initialize() {
  mNewPosition = Robot::elevator->GetInnerPosInches() - Robot::elevator->kHatchReleasePos;
}

/**
 * @brief Called repeatedly when this Command is scheduled to run
 * 
 * Constantly set the inner elevator position to mNewPosition.
 */
void DropHatch::Execute() {
  Robot::elevator->SetInnerPosition(mNewPosition);
}

/**
 * @brief Make this return true when this Command no longer needs to run execute()
 * 
 * Terminate this command once the inner elevator reaches the desired position.
 * 
 * @return true 
 * @return false 
 */
bool DropHatch::IsFinished() { 
  bool retVal = false;
  if (Robot::elevator->InnerAtPosition()) {
        retVal = true;
  }
  return retVal;
}

/**
 * @brief Called once after isFinished returns true
 */
void DropHatch::End() {}

/**
 * @brief Called when another command which requires one or more of the same subsystems is scheduled to run
 */
void DropHatch::Interrupted() {}
