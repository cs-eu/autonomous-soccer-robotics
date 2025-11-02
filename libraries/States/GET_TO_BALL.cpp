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

GET_TO_BALL::GET_TO_BALL() {
}

void GET_TO_BALL::act(Machine *m) {
        step();
        getNextState(m);
}

void GET_TO_BALL::step() {
        Movement::setDribbler(255);
        int bias = 0; // + SensorData::GOAL_ENEMY.ad;
        int speed = max(SensorData::BALL.r - 5, 20);

        if (abs(SensorData::BALL.ad) > 100) {
                speed = 255;
        }
        else if (abs(SensorData::GOAL_ENEMY.at) > 50) {
                speed = 20;
        }
        else if (SensorData::GOAL_ENEMY.x < 20) {
                speed = 20;
        }

        int upperBound = 0; // 2
        int lowerBound = -6; // -12 -10

        if (SensorData::BALL.at > upperBound || SensorData::BALL.at < lowerBound) {
                Movement::moveTo(SensorData::BALL.ad, 255);
        }
        else {
                // Movement::moveToCart(SensorData::BALL.x - 12, SensorData::BALL.y, speed);
                Movement::moveTo(SensorData::BALL.at, 255);
        }

        // if (abs(SensorData::BALL.at) < 45 && SensorData::switch2) {
        //         bias = SensorData::BALL.at;
        // }
        // else {
        //         if (SensorData::GOAL_ENEMY.at > 20 && SensorData::GOAL_ENEMY.visible) { //links aussen
        //                 bias = 30;
        //         }
        //         else if (SensorData::GOAL_ENEMY.at > 0 && SensorData::GOAL_ENEMY.visible) {
        //                 bias = SensorData::GOAL_ENEMY.ad * 20 / 30;
        //         }
        // }

        Movement::move(SensorData::RECEIVE.getCompass() - bias);
}

void GET_TO_BALL::getNextState(Machine *m) {
        if (SensorData::HAS_BALL) {
                m->setCurrent(new GET_TO_ENEMY_GOAL());
        }
        else if (!SensorData::BALL.visible) {
                m->setCurrent(new GET_TO_MID());
        }
}

void GET_TO_BALL::DEBUG() {
        Serial.println("GET_TO_BALL");
        Serial.print("BALL_ANGLE: ");
        Serial.print(SensorData::BALL.ad);
        Serial.print(" BALL_RADIUS: ");
        Serial.println(SensorData::BALL.r);
}
