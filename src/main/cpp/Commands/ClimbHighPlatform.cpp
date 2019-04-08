/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/ClimbHighPlatform.h"
#include "Commands/RaiseRobot.h"
#include "Commands/ElevatorInnerPos.h"
#include "Commands/ElevatorOuterPos.h"
#include "Commands/ElevatorRearPos.h"
#include "Commands/IntakeUp.h"
#include "Commands/IntakeDown.h"
#include "Commands/DriveStraightDistance.h"
#include "Commands/DriveStraightVelocity.h"

ClimbHighPlatform::ClimbHighPlatform() {
  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.

  // To run multiple commands at the same time,
  // use AddParallel()
  // e.g. AddParallel(new Command1());
  //      AddSequential(new Command2());
  // Command1 and Command2 will run in parallel.

  // A command group will require all of the subsystems that each member
  // would require.
  // e.g. if Command1 requires chassis, and Command2 requires arm,
  // a CommandGroup containing them would require both the chassis and the
  // arm.
  //AddSequential(new IntakeUp());
  AddSequential(new ElevatorInnerPos(25.0, false));
  AddSequential(new ElevatorOuterPos(0.0, false));
  AddSequential(new frc::PrintCommand("RAISE"));
  AddSequential(new RaiseRobot());
  AddSequential(new IntakeDown());
  AddSequential(new frc::PrintCommand("CREEP"));
  AddSequential(new ElevatorInnerPos(37, false));    // creep forward
  AddSequential(new frc::PrintCommand("LOWER"));
  AddSequential(new ElevatorOuterPos(3.0, false));
  AddSequential(new DriveStraightDistance(1.0));    // 16" forward
  AddSequential(new ElevatorRearPos(0.0, false));
  AddSequential(new DriveStraightDistance(1.5));    // 8" forward
}
