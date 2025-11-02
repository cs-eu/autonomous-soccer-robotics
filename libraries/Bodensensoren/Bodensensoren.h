#ifndef BODENSENSOREN_H
#define BODENSENSOREN_H

#include "Arduino.h"
#include "TSL2584TSV.h"
#include "PIN_NAMES.h"

class Bodensensoren
{
private:
TSL2584TSV bodens[4] = {
        TSL2584TSV(0x49, 0),
        TSL2584TSV(0x49, 1),
        TSL2584TSV(0x49, 2),
        TSL2584TSV(0x49, 3)
};
int adressPinStorage[8] = {
        BODENADRESS1,
        BODENADRESS2,
        BODENADRESS3,
        BODENADRESS4,
        BODENADRESS5,
        BODENADRESS6,
        BODENADRESS7,
        BODENADRESS8
};
public:
Bodensensoren();
void initSecond();
TSL2584TSV getBoden(int id);
void setThresholds();
int resetInterrupt();
uint16_t calibValues[32] = {
        564,
        510,
        485,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510,
        510
};
};

#endif
