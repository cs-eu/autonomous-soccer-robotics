#ifndef PID_H
# define PID_H

#include <Arduino.h>

class PID {
public:
PID(float KpNew, float KiNew, float KdNew);
PID(float KpNew, float KiNew, float KdNew, int maxNew);
PID(float KpNew, float KiNew, float KdNew, int maxNew, int constNew);
void update(int newError);
void resetIntegral();
int getOutput();
private:
float present, integral, derivative, before;
float Kp, Ki, Kd;
long pastTime, lastChangeTime;
float lastChangeVal;
int max;
int constant;
};

#endif
