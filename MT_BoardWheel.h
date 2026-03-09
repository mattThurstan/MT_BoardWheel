/*
 * MT_BoardWheel.h - Library for long/short/skate board single wheel setup. Used in longboardLight1 project..
 * Calculates speed and travel distance. 
 * Latching bipolar hall effect sensor mounted on the chassis, with 4/8 magnets mounted on the adjacent wheel.
 * MTS Standish (mattThurstan), 2026.
 * Copyleft.
 */
 
#ifndef __MT_BOARDWHEEL_H__
#define __MT_BOARDWHEEL_H__
 
#include "Arduino.h"


/*----------------------------main header declerations----------------------------*/
class MT_BoardWheel
{
  private:
	byte sensorPin;
	float radius;
	float circumference;
	byte magnetTotal;
	volatile byte counter;
	//unsigned long sensorReadPrevMillis;
	double rps;
	double mps;
	double maxMps;
	unsigned long distTraveledForward;
	unsigned long distTraveledBackward;
  
  public:
	MT_BoardWheel();			//declaration
	void Init(byte sensorPin, float radius, byte magnetTotal);
	void SetCounter(byte value); //set counter to value
	void IncrementCounter();	//increment counter by 1
	void DecrementCounter();	//decrement counter by 1
	void ResetWheel();
	
	void DoUpdate(byte direction);		//call every 1 second from main program loop
	void DoUpdateEverySec(byte direction);

	double GetRps();			//revolutions per second
	double GetMps();			//meters per second (speed)
	double GetMaxMps();			//max speed reached
	unsigned long GetDistTraveledForward();	//total dist traveled forwards
	unsigned long GetDistTraveledBackward();//total dist traveled backwards
};

#endif