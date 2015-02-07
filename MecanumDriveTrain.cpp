#include "MecanumDriveTrain.h"

MecDriveTrain::MecDriveTrain()
{
	frontLeft	= new Jaguar(3);
	frontRight	= new Jaguar(4);
	backLeft	= new Jaguar(1);
	backRight	= new Jaguar(2);
			
	frontLeftEncoder	= new Encoder(5,6, false);
	frontRightEncoder	= new Encoder(7,8, false);
	backLeftEncoder		= new Encoder(1,2, false);
	backRightEncoder	= new Encoder(3,4, false);

	p = .0004;
	i = .0000005;
	d = .0004;
	mecFrontLeft	= new PIDController(p, i, d, frontLeftEncoder, frontLeft);
	mecFrontRight	= new PIDController(p, i, d, frontRightEncoder, frontRight);
	mecBackLeft		= new PIDController(p, i, d, backLeftEncoder, backLeft);
	mecBackRight	= new PIDController(p, i, d, backRightEncoder, backRight);

	LCD = DriverStationLCD::GetInstance();

	frontLeft->SetSafetyEnabled(false);
	frontRight->SetSafetyEnabled(false);
	backLeft->SetSafetyEnabled(false);
	backRight->SetSafetyEnabled(false);
	
	frontLeftEncoder->Start();
	backLeftEncoder->Start();
	frontRightEncoder->Start();
	backRightEncoder->Start();

	deadZone = 0.1;
	xr = 0;
	xl = 0;
	ramp = 0;
}

void MecDriveTrain::Set(float val)
{
	if(frontLeftEncoder->Get() > -3000)
	{
		if(ramp < val)
		{
			ramp += val/100;
		}
		frontLeft->Set(ramp);
		backLeft->Set(ramp);
		frontRight->Set(ramp);
		backRight->Set(ramp);
	}
	else
	{
		frontLeft->Set(0);
		backLeft->Set(0);
		frontRight->Set(0);
		backRight->Set(0);
	}
}

void MecDriveTrain::MecanumDrive(float x, float y, float z, int turboButton)
{
	//Dead zone code
	if (x < deadZone && x > -deadZone)
	{
		x = 0;
	}

	if (y < deadZone && y > -deadZone)
	{
		y = 0;
	}

	if (z < deadZone && z > -deadZone)
	{
		z = 0;
	}
	
	float multiplier = .7;
	
	if(turboButton) 
	{
		multiplier = 1;
	}

	frontLeft->Set((z - y - x) * -multiplier);
	frontRight->Set((z + y - x) * -multiplier);
	backLeft->Set((z - y + x) * -multiplier);
	backRight->Set((z + y + x) * -multiplier);	
}

void MecDriveTrain::ArcadeDrive(float x, float y, int turboButton)
{
	//Dead zone code
		if (x < deadZone && x > -deadZone)
		{
			x = 0;
		}

		if (y < deadZone && y > -deadZone)
		{
			y = 0;
		}

		
		
		float multiplier = .7;
		
		if(turboButton) 
		{
			multiplier = 1;
		}
		
		if (y > 0)
		{
			xr = y;
		}
		else
		{
			xr = y * 3/4;
		}
		
		if (y < 0)
		{
			xl = y;
		}
		else
		{
			xl = y * 3 / 4;
		}

		frontLeft->Set((xl - x) * -multiplier);
		frontRight->Set((xr + x) * -multiplier);
		backLeft->Set((xl - x) * -multiplier);
		backRight->Set((xr + x) * -multiplier);	
}


void MecDriveTrain::MecanumEncoderReset()
{
	frontLeftEncoder->Reset();
	frontRightEncoder->Reset();
	backLeftEncoder->Reset();
	backRightEncoder->Reset();
}

void MecDriveTrain::MecanumPID_Enable()
{
	mecFrontLeft->Enable();
	mecFrontRight->Enable();
	mecBackLeft->Enable();
	mecBackRight->Enable();

	mecFrontLeft->SetOutputRange(-.3, .3);
	mecFrontRight->SetOutputRange(-.3, .3);
	mecBackLeft->SetOutputRange(-.3, .3);
	mecBackRight->SetOutputRange(-.3, .3);	
}

void MecDriveTrain::MecanumPID_SetPoint(float target)
{
    MecanumEncoderReset();
	mecFrontLeft->SetSetpoint(TicksToFeet * target * -1);
	mecFrontRight->SetSetpoint(TicksToFeet * target * 1);
	mecBackLeft->SetSetpoint(TicksToFeet * target * -1);
	mecBackRight->SetSetpoint(TicksToFeet * target * 1);
}

void MecDriveTrain::MecanumPID_Disable()
{
	mecFrontLeft->Disable();
	mecFrontRight->Disable();
	mecBackLeft->Disable();
	mecBackRight->Disable();
}

void MecDriveTrain::EncoderStatus()
{
	LCD->PrintfLine(DriverStationLCD::kUser_Line1, "fl: %i", frontLeftEncoder->Get());
	LCD->PrintfLine(DriverStationLCD::kUser_Line2, "fr: %i", frontRightEncoder->Get());
	LCD->PrintfLine(DriverStationLCD::kUser_Line3, "bl: %i", backLeftEncoder->Get());
	LCD->PrintfLine(DriverStationLCD::kUser_Line4, "br: %i", backRightEncoder->Get());
}

void MecDriveTrain::EncoderRate()
{
	LCD->PrintfLine(DriverStationLCD::kUser_Line1, "fl: %f", frontLeftEncoder->GetRate());
	LCD->PrintfLine(DriverStationLCD::kUser_Line2, "fr: %f", frontRightEncoder->GetRate());
	LCD->PrintfLine(DriverStationLCD::kUser_Line3, "bl: %f", backLeftEncoder->GetRate());
	LCD->PrintfLine(DriverStationLCD::kUser_Line4, "br: %f", backRightEncoder->GetRate());	
}

void MecDriveTrain::DriveStatus()
{
	LCD->PrintfLine(DriverStationLCD::kUser_Line1, "fl: %f", frontLeft->Get());
	LCD->PrintfLine(DriverStationLCD::kUser_Line2, "fr: %f", frontRight->Get());
	LCD->PrintfLine(DriverStationLCD::kUser_Line3, "bl: %f", backLeft->Get());
	LCD->PrintfLine(DriverStationLCD::kUser_Line4, "br: %f", backRight->Get());
}



int MecDriveTrain::GetDistance()
{
	return(frontLeftEncoder->Get());
}

/*
void MecanumDriveTrain::mecanumDriveAuto()
{
	MecanumEncoderReset();
	MecanumPID_Enable();
	MecanumPID_SetPoint();
	MecanumPID_Disable();
}
*/
