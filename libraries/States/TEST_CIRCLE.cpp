#include <Arduino.h>
#include "Motors.h"
#include "PIN_NAMES.h"
#include "Movement.h"
#include "SensorData.h"
#include "GET_TO_BALL.h"
#include "GET_TO_ENEMY_GOAL.h"
#include "STAND_STILL.h"
#include "TEST_CIRCLE.h"
#include "State.h"

TEST_CIRCLE::TEST_CIRCLE() {
}

void TEST_CIRCLE::act(Machine *m) {
        step();
        getNextState(m);
}

void TEST_CIRCLE::step() {
        if ((millis() - lastTime) >= (circleTime / 360)) {
                lastTime = millis();
                dir++;
                if (dir > -181 && dir < 181) {
                        Movement::moveTo(dir, circleSpeed);
                }
                else {
                        done = true;
                }
        }
        Movement::setDribbler(0);
        Movement::move(SensorData::RECEIVE.getCompass());
}

void TEST_CIRCLE::getNextState(Machine *m) {
        if (done) {
                m->setCurrent(new STAND_STILL());
        }
}

void TEST_CIRCLE::DEBUG() {

}
