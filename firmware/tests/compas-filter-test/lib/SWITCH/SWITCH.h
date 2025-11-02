#ifndef SWITCH_h
#define SWITCH_h

#include <Arduino.h>
#include <PIN_NAMES.h>

class SWITCH
{
	public:
		SWITCH();
		bool switch1On();
		bool switch1Off();
		bool switch2On();
		bool switch2Off();
		bool switch3On();
		bool switch3Off();
		bool switch4On();
		bool switch4Off();
		bool switchProgramOn();
		bool switchProgramOff();
};
#endif