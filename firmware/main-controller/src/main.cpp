#include <Arduino.h>
#include "Motors.h"
#include "PIN_NAMES.h"
#include "SWITCH.h"
#include "Adafruit_NeoPixel.h"
#include "Movement.h"
#include "COM.h"
#include "State.h"
#include "GET_TO_BALL.h"
#include "GET_TO_MID.h"
#include "STARTUP.h"
#include "STAND_STILL.h"
#include "Machine.h"
#include <math.h>

// m381L431a3827PK2r916

#define NUMPIXELS_TOP 3
#define NUMPIXELS_BOT 32
Adafruit_NeoPixel strip_bot(NUMPIXELS_BOT, LED_PIN_BOT);
Adafruit_NeoPixel strip_top(NUMPIXELS_TOP, LED_PIN_TOP);

Machine m;

void setup() {
        Serial.begin(9600);
        strip_bot.begin();
        for (int o = 0; o < NUMPIXELS_BOT; o++) {
                strip_bot.setPixelColor(o, 255, 255, 255);
        }
        strip_bot.show();
        strip_top.begin();
        strip_top.show();
        Movement::init();
        SensorData::init();
        m.setCurrent(new STARTUP());
}

void loop() {
        SensorData::update();
        if (!SensorData::switchProgramOn) {
                m.setCurrent(new STARTUP());
        }
        if ((millis() % 7) == 0) {
                m.DEBUG();
                SensorData::DEBUG();
                // Serial.println(SensorData::GOAL_ENEMY.x - SensorData::RECEIVE.getTofFront());
                // Serial.println(SensorData::RECEIVE.getCompass());
                // Serial.println(60 - Movement::getCurrentFeedback(3));
                // Serial.println(SensorData::BALL_RADIUS);
        }
        if (SensorData::switch4) {
                strip_top.setPixelColor(1, 255, 255, 0);
        }
        else {
                strip_top.setPixelColor(1, 0, 0, 255);
        }
        if (SensorData::switch3) {
                strip_top.setPixelColor(2, 0, 255,  0);
        }
        else {
                strip_top.setPixelColor(2, 0, 0, 0);
        }
        if (!SensorData::calibrated) {
                strip_top.setPixelColor(0, 255, 255, 255);
        }
        else {
                // dd magenta
                // do none
                if (SensorData::switch2) {
                        strip_top.setPixelColor(0, 255, 0, 255);
                }
                else {
                        strip_top.setPixelColor(0, 0, 0, 0);
                }
        }
        if (SensorData::switchProgramOn) {
                for (int i = 0; i < 3; i++) {
                        strip_top.setPixelColor(i, 0, 0, 0);
                }
        }
        if ((millis() - SensorData::hascallibedtime) < 1000) {
                strip_top.setPixelColor(2, 255, 255, 255);
        }
        strip_top.show();
        m.act();
}
