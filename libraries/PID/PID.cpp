#include <Arduino.h>
#include "PID.h"
#include "PIN_NAMES.h"

PID::PID(float KpNew, float KiNew, float KdNew) {
        Kp = KpNew; Ki = KiNew; Kd = KdNew; max = INT16_MAX; constant = 0;
}

PID::PID(float KpNew, float KiNew, float KdNew, int maxNew) {
        Kp = KpNew; Ki = KiNew; Kd = KdNew; max = abs(maxNew); constant = 0;
}


PID::PID(float KpNew, float KiNew, float KdNew, int maxNew, int constNew) {
        Kp = KpNew; Ki = KiNew; Kd = KdNew; max = abs(maxNew); constant = constNew;
}

void PID::update(int newError) {
        present = (float) newError;
        before = present;
        if (pastTime != 0) {
                long delta = micros() - pastTime;
                if (lastChangeVal != present) {
                        derivative = (present - lastChangeVal) / (micros() - lastChangeTime) * 1000000;
                        lastChangeTime = micros();
                        lastChangeVal = present;
                }
                if (abs(getOutput()) < abs(max)) {
                        integral += present * delta / 1000000;
                }
                if (present == 0) {
                        integral = 0;
                }
        }
        pastTime = micros();
}

void PID::resetIntegral() {
        integral = 0;
}

int PID::getOutput() {
        if (present == 0) {
                return 0;
        }
        int sum = (int) ((Kp * present) + (Ki * integral) + (Kd * derivative));
        return constrain(sum + constant, -max, max);
}
