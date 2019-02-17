// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Elevator.h"
#include "Commands/TeleopElevator.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Elevator::Elevator() : frc::Subsystem("Elevator"),
    kPVinner(frc::Preferences::GetInstance()->GetDouble("kPVinner", 1.0)),
    kVMaxInner(frc::Preferences::GetInstance()->GetDouble("kVMaxInner", 1.0)),
    kP_Inner(frc::Preferences::GetInstance()->GetDouble("kP Inner", 0.0)),
    kD_Inner(frc::Preferences::GetInstance()->GetDouble("kD Inner", 0.0)),
    kI_Inner(frc::Preferences::GetInstance()->GetDouble("kI Inner", 0.0)),
    kF_Inner(frc::Preferences::GetInstance()->GetDouble("kF Inner", 0.0)),
    kP_Outer(frc::Preferences::GetInstance()->GetDouble("kP Outer", 0.0)),
    kD_Outer(frc::Preferences::GetInstance()->GetDouble("kD Outer", 0.0)),
    kI_Outer(frc::Preferences::GetInstance()->GetDouble("kI Outer", 0.0)),
    kF_Outer(frc::Preferences::GetInstance()->GetDouble("kF Outer", 0.0)),
    kPVouter(frc::Preferences::GetInstance()->GetDouble("kPVouter", 1.0)),
    kVMaxOuter(frc::Preferences::GetInstance()->GetDouble("kVMaxOuter", 1.0)),
    kPVrear(frc::Preferences::GetInstance()->GetDouble("kPVrear", 1.0)),
    kVMaxRear(frc::Preferences::GetInstance()->GetDouble("kVMaxRear", 1.0)) {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    limitSwitchInnerTop.reset(new frc::DigitalInput(0));
    limitSwitchInnerBottom.reset(new frc::DigitalInput(1));
    talonInnerFront.reset(new WPI_TalonSRX(9));
    talonRear.reset(new WPI_TalonSRX(8));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    sparkMaxOuter.reset(new rev::CANSparkMax(sparkElevatorID, rev::CANSparkMax::MotorType::kBrushless));

    // setup elevator motors
    talonInnerFront->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
    talonInnerFront->ConfigReverseLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_FeedbackConnector, LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 0);
    talonInnerFront->SetSensorPhase(true);
    talonInnerFront->SetSelectedSensorPosition(0, 0);
    talonInnerFront->Config_kP(0, kP_Inner);
    talonInnerFront->Config_kI(0, kI_Inner);
    talonInnerFront->Config_kD(0, kD_Inner);
    talonInnerFront->Config_kF(0, kF_Inner);

    talonRear->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
    talonRear->SetSensorPhase(true);
    talonRear->SetSelectedSensorPosition(0, 0);

    pidOuter.reset(new rev::CANPIDController(sparkMaxOuter->GetPIDController()));
    sparkMaxOuterEncoder.reset(new rev::CANEncoder(sparkMaxOuter->GetEncoder()));

    // Config PID gains for Spark Max Outer
    pidOuter->SetOutputRange(kMinOutput, kMaxOutput);
    pidOuter->SetP(kP_Outer);
    pidOuter->SetI(kI_Outer);
    pidOuter->SetD(kD_Outer);
    pidOuter->SetFF(kF_Outer);

    // set scaling factor for position (since encoder is in motor)
    sparkMaxOuterEncoder->SetPositionConversionFactor(OUTER_GEAR_RATIO / OUTER_SPROCKET_PITCH);

    // Set encoder to 0 position
    sparkMaxOuterEncoder->SetPosition(0.0);
}

void Elevator::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new TeleopElevator());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Elevator::Periodic() {
    // Put code here to be run every loop
    SetElevatorPositions();

    // put elevator positions on smartdash
    frc::SmartDashboard::PutNumber("Inner Elevator", GetInnerPosInches());
    frc::SmartDashboard::PutNumber("Outer Elevator", GetOuterPosInches());
    frc::SmartDashboard::PutNumber("Rear Elevator", GetRearPosInches());
}

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator::SetElevatorPositions() {
    SetInnerPosition();
    SetOuterPosition();
    SetRearPosition();
}

void Elevator::SetInnerPosition() {
    double cmd = kPVinner * (mInnerPosCmd - GetInnerPos());

    if (cmd > kVMaxInner) {
        cmd = kVMaxInner;
    }
    else if (cmd < -kVMaxInner) {
        cmd = -kVMaxInner;
    }

    talonInnerFront->Set(ControlMode::Position, cmd * kTs);
}

void Elevator::SetOuterPosition() {
    double cmd = kPVouter * (mOuterPosCmd - GetOuterPos());

    if (cmd > kVMaxOuter) {
        cmd = kVMaxOuter;
    }
    else if (cmd < -kVMaxOuter) {
        cmd = -kVMaxOuter;
    }
    
    pidOuter->SetReference(cmd * kTs, rev::ControlType::kPosition);
}

void Elevator::SetRearPosition() {
    double cmd = kPVrear * (mRearPosCmd - GetRearPos());

    if (cmd > kVMaxRear) {
        cmd = kVMaxRear;
    }
    else if (cmd < -kVMaxRear) {
        cmd = -kVMaxRear;
    }
    
    talonRear->Set(ControlMode::Position, cmd * kTs);
}

bool Elevator::InnerAtPosition() {
    bool atPositionWithDeadband;

    if (std::abs(mRearPosCmd - GetInnerPos()) < 0.05 && std::abs(mRearPosCmd - GetInnerPos()) >= 0) {
        atPositionWithDeadband = true;
    }

    return atPositionWithDeadband;
}

bool Elevator::OuterAtPosition() {
    bool atPositionWithDeadband;

    if (std::abs(mOuterPosCmd - GetOuterPos()) < 0.05 && std::abs(mOuterPosCmd - GetOuterPos()) >= 0) {
        atPositionWithDeadband = true;
    }
    
    return atPositionWithDeadband;
}

bool Elevator::RearAtPosition() {
    bool atPositionWithDeadband;

    if (std::abs(mRearPosCmd - GetRearPos()) < 0.05 && std::abs(mRearPosCmd - GetRearPos()) >= 0) {
        atPositionWithDeadband = true;
    }
    
    return atPositionWithDeadband;
}

void Elevator::StopAllElevators() {
    StopInner();
    StopOuter();
    StopRear();
}

void Elevator::StopInner() {
    mInnerPosCmd = GetInnerPos();
}

void Elevator::StopRear() {
    mRearPosCmd = GetRearPos();
}

void Elevator::StopOuter() {
    mOuterPosCmd = GetOuterPos();
}

double Elevator::inchesToRotationsOuter(double inches){
    return inches / OUTER_SPROCKET_PITCH * OUTER_GEAR_RATIO;
}

double Elevator::rotationsToInchesOuter(double rotations) {
    return rotations * OUTER_SPROCKET_PITCH;
}

double Elevator::GetInnerPosInches() {
    return GetInnerPos() / ENCODER_CNTS_PER_REV * INNER_SPROCKET_PITCH;
}

double Elevator::GetRearPosInches() {
    // Implement this later!
}

double Elevator::GetOuterPosInches() {
    return GetOuterPos();   // No need for math here because we have the scale factor
}
