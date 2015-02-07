#ifndef ARCADEDRIVETRAIN_H
#define ARCADEDRIVETRAIN_H

#include "WPILib.h"

class ArcDriveTrain
{
	//Arcade Drive Motors
	Jaguar *frontLeft;
	Jaguar *backLeft;
	Jaguar *frontRight;
	Jaguar *backRight;
	
	//Arcade Encoders
	Encoder *leftEncoder;
	Encoder *rightEncoder;
	
	//Arcade PIDs
	PIDController *arcadeLeft;
	PIDController *arcadeRight;
	
	RobotDrive *arcDrive;
	
public:
	ArcDriveTrain();
	~ArcDriveTrain();
		
	void arcadeDriveAuto();
		
	void ArcadeDrive();
	
	void ArcadeEncoderReset();
	void ArcadePID_Enable();
	void ArcadePID_SetPoint();
	void ArcadePID_Disable();
	
	float y;
};
#endif
