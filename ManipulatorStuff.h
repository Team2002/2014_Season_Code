#ifndef MANIPULATORSTUFF_H
#define MANIPULATORSTUFF_H

#define armToTuskRatio 1
#define togetherRatio 2

#include "WPILib.h"

class ManipulatorStuff
{
	
	float	voltageThreshold,
			deadZone;

	
	Jaguar	*mtrTusks,	//Winch Motor
			*mtrIntake,	//Intake Wheel Motor
			*mtrArm;	//Raising and lowering previous motor Motor
	
	//Limit switches
	AnalogChannel	*topTusks,
					*btmTusks,
					*topArm,
					*btmArm;
	
	DriverStationLCD *LCD;
public:
	ManipulatorStuff();
	~ManipulatorStuff();
	
	void ManipulatorReset();
	
	void TuskMovement(float yVal);
	void IntakeFunction(bool switchMotor, bool bumper1, bool bumper2, int toggle);
	void ArmFunction(float otherVal);
	void dispSwitches();
	void motorStatus();
	void ManipulatorAuto();
	void stop();

	void movingTogether(bool bumper1, bool bumper2);
};
#endif
