#include "Arduino.h"
#include "Bodensensoren.h"
#include "TSL2584TSV.h"
#include "PIN_NAMES.h"

Bodensensoren::Bodensensoren() {
}

void Bodensensoren::initSecond() {
        for (int i = 0; i < 32; i++) {
                if (i != 17) { // orion2: 17, orion1: keiner
                        Serial.println(i);
                        getBoden(i).begin();
                }
        }
        setThresholds();
}

TSL2584TSV Bodensensoren::getBoden(int id) {
        int pin = id / 4;
        for (int i = 0; i < 8; i++) {
                if (i != pin) {
                        digitalWrite(adressPinStorage[i], LOW);
                }
                else {
                        digitalWrite(adressPinStorage[i], HIGH);
                }
        }
        return bodens[id % 4];
}

void Bodensensoren::setThresholds() {
        for (int i = 0; i < 32; i++) {
                getBoden(i).setThreshold(calibValues[i]);
        }
}

int Bodensensoren::resetInterrupt() {
        int ret = 0;
        for (int i = 0; i < 32; i++) {
                if (i != 22 && i != 17) { // orion2: 22, orion1: keiner
                        TSL2584TSV current = getBoden(i);
                        current.resetInterrupt();
                        if (current.getLuminosity(0) > calibValues[i]) {
                                ret = 1;
                        }
                }
        }
        return ret;
}
