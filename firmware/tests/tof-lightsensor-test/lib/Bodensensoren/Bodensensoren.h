#ifndef _TSL2584TSV_H_
#define _TSL2584TSV_H_

#include <Arduino.h>
#include <I2C_HELPER.h>
#include <i2c_t3.h>
#include <TSL2584TSV.h>



class BODENSENSOREN {
 public:
  BODENSENSOREN();
  int getValue(int number);
  void setGain(int number);
  void setTiming(int number);
 private:
  TSL2584TSV getSensor(int number);
};
#endif
