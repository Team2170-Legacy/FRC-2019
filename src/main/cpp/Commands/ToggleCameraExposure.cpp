/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/ToggleCameraExposure.h"
bool toggle = false;
const double FOR_DRIVE = 40.0;
const double FOR_VISION = 15.0;

ToggleCameraExposure::ToggleCameraExposure() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

/**
 * @brief Get exposure from VisionTable NetworkTable and change it 
 * between FOR_DRIVE and FOR_VISION
 * 
 * @param FOR_DRIVE = 40.0
 * @param FOR_VISION = 0.0
 */
void ToggleCameraExposure::Initialize() {
    // OLD code
    // if (toggle) {
    //     auto inst = nt::NetworkTableInstance::GetDefault();
    //     auto table = inst.GetTable("VisionTable");
    //     table->GetEntry("vt_exposure_flag").SetDouble(toggle);

    //     toggle = !toggle;
    // }
    // else {
    //     auto inst = nt::NetworkTableInstance::GetDefault();
    //     auto table = inst.GetTable("VisionTable");
    //     table->GetEntry("vt_exposure_flag").SetDouble(toggle);  

    //     toggle = !toggle;
    // }

    auto inst = nt::NetworkTableInstance::GetDefault();
    auto table = inst.GetTable("VisionTable");
    table->GetEntry("vt_exposure_flag").SetBoolean(toggle);
    toggle = !toggle;
}
