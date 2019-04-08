/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/DriveStraightVelocity.h"
#define MAXV 3.0
#define MAXA 3.0
#define STOP_DISTANCE (2.0/12.0)

DriveStraightVelocity::DriveStraightVelocity(double velocity, double distance) : frc::Command() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::driveTrain.get());
  mDistance = distance;
  mVelocity = velocity;
}

// Called just before this Command runs the first time
void DriveStraightVelocity::Initialize() {
  Robot::driveTrain->ZeroPosition();
  Robot::driveTrain->SetMaxVelocity(MAXV);
  Robot::driveTrain->SetMaxAccel(MAXA);
  Robot::driveTrain->SmartMotionVelocity(mVelocity);
  SetTimeout(mDistance / mVelocity);
}

// Called repeatedly when this Command is scheduled to run
void DriveStraightVelocity::Execute() {
  Robot::driveTrain->SmartMotionVelocity(mVelocity);
  frc::SmartDashboard::PutNumber("Drive Position", Robot::driveTrain->GetPosition());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightVelocity::IsFinished() { 
  return ((fabs(Robot::driveTrain->GetPosition() - mDistance) < STOP_DISTANCE) ||
            IsTimedOut());
}

// Called once after isFinished returns true
void DriveStraightVelocity::End() {
  Robot::driveTrain->SmartMotionVelocity(0.0);
  Robot::driveTrain->SetMaxVelocity();
  Robot::driveTrain->SetMaxAccel();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightVelocity::Interrupted() { End(); }
