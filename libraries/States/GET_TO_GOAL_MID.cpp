#include <Arduino.h>
#include "PIN_NAMES.h"
#include "Movement.h"
#include "SensorData.h"
#include "GET_TO_GOAL_MID.h"
#include "DEFEND.h"
#include "State.h"
#include <math.h>

/*
   wenn tor nicht sichtbar -> nach hinten fahren
   wenn ball sichtbar && ballangletrue < -90 oder > 90 ->fahr zum ball /weil dann nimmt er tangente, solange bis ball vor ihm -> keine gefahr mehr
 */

GET_TO_GOAL_MID::GET_TO_GOAL_MID() {
}

void GET_TO_GOAL_MID::act(Machine *m) {
        step();
        getNextState(m);
}

void GET_TO_GOAL_MID::step() {
        if (SensorData::GOAL_HOME.visible) {
                if (SensorData::BALL.visible && abs(SensorData::BALL.at) > 90) {
                        Movement::moveTo(SensorData::BALL.ad, 255);
                }
                else {
                        double dy = SensorData::GOAL_HOME.y;
                        double dx = SensorData::GOAL_HOME.x + 30;
                        Movement::moveToCart(dx, dy);
                }
        }
        else {
                Movement::moveTo(180, 255);
        }
        Movement::setDribbler(0);
        Movement::move(SensorData::RECEIVE.getCompass());
}

void GET_TO_GOAL_MID::getNextState(Machine *m) {
        if (SensorData::switch2) {
                if (SensorData::BALL.visible && SensorData::GOAL_HOME.x > -35) { // && SensorData::GOAL_HOME_RADIUS > 1) {
                        m->setCurrent(new DEFEND());
                }
        }
        else if (SensorData::BALL.visible) { // && SensorData::GOAL_HOME_RADIUS > 1) {
                m->setCurrent(new DEFEND());
        }
}

void GET_TO_GOAL_MID::DEBUG() {
        Serial.println("GET_TO_GOAL_MID");
        Serial.print("GOAL_HOME_ANGLE: ");
        Serial.print(SensorData::GOAL_HOME_ANGLE);
        Serial.print(" GOAL_HOME_RADIUS: ");
        Serial.println(SensorData::GOAL_HOME_RADIUS);
}
