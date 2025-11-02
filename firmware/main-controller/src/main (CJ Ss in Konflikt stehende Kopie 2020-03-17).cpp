#include "Arduino.h"
#include "PIN_NAMES.h"
//#include "MotorSpeeds.h"
#include "Motors.h"

int angle;
Motors motors;
long start;
long delta;

void setup() {
        Serial.begin(9600);
        motors.initMotors();
}
void loop() {
        if (millis() > start + 1000) {
                start = millis();
                if (angle == 0) {
                        angle = 90;
                }
                else if (angle == 90) {
                        angle = 0;
                }
        }
        uint8_t length = Serial.available();
        if (length > 0) {
                //Serial.print("Received message of length: ");
                //Serial.println(length);
                for (uint8_t i = 0; i < length; i++) {
                        int newAngle = Serial.read();
                        if (newAngle == 'w') {
                                angle = 0;
                        }
                        else if (newAngle == 'a') {
                                angle = 90;
                        }
                        else if (newAngle == 's') {
                                angle = -180;
                        }
                        else if (newAngle == 'd') {
                                angle = -90;
                        }
                }
        }
        if (angle == 0) {
                //motors.stop();
        }
        else {
                //motors.setSpeeds(angle, 0);
        }
        if (motors.getFeedback(3) < 200) {
                motors.setDribblerSpeed(255);
        }
        else {
                motors.setDribblerSpeed(0);
        }
        motors.writeSpeeds();
        //Serial.println(ACTIVE_BRAKE * motors.getFeedback(2));
        Serial.println(motors.getFeedback(3));
}
