#include <Arduino.h>
#include "Movement.h"
#include "Kicker.h"
#include "Motors.h"
#include "PID.h"

#define POWER_CONSTANT 0.000282352941

void Front() {
        Movement::setFront(true);
        Movement::setAngle(Movement::getLine());
}

void Left() {
        Movement::setLeft(true);
        Movement::setAngle(Movement::getLine());
}

void Right() {
        Movement::setRight(true);
        Movement::setAngle(Movement::getLine());
}

void Back() {
        Movement::setBack(true);
        Movement::setAngle(Movement::getLine());
}

namespace Movement {
  int speed;
  int angle;
  int dribbler;
  boolean stop;
  boolean kickerBool;
  Motors motors;
  Kicker kicker;
  PID orientationPIDdriving(3, 0, 10000);
  PID orientationPIDstill(2, 0, 0);
  PID positionPID(100, 0, 0);
  boolean bFront = false, bLeft = false, bRight = false, bBack = false;
  int bodenInterruptPins[16] = {
          BODENINTERRUPT_FRONT1,
          BODENINTERRUPT_FRONT2,
          BODENINTERRUPT_FRONT3,
          BODENINTERRUPT_FRONT4,
          BODENINTERRUPT_RIGHT1,
          BODENINTERRUPT_RIGHT2,
          BODENINTERRUPT_RIGHT3,
          BODENINTERRUPT_RIGHT4,
          BODENINTERRUPT_LEFT1,
          BODENINTERRUPT_LEFT2,
          BODENINTERRUPT_LEFT3,
          BODENINTERRUPT_LEFT4,
          BODENINTERRUPT_BACK1,
          BODENINTERRUPT_BACK2,
          BODENINTERRUPT_BACK3,
          BODENINTERRUPT_BACK4
  };
void move(int compass) {
        checkBoden();
        orientationPIDstill.update(compass);
        orientationPIDdriving.update(compass);
        if (millis() % 20 == 0) {
                Serial.println(orientationPIDstill.getOutput());
        }
        if (getLine() == 181) {
                if (!stop) {
                        motors.setSpeeds(angle, orientationPIDdriving.getOutput(), speed);
                }
                else {
                        motors.stop(orientationPIDstill.getOutput(), 80);
                }
        }
        else {
                motors.setSpeeds(getLine(), orientationPIDdriving.getOutput(), 255);
        }

        motors.setDribblerSpeed(dribbler);
        motors.writeSpeeds();

        if (kickerBool) {
                kicker.kick();
        }
}

void moveTo(int angle, int radius) {
        Movement::setAngle(angle);
        positionPID.update(radius);
        int s = positionPID.getOutput();
        if (s != 0) {
                Movement::setSpeed(s);
                Movement::setStop(false);
        }
        else {
                Movement::setStop(true);
        }
}

int getCurrentFeedback(int motor) {
        return motors.getFeedback(motor);
}

void setAngle(int newAngle) {
        angle = newAngle;
}

void setStop(boolean newStop) {
        stop = newStop;
}

void setSpeed(int newSpeed) {
        speed = newSpeed;
}

void setFront(boolean newVal) {
        bFront = newVal;
}

void setBack(boolean newVal) {
        bBack = newVal;
}

void setLeft(boolean newVal) {
        bLeft = newVal;
}

void setRight(boolean newVal) {
        bRight = newVal;
}

void init() {
        motors.initMotors();
        angle = 0;
        dribbler = 0;
        stop = false;
        kickerBool = false;
        speed = 255;
        for (int i = 0; i < 16; i++) {
                pinMode(bodenInterruptPins[i], INPUT_PULLUP);
        }
        for (int i = 0; i < 4; i++) {
                attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[i]), Front, FALLING);
        }
        for (int i = 4; i < 8; i++) {
                attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[i]), Right, FALLING);
        }
        for (int i = 8; i < 12; i++) {
                attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[i]), Left, FALLING);
        }
        for (int i = 12; i < 16; i++) {
                attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[i]), Back, FALLING);
        }
}

int getLine() {
        return 181;
        if (bFront) {
                if (bLeft) {
                        return 135;
                }
                else if (bRight) {
                        return -135;
                }
                else {
                        return 180;
                }
        }
        else if (bBack) {
                if (bLeft) {
                        return 45;
                }
                else if (bRight) {
                        return -45;
                }
                else {
                        return 0;
                }
        }
        else if (bLeft) {
                return 90;
        }
        else if (bRight) {
                return -90;
        }
        else {
                return 181;
        }
}

void checkBoden() {
        bFront = (digitalRead(bodenInterruptPins[0]) == 0) || (digitalRead(bodenInterruptPins[1]) == 0 || (digitalRead(bodenInterruptPins[2]) == 0) || (digitalRead(bodenInterruptPins[3]) == 0));
        bRight = (digitalRead(bodenInterruptPins[4]) == 0) || (digitalRead(bodenInterruptPins[5]) == 0 || (digitalRead(bodenInterruptPins[6]) == 0) || (digitalRead(bodenInterruptPins[7]) == 0));
        bLeft = (digitalRead(bodenInterruptPins[8]) == 0) || (digitalRead(bodenInterruptPins[9]) == 0 || (digitalRead(bodenInterruptPins[10]) == 0) || (digitalRead(bodenInterruptPins[11]) == 0));
        bBack = (digitalRead(bodenInterruptPins[12]) == 0) || (digitalRead(bodenInterruptPins[13]) == 0 || (digitalRead(bodenInterruptPins[14]) == 0) || (digitalRead(bodenInterruptPins[15]) == 0));
}
}
