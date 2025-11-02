#include <Arduino.h>
#include "PIN_NAMES.h"
#include "Movement.h"
#include "SensorData.h"
#include "DEFEND.h"
#include "GET_TO_GOAL_MID.h"
#include "State.h"
#include <math.h>

DEFEND::DEFEND() {
}

void DEFEND::act(Machine *m) {
        step();
        getNextState(m);
}

void DEFEND::step() {
        if (abs(SensorData::BALL.at) > 90) {
                Movement::moveTo(SensorData::BALL.ad, 255);
        }
        else {
                // double dx = (2 * SensorData::BALL.x) + SensorData::GOAL_HOME.x; // SensorData::GOAL_HOME.x + 35;
                // double dy = (2 * SensorData::BALL.y) + SensorData::GOAL_HOME.y; // SensorData::BALL.y;
                // Movement::moveToCart(dx, dy);
                // Movement::moveTo(SensorData::BALL.at, 255);
                if (SensorData::BALL.ad > 0) {
                        Movement::moveTo(90, 255);
                }
                else {
                        Movement::moveTo(-90, 255);
                }
        }
        if (SensorData::HAS_BALL) {
                Movement::setDribbler(-255);
                Movement::move(SensorData::RECEIVE.getCompass());
                delay(5);
                Movement::kick();
                Serial.println("SHOT");
        }
        Movement::setDribbler(0);
        Movement::move(SensorData::RECEIVE.getCompass());
}

void DEFEND::getNextState(Machine *m) {
        if (SensorData::switch2) {
                if (!SensorData::BALL.visible || SensorData::GOAL_HOME.x < -35) { // || SensorData::GOAL_HOME_RADIUS < 2) {
                        m->setCurrent(new GET_TO_GOAL_MID());
                }
        }
        else if (!SensorData::BALL.visible) { // || SensorData::GOAL_HOME_RADIUS < 2) {
                m->setCurrent(new GET_TO_GOAL_MID());
        }
}

void DEFEND::DEBUG() {
        Serial.println("DEFEND");
}
