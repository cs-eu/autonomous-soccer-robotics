#if defined ( ESP8266 )
  #include <pgmspace.h>
#else
  #include <avr/pgmspace.h>
  #include <util/delay.h>
#endif
#include <stdlib.h>
#include "TSL2584TSV.h"
#include <I2C_HELPER.h>
#include <i2c_t3.h>

TSL2584TSV::TSL2584TSV(uint8_t addr, int whichWire) {
        _addr = addr;
        _initialized = false;
        _integration = TSL2584TSV_INTEGRATIONTIME_2_7MS;
        _gain = TSL2584TSV_GAIN_8X;
        _whichWire = whichWire;
}

boolean TSL2584TSV::begin(void) {
        _initialized = true;
        disable();
        setGain(_gain);
        setTiming(_integration);
        delay(2);
        enable();
        return true;
}

void TSL2584TSV::enable(void) {
        if (!_initialized) begin();
        write8(_addr, TSL2584TSV_COMMAND_BIT | TSL2584TSV_REGISTER_CONTROL, TSL2584TSV_CONTROL_POWERON_ADCENABLE);
}

void TSL2584TSV::disable(void) {
        if (!_initialized) begin();
        write8(_addr, TSL2584TSV_COMMAND_BIT | TSL2584TSV_REGISTER_CONTROL, TSL2584TSV_CONTROL_POWERON_ADCDISABLE);
}

void TSL2584TSV::setGain(TSL2584TSVGain_t gain) {
        _gain = gain;
        write8(_addr, TSL2584TSV_COMMAND_BIT | TSL2584TSV_REGISTER_ANALOG, _gain);
}

void TSL2584TSV::setTiming(TSL2584TSVIntegrationTime_t integration) {
        _integration = integration;
        write8(_addr, TSL2584TSV_COMMAND_BIT | TSL2584TSV_REGISTER_TIMING, _integration);
}

uint16_t TSL2584TSV::getLuminosity (uint8_t channel) {
        uint16_t x;
        if (channel == 0) {
                x = read16(_addr, TSL2584TSV_COMMAND_BIT | TSL2584TSV_REGISTER_DATA0LOW);
        }
        else if (channel == 1) {
                x = read16(_addr, TSL2584TSV_COMMAND_BIT | TSL2584TSV_REGISTER_DATA1LOW);
        }
        return x;
}

uint16_t TSL2584TSV::read8(uint8_t adress, uint8_t reg) {
        uint16_t value;
        if (_whichWire == 0) {
                Wire.beginTransmission(adress);
                Wire.write(reg);
                Wire.endTransmission();
                Wire.requestFrom(adress, (uint8_t)1);
                value = Wire.read();
        }
        else if (_whichWire == 1) {
                Wire1.beginTransmission(adress);
                Wire1.write(reg);
                Wire1.endTransmission();
                Wire1.requestFrom(adress, (uint8_t)1);
                value = Wire1.read();
        }
        else if (_whichWire == 2) {
                Wire2.beginTransmission(adress);
                Wire2.write(reg);
                Wire2.endTransmission();
                Wire2.requestFrom(adress, (uint8_t)1);
                value = Wire2.read();
        }
        else if (_whichWire == 3) {
                Wire3.beginTransmission(adress);
                Wire3.write(reg);
                Wire3.endTransmission();
                Wire3.requestFrom(adress, (uint8_t)1);
                value = Wire3.read();
        }
        return value;
}

uint16_t TSL2584TSV::read16(uint8_t adress, uint8_t reg)
{
        uint16_t value;
        if (_whichWire == 0) {
                Wire.beginTransmission(adress);
                Wire.write(reg);
                Wire.endTransmission();
                Wire.requestFrom(adress, (uint8_t)2);
                value  = (uint16_t)Wire.read() << 8;
                value |=           Wire.read();
        }
        else if (_whichWire == 1) {
                Wire1.beginTransmission(adress);
                Wire1.write(reg);
                Wire1.endTransmission();
                Wire1.requestFrom(adress, (uint8_t)2);
                value  = (uint16_t)Wire1.read() << 8;
                value |=           Wire1.read();
        }
        else if (_whichWire == 2) {
                Wire2.beginTransmission(adress);
                Wire2.write(reg);
                Wire2.endTransmission();
                Wire2.requestFrom(adress, (uint8_t)2);
                value  = (uint16_t)Wire2.read() << 8;
                value |=           Wire2.read();
        }
        else if (_whichWire == 3) {
                Wire3.beginTransmission(adress);
                Wire3.write(reg);
                Wire3.endTransmission();
                Wire3.requestFrom(adress, (uint8_t)2);
                value  = (uint16_t)Wire3.read() << 8;
                value |=           Wire3.read();
        }
        return value;
}

void TSL2584TSV::write8 (uint8_t adress, uint8_t reg, uint8_t value)
{
        if (_whichWire == 0) {
                Wire.beginTransmission(adress);
                Wire.write(reg);
                Wire.write(value);
                Wire.endTransmission();
        }
        else if (_whichWire == 1) {
                Wire1.beginTransmission(adress);
                Wire1.write(reg);
                Wire1.write(value);
                Wire1.endTransmission();
        }
        else if (_whichWire == 2) {
                Wire2.beginTransmission(adress);
                Wire2.write(reg);
                Wire2.write(value);
                Wire2.endTransmission();
        }
        else if (_whichWire == 3) {
                Wire3.beginTransmission(adress);
                Wire3.write(reg);
                Wire3.write(value);
                Wire3.endTransmission();
        }
}
