#ifndef MOVEMENT_H
# define MOVEMENT_H

#include <Arduino.h>
#include "Kicker.h"
#include "Motors.h"
#include "PID.h"

namespace Movement {
void move(int compass);
void init();
void moveTo(int angle, int radius);
void moveToCart(double dx, double dy);
void moveToCart(double dx, double dy, int speed);
int getLine();
void setAngle(int newAngle);
void setStop(boolean newStop);
void setSpeed(int newSpeed);
void setFront(boolean newVal);
void setBack(boolean newVal);
void setLeft(boolean newVal);
void setRight(boolean newVal);
void checkBoden();
int getCurrentFeedback(int motor);
void setDribbler(int newVal);
void kick();
extern int firstLine;
extern int bodens[16];
extern int bodenAngles[16];
};

#endif
