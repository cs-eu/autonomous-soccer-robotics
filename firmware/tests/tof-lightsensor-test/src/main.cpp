#include <Arduino.h>
#include <i2c_t3.h>
#include <TSL2584TSV.h>
#include <VL53L1X.h>
#include <PIN_NAMES.h>

#define HIGH_ADRESS (0x49)

VL53L1X TOF1;
VL53L1X TOF2;
VL53L1X TOF3;
VL53L1X TOF4;
int distance;

TSL2584TSV b0 = TSL2584TSV(HIGH_ADRESS, 0);
TSL2584TSV b1 = TSL2584TSV(HIGH_ADRESS, 1);
TSL2584TSV b2 = TSL2584TSV(HIGH_ADRESS, 2);
TSL2584TSV b3 = TSL2584TSV(HIGH_ADRESS, 3);

void setup() {
        pinMode(XTOF_FRONT, OUTPUT);
        pinMode(XTOF_BACK, OUTPUT);
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
        digitalWrite(XTOF_BACK, LOW);
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

        Serial.begin(9600);
        while (!Serial) {}
        Serial.println("Program started!");

        Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
        Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_37_38, I2C_PULLUP_EXT, 400000);
        Wire2.begin(I2C_MASTER, 0x00, I2C_PINS_3_4, I2C_PULLUP_EXT, 400000);
        Wire3.begin(I2C_MASTER, 0x00, I2C_PINS_56_57, I2C_PULLUP_EXT, 400000);

        digitalWrite(XTOF_FRONT, HIGH);
        delay(150);
        TOF1.init();
        TOF1.setAddress(0x31);

        digitalWrite(XTOF_BACK, HIGH);
        delay(150);
        TOF2.init();
        TOF2.setAddress(0x32);

        digitalWrite(XTOF_LEFT, HIGH);
        delay(150);
        TOF3.init();
        TOF3.setAddress(0x33);

        digitalWrite(XTOF_RIGHT, HIGH);
        delay(150);
        TOF4.init();
        TOF4.setAddress(0x34);


        TOF1.setDistanceMode(VL53L1X::Short);
        TOF1.setMeasurementTimingBudget(30000);
        TOF1.startContinuous(30);
        TOF1.setTimeout(100);

        TOF2.setDistanceMode(VL53L1X::Short);
        TOF2.setMeasurementTimingBudget(30000);
        TOF2.startContinuous(30);
        TOF2.setTimeout(100);

        TOF3.setDistanceMode(VL53L1X::Short);
        TOF3.setMeasurementTimingBudget(30000);
        TOF3.startContinuous(30);
        TOF3.setTimeout(100);

        TOF4.setDistanceMode(VL53L1X::Short);
        TOF4.setMeasurementTimingBudget(30000);
        TOF4.startContinuous(30);
        TOF4.setTimeout(100);

        digitalWrite(BODENADRESS1, LOW); //b3 = 256
        digitalWrite(BODENADRESS2, LOW); //b2 = 256
        digitalWrite(BODENADRESS3, HIGH); //b0 & b2 = 256
        digitalWrite(BODENADRESS4, LOW);
        digitalWrite(BODENADRESS5, LOW);
        digitalWrite(BODENADRESS6, LOW);
        digitalWrite(BODENADRESS7, LOW);
        digitalWrite(BODENADRESS8, LOW);

        b0.begin();
        b1.begin();
        b2.begin();
        b3.begin();
}

void loop() {
        Serial.print("B0: ");
        Serial.print(b0.getLuminosity(0));
        Serial.println();

        Serial.print("B1: ");
        Serial.print(b1.getLuminosity(0));
        Serial.println();

        Serial.print("B2: ");
        Serial.print(b2.getLuminosity(0));
        Serial.println();

        Serial.print("B3: ");
        Serial.print(b3.getLuminosity(0));
        Serial.println();

        Serial.print("Sensor Rechts:  ");
        distance = round(TOF1.read()/10);
        Serial.print(distance);
        if (TOF1.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
        Serial.println();

        Serial.print("Sensor Links:  ");
        Serial.print(TOF2.read());
        if (TOF2.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
        Serial.println();

        Serial.print("Sensor Vorne:  ");
        Serial.print(TOF3.read());
        if (TOF3.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
        Serial.println();

        Serial.print("Sensor Hinten:  ");
        Serial.print(TOF4.read());
        if (TOF4.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
        Serial.println();
}
