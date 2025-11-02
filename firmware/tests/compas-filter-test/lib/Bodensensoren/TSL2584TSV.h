#ifndef _TSL2584TSV_H_
#define _TSL2584TSV_H_

#include <Arduino.h>
#include <I2C_HELPER.h>
#include <i2c_t3.h>

#define TSL2584TSV_VISIBLE 2                   // channel 0 - channel 1
#define TSL2584TSV_INFRARED 1                  // channel 1
#define TSL2584TSV_FULLSPECTRUM 0              // channel 0

// 3 i2c address options!
#define TSL2584TSV_ADDR_LOW  0x29
#define TSL2584TSV_ADDR_FLOAT 0x39
#define TSL2584TSV_ADDR_HIGH 0x49


#define TSL2584TSV_COMMAND_BIT       (0x80)    // Must be 1
#define TSL2584TSV_AUTO_INCREMENT    (0x01)


#define TSL2584TSV_CONTROL_POWERON_ADCENABLE   (0x03)
#define TSL2584TSV_CONTROL_POWERON_ADCDISABLE  (0x01)

enum
{
  TSL2584TSV_REGISTER_CONTROL          = 0x00,
  TSL2584TSV_REGISTER_TIMING           = 0x01,
  TSL2584TSV_REGISTER_INTERRUPT        = 0x02,
  TSL2584TSV_REGISTER_THRESHHOLDL_LOW  = 0x03,
  TSL2584TSV_REGISTER_THRESHHOLDL_HIGH = 0x04,
  TSL2584TSV_REGISTER_THRESHHOLDH_LOW  = 0x05,
  TSL2584TSV_REGISTER_THRESHHOLDH_HIGH = 0x06,
  TSL2584TSV_REGISTER_ANALOG           = 0x07,
  TSL2584TSV_REGISTER_ID               = 0x12,
  TSL2584TSV_REGISTER_DATA0LOW         = 0x14,
  TSL2584TSV_REGISTER_DATA0HIGH        = 0x15,
  TSL2584TSV_REGISTER_DATA1LOW         = 0x16,
  TSL2584TSV_REGISTER_DATA1HIGH        = 0x17,
  TSL2584TSV_REGISTER_TIMERLOW         = 0x18,
  TSL2584TSV_REGISTER_TIMERHIGH        = 0x19,
  TSL2584TSV_REGISTER_ID2              = 0x1E,
};

typedef enum
{
  TSL2584TSV_INTEGRATIONTIME_2_7MS      = 0xFF,    // 2.7ms
  TSL2584TSV_INTEGRATIONTIME_5_4MS      = 0xFE,    // 5.4ms
  TSL2584TSV_INTEGRATIONTIME_8_1MS      = 0xFD     // 8.1ms
}
TSL2584TSVIntegrationTime_t;

typedef enum
{
  TSL2584TSV_GAIN_8X                   = 0x01,    // 8x gain
  TSL2584TSV_GAIN_16X                  = 0x02,    // 16x gain
  TSL2584TSV_GAIN_111X                 = 0x03     // 111x gain
}
TSL2584TSVGain_t;


class TSL2584TSV {
 public:
  TSL2584TSV(uint8_t addr, int _whichWire);
  boolean begin(void);
  void enable(void);
  void disable(void);
  void setTiming(TSL2584TSVIntegrationTime_t integration);
  void setGain(TSL2584TSVGain_t gain);
  uint16_t getLuminosity (uint8_t channel);

  uint16_t read8(uint8_t adress, uint8_t reg);
  uint16_t read16(uint8_t adress, uint8_t reg);
  void write8 (uint8_t adress, uint8_t reg, uint8_t value);

 private:
  int8_t _addr;
  TSL2584TSVIntegrationTime_t _integration;
  TSL2584TSVGain_t _gain;

  boolean _initialized;
  int _whichWire;
};
#endif
