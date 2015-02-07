#include "ArcadeDriveTrain.h"

ArcDriveTrain::ArcDriveTrain()
{
	frontLeft		= new Jaguar(3);
	backLeft		= new Jaguar(4);
	frontRight		= new Jaguar(1);
	backRight		= new Jaguar(2);
	
	leftEncoder		= new Encoder(1,2);
	rightEncoder	= new Encoder(3,4);
	
	arcadeLeft		= new PIDController(.0001, .0001, .0001, leftEncoder, frontLeft);
	arcadeRight		= new PIDController(.0001, .0001, .0001, rightEncoder, frontRight);
	
	arcDrive		= new RobotDrive(frontLeft, frontRight);
}

void ArcDriveTrain::ArcadeEncoderReset()
{
	leftEncoder->Reset();
	rightEncoder->Reset();
}

void ArcDriveTrain::ArcadePID_Enable()
{
	arcadeLeft->Enable();
	arcadeRight->Enable();
}
/*
void ArcDriveTrain::ArcadePID_SetPoint()
{
	arcadeLeft->SetSetPoint(TicksToFeet*2);
	arcadeRight->SetSetPoint(TicksToFeet*2);
}
*/

void ArcDriveTrain::ArcadePID_Disable()
{
	arcadeLeft->Disable();
	arcadeRight->Disable();
}

/*
void ArcDriveTrain::ArcadeDriveAuto()
{
	
}
*/
