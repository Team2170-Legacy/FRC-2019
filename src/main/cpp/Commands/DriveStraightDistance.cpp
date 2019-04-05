/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/DriveStraightDistance.h"

DriveStraightDistance::DriveStraightDistance(double distance) : frc::Command() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::driveTrain.get());
  mDistance = distance;
}

// Called just before this Command runs the first time
void DriveStraightDistance::Initialize() {
  Robot::driveTrain->ZeroPosition();
  mSavedSpeed = Robot::driveTrain->GetMaxVelocity();
  Robot::driveTrain->SetMaxVelocity(3.0);
  SetTimeout(mDistance / 3.0 + 10.0);
}

// Called repeatedly when this Command is scheduled to run
void DriveStraightDistance::Execute() {
  Robot::driveTrain->SmartMotionDrive(mDistance);
  frc::SmartDashboard::PutNumber("Drive Position", Robot::driveTrain->GetPosition());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightDistance::IsFinished() { 
  return ((fabs(Robot::driveTrain->GetPosition() - mDistance) < 0.5) ||
            IsTimedOut());
}

// Called once after isFinished returns true
void DriveStraightDistance::End() {
  Robot::driveTrain->SetMaxVelocity(mSavedSpeed);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightDistance::Interrupted() {}
