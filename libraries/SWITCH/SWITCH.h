#ifndef SWITCH_h
#define SWITCH_h

#include <Arduino.h>
#include <PIN_NAMES.h>

class SWITCH
{
public:
SWITCH();
bool switch1On();      // frei
bool switch1Off();
bool switch2On();      // Taktik / Schuss
bool switch2Off();
bool switch3On();      // Offensiv-Defensiv
bool switch3Off();
bool switch4On();      // Torfarbe (weil nur mit Akku drausen erreichber -> Halbzeit)
bool switch4Off();
bool switchProgramOn();
bool switchProgramOff();
};
#endif
