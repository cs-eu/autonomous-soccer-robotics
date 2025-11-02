#include <Arduino.h>
#include "COM.h"

Vision::Vision(){
}
void Vision::init() {
        RASPI.begin(115200);
}
void Vision::receive(int msg) {
        length = RASPI.available();
        for (int i = 0; i < length; i++) {
                inByte = RASPI.read();
                // if ((raspiIndex == -1) && (inByte == 255)) {
                if (inByte == 255) {
                        if (raspiIndexFinder == 255) {
                                raspiIndex = 15; // 9
                        }
                }
                else if (raspiIndex == 0) {
                        angle = inByte;
                }
                else if (raspiIndex == 1) {
                        angle += inByte * 255;
                        if (angle > 180) {
                                angle -= 360;
                        }
                        BALL_ANGLE = angle;
                }
                else if (raspiIndex == 2) {
                        distance = inByte;
                }
                else if (raspiIndex == 3) {
                        distance += inByte * 255;
                        BALL_DISTANCE = distance;
                }
                else if (raspiIndex == 4) {
                        angleY = inByte;
                }
                else if (raspiIndex == 5) {
                        angleY += inByte * 255;
                        if (angleY > 180) {
                                angleY -= 360;
                        }
                        GOAL_YELLOW_ANGLE = -angleY;
                }
                else if (raspiIndex == 6) {
                        distanceY = inByte;
                }
                else if (raspiIndex == 7) {
                        distanceY += inByte * 255;
                        GOAL_YELLOW_DISTANCE = distanceY;
                }
                else if (raspiIndex == 8) {
                        angleB = inByte;
                }
                else if (raspiIndex == 9) {
                        angleB += inByte * 255;
                        if (angleB > 180) {
                                angleB -= 360;
                        }
                        GOAL_BLUE_ANGLE = -angleB;
                }
                else if (raspiIndex == 10) {
                        distanceB = inByte;
                }
                else if (raspiIndex == 11) {
                        distanceB += inByte * 255;
                        GOAL_BLUE_DISTANCE = distanceB;
                }
                else if (raspiIndex == 12) {
                        angleT = inByte;
                }
                else if (raspiIndex == 13) {
                        angleT += inByte * 255;
                        if (angleT > 180) {
                                angleT -= 360;
                        }
                        BALL_ANGLE_TRUE = -angleT;
                }
                if (raspiIndex > -1) {
                        raspiIndex++;
                }
                if (raspiIndex > 15)  {
                        RASPI.write(msg);
                        raspiIndex = 0;
                }
                raspiIndexFinder = inByte;
        }
}

int Vision::getBallAngle() {
        return BALL_ANGLE;
}
int Vision::getBallRadius() {
        return BALL_DISTANCE;
}
int Vision::getBlueAngle() {
        return GOAL_BLUE_ANGLE;
}
int Vision::getBlueRadius() {
        return GOAL_BLUE_DISTANCE;
}
int Vision::getYellowAngle() {
        return GOAL_YELLOW_ANGLE;
}
int Vision::getYellowRadius() {
        return GOAL_YELLOW_DISTANCE;
}
int Vision::getTrueAngle() {
        return BALL_ANGLE_TRUE;
}



Receiver::Receiver(){
}

void Receiver::init() {
        OTHER_TEENSY.begin(115200);
}

void Receiver::receive() {
        int length = OTHER_TEENSY.available();
        for (int i = 0; i < length; i++) {
                ready = true;
                inByte = OTHER_TEENSY.read();
                if (inByte == 255 || pos == 7) {
                        pos = 0;
                }
                else if (pos < 7) {
                        receivedValues[pos] = inByte;
                        pos++;
                }
        }
}

boolean Receiver::isReady() {
        return ready;
}

int Receiver::getCompass() {
        int comp = (receivedValues[0] * 4) + (receivedValues[1] >> 6);
        while (comp > 180) {
                comp -= 360;
        }
        if (comp <= 1 && comp >= -1) {
                return 0;
        }
        return comp;
}

int Receiver::getError() {
        return receivedValues[1] - ((receivedValues[1] >> 6) * 64);
}

int Receiver::getTofFront() {
        return receivedValues[2];
}

int Receiver::getTofRight() {
        return receivedValues[3];
}

int Receiver::getTofLeft() {
        return receivedValues[4];
}

int Receiver::getLine() {
        return receivedValues[5];
}

int Receiver::dummy() {
        return receivedValues[6];
}

void Receiver::setZeroIMU() {
        OTHER_TEENSY.write(2);
}

void Receiver::resetBoden() {
        OTHER_TEENSY.write(1);
}

void Receiver::setGameMode() {
        OTHER_TEENSY.write(0);
}

void Receiver::setCallibIMU() {
        OTHER_TEENSY.write(3);
}

Transmitter::Transmitter(){
}

void Transmitter::init() {
        OTHER_TEENSY.begin(115200);
        transmitValues[0] = 255;
}

void Transmitter::transmit() {
        for (uint8_t i = 0; i < 8; i++) {
                OTHER_TEENSY.write(transmitValues[i]);
        }
        if (OTHER_TEENSY.available() > 0) {
                command = OTHER_TEENSY.read();
        }
}

int Transmitter::getCurrentCommand() {
        return command;
}

void Transmitter::setCompass(uint16_t value) {
        actualValues[0] = value;
        transmitValues[1] = actualValues[0] >> 2;
        transmitValues[2] = (actualValues[0] << 6) + actualValues[1];
}

void Transmitter::setError(uint8_t value) {
        actualValues[1] = value;
        transmitValues[2] = (actualValues[0] << 6) + actualValues[1];
}

void Transmitter::setTofFront(uint8_t value) {
        actualValues[2] = value;
        transmitValues[3] = value;
}

void Transmitter::setTofRight(uint8_t value) {
        actualValues[3] = value;
        transmitValues[4] = value;
}

void Transmitter::setTofLeft(uint8_t value) {
        actualValues[4] = value;
        transmitValues[5] = value;
}

void Transmitter::setLine(uint8_t value) {
        actualValues[5] = value;
        transmitValues[6] = value;
}

void Transmitter::dummy(uint8_t value) {
        actualValues[6] = value;
        transmitValues[7] = value;
}
