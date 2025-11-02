#include <Arduino.h>
#include "Motors.h"
#include "PIN_NAMES.h"
#include "Movement.h"
#include "SensorData.h"
#include "GET_TO_BALL.h"
#include "GET_TO_ENEMY_GOAL.h"
#include "GET_TO_MID.h"
#include "State.h"
#include <math.h>

GET_TO_MID::GET_TO_MID() {
}

void GET_TO_MID::act(Machine *m) {
        step();
        getNextState(m);
}

void GET_TO_MID::step() {
        if (SensorData::GOAL_ENEMY.visible) {
                if (SensorData::GOAL_HOME.visible) {
                        dx = (SensorData::GOAL_ENEMY.x + SensorData::GOAL_HOME.x) / 2 + 10; // + SensorData::RECEIVE.getTofFront() - 100) / 3;
                        dy = (SensorData::GOAL_ENEMY.y + SensorData::GOAL_HOME.y) / 2; // + SensorData::RECEIVE.getTofLeft() - SensorData::RECEIVE.getTofRight()) / 3;
                }
                else {
                        dx = (SensorData::GOAL_ENEMY.x - 92 + SensorData::RECEIVE.getTofFront() - 92) / 2 + 10;
                        dy = (-SensorData::GOAL_ENEMY.y - SensorData::RECEIVE.getTofLeft() + SensorData::RECEIVE.getTofRight()) / 2;
                }
        }
        else if (SensorData::GOAL_HOME.visible) {
                dx = (SensorData::GOAL_HOME.x + 92 + SensorData::RECEIVE.getTofFront() - 92) / 2 + 10;
                dy = (-SensorData::GOAL_HOME.y - SensorData::RECEIVE.getTofLeft() + SensorData::RECEIVE.getTofRight()) / 2;
        }
        else {
                dx = SensorData::RECEIVE.getTofFront() - 92 + 10;
                dy = -SensorData::RECEIVE.getTofLeft() + SensorData::RECEIVE.getTofRight();
        }
        Movement::moveToCart(dx, dy);
        Movement::setDribbler(255);
        Movement::move(SensorData::RECEIVE.getCompass());
}

void GET_TO_MID::getNextState(Machine *m) {
        if (SensorData::BALL.visible) {
                m->setCurrent(new GET_TO_BALL());
        }
}

void GET_TO_MID::DEBUG() {
        Serial.println("GET_TO_MID");
        Serial.print(" TOF Front: ");
        Serial.print(SensorData::RECEIVE.getTofFront());
        Serial.print(" TOF Left: ");
        Serial.print(SensorData::RECEIVE.getTofLeft());
        Serial.print(" TOF Right: ");
        Serial.println(SensorData::RECEIVE.getTofRight());
}
