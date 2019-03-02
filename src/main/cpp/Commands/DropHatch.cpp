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

// Called just before this Command runs the first time
void DropHatch::Initialize() {
  mNewPosition = Robot::elevator->GetInnerPosInches() - Robot::elevator->kHatchReleasePos;
}

// Called repeatedly when this Command is scheduled to run
void DropHatch::Execute() {
  Robot::elevator->SetInnerPosition(mNewPosition);
}

// Make this return true when this Command no longer needs to run execute()
bool DropHatch::IsFinished() { 
  bool retVal = false;
  if (Robot::elevator->InnerAtPosition()) {
        retVal = true;
  }
  return retVal;
}

// Called once after isFinished returns true
void DropHatch::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DropHatch::Interrupted() {}
