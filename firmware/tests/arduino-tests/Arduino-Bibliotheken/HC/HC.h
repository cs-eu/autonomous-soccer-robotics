#ifndef HC_H
#define HC_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
//#include "pins_arduino.h"

#include <inttypes.h>
class HC {
public:
	static void setEcho(int echoPin);
	static void setTrigger(int triggerPin);
	static void setStart(int Start);
	static void setDistance(int Distance);
	static int getDistance();
	static int getEcho();
	static int getTrigger();
	static int getStart();
	static void changeReal();
	static void change();
	
private:
	static int distance;
	static int echo;
	static int trigger;
	static long start;

};
#endif