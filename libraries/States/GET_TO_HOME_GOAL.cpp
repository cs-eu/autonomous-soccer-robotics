#include <Arduino.h>
#include "PIN_NAMES.h"
#include "Movement.h"
#include "SensorData.h"
#include "GET_TO_HOME_GOAL.h"
#include "State.h"
#include <math.h>

GET_TO_HOME_GOAL::GET_TO_HOME_GOAL() {
}

void GET_TO_HOME_GOAL::act(Machine *m) {
        step();
        getNextState(m);
}

void GET_TO_HOME_GOAL::step() {
        Movement::moveTo(SensorData::GOAL_HOME_ANGLE, 255);
        Movement::move(SensorData::RECEIVE.getCompass());
}

void GET_TO_HOME_GOAL::getNextState(Machine *m) {
        if (SensorData::GOAL_HOME_RADIUS < 40) {
                // m->setCurrent(new GET_TO_MID_OF_HOME_GOAL());
        }
}

void GET_TO_HOME_GOAL::DEBUG() {
        Serial.println("GET_TO_HOME_GOAL");
}
