#include <Arduino.h>
#include "Motors.h"
#include "PIN_NAMES.h"
#include "PID.h"

Motors::Motors() {
}

void Motors::initMotors() {
        for (int i = 0; i < 12; i += 1) {
                pinMode(motorOutPins[i], OUTPUT);
        }
        for (int i = 2; i < 12; i += 3) {
                // analogWriteFrequency(motorOutPins[i], 29296.875);
                analogWriteFrequency(motorOutPins[i], 440);
                // analogWriteFrequency(motorOutPins[i], 4000);
        }
        analogWriteResolution(8);
}

void Motors::writeSpeeds() {
        for (int i = 0; i < 12; i += 3) {
                int motor = i / 3;
                digitalWrite(motorOutPins[i], dir1Motor[motor]);
                digitalWrite(motorOutPins[i + 1], dir2Motor[motor]);
                analogWrite(motorOutPins[i + 2], SPEED * pwmMotor[motor]);
        }
}

void Motors::setMotorSpeed(uint8_t motor, int speed) {
        // motorPID[motor].update(speed - motorFilter[motor].updateEstimate(((double) abs(speed) * 12 / 2) - ((double) getFeedback(2) * 6.4)));
        // int s = motorPID[motor].getOutput();
        if (speed > 0 && speed <= 255) {
                if (speed >= speedBefore[motor]) {
                        pwmMotor[motor] = speed;//speedConversionfromLower[speed];
                }
                else {
                        pwmMotor[motor] = speed;//speedConversionfromUpper[speed];
                }
                speedBefore[motor] = speed;
                dir1Motor[motor] = 0;
                dir2Motor[motor] = 1;
        }
        else if (speed < 0 && speed >= -255) {
                speed = -speed;
                if (speed > 0 && speed <= 255) {
                        if (speed >= speedBefore[motor]) {
                                pwmMotor[motor] = speed;//speedConversionfromLower[speed];
                        }
                        else {
                                pwmMotor[motor] = speed;//speedConversionfromUpper[speed];
                        }
                        speedBefore[motor] = speed;
                        dir1Motor[motor] = 1;
                        dir2Motor[motor] = 0;
                }
        }
        else if (speed == 0) {
                pwmMotor[motor] = 0;
                dir1Motor[motor] = 0;
                dir2Motor[motor] = 0;
        }
}

void Motors::setSpeeds(int angle, int bias, int speed) {
        setMotorSpeed(0, constrain(constrain(motor1Speeds[angle + 180] * speed / 255, -abs(speed), abs(speed)) + bias, -255, 255));
        setMotorSpeed(1, constrain(constrain(motor2Speeds[angle + 180] * speed / 255, -abs(speed), abs(speed)) + bias, -255, 255));
        setMotorSpeed(2, constrain(constrain(motor3Speeds[angle + 180] * speed / 255, -abs(speed), abs(speed)) + bias, -255, 255));
}

void Motors::setSpeeds(int angle, int bias) {
        setSpeeds(angle, bias, 255);
}

void Motors::setSpeedsBiasRear(int angle, int bias, int speed) {
        setMotorSpeed(0, constrain(constrain(motor1Speeds[angle + 180], -abs(speed), abs(speed)) + bias, -255, 255));
        setMotorSpeed(1, constrain(constrain(motor2Speeds[angle + 180], -abs(speed), abs(speed)), -255, 255));
        setMotorSpeed(2, constrain(constrain(motor3Speeds[angle + 180], -abs(speed), abs(speed)), -255, 255));
}

void Motors::setSpeedsBiasRear(int angle, int bias) {
        setSpeedsBiasRear(angle, bias, 255);
}

void Motors::setDribblerSpeed(int speed) {
        setMotorSpeed(3, speed);
}

int Motors::getFeedback(int motor) {
        // int erg = map(analogRead(motorFeedbackPins[motor]), 0, 1023, 0, 255);
        // motorFeedbacks[motor].lastValue = motorFeedbacks[motor].value;
        // motorFeedbacks[motor].value = erg;
        // return erg;
        int ret = analogRead(motorFeedbackPins[motor]);
        if (ret < 5) {
                ret = 0;
        }
        return ret;
}
void Motors::stop(int bias, int speed) {
        setMotorSpeed(0, constrain(bias, max(-speed, -255), min(speed, 255)));
        setMotorSpeed(1, constrain(bias, max(-speed, -255), min(speed, 255)));
        setMotorSpeed(2, constrain(bias, max(-speed, -255), min(speed, 255)));
}
void Motors::testSpeed(int speed) {
        testSetMotorSpeed(0, constrain(speed, -255, 255));
        testSetMotorSpeed(1, constrain(speed, -255, 255));
        testSetMotorSpeed(2, constrain(speed, -255, 255));
}
void Motors::testSetMotorSpeed(uint8_t motor, int speed) {
        if (speed > 0 && speed <= 255) {
                pwmMotor[motor] = speed;
                dir1Motor[motor] = 0;
                dir2Motor[motor] = 1;
        }
        else if (speed < 0 && speed >= -255) {
                speed = -speed;
                if (speed > 0 && speed <= 255) {
                        pwmMotor[motor] = speed;
                        dir1Motor[motor] = 1;
                        dir2Motor[motor] = 0;
                }
        }
        else if (speed == 0) {
                pwmMotor[motor] = 0;
                dir1Motor[motor] = 0;
                dir2Motor[motor] = 0;
        }
}
