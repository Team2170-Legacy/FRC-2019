// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "Commands/InitRobot.h"
#include "Commands/ElevatorOuterPos.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

/**
 * @brief Construct a new Init Robot:: Init Robot object
 * 
 * This is a command group that this robot runs right after starting up.
 * It sets the outer elevator to a position of 4 in above the groud.
 * Also it prints a debug message to the console to notify the drivers.
 */
InitRobot::InitRobot() {
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
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
    if (!Robot::IsPracticeBot()) {
      AddSequential(new ElevatorOuterPos(4.0, false));
    }
    AddSequential(new frc::PrintCommand("Init Robot Complete"));
 }
