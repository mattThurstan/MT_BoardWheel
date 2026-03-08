/*
 * MT_BoardWheels.cpp - Library for long/short/skate board wheel setup. Used in longboardLight1 project..
 * Latching bipolar hall effect sensor mounted on the chassis, with 4/8 magnets mounted on the adjacent wheel(s).
 * Add one array per wheel sensor.
 * MTS Standish (mattThurstan), 2026.
 * Copyleft.
 */
 
#include "Arduino.h"
#include "MT_BoardWheel.h"

//#define DEBUG	//comment/un-comment

#ifdef DEBUG
  #define DEBUG_PRINT_HEADER(x); Serial.print(F("MT_BoardWheel - Wheel "))
  #define DEBUG_PRINT(x);    Serial.print(x)
  #define DEBUG_PRINTF(x);    Serial.print(F(x))
  #define DEBUG_PRINTLN(x);  Serial.println(x)
  #define DEBUG_PRINTLNF(x); Serial.println(F(x))
#else
  #define DEBUG_PRINT_HEADER(x)
  #define DEBUG_PRINT(x)     //blank line
  #define DEBUG_PRINTF(x)    //blank line
  #define DEBUG_PRINTLN(x)   //blank line
  #define DEBUG_PRINTLNF(x)  //blank line
#endif
 
MT_BoardWheel::MT_BoardWheel() {
	//empty declaration
}

void MT_BoardWheel::Init(byte sensorPin, float radius, byte magnetTotal) {
	sensorPin = sensorPin;
	radius = radius;
	circumference = 2 * PI * radius;
	magnetTotal = magnetTotal;
	counter = 0;
	//sensorReadPrevMillis = 0;
	rps = 0;
	mps = 0;
	maxMps = 0;
	distTraveledForward = 0;
	distTraveledBackward = 0;
	
	DEBUG_PRINT_HEADER()
	DEBUG_PRINTLNF("Wheel setup.");
}

void MT_BoardWheel::SetCounter(byte value) {
	counter = value;
}

void MT_BoardWheel::IncrementCounter() {
	counter++;
}

void MT_BoardWheel::DecrementCounter() {
	counter--;
}

void MT_BoardWheel::ResetWheel() {
	counter = 0;
	//sensorReadPrevMillis = 0;
	rps = 0;
	mps = 0;
	maxMps = 0;
	distTraveledForward = 0;
	distTraveledBackward = 0;
	
	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLNF("Wheel reset.");
}

/* DoUpdate - call from a timed-loop every second.
 * This NEEDS to be called every 1 sec, otherwise we don't get 'revolutions per SECOND'!
 * Call after orientation has been calculated.
 * Remember to detachInterrupt before calling,
 * and (re-)attachInterrupt after calling.
 * direction: 0=forward, 1=backward, 2=
 */
void MT_BoardWheel::DoUpdate(byte direction) { DoUpdateEverySec(direction); }
void MT_BoardWheel::DoUpdateEverySec(byte direction) {
	rps = counter / magnetTotal;
	mps = rps * circumference; //speed in meters per second. distance travelled in 1 second
	maxMps = mps;
	
	if (direction == 0) {
	  distTraveledForward = (distTraveledForward + (unsigned long)mps);
	} else if (direction == 1) {
	  distTraveledBackward = (distTraveledBackward + (unsigned long)mps);
	}
	
	counter = 0; //reset the counter to 0 after reading
	
	DEBUG_PRINT_HEADER();
	DEBUG_PRINTF("RPS = ");
	DEBUG_PRINT(rps);
	DEBUG_PRINTF(", MPS = ");
	DEBUG_PRINT(mps);
	DEBUG_PRINTF(", Forward = ");
	DEBUG_PRINT(distTraveledForward);
	DEBUG_PRINTF(", Backward = ");
	DEBUG_PRINT(distTraveledBackward);
	DEBUG_PRINTLNF(".");
}

double MT_BoardWheel::GetRps() {
	return rps;
}
double MT_BoardWheel::GetMps() {
	return mps;
}
double MT_BoardWheel::GetMaxMps() {
	return maxMps;
}
unsigned long MT_BoardWheel::GetDistTraveledForward() {
	return distTraveledForward;
}
unsigned long MT_BoardWheel::GetDistTraveledBackward() {
	return distTraveledBackward;
}