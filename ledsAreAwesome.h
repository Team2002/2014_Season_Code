#ifndef LEDSAREAWESOME_H
#define LEDSAREAWESOME_H
#include "WPILib.h"
#include "math.h"

class ledsAreAwesome
{
	//LED color controllers
	Jaguar* red;
	Jaguar* blue;
	Jaguar* green;
	Timer* theTimer;
	
	DriverStationLCD* LCD;
	
	float rValue;
	float gValue;
	float bValue;
public:
	ledsAreAwesome();
	~ledsAreAwesome();
	void timerStart();
	void colorSet(int r, int g, int b);
	void breathing(float period, float high, float low);
	void strobe(float period, float high, float low);
	void solid(float intensity);
	void ledsOutput();
};
#endif
