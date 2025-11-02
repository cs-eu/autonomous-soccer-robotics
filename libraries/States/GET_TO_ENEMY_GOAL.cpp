#include <Arduino.h>
#include "Motors.h"
#include "PIN_NAMES.h"
#include "Movement.h"
#include "SensorData.h"
#include "GET_TO_BALL.h"
#include "GET_TO_ENEMY_GOAL.h"
#include "GET_BALL_TO_MID.h"
#include "State.h"
#include <math.h>

/*
   180 -50
   90 -40
   50 -20
   20 -15
   -0.2159763*x - 13.31361
 */

#define DRIBBLER_ANGLE 30

GET_TO_ENEMY_GOAL::GET_TO_ENEMY_GOAL() {
}

void GET_TO_ENEMY_GOAL::act(Machine *m) {
        step();
        getNextState(m);
}

void GET_TO_ENEMY_GOAL::step() {
        int bias = 0; // SensorData::GOAL_ENEMY.at;

        if (SensorData::GOAL_ENEMY.at < -40) {  // rechts aussen
                Movement::moveTo(-135, 255);
                Movement::setDribbler(90);
        }
        else if (SensorData::GOAL_ENEMY.at > 40) { // links aussen
                Movement::moveTo(105, 255);
                Movement::setDribbler(90);
        }
        else {  // alles andere
                Movement::moveTo(SensorData::GOAL_ENEMY.ad, 255);
                Movement::setDribbler(-20);
        }

        int a1 = (int) (atan2(SensorData::GOAL_ENEMY.y - 20, SensorData::GOAL_ENEMY.x) * 180 / PI);
        int a2 = (int) (atan2(SensorData::GOAL_ENEMY.y + 20, SensorData::GOAL_ENEMY.x) * 180 / PI);

        // if (SensorData::RECEIVE.getTofFront()  < 30) { // gegner erkannt
        //         if (SensorData::GOAL_ENEMY.at < 0) {
        //                 Movement::moveTo(-135, 20);
        //         }
        //         else {
        //                 Movement::moveTo(135, 20);
        //         }
        //         Movement::setDribbler(100);
        // }
        // SensorData::RECEIVE.getCompass() > a1 && SensorData::RECEIVE.getCompass() < a2
        // int a = SensorData::GOAL_ENEMY.x - SensorData::RECEIVE.getTofFront();
        // if (SensorData::GOAL_ENEMY.ad < a2 && SensorData::GOAL_ENEMY.ad > a1 && SensorData::GOAL_ENEMY.x < 70 && !first && SensorData::GOAL_ENEMY.visible && SensorData::ballMS > 50000) { // schuss
        if (abs(SensorData::GOAL_ENEMY.ad) < 30 && SensorData::GOAL_ENEMY.x < 70 && !first && SensorData::GOAL_ENEMY.visible && SensorData::ballMS > 50000) {         // schuss
                // if (a < 10 && a > 0 && SensorData::GOAL_ENEMY.x < 60 && !first && SensorData::GOAL_ENEMY.visible && SensorData::ballMS > 50000) { // schuss
                Movement::setDribbler(-255);
                Movement::move(SensorData::RECEIVE.getCompass() - bias);
                delay(5);
                Movement::kick();
                Serial.println("SHOT");
        }

        // if (SensorData::GOAL_ENEMY.at > 0) {  //links aussen
        bias = SensorData::GOAL_ENEMY.ad;
        // }
        // if (SensorData::GOAL_ENEMY.at > 20 && SensorData::GOAL_ENEMY.visible) { //links aussen
        //         bias = 30;
        // }
        // else if (SensorData::GOAL_ENEMY.at > 0 && SensorData::GOAL_ENEMY.visible) {
        //         bias = SensorData::GOAL_ENEMY.ad * 20 / 30;
        // }
        // else if (SensorData::GOAL_ENEMY.at > 0) {  //links aussen
        //         bias = map(SensorData::GOAL_ENEMY.at, 0, 20, 0, 30);
        // }

        // if (!SensorData::GOAL_ENEMY.visible) {
        //         bias = 30;
        // }

        // Movement::move(SensorData::RECEIVE.getCompass() - bias);
        Movement::move(-bias);

        first = false;
}

void GET_TO_ENEMY_GOAL::getNextState(Machine *m) {
        if (!SensorData::HAS_BALL) {
                m->setCurrent(new GET_TO_BALL());
        }
}

void GET_TO_ENEMY_GOAL::DEBUG() {
        Serial.println("GET_TO_ENEMY_GOAL");
        Serial.print("GOAL_ENEMY.at: ");
        Serial.print(SensorData::GOAL_ENEMY.at);
        Serial.print(" GOAL_ENEMY.r: ");
        Serial.println(SensorData::GOAL_ENEMY.r);
}
