#ifndef I2C_HELPER_H
#define I2C_HELPER_H

#include <Arduino.h>
#include <i2c_t3.h>

class I2C_HELPER {
public:
I2C_HELPER();
static uint8_t write(uint8_t whichWire, uint8_t address, uint16_t reg, uint8_t value);
static uint8_t write16(uint8_t whichWire, uint8_t address, uint16_t reg, uint16_t value);
static uint8_t write32(uint8_t whichWire, uint8_t address, uint16_t reg, uint32_t value);
static uint8_t read8(uint8_t whichWire, uint8_t address, uint16_t reg);
static uint16_t read16(uint8_t whichWire, uint8_t address, uint16_t reg);
static uint32_t read32(uint8_t whichWire, uint8_t address, uint16_t reg);
//void init();
private:
//checkConnection();
};
#endif
