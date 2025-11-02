#include <Arduino.h>
#include "Motors.h"
#include "PIN_NAMES.h"
#include "Movement.h"
#include "SensorData.h"
#include "GET_TO_BALL.h"
#include "GET_TO_ENEMY_GOAL.h"
#include "GET_TO_MID.h"
#include "GET_BALL_TO_MID.h"
#include "State.h"
#include <math.h>

GET_BALL_TO_MID::GET_BALL_TO_MID() {
}

void GET_BALL_TO_MID::act(Machine *m) {
        step();
        getNextState(m);
}

void GET_BALL_TO_MID::step() {
        // if (SensorData::GOAL_HOME.visible) {
        //         dx = 30;
        //         dy = (-SensorData::GOAL_HOME_ANGLE) + (SensorData::RECEIVE.getTofLeft() - SensorData::RECEIVE.getTofRight());
        //         dy /= 2;
        // }
        // else {
        //         dx = 30;
        //         dy = SensorData::RECEIVE.getTofLeft() - SensorData::RECEIVE.getTofRight();
        // }
        // int val = 180 / PI;
        // midAngle = (int) -val * atan2((double) dy, (double) dx);
        // midRadius = (int) sqrt((double) ((dx * dx) + (dy * dy)));
        //
        // if (dy > 4) {
        //         Movement::moveTo(midAngle, midRadius);
        // }
        // else {
        //         Movement::setStop(true);
        // }
        // Movement::setDribbler(255);
        // Movement::move(SensorData::RECEIVE.getCompass());
}

void GET_BALL_TO_MID::getNextState(Machine *m) {
        if (!SensorData::HAS_BALL) {
                m->setCurrent(new GET_TO_BALL());
        }
        else if (SensorData::GOAL_ENEMY.visible) {
                m->setCurrent(new GET_TO_ENEMY_GOAL());
        }
}

void GET_BALL_TO_MID::DEBUG() {
        Serial.println("GET_BALL_TO_MID");
}
