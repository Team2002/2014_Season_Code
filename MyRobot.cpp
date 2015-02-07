#include "WPILib.h"
#include "MecanumDriveTrain.h"
#include "ArcadeDriveTrain.h"
#include "ManipulatorStuff.h"
#include "ledsAreAwesome.h"

class RobotDemo : public SimpleRobot
{
	MecDriveTrain*		robot;
	Joystick*			stick;
	Joystick*			armStick;
	DriverStationLCD* 	LCD;
	ManipulatorStuff* 	arm;
	ledsAreAwesome*		leds;
	
public:
	RobotDemo()
	{
		stick		= new Joystick(1);
		armStick	= new Joystick(2);

		robot		= new MecDriveTrain();	
		arm 		= new ManipulatorStuff();
				
		leds 		= new ledsAreAwesome();
		
		LCD 		= DriverStationLCD::GetInstance();
	}

	void Autonomous()
	{
		robot->MecanumPID_Enable();
		robot->MecanumPID_SetPoint(14);
		while (IsAutonomous())
		{
			if(robot->GetDistance() < -3300)
			{
				arm->ManipulatorAuto();
			}
			robot->EncoderStatus();
			LCD->UpdateLCD();
			if(IsDisabled()) {
				robot->MecanumPID_Disable();
			}
		}

	}

	void OperatorControl()
	{
		while (IsOperatorControl())
		{
			robot->ArcadeDrive(stick->GetY(), stick->GetZ(), stick->GetRawButton(1));
			//robot->MecanumDrive(stick->GetX(), stick->GetY(), stick->GetZ(), stick->GetRawButton(1));
//			robot->MecanumDrive(0, stick->GetY(), 0, stick->GetRawButton(1));
			//robot->Test();

			arm->TuskMovement(armStick->GetY());
			arm->ArmFunction(armStick->GetTwist());
			arm->IntakeFunction(armStick->GetRawButton(2), armStick->GetRawButton(6), armStick->GetRawButton(8), 0);	//Takes ball in
			arm->movingTogether(armStick->GetRawButton(5), armStick->GetRawButton(7));
			
			leds->ledsOutput();
			
			robot->DriveStatus();
			//robot->Turning(stick->GetRawButton(3), stick->GetRawButton(4));
			//arm->dispSwitches();
			LCD->UpdateLCD();
			Wait(0.005);				// wait for a motor update time
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {
		robot->MecanumPID_Enable();
		robot->MecanumPID_SetPoint(-15);
		while(IsTest()) {
			arm->ManipulatorReset();
			//
			robot->EncoderStatus();
			LCD->UpdateLCD();		

			if(IsDisabled()) {
				robot->MecanumPID_Disable();
			}
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

