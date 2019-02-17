// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "frc/smartdashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/ElevatorInnerPos.h"
#include "Commands/ElevatorOutterPos.h"
#include "Commands/ElevatorRearPos.h"
#include "Commands/IntakeDown.h"
#include "Commands/IntakeToggle.h"
#include "Commands/IntakeUp.h"
#include "Commands/TeleopDrive.h"
#include "Commands/TeleopElevator.h"
#include "Commands/TeleopIntake.h"
#include "Commands/TeleopOuttake.h"
#include "Commands/VisionDrive.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    pushbuttonPanel.reset(new frc::Joystick(2));
    
    pushBUttonRed2.reset(new frc::JoystickButton(pushbuttonPanel.get(), 1));
    pushBUttonRed2->WhenPressed(new ElevatorInnerPos(20, true));
    pushButtonRed1.reset(new frc::JoystickButton(pushbuttonPanel.get(), 1));
    pushButtonRed1->WhenPressed(new ElevatorInnerPos(8, true));
    operatorJoystick.reset(new frc::Joystick(1));
    
    joystickButtonToggleIntake.reset(new frc::JoystickButton(operatorJoystick.get(), 3));
    joystickButtonToggleIntake->WhenPressed(new IntakeToggle());
    joystickButtonOuttake.reset(new frc::JoystickButton(operatorJoystick.get(), 2));
    joystickButtonOuttake->WhileHeld(new TeleopOuttake());
    joystickButtonIntake.reset(new frc::JoystickButton(operatorJoystick.get(), 1));
    joystickButtonIntake->WhileHeld(new TeleopIntake());
    driverJoystick.reset(new frc::Joystick(0));
    

    // SmartDashboard Buttons

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getDriverJoystick() {
   return driverJoystick;
}

std::shared_ptr<frc::Joystick> OI::getOperatorJoystick() {
   return operatorJoystick;
}

std::shared_ptr<frc::Joystick> OI::getPushbuttonPanel() {
   return pushbuttonPanel;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
