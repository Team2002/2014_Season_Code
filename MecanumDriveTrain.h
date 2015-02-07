#ifndef MECANUMDRIVETRAIN_H
#define MECANUMDRIVETRAIN_H

#include "WPILib.h"
#define TicksToFeet 253
//Robot sprocket ratio is 15:24

class MecDriveTrain
{
	float deadZone;
	
	//Mecanum Drive Motors
	Jaguar	*frontLeft,
			*frontRight,
			*backLeft,
			*backRight;
	
	//Mecanum Encoders
	Encoder	*frontLeftEncoder,
			*frontRightEncoder,
			*backLeftEncoder,
			*backRightEncoder;
	
	//Mecanum PIDs
	PIDController	*mecFrontLeft,
					*mecFrontRight,
					*mecBackLeft,
					*mecBackRight;
	
	DriverStationLCD *LCD;
	
	float ramp;
	float xr;
	float xl;
	
	float p, i, d;
	
public:
		MecDriveTrain();
		~MecDriveTrain();
		
		//void mecunumDriveAuto();
		
		void MecanumDrive(float x, float y, float z, int turboButton);
		void ArcadeDrive(float x, float y, int turboButton);
		void MecanumEncoderReset();
		void MecanumPID_Enable();
		void MecanumPID_SetPoint(float target);
		void MecanumPID_Disable();
		void Set(float val);
		void EncoderStatus();
		void EncoderRate();
		void DriveStatus();
		int GetDistance();

};
#endif
