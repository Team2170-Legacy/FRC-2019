// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "frc/commands/Subsystem.h"
#include "frc/WPILib.h"
#include "rev/CANSparkMax.h"
#include "ctre/Phoenix.h"
#include <cmath>

#define ENCODER_CNTS_PER_REV 4096

#define INNER_MAX_RPM 18730
#define INNNER_GEAR_RATIO 49.0
#define INNER_SPROCKET_PITCH 1.432
#define INNER_MAGIC_VELOCITY 2000			// 27"/sec = 2.7"/100 msec = .6 rev/100 msec = 2457 cnts/100 msec
#define INNER_MAGIC_ACCEL	(INNER_MAGIC_VELOCITY * 2)		// accel in terms of cnts/100msec / second

#define OUTER_MAX_RPM 5676
#define OUTER_GEAR_RATIO 14.2
#define OUTER_SPROCKET_PITCH 1.432
#define OUTER_MAGIC_VELOCITY 20			// inches/sec
#define OUTER_MAGIC_ACCEL (OUTER_MAGIC_VELOCITY * 3) 	// inches/sec^2

#define REAR_MAX_RPM 5840
#define REAR_GEAR_RATIO 81.0
#define REAR_SMALL_SPROCKET_PITCH 1.432
#define REAR_LARGE_SPROCKET_PITCH 1.751
#define REAR_DRUM_DIAMETER 1.22
#define REAR_INCHES_PER_ROTAION ((REAR_SMALL_SPROCKET_PITCH / REAR_LARGE_SPROCKET_PITCH) * REAR_DRUM_DIAMETER * M_PI)
#define IN_POSITION_DEADBAND 1.0
#define REAR_MAGIC_VELOCITY	450			// 3"/sec = 0.3"/100 msec ~ 0.1 rev/100 msec = 393 cnts/100 msec
#define REAR_MAGIC_ACCEL (REAR_MAGIC_VELOCITY * 5)
/**
 *
 *
 * @author ExampleAuthor
 */
class Elevator: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<frc::DigitalInput> limitSwitchInnerTop;
	std::shared_ptr<frc::DigitalInput> limitSwitchInnerBottom;
	std::shared_ptr<WPI_TalonSRX> talonInnerFront;
	std::shared_ptr<WPI_TalonSRX> talonRear;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	const int sparkElevatorID = 5;
	const double kTs = 0.02;		// 20 msec tick for periodic
	const double kP_Inner;
	const double kD_Inner;
	const double kI_Inner;
	const double kF_Inner;
	const double kP_Outer;
	const double kD_Outer;
	const double kI_Outer;
	const double kF_Outer;
	const double kP_Rear;
	const double kD_Rear;
	const double kI_Rear;
	const double kF_Rear;
	const bool bMagic;

	const double kMaxOutput = 1, kMinOutput = -1;

	const double kMaxInnerPos;
	const double kMinInnerPos;
	const double kMaxOuterPos;
	const double kMinOuterPos;
	const double kMaxRearPos;
	const double kMinRearPos;
	std::shared_ptr<rev::CANSparkMax> sparkMaxOuter;
	std::shared_ptr<rev::CANEncoder> sparkMaxOuterEncoder;
	std::shared_ptr<rev::CANPIDController> pidOuter;

	double mInnerPosCmd = 0.0;
	double mOuterPosCmd = 0.0;
	double mRearPosCmd = 0.0;
	void ControlElevatorPositions();
	void ControlInnerPosition(bool bMagic = false);
	void ControlOuterPosition(bool bMagic = false);
	void ControlRearPosition();
	void StopAllElevators();
	void StopInner();
	void StopOuter();
	void StopRear();
	double GetInnerPos() { return talonInnerFront->GetSelectedSensorPosition(0);}
	double GetRearPos() { return talonRear->GetSelectedSensorPosition(0);}
	double GetOuterPos() { return sparkMaxOuter->GetEncoder().GetPosition();}
	double inchesToRotationsOuter(double inches);
	double rotationsToInchesOuter(double rotations);
	double inchesToCountsInner(double inches);
	double countsToInchesInner(double counts);
	double inchesToCountsRear(double inches);
	double countsToInchesRear(double counts);

public:
	const double kHatchL1;
	const double kHatchL2;
	const double kHatchL3;
	const double kCargoL1;
	const double kCargoL2;
	const double kCargoL3;
	const double kOuterHome = 3.0;
	const double kInnerHome = 0.1;
	const double kHatchReleasePos;
	const double kRearLiftPos;
	const double kFwdLiftPos;
	
	Elevator();
	void InitDefaultCommand() override;
	void Periodic() override;
	bool LimitInnerTop() { return limitSwitchInnerTop->Get();}
	bool LimitInnerBottom() { return limitSwitchInnerBottom->Get();}
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void SetInnerPosition(double pos) { mInnerPosCmd = pos;}
	void IndexInnerPosition(double index) { mInnerPosCmd += index;}
	void SetOuterPosition(double pos) { mOuterPosCmd = -pos;}
	void IndexOuterPosition(double index) { mOuterPosCmd += -index;}
	void SetRearPosition(double pos) { mRearPosCmd = pos;}
	bool InnerAtPosition();
	bool OuterAtPosition();
	bool RearAtPosition();
	double GetInnerPosInches();
	double GetInnerCmd() { return mInnerPosCmd;}
	double GetRearPosInches();
	double GetOuterPosInches();
	double GetOuterCmd() { return -mOuterPosCmd;}
	void SlewInner(double slew);
	void SlewOuter(double slew);
	void UpdateDisabledElevators();
	void RigForClimb();
};
#endif
