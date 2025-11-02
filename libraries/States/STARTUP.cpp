#include <Arduino.h>
#include "PIN_NAMES.h"
#include "Movement.h"
#include "SensorData.h"
#include "STARTUP.h"
#include "GET_TO_BALL.h"
#include "TEST_CIRCLE.h"
#include "GET_TO_GOAL_MID.h"
#include "State.h"
#include <math.h>

STARTUP::STARTUP() {
}

void STARTUP::act(Machine *m) {
        step();
        getNextState(m);
}

void STARTUP::step() {
        Movement::setStop(true);
        // if (!SensorData::switch3) {
        //         Movement::setDribbler(255);
        // }
        // else {
        Movement::setDribbler(0);
        // }
        if (SensorData::RECEIVE.isReady()) {
                Movement::move(SensorData::RECEIVE.getCompass());
        }
}

void STARTUP::getNextState(Machine *m) {
        if (SensorData::switchProgramOn && SensorData::RECEIVE.isReady()) {
                if (SensorData::calibrated) {
                        if (!SensorData::switch3) {
                                m->setCurrent(new GET_TO_BALL());
                        }
                        else {
                                m->setCurrent(new GET_TO_GOAL_MID());
                        }
                }
        }
}

void STARTUP::DEBUG() {
        Serial.println("STARTUP");
}
