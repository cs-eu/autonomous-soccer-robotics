#include <Arduino.h>
#include <I2C_HELPER.h>
#include <i2c_t3.h>

I2C_HELPER::I2C_HELPER() {

}

/*I2C_HELPER::init() {
   Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
   Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_37_38, I2C_PULLUP_EXT, 400000);
   Wire2.begin(I2C_MASTER, 0x00, I2C_PINS_3_4, I2C_PULLUP_EXT, 400000);
   Wire3.begin(I2C_MASTER, 0x00, I2C_PINS_56_57, I2C_PULLUP_EXT, 400000);
   digitalWrite(BODENADRESS1, HIGH);
   digitalWrite(BODENADRESS2, HIGH);
   digitalWrite(BODENADRESS3, HIGH);
   digitalWrite(BODENADRESS4, HIGH);
   digitalWrite(BODENADRESS5, HIGH);
   digitalWrite(BODENADRESS6, HIGH);
   digitalWrite(BODENADRESS7, HIGH);
   digitalWrite(BODENADRESS8, HIGH);
   }*/

uint8_t I2C_HELPER::write(uint8_t whichWire, uint8_t address, uint16_t reg, uint8_t value) {
        if (whichWire == 0) {
                Wire.beginTransmission(address);
                Wire.write((reg >> 8) & 0xFF);
                Wire.write( reg       & 0xFF);
                Wire.write(value);
                return Wire.endTransmission();
        }
        else if (whichWire == 1) {
                Wire1.beginTransmission(address);
                Wire1.write((reg >> 8) & 0xFF);
                Wire1.write( reg       & 0xFF);
                Wire1.write(value);
                return Wire1.endTransmission();
        }
        else if (whichWire == 2) {
                Wire2.beginTransmission(address);
                Wire2.write((reg >> 8) & 0xFF);
                Wire2.write( reg       & 0xFF);
                Wire2.write(value);
                return Wire2.endTransmission();
        }
        else if (whichWire == 3) {
                Wire3.beginTransmission(address);
                Wire3.write((reg >> 8) & 0xFF);
                Wire3.write( reg       & 0xFF);
                Wire3.write(value);
                return Wire3.endTransmission();
        }
}

uint8_t I2C_HELPER::write16(uint8_t whichWire, uint8_t address, uint16_t reg, uint16_t value) {
        if (whichWire == 0) {
                Wire.beginTransmission(address);
                Wire.write((reg >> 8) & 0xFF);
                Wire.write( reg       & 0xFF);
                Wire.write((value >> 8) & 0xFF);
                Wire.write( value       & 0xFF);
                return Wire.endTransmission();
        }
        else if (whichWire == 1) {
                Wire1.beginTransmission(address);
                Wire1.write((reg >> 8) & 0xFF);
                Wire1.write( reg       & 0xFF);
                Wire1.write((value >> 8) & 0xFF);
                Wire1.write( value       & 0xFF);
                return Wire1.endTransmission();
        }
        else if (whichWire == 2) {
                Wire2.beginTransmission(address);
                Wire2.write((reg >> 8) & 0xFF);
                Wire2.write( reg       & 0xFF);
                Wire2.write((value >> 8) & 0xFF);
                Wire2.write( value       & 0xFF);
                return Wire2.endTransmission();
        }
        else if (whichWire == 3) {
                Wire3.beginTransmission(address);
                Wire3.write((reg >> 8) & 0xFF);
                Wire3.write( reg       & 0xFF);
                Wire3.write((value >> 8) & 0xFF);
                Wire3.write( value       & 0xFF);
                return Wire3.endTransmission();
        }
}

uint8_t I2C_HELPER::write32(uint8_t whichWire, uint8_t address, uint16_t reg, uint32_t value) {
        if (whichWire == 0) {
                Wire.beginTransmission(address);
                Wire.write((reg >> 8) & 0xFF);
                Wire.write( reg       & 0xFF);
                Wire.write((value >> 24) & 0xFF);
                Wire.write((value >> 16) & 0xFF);
                Wire.write((value >>  8) & 0xFF);
                Wire.write( value        & 0xFF);
                return Wire.endTransmission();
        }
        else if (whichWire == 1) {
                Wire1.beginTransmission(address);
                Wire1.write((reg >> 8) & 0xFF);
                Wire1.write( reg       & 0xFF);
                Wire1.write((value >> 24) & 0xFF);
                Wire1.write((value >> 16) & 0xFF);
                Wire1.write((value >>  8) & 0xFF);
                Wire1.write( value        & 0xFF);
                return Wire1.endTransmission();
        }
        else if (whichWire == 2) {
                Wire2.beginTransmission(address);
                Wire2.write((reg >> 8) & 0xFF);
                Wire2.write( reg       & 0xFF);
                Wire2.write((value >> 24) & 0xFF);
                Wire2.write((value >> 16) & 0xFF);
                Wire2.write((value >>  8) & 0xFF);
                Wire2.write( value        & 0xFF);
                return Wire2.endTransmission();
        }
        else if (whichWire == 3) {
                Wire3.beginTransmission(address);
                Wire3.write((reg >> 8) & 0xFF);
                Wire3.write( reg       & 0xFF);
                Wire3.write((value >> 24) & 0xFF);
                Wire3.write((value >> 16) & 0xFF);
                Wire3.write((value >>  8) & 0xFF);
                Wire3.write( value        & 0xFF);
                return Wire3.endTransmission();
        }
}

uint8_t I2C_HELPER::read8(uint8_t whichWire, uint8_t address, uint16_t reg) {
        uint8_t value;
        if (whichWire == 0) {
                Wire.beginTransmission(address);
                Wire.write((reg >> 8) & 0xFF);
                Wire.write( reg       & 0xFF);
                Wire.endTransmission();
                Wire.requestFrom(address, (uint8_t)1);
                value = Wire.read();
        }
        else if (whichWire == 1) {
                Wire1.beginTransmission(address);
                Wire1.write((reg >> 8) & 0xFF);
                Wire1.write( reg       & 0xFF);
                Wire1.endTransmission();
                Wire1.requestFrom(address, (uint8_t)1);
                value = Wire1.read();
        }
        else if (whichWire == 2) {
                Wire2.beginTransmission(address);
                Wire2.write((reg >> 8) & 0xFF);
                Wire2.write( reg       & 0xFF);
                Wire2.endTransmission();
                Wire2.requestFrom(address, (uint8_t)1);
                value = Wire2.read();
        }
        else if (whichWire == 3) {
                Wire3.beginTransmission(address);
                Wire3.write((reg >> 8) & 0xFF);
                Wire3.write( reg       & 0xFF);
                Wire3.endTransmission();
                Wire3.requestFrom(address, (uint8_t)1);
                value = Wire3.read();
        }
        return value;
}

uint16_t I2C_HELPER::read16(uint8_t whichWire, uint8_t address, uint16_t reg) {
        uint16_t value;
        if (whichWire == 0) {
                Wire.beginTransmission(address);
                Wire.write((reg >> 8) & 0xFF);
                Wire.write( reg       & 0xFF);
                Wire.endTransmission();
                Wire.requestFrom(address, (uint8_t)2);
                value  = (uint16_t)Wire.read() << 8;
                value |=           Wire.read();
        }
        else if (whichWire == 1) {
                Wire1.beginTransmission(address);
                Wire1.write((reg >> 8) & 0xFF);
                Wire1.write( reg       & 0xFF);
                Wire1.endTransmission();
                Wire1.requestFrom(address, (uint8_t)2);
                value  = (uint16_t)Wire1.read() << 8;
                value |=           Wire1.read();
        }
        else if (whichWire == 2) {
                Wire2.beginTransmission(address);
                Wire2.write((reg >> 8) & 0xFF);
                Wire2.write( reg       & 0xFF);
                Wire2.endTransmission();
                Wire2.requestFrom(address, (uint8_t)2);
                value  = (uint16_t)Wire2.read() << 8;
                value |=           Wire2.read();
        }
        else if (whichWire == 3) {
                Wire3.beginTransmission(address);
                Wire3.write((reg >> 8) & 0xFF);
                Wire3.write( reg       & 0xFF);
                Wire3.endTransmission();
                Wire3.requestFrom(address, (uint8_t)2);
                value  = (uint16_t)Wire3.read() << 8;
                value |=           Wire3.read();
        }
        return value;
}

uint32_t I2C_HELPER::read32(uint8_t whichWire, uint8_t address, uint16_t reg) {
        uint32_t value;
        if (whichWire == 0) {
                Wire.beginTransmission(address);
                Wire.write((reg >> 8) & 0xFF);
                Wire.write( reg       & 0xFF);
                Wire.endTransmission();
                Wire.requestFrom(address, (uint8_t)4);
                value  = (uint32_t)Wire.read() << 24;
                value |= (uint32_t)Wire.read() << 16;
                value |= (uint16_t)Wire.read() <<  8;
                value |=           Wire.read();
        }
        else if (whichWire == 1) {
                Wire1.beginTransmission(address);
                Wire1.write((reg >> 8) & 0xFF);
                Wire1.write( reg       & 0xFF);
                Wire1.endTransmission();
                Wire1.requestFrom(address, (uint8_t)4);
                value  = (uint32_t)Wire1.read() << 24;
                value |= (uint32_t)Wire1.read() << 16;
                value |= (uint16_t)Wire1.read() <<  8;
                value |=           Wire1.read();
        }
        else if (whichWire == 2) {
                Wire2.beginTransmission(address);
                Wire2.write((reg >> 8) & 0xFF);
                Wire2.write( reg       & 0xFF);
                Wire2.endTransmission();
                Wire2.requestFrom(address, (uint8_t)4);
                value  = (uint32_t)Wire2.read() << 24;
                value |= (uint32_t)Wire2.read() << 16;
                value |= (uint16_t)Wire2.read() <<  8;
                value |=           Wire2.read();
        }
        else if (whichWire == 3) {
                Wire3.beginTransmission(address);
                Wire3.write((reg >> 8) & 0xFF);
                Wire3.write( reg       & 0xFF);
                Wire3.endTransmission();
                Wire3.requestFrom(address, (uint8_t)4);
                value  = (uint32_t)Wire3.read() << 24;
                value |= (uint32_t)Wire3.read() << 16;
                value |= (uint16_t)Wire3.read() <<  8;
                value |=           Wire3.read();
        }
        return value;
}
