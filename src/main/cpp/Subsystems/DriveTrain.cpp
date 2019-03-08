// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/DriveTrain.h"
#include "Commands/TeleopDrive.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/TeleopDrive.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain"),
    kWheelDiameter(frc::Preferences::GetInstance()->GetDouble("Wheel Diameter", 6.0)),
    kP(frc::Preferences::GetInstance()->GetDouble("Drive kP", 0.0)),
    kFF(frc::Preferences::GetInstance()->GetDouble("Drive kFF", 180.0e-6)),
    maxFeetPerSec(frc::Preferences::GetInstance()->GetDouble("Drive FPS", 18.0)),
    maxAccelPerSec(frc::Preferences::GetInstance()->GetDouble("Drive Accel FPS^2", 10.0)),
    kP_Vision(frc::Preferences::GetInstance()->GetDouble("kP Vision", 30.0))
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    powerDistributionPanel.reset(new frc::PowerDistributionPanel(0));
    AddChild("PowerDistributionPanel", powerDistributionPanel);
    

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    sparkMaxLeftLead.reset(new rev::CANSparkMax(leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless));
    sparkMaxLeftFollow.reset(new rev::CANSparkMax(leftFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless));
    sparkMaxRightLead.reset(new rev::CANSparkMax(rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless));
    sparkMaxRightFollow.reset(new rev::CANSparkMax(rightFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless));
    analogGyro.reset(new frc::ADXRS450_Gyro());
    differentialDrive.reset(new frc::DifferentialDrive(*sparkMaxLeftLead, *sparkMaxRightLead));
    spikeLED.reset(new frc::Relay(0));
    spikeLED->Set(frc::Relay::kForward);

    // Set follower modes for sparkMax2 and sparkMax4
    sparkMaxLeftFollow->Follow(*sparkMaxLeftLead);
    sparkMaxRightFollow->Follow(*sparkMaxRightLead);

    pidControllerL.reset(new rev::CANPIDController(sparkMaxLeftLead->GetPIDController()));
    pidControllerR.reset(new rev::CANPIDController(sparkMaxRightLead->GetPIDController()));
    encoderControllerL.reset(new rev::CANEncoder(sparkMaxLeftLead->GetEncoder()));
    encoderControllerR.reset(new rev::CANEncoder(sparkMaxRightLead->GetEncoder()));

    // Set velocity scaling
    encoderControllerL->SetVelocityConversionFactor((M_PI * kWheelDiameter) / (kGearRatio * 60.0 * 12.0));
    encoderControllerR->SetVelocityConversionFactor((M_PI * kWheelDiameter) / (kGearRatio * 60.0 * 12.0));
    encoderControllerL->SetPositionConversionFactor((M_PI * kWheelDiameter) / (kGearRatio * 12.0));
    encoderControllerR->SetPositionConversionFactor((M_PI * kWheelDiameter) / (kGearRatio * 12.0));


    // Set min/max powers
    pidControllerL->SetOutputRange(kMinOutput, kMaxOutput);
    pidControllerR->SetOutputRange(kMinOutput, kMaxOutput);
    pidControllerL->SetSmartMotionMaxVelocity(maxFeetPerSec);
    pidControllerR->SetSmartMotionMaxVelocity(maxFeetPerSec);
    pidControllerL->SetSmartMotionMaxAccel(maxAccelPerSec);
    pidControllerR->SetSmartMotionMaxAccel(maxAccelPerSec);

    // Set kFF and kP (after tuning, since gains have already been determined)
    pidControllerL->SetP(kP);
    pidControllerR->SetP(kP);

    pidControllerL->SetFF(kFF);
    pidControllerR->SetFF(kFF);
}

void DriveTrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new TeleopDrive());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void DriveTrain::Periodic() {
    // Put code here to be run every loop
    differentialDrive->FeedWatchdog();
    frc::SmartDashboard::PutNumber("Drive Velocity", encoderControllerL->GetVelocity());

}

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrain::TankDrive(double left, double right) {
    differentialDrive->TankDrive(left, right);
}

void DriveTrain::ArcadeDrive(double xSpeed, double zRotation) 
{
    differentialDrive->ArcadeDrive(-xSpeed, zRotation);
}

void DriveTrain::VelocityArcade(double xSpeed, double zRotation, bool squaredInputs)
{
    double moveValue = xSpeed;
    double rotateValue = zRotation;

    if(moveValue > 0.0 && moveValue < 0.05){
        moveValue = 0.0;
    } else if(moveValue < 0.0 && moveValue > -0.05){
        moveValue = 0.0;
    } 

    if (fabs(rotateValue) < 0.01) {
        rotateValue = 0.0;
    }

    static bool reported = false;
    if (!reported)
    {
        HAL_Report(HALUsageReporting::kResourceType_RobotDrive, 4,
                   HALUsageReporting::kRobotDrive_ArcadeStandard);
        reported = true;
    }

    // local variables to hold the computed PWM values for the motors
    double leftMotorOutput;
    double rightMotorOutput;

    // LeftMove and leftRotate limits to +-1.0
    if (moveValue > 1.0)
    {
        moveValue = 1.0;
    }
    if (moveValue < -1.0)
    {
        moveValue = -1.0;
    }
    if (rotateValue > 1.0)
    {
        rotateValue = 1.0;
    }
    if (rotateValue < -1.0)
    {
        rotateValue = -1.0;
    }

    // square the inputs (while preserving the sign) to increase fine control
    // while permitting full power
    if (squaredInputs)
    {
        moveValue = std::copysign(moveValue * moveValue, moveValue);
        rotateValue = std::copysign(rotateValue * rotateValue, rotateValue);
    }

    if (moveValue > 0.0)
    {
        if (rotateValue > 0.0)
        {
            leftMotorOutput = moveValue - rotateValue;
            rightMotorOutput = std::max(moveValue, rotateValue);
        }
        else
        {
            leftMotorOutput = std::max(moveValue, -rotateValue);
            rightMotorOutput = moveValue + rotateValue;
        }
    }
    else
    {
        if (rotateValue > 0.0)
        {
            leftMotorOutput = -std::max(-moveValue, rotateValue);
            rightMotorOutput = moveValue + rotateValue;
        }
        else
        {
            leftMotorOutput = moveValue - rotateValue;
            rightMotorOutput = -std::max(-moveValue, -rotateValue);
        }
    }

    double leftMotorSpeed = leftMotorOutput * maxFeetPerSec;
    double rightMotorSpeed = rightMotorOutput * -maxFeetPerSec;

    // Send setpoints to pid controllers
    pidControllerL->SetReference(leftMotorSpeed, rev::ControlType::kSmartVelocity);
    pidControllerR->SetReference(rightMotorSpeed, rev::ControlType::kSmartVelocity);
}

void DriveTrain::VelocityTankDrive(double left, double right, bool squaredInputs) {
    static bool reported = false;
    if (!reported)
    {
        HAL_Report(HALUsageReporting::kResourceType_RobotDrive, 4,
                   HALUsageReporting::kRobotDrive_Tank);
        reported = true;
    }

    if (left > 1.0)
    {
        left = 1.0;
    }
    if (left < -1.0)
    {
        left = -1.0;
    }
    if (right > 1.0)
    {
        right = 1.0;
    }
    if (right < -1.0)
    {
        right = -1.0;
    }

    // square the inputs (while preserving the sign) to increase fine control
    // while permitting full power
    if (squaredInputs)
    {
        left = std::copysign(left * left, left);
        right = std::copysign(right * right, right);
    }

    double leftMotorSpeed = left * maxFeetPerSec;
    double rightMotorSpeed = right * -maxFeetPerSec;

    // Send setpoints to pid controllers
    pidControllerL->SetReference(leftMotorSpeed, rev::ControlType::kSmartVelocity);
    pidControllerR->SetReference(rightMotorSpeed, rev::ControlType::kSmartVelocity);
}

void DriveTrain::ClosedLoopVelocityControl(double speed)
{
    // read PID coefficients from SmartDashboard

    // // if PID coefficients on SmartDashboard have changed, write new values to controller
    // if(p != kP) {
    //     pidControllerL->SetP(p); kP = p;
    //     pidControllerR->SetP(p); kP = p;
    // }
    // if(i != kI) {
    //     pidControllerL->SetI(i); kI = i;
    //     pidControllerR->SetI(i); kI = i;
    // }
    // if(d != kD) {
    //     pidControllerL->SetD(d); kD = d;
    //     pidControllerR->SetD(d); kD = d;
    // }
    // if(iz != kIz) {
    //     pidControllerL->SetIZone(iz); kIz = iz;
    //     pidControllerR->SetIZone(iz); kIz = iz;
    // }
    // if(ff != kFF) {
    //     pidControllerL->SetFF(ff); kFF = ff;
    //     pidControllerR->SetFF(ff); kFF = ff;
    // }

    if (speed > 0.5)
    {
        speed = 0.5;
    }
    else if (speed < -0.5)
    {
        speed = -0.5;
    }
    //set the max speeds of the axis to 0.5.

    // read setpoint from joystick and scale by max rpm
    double setPointL = maxFeetPerSec * speed;
    double setPointR = maxFeetPerSec * -speed;

    // Send setpoints to pid controllers
    pidControllerL->SetReference(setPointL, rev::ControlType::kVelocity);
    pidControllerR->SetReference(setPointR, rev::ControlType::kVelocity);

    // Put editable PID values on Dashboard

    //std::cout << kFF << std::endl;
}

void DriveTrain::TankDriveVelocityError(double velocity, double error) {
    // double setPointL = -velocity_RPM - (kP_Vision * error);
    // double setPointR = velocity_RPM - (kP_Vision * error);
    double setPointL = velocity - (kP_Vision * error);
    double setPointR = velocity + (kP_Vision * error);

    printf ("Velocity Command %f\n", setPointL);
    pidControllerL->SetReference(setPointL, rev::ControlType::kVelocity);
    pidControllerR->SetReference(setPointR, rev::ControlType::kVelocity);
}

double DriveTrain::FPStoRPM(double fps) {
     return fps * kGearRatio * 60.0 * 12.0 / M_PI / kWheelDiameter;
}

double DriveTrain::RPMtoFPS(double rpm) {
    return rpm / kGearRatio / 60.0 / 12.0 * M_PI * kWheelDiameter;
}

double DriveTrain::GetVelocity() {
    return RPMtoFPS(sparkMaxLeftLead->GetEncoder().GetVelocity());
}

void DriveTrain::VisionSteerController(double distance, double angle, double h_pix_L, double h_pix_R) {
    // NOTE: Controlled updated to v3 by Jacob Krucinski on 3/03/19

    // Before we do anything, make sure to grab all controller gains from SmartDashboard
    kP_Vision       = frc::Preferences::GetInstance()->GetDouble("Vision kP", kP_Vision);
	kP_Omega        = frc::Preferences::GetInstance()->GetDouble("Vision kP Omega", kP_Omega);
    omega_Max       = frc::Preferences::GetInstance()->GetDouble("Vision Omega MAX", omega_Max);
	kP_Align_Master = frc::Preferences::GetInstance()->GetDouble("Vision kP Alignment", -1.0);

    // NOTE _v002 uses DISTANCE in ft AND angle in PIXELS
    // OUTPUT is v in ft/s   AND omega in -rad/s

    // Martin Krucinski 2018-03-07, converted to C++ by Jacob Krucinski

    // This is 2019-03-02 tuning
    // kP_Vision = 2;
    // kP_omega = 0.10;
    // Already set in .h file

    // *** TUNED VALUE 2019-03-01 Kp = 2;%0.5;
    // Kp_omega = 0.05;


    //   2018-03-05  Martin Krucinski
    //   Try to get robot to track angle better, increase Kp_omega from 8.0 to
    //   larger value, OR IS IT Robot.omega_max that limits this???
    //   Robot.omega_max  was set to 1.0!!
    // Kp_omega = 32;

    //   Jacob Krucinski 2019, Addition of wall alignment control
    //                   utilizing Priyanshu's L & R target height estimates

    //*** CONSTANT GAIN DOES NOT WORK, TOO NON LINEAR, USE DISTANCE VARYING GAIN
    //***Kp_align = -1;  % needs NEGATIVE since we define the alignment error as e_h_pix_L_R, L - R heights!
    //   Positive omega means robot turns to the LEFT
    double ref_distance =  3;  // [ft] distance where gain scaling is 1.0
    double kP_Align = kP_Align_Master * (distance / ref_distance); 

    // Angle

    double stop_turning_distance   = 1;    // [ft]  distance when steering control stops
    double start_cruising_distance = 1;    // [ft]  distance when velocity P-control turns off and cruising at constant velocity starts

    // Error for target heights
    double e_h_pix_L_R = h_pix_L - h_pix_R;

    double omega_temp;
    if (distance > stop_turning_distance) {    // distance units are in ft
        omega_temp = kP_Omega * angle + kP_Align * e_h_pix_L_R;
    }
    else {
        omega_temp = 0;
    }

    double omega;
    if (omega_temp > omega_Max) {
        omega = omega_Max;
    }
    else if  (omega_temp < -omega_Max) {
        omega = -omega_Max;
    }
    else {
        omega = omega_temp;
    }

    // Distance
    //
    //  MK 2019-03-02
    //  NOTE THAT VELOCITIES are in ft!!!
    //  Need to convert v_max to ft !!!
    //  Jacob: Added to .h file

    double v_offset    = 1;  // [ ft/s ]

    double v_temp;
    if (distance < start_cruising_distance) {    // distance units are in ft
        v_temp = v_offset;
    }
    else {
        v_temp = kP_Vision * distance + v_offset;
    }

    double v;
    if (v_temp > maxFeetPerSec) {
        v = maxFeetPerSec;
    }
    else if (v_temp < -maxFeetPerSec) {
        v = -maxFeetPerSec;
    }
    else {
        v = v_temp;
    }

    // Convert v to vL and vR
    double vLtemp      = v - omega * d / 2;
    double vL          = std::max(-maxFeetPerSec, std::min(+maxFeetPerSec, vLtemp));
    double vRtemp      = v + omega * d / 2;
    double vR          = std::max(-maxFeetPerSec, std::min(+maxFeetPerSec, vRtemp));

    // Send vL and vR to CAN Spark Maxes
    pidControllerL->SetReference(vL, rev::ControlType::kVelocity);  
    pidControllerR->SetReference(-vR, rev::ControlType::kVelocity);  
}

void DriveTrain::SmartMotionDrive(double distance) {
    pidControllerL->SetReference(distance, rev::ControlType::kSmartMotion);  
    pidControllerR->SetReference(-distance, rev::ControlType::kSmartMotion);  
}

void DriveTrain::SetLEDOn(bool LEDOn) {
    if (LEDOn) {
        spikeLED->Set(frc::Relay::kForward);
    }
    else {
        spikeLED->Set(frc::Relay::kOff);
    }
}

void DriveTrain::ZeroPosition() {
    encoderControllerL->SetPosition(0.0);
    encoderControllerR->SetPosition(0.0);
}