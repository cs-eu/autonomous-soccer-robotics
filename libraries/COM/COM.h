#ifndef COM_H
# define COM_H

#include "Arduino.h"

#define OTHER_TEENSY Serial2
#define RASPI Serial1

class Vision {
public:
Vision();
void init();
void receive(int msg);
int getBallAngle();
int getBallRadius();
int getBlueAngle();
int getBlueRadius();
int getYellowAngle();
int getYellowRadius();
int getTrueAngle();
private:
int inByte;
int length;
int raspiIndexFinder;
int raspiIndex;
int BALL_ANGLE = 0;
int BALL_ANGLE_TRUE = 0;
int BALL_DISTANCE = -1;

int GOAL_BLUE_ANGLE = 0;
int GOAL_BLUE_DISTANCE = 0;
int GOAL_BLUE_DISTANCE_TRUE = 0;

int GOAL_YELLOW_ANGLE = 0;
int GOAL_YELLOW_DISTANCE = 0;
int GOAL_YELLOW_DISTANCE_TRUE = 0;
int angle, distance, angleY, distanceY, angleB, distanceB, angleT;
uint8_t receivedValues[9] = {0};
};

class Receiver {
public:
Receiver();
void init();
void receive();
void resetBoden();
void setGameMode();
void setZeroIMU();
void setCallibIMU();
int getCompass();
int getError();
int getTofFront();
int getLine();
int getTofLeft();
int getTofRight();
int dummy();
boolean isReady();
private:
int pos;
int inByte;
int length;
uint8_t receivedValues[6] = {0};
boolean ready;
};

class Transmitter {
public:
Transmitter();
void init();
void setCompass(uint16_t value);
void setError(uint8_t value);
void setTofFront(uint8_t value);
void setLine(uint8_t value);
void setTofLeft(uint8_t value);
void setTofRight(uint8_t value);
void dummy(uint8_t value);
void transmit();
int getCurrentCommand();
private:
uint8_t command;
uint16_t actualValues[7] = {0};
uint8_t transmitValues[8] = {0};
};

#endif
