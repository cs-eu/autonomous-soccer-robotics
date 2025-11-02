#include <Arduino.h>
#include "PIN_NAMES.h"
#include "Movement.h"
#include "SensorData.h"
#include "TEST_DRIBBLER.h"
#include "State.h"
#include <math.h>

TEST_DRIBBLER::TEST_DRIBBLER() {
}

void TEST_DRIBBLER::act(Machine *m) {
        step();
        getNextState(m);
}

void TEST_DRIBBLER::step() {
        Movement::setDribbler(255);
        if (SensorData::HAS_BALL) {
                Movement::moveTo(30, 255);
        }
        else {
                Movement::moveTo(0, 0);
        }
}

void TEST_DRIBBLER::getNextState(Machine *m) {
}

void TEST_DRIBBLER::DEBUG() {
        Serial.println("TEST_DRIBBLER");
}
