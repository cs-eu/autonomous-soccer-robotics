#include <Arduino.h>
#include "TSL2584TSV.h"
#include "i2c_t3.h"
#include "PIN_NAMES.h"
#include "VL53L1X.h"
#include "TOF.h"
#include "Bodensensoren.h"

uint16_t maxValues[32] = {0};
uint16_t minValues[32] = {10000};

Bodensensoren boden;
TOF tof;

void setup() {
        Serial.begin(9600);
        tof.init();
        boden.initSecond();
}
void loop() {
        for (int i = 0; i < 32; i++) {
                maxValues[i] = max(maxValues[i], boden.getBoden(i).getLuminosity(0));
                minValues[i] = min(minValues[i], boden.getBoden(i).getLuminosity(0));
                boden.calibValues[i] = minValues[i] + ((maxValues[i] - minValues[i]) / 2);
                Serial.println(boden.calibValues[i]);
        }
        boden.setThresholds();
        Serial.println();
}
