#ifndef TOF_h
#define TOF_h

#include "Arduino.h"
#include "VL53L1X.h"
#include "PIN_NAMES.h"

class TOF
{
public:
TOF();
void init();
uint8_t readFront();
uint8_t readRight();
uint8_t readBack();
uint8_t readLeft();
private:
int distance16;
uint8_t distance8;
VL53L1X TOF_FRONT;
VL53L1X TOF_RIGHT;
VL53L1X TOF_BACK;
VL53L1X TOF_LEFT;
uint8_t read(VL53L1X sensor);
};

#endif
