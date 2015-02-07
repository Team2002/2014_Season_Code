#include "ManipulatorStuff.h"

ManipulatorStuff::ManipulatorStuff()
{
	mtrTusks	= new Jaguar(5);
	mtrIntake	= new Jaguar(7);
	mtrArm		= new Jaguar(6);
	
	topTusks	= new AnalogChannel(1);
	btmTusks	= new AnalogChannel(3);
	topArm		= new AnalogChannel(4);
	btmArm		= new AnalogChannel(2);
	
	LCD			= DriverStationLCD::GetInstance();

	voltageThreshold = 3;
	deadZone = 0.1;
}

void ManipulatorStuff::ManipulatorReset()
{
	mtrIntake->Set(0);
	if(topTusks->GetVoltage() < voltageThreshold)
	{
		mtrTusks->Set(.4);
	} else {
		mtrTusks->Set(0);
	}
	
	if(topArm->GetVoltage() < voltageThreshold)
	{
		mtrArm->Set(.4);
	} else {
		mtrArm->Set(0);
	}
}

void ManipulatorStuff::TuskMovement(float yVal)
{
	yVal *= -1; // Invert b/c backwords
	if (yVal > deadZone && topTusks->GetVoltage() < voltageThreshold)
	{
		mtrTusks->Set(yVal/2);
	}
	else if(yVal < -deadZone && btmTusks->GetVoltage() < voltageThreshold)
	{
		mtrTusks->Set(yVal/2);
	}
	else
	{
		mtrTusks->Set(0);
	}
}

void ManipulatorStuff::IntakeFunction(bool switchMotor, bool bumper1, bool bumper2, int toggle)
{
	float speed = .25;
/*
	if(toggle == 0 && switchMotor)
	{
		toggle = 1;
	}
	
	else if(toggle == 1 && (bumper1 == true || bumper2 == true))
	{
		toggle = 0;
	}
	*/
	if(bumper1 == true)
	{
		mtrIntake->Set(speed);
	}
	else if(bumper2 == true)
	{
		mtrIntake->Set(-speed);
	} else {
		mtrIntake->Set(0);
	}
}

void ManipulatorStuff::ArmFunction(float otherVal)
{
	otherVal *= -1;
	if (otherVal < -deadZone && btmArm->GetVoltage() < voltageThreshold)
	{
		mtrArm->Set(-otherVal/2);
	}
	else if (otherVal > deadZone && topArm->GetVoltage() < voltageThreshold)
	{
		mtrArm->Set(-otherVal/2);
	}
	else
	{
		mtrArm->Set(0);
	}	
}

void ManipulatorStuff::movingTogether(bool bumper1, bool bumper2)
{
	if(bumper1)
	{
		mtrArm->Set((1 / armToTuskRatio) / togetherRatio);
		mtrTusks->Set((1 / armToTuskRatio) / (togetherRatio * 2));
	}
	else if(bumper2)
	{
		mtrArm->Set((-1/armToTuskRatio)/togetherRatio);
		mtrTusks->Set((-1/armToTuskRatio)/(togetherRatio*2));
	}
}

void ManipulatorStuff::stop()
{
	mtrArm->Set(0);
	mtrIntake->Set(0);
	mtrTusks->Set(0);
}

void ManipulatorStuff::dispSwitches()
{
	LCD->PrintfLine(DriverStationLCD::kUser_Line1, "TT: %f", topTusks->GetVoltage());
	LCD->PrintfLine(DriverStationLCD::kUser_Line2, "BT: %f", btmTusks->GetVoltage());
	LCD->PrintfLine(DriverStationLCD::kUser_Line3, "TA: %f", topArm->GetVoltage());
	LCD->PrintfLine(DriverStationLCD::kUser_Line4, "BA: %f", btmArm->GetVoltage());
}

void ManipulatorStuff::ManipulatorAuto()
{
	mtrIntake->Set(1);
	if(btmTusks->GetVoltage() < voltageThreshold)
	{
		mtrTusks->Set(-.2);
	} else {
		mtrTusks->Set(0);
	}
	
	if(btmArm->GetVoltage() < voltageThreshold)
	{
		mtrArm->Set(-.4);
	} else {
		mtrArm->Set(0);
	}
	
}

void ManipulatorStuff::motorStatus()
{
	LCD->PrintfLine(DriverStationLCD::kUser_Line1, "tusk: %f", mtrTusks->Get());
	LCD->PrintfLine(DriverStationLCD::kUser_Line2, "arm: %f", mtrArm->Get());	
}
