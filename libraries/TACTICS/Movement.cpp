#include <Arduino.h>
#include "Movement.h"
#include "Kicker.h"
#include "Motors.h"
#include "PID.h"
#include "SensorData.h"
#include <math.h>

void Front() {
        if (Movement::getLine() == 181 || Movement::getLine() == 90 || Movement::getLine() == -90) {
                Movement::setFront(true);
        }
}

void Left() {
        if (Movement::getLine() == 181 || Movement::getLine() == 180 || Movement::getLine() == 0) {
                Movement::setLeft(true);
        }
}

void Right() {
        if (Movement::getLine() == 181 || Movement::getLine() == 180 || Movement::getLine() == 0) {
                Movement::setRight(true);
        }
}

void Back() {
        if (Movement::getLine() == 181 || Movement::getLine() == 90 || Movement::getLine() == -90) {
                Movement::setBack(true);
        }
}

// Front
void b1() {
        Movement::bodens[0] = 1;
}
void b2() {
        Movement::bodens[1] = 1;
}
void b3() {
        Movement::bodens[2] = 1;
}
void b4() {
        Movement::bodens[3] = 1;
}
// Right
void b5() {
        Movement::bodens[4] = 1;
}
void b6() {
        Movement::bodens[5] = 1;
}
void b7() {
        Movement::bodens[6] = 1;
}
void b8() {
        Movement::bodens[7] = 1;
}
// Left
void b9() {
        Movement::bodens[12] = 1;
}
void b10() {
        Movement::bodens[13] = 1;
}
void b11() {
        Movement::bodens[14] = 1;
}
void b12() {
        Movement::bodens[15] = 1;
}
// Back
void b13() {
        Movement::bodens[8] = 1;
}
void b14() {
        Movement::bodens[9] = 1;
}
void b15() {
        Movement::bodens[10] = 1;
}
void b16() {
        Movement::bodens[11] = 1;
}

namespace Movement {
int speed;
int angle;
int dribbler;
boolean stop;
boolean kickerBool;
Motors motors;
Kicker kicker;
PID orientationPID(5, 0, 0.4, 90); // 5, 0, 0.4, 90
PID orientationPIDball(20, 0, 0.4, 255); // 10, 0, 0.4, 200
PID positionPID(10, 10, 0, 255, 0); // 10, 10, 0, 255, 0 // 7
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
int bodens[16] = {0};
// verschiebung = 28,125
int bodenAngles[16] = {
        332,
        355,
        16,
        39,
        61,
        84,
        106,
        129,
        151,
        174,
        196,
        219,
        241,
        264,
        286,
        309
};
void kick() {
        kickerBool = true;
}
void move(int compass) {
        checkBoden();
        orientationPID.update(compass);
        orientationPIDball.update(compass);
        if (SensorData::HAS_BALL || abs(SensorData::BALL_ANGLE) > 90) {
                positionPID.resetIntegral();
        }
        if (getLine() == 181) {
                if (!stop) {
                        if (SensorData::HAS_BALL) {
                                motors.setSpeedsBiasRear(angle, orientationPIDball.getOutput());
                                // motors.setSpeeds(angle, orientationPID.getOutput(), speed);
                        }
                        else {
                                if (abs(SensorData::RECEIVE.getCompass()) > 90) {
                                        motors.setSpeeds(angle, orientationPID.getOutput(), 0);
                                }
                                else {
                                        motors.setSpeeds(angle, orientationPID.getOutput(), speed);
                                }
                        }
                }
                else {
                        motors.stop(orientationPID.getOutput(), 20);
                }
        }
        else {
                motors.setSpeeds(getLine(), orientationPID.getOutput(), 255);
        }

        if (SensorData::HAS_BALL) {
                motors.setDribblerSpeed(dribbler);
        }
        else {
                motors.setDribblerSpeed(dribbler);
        }
        motors.writeSpeeds();

        if (kickerBool) {
                kicker.kick();
                kickerBool = false;
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

void moveToCart(double dx, double dy) {
        int midRadius = sqrt(dx * dx + dy * dy);
        int midAngle = (int) (atan2((double) dy, (double) dx) * 180 / PI);
        Movement::moveTo(midAngle, midRadius);
}

void moveToCart(double dx, double dy, int speed) {
        int midAngle = (int) (atan2((double) dy, (double) dx) * 180 / PI);
        Movement::moveTo(midAngle, speed);
}

void setDribbler(int newVal) {
        dribbler = newVal;
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
        stop = true;
        kickerBool = false;
        pinMode(KICKER, OUTPUT);
        speed = 255;
        for (int i = 0; i < 16; i++) {
                pinMode(bodenInterruptPins[i], INPUT_PULLUP);
        }
        // for (int i = 0; i < 4; i++) {
        //         attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[i]), Front, FALLING);
        // }
        // for (int i = 4; i < 8; i++) {
        //         attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[i]), Right, FALLING);
        // }
        // for (int i = 8; i < 12; i++) {
        //         attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[i]), Left, FALLING);
        // }
        // for (int i = 12; i < 16; i++) {
        //         attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[i]), Back, FALLING);
        // }
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[0]), b1, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[1]), b2, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[2]), b3, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[3]), b4, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[4]), b5, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[5]), b6, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[6]), b7, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[7]), b8, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[8]), b9, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[9]), b10, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[10]), b11, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[11]), b12, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[12]), b13, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[13]), b14, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[14]), b15, FALLING);
        attachInterrupt(digitalPinToInterrupt(bodenInterruptPins[15]), b16, FALLING);
}

int getLine() {
        int num = 0;
        int angles[16] = {0};
        for (int i = 0; i < 16; i++) {
                int val = bodens[i];
                if (i == 13) {
                        val = bodens[14];
                }
                else if (i == 12) {
                        val = bodens[11];
                }
                num += val;
                angles[i] = val * bodenAngles[i];
        }
        if (num == 0) {
                return 181;
        }
        double sumC = 0;
        double sumS = 0;
        for (int i = 0; i < 16; i++) {
                if (angles[i] != 0) {
                        sumC += cos(angles[i] * PI / 180) / num;
                        sumS += sin(angles[i] * PI / 180) / num;
                }
        }
        int ret = (int) atan2(sumS, sumC) * 180 / PI;
        if (ret < 0) {
                return ret + 180;
        }
        return ret - 180;

        if (bFront) {
                if (bLeft) {
                        return 180 - 15; // -45
                }
                else if (bRight) {
                        return -180 + 15; // +45
                }
                else if (bBack) {
                        return 181;
                }
                else {
                        return 180;
                }
        }
        else if (bBack) {
                if (bLeft) {
                        return 15; // +45
                }
                else if (bRight) {
                        return -15; // -45
                }
                else {
                        return 0;
                }
        }
        else if (bLeft) {
                if (bRight) {
                        return 181;
                }
                else {
                        return 90;
                }
        }
        else if (bRight) {
                return -90;
        }
        else {
                return 181;
        }
}

void checkBoden() {
        // for (int i = 0; i < 16; i++) {
        //         if (digitalRead(bodenInterruptPins[0]) == 0) {
        //                 return 1;
        //         }
        //         else if (sensor.getvalueof(i) == true) {
        //                 return 1
        //         }
        //         return 0;
        // }
        // boolean Front = (digitalRead(bodenInterruptPins[0]) == 0) || (digitalRead(bodenInterruptPins[1]) == 0 || (digitalRead(bodenInterruptPins[2]) == 0) || (digitalRead(bodenInterruptPins[3]) == 0));
        // boolean Right = (digitalRead(bodenInterruptPins[4]) == 0) || (digitalRead(bodenInterruptPins[5]) == 0 || (digitalRead(bodenInterruptPins[6]) == 0) || (digitalRead(bodenInterruptPins[7]) == 0));
        // boolean Left = (digitalRead(bodenInterruptPins[8]) == 0) || (digitalRead(bodenInterruptPins[9]) == 0 || (digitalRead(bodenInterruptPins[10]) == 0) || (digitalRead(bodenInterruptPins[11]) == 0));
        // boolean Back = (digitalRead(bodenInterruptPins[12]) == 0) || (digitalRead(bodenInterruptPins[13]) == 0 || (digitalRead(bodenInterruptPins[14]) == 0) || (digitalRead(bodenInterruptPins[15]) == 0));
        // boolean line = Front || Back || Left || Right;
        // if (!line) {
        //         bFront = false;
        //         bBack = false;
        //         bLeft = false;
        //         bRight = false;
        // }
        if (SensorData::RECEIVE.getLine() == 0) {
                bFront = false;
                bBack = false;
                bLeft = false;
                bRight = false;
        }
        if (SensorData::RECEIVE.getLine() == 0) {
                for (int i = 0; i < 16; i++) {
                        bodens[i] = 0;
                }
        }
}
}
