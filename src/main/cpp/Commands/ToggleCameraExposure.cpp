/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/ToggleCameraExposure.h"
bool toggle = true;
const double FOR_DRIVE = 40.0;
const double FOR_VISION = 0.0;

ToggleCameraExposure::ToggleCameraExposure() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called once when the command executes
void ToggleCameraExposure::Initialize() {
    if (toggle) {
        auto inst = nt::NetworkTableInstance::GetDefault();
        auto table = inst.GetTable("VisionTable");
        table->GetEntry("exposure").SetDouble(FOR_DRIVE);

        toggle = !toggle;
    }
    else {
        auto inst = nt::NetworkTableInstance::GetDefault();
        auto table = inst.GetTable("VisionTable");
        table->GetEntry("exposure").SetDouble(FOR_VISION);  

        toggle = !toggle;
    }
}
