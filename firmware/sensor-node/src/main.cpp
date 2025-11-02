// Sensorik Hauptprogramm
#include <Arduino.h>
#include "TOF.h"
#include "IMU.h"
#include "COM.h"
#include "Bodensensoren.h"
#include "i2c_t3.h"
#include "PIN_NAMES.h"
#include "VL53L1X.h"

IMU IMU;
TOF TOF;
Bodensensoren BODEN;
Transmitter TRANSMIT;
uint16_t maxValues[32] = {0};
uint16_t minValues[32] = {10000};

void calibBoden() {
        for (int i = 0; i < 32; i++) {
                maxValues[i] = max(maxValues[i], BODEN.getBoden(i).getLuminosity(0));
                minValues[i] = min(minValues[i], BODEN.getBoden(i).getLuminosity(0));
                BODEN.calibValues[i] = minValues[i] + ((maxValues[i] - minValues[i]) / 2);
                Serial.println(BODEN.getBoden(i).getThreshold());
        }
        BODEN.setThresholds();
}

void setup() {
        delay(100);
        Serial.begin(9600);
        TRANSMIT.init();
        TOF.init();
        BODEN.initSecond();
        IMU.init();
        TRANSMIT.setCompass(362);
        TRANSMIT.transmit();
        TRANSMIT.setError(5);
        TRANSMIT.setTofRight(20);
        TRANSMIT.setTofFront(20);
        TRANSMIT.setTofLeft(20);
        TRANSMIT.setLine(20);
        delay(2);
        TOF.readRight();
        TOF.readFront();
        TOF.readLeft();
        TOF.readBack();
        delay(2);
}
void scan();
void loop() {
        int a = IMU.getAngle();
        int line = BODEN.resetInterrupt();
        TRANSMIT.setCompass(a);
        TRANSMIT.setError(5);
        TRANSMIT.setTofFront(TOF.readBack());
        TRANSMIT.setTofRight(TOF.readRight());
        TRANSMIT.setTofLeft(TOF.readLeft());
        if (TRANSMIT.getCurrentCommand() == 1) {
                calibBoden();
        }
        else if (TRANSMIT.getCurrentCommand() == 2) {
                IMU.setZero();
        }
        // else if (TRANSMIT.getCurrentCommand() == 3) {
        //         IMU.callibrate(5000);
        // }
        TRANSMIT.setLine(line);
        TRANSMIT.transmit();
        // Serial.println(a);
        Serial.println(millis());
}

void scan() {
        byte error, address;
        int nDevices;

        Serial.println("Scanning...");

        nDevices = 0;
        for(address = 1; address < 127; address++ )
        {
                // The i2c_scanner uses the return value of
                // the Write.endTransmisstion to see if
                // a device did acknowledge to the address.
                Wire.beginTransmission(address);
                error = Wire.endTransmission();

                Serial.print("Got Error: ");
                Serial.print(error);
                Serial.print(" at address 0x");
                if (address<16)
                        Serial.print("0");
                Serial.print(address,HEX);
                Serial.println("  !");

                if (error == 0)
                {
                        Serial.print("I2C device found at address 0x");
                        if (address<16)
                                Serial.print("0");
                        Serial.print(address,HEX);
                        Serial.println("  !");

                        nDevices++;
                }
                else if (error==4)
                {
                        Serial.print("Unknown error at address 0x");
                        if (address<16)
                                Serial.print("0");
                        Serial.println(address,HEX);
                }
        }
        if (nDevices == 0)
                Serial.println("No I2C devices found\n");
        else
                Serial.println("done\n");
}
