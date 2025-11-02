#include <Arduino.h>
#include "Kicker.h"
#include "PIN_NAMES.h"

Kicker::Kicker() {
        lastShot = millis();
}

void Kicker::kick() {
        if ((millis() - lastShot) >= COOLDOWN_MS) {
                digitalWrite(KICKER, HIGH);
                delay(ON_TIME_MS);
                digitalWrite(KICKER, LOW);
                lastShot = millis();
        }
}
