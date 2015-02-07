#include "ledsAreAwesome.h"

ledsAreAwesome::ledsAreAwesome()
{
	red		= new Jaguar(8);
	green	= new Jaguar(10);
	blue	= new Jaguar(9);
	
	theTimer = new Timer();
	
	LCD		= DriverStationLCD::GetInstance();
	
	rValue	= 0;
	gValue	= 0;
	bValue	= 0;
}

void ledsAreAwesome::timerStart()
{
	theTimer->Start();
}

void ledsAreAwesome::colorSet(int r, int g, int b)
{
	rValue = r/255.0;
	gValue = g/255.0;
	bValue = b/255.0;
}

void ledsAreAwesome::breathing(float period, float high, float low)
{
	red->Set(rValue * (sin(theTimer->Get() * period / 6.28318)) * (high-low) / 2 + (high-low) / 2 + low);
	green->Set(gValue * (sin(theTimer->Get() * period / 6.28318)) * (high-low) / 2 + (high-low) / 2 + low);
	blue->Set(bValue * (sin(theTimer->Get() * period / 6.28318)) * (high-low) / 2 + (high-low) / 2 + low);
	
}

void ledsAreAwesome::strobe(float period, float high, float low)
{
	if(fmod(theTimer->Get(), period) > (period / 2))
	{
		red->Set(high * rValue);
		green->Set(high * gValue);
		blue->Set(high * bValue);
	}
	else
	{
		red->Set(low * rValue);
		green->Set(low * gValue);
		blue->Set(low * bValue);
	}
}

void ledsAreAwesome::solid(float intensity) {
	red->Set(intensity * rValue *-1);
	green->Set(intensity * gValue *-1);
	blue->Set(intensity * bValue *-1);
}

void ledsAreAwesome::ledsOutput() {
	LCD->PrintfLine(DriverStationLCD::kUser_Line5, "%.2f %.2f %.2f", red->Get(), green->Get(), blue->Get());
}
