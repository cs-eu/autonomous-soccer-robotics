#include <Arduino.h>
#include "Motors.h"
#include "PIN_NAMES.h"
#include "Movement.h"
#include "SensorData.h"
#include "GET_TO_BALL.h"
#include "GET_TO_ENEMY_GOAL.h"
#include "STAND_STILL.h"
#include "State.h"

STAND_STILL::STAND_STILL() {
}

void STAND_STILL::act(Machine *m) {
        step();
        getNextState(m);
}

void STAND_STILL::step() {
        Movement::moveTo(0, 0);
        Movement::setDribbler(0);
        Movement::move(SensorData::RECEIVE.getCompass());
}

void STAND_STILL::getNextState(Machine *m) {
        //m->setCurrent(new STAND_STILL());
}

void STAND_STILL::DEBUG() {
        Serial.println("STAND_STILL");
        Serial.print("GOAL_HOME_ANGLE ");
        Serial.print(SensorData::GOAL_HOME_ANGLE);
        Serial.print(" GOAL_HOME_RADIUS ");
        Serial.print(SensorData::GOAL_HOME_RADIUS);
        Serial.print(" GOAL_ENEMY_ANGLE ");
        Serial.print(SensorData::GOAL_ENEMY_ANGLE);
        Serial.print(" GOAL_ENEMY_RADIUS ");
        Serial.print(SensorData::GOAL_ENEMY_RADIUS);
        Serial.print(" BALL_ANGLE ");
        Serial.print(SensorData::BALL_ANGLE);
        Serial.print(" BALL_RADIUS ");
        Serial.println(SensorData::BALL_RADIUS);
}
