#include "Arduino.h"
#include "TOF.h"
#include "VL53L1X.h"
#include "PIN_NAMES.h"
#include "i2c_t3.h"

TOF::TOF(){
}

void TOF::init()
{
        pinMode(XTOF_FRONT, OUTPUT);
        pinMode(XTOF_LEFT, OUTPUT);
        pinMode(XTOF_RIGHT, OUTPUT);

        pinMode(BODENADRESS1, OUTPUT);
        pinMode(BODENADRESS2, OUTPUT);
        pinMode(BODENADRESS3, OUTPUT);
        pinMode(BODENADRESS4, OUTPUT);
        pinMode(BODENADRESS5, OUTPUT);
        pinMode(BODENADRESS6, OUTPUT);
        pinMode(BODENADRESS7, OUTPUT);
        pinMode(BODENADRESS8, OUTPUT);

        digitalWrite(XTOF_FRONT, LOW);
        digitalWrite(XTOF_LEFT, LOW);
        digitalWrite(XTOF_RIGHT, LOW);

        digitalWrite(BODENADRESS1, HIGH);
        digitalWrite(BODENADRESS2, HIGH);
        digitalWrite(BODENADRESS3, HIGH);
        digitalWrite(BODENADRESS4, HIGH);
        digitalWrite(BODENADRESS5, HIGH);
        digitalWrite(BODENADRESS6, HIGH);
        digitalWrite(BODENADRESS7, HIGH);
        digitalWrite(BODENADRESS8, HIGH);

        Wire.begin(I2C_MASTER, 0x00, I2C_PINS_33_34, I2C_PULLUP_EXT, 400000);
        Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_37_38, I2C_PULLUP_EXT, 400000);
        Wire2.begin(I2C_MASTER, 0x00, I2C_PINS_3_4, I2C_PULLUP_EXT, 400000);
        Wire3.begin(I2C_MASTER, 0x00, I2C_PINS_56_57, I2C_PULLUP_EXT, 400000);
        Wire.resetBus();
        Wire.setDefaultTimeout(1000);
        Wire1.resetBus();
        Wire2.resetBus();
        Wire3.resetBus();

        TOF_BACK.init();
        TOF_BACK.setAddress(0x32);

        digitalWrite(XTOF_FRONT, HIGH);
        delay(15);
        TOF_FRONT.init();
        TOF_FRONT.setAddress(0x31);

        digitalWrite(XTOF_LEFT, HIGH);
        delay(15);
        TOF_LEFT.init();
        TOF_LEFT.setAddress(0x33);

        digitalWrite(XTOF_RIGHT, HIGH);
        delay(15);
        TOF_RIGHT.init();
        TOF_RIGHT.setAddress(0x34);


        TOF_BACK.setDistanceMode(VL53L1X::Medium);
        delay(2);
        TOF_BACK.setMeasurementTimingBudget(30000);
        delay(2);
        TOF_BACK.startContinuous(32);
        delay(2);
        TOF_BACK.setTimeout(100);
        delay(2);

        TOF_FRONT.setDistanceMode(VL53L1X::Medium);
        delay(2);
        TOF_FRONT.setMeasurementTimingBudget(30000);
        delay(2);
        TOF_FRONT.startContinuous(32);
        delay(2);
        TOF_FRONT.setTimeout(100);
        delay(2);

        TOF_LEFT.setDistanceMode(VL53L1X::Medium);
        delay(2);
        TOF_LEFT.setMeasurementTimingBudget(30000);
        delay(2);
        TOF_LEFT.startContinuous(32);
        delay(2);
        TOF_LEFT.setTimeout(100);
        delay(2);

        TOF_RIGHT.setDistanceMode(VL53L1X::Medium);
        delay(2);
        TOF_RIGHT.setMeasurementTimingBudget(30000);
        delay(2);
        TOF_RIGHT.startContinuous(32);
        delay(2);
        TOF_RIGHT.setTimeout(100);
        delay(2);
}

uint8_t TOF::readFront()
{
        distance16 = round(TOF_FRONT.read(false)/10);
        distance8 = min(distance16, 253);
        if (TOF_FRONT.timeoutOccurred()) {
                distance8 = 254;
        }
        if (distance8 == 0) {
                distance8 = 254;
        }
        return distance8;
        // return read(TOF_FRONT);
}

uint8_t TOF::readRight()
{
        distance16 = round(TOF_RIGHT.read(false)/10);
        distance8 = min(distance16, 253);
        if (TOF_RIGHT.timeoutOccurred()) {
                distance8 = 254;
        }
        if (distance8 == 0) {
                distance8 = 254;
        }
        return distance8;
        // return read(TOF_RIGHT);
}

uint8_t TOF::readBack()
{
        distance16 = round(TOF_BACK.read(false) / 10);
        distance8 = min(distance16, 253);
        if (TOF_BACK.timeoutOccurred()) {
                distance8 = 254;
        }
        if (distance8 == 0) {
                distance8 = 254;
        }
        return distance8;
        // return read(TOF_BACK);
}

uint8_t TOF::readLeft()
{
        distance16 = round(TOF_LEFT.read(false)/10);
        distance8 = min(distance16, 253);
        if (TOF_LEFT.timeoutOccurred()) {
                distance8 = 254;
        }
        if (distance8 == 0) {
                distance8 = 254;
        }
        return distance8;
        // return read(TOF_LEFT);
}

uint8_t TOF::read(VL53L1X sensor)
{
        distance16 = round(sensor.read(false)/10);
        distance8 = min(distance16, 253);
        if (sensor.timeoutOccurred()) {
                distance8 = 254;
        }
        if (distance8 == 0) {
                distance8 = 254;
        }
        return distance8;
}
