#ifndef IMU_h
#define IMU_h

#include "Arduino.h"
#include "i2c_t3.h"
#include "MPU9250.h"

class IMU
{
public:
IMU();
bool init();
uint16_t getAngle();
void setZero();
bool callibrate(int calibrationVals);
private:
bool getGyroValues();
void getAngularVelocity();
void calculateAngle();
bool IMUavailable;
uint16_t angle = 0;
float gyroXCalli = 0, gyroYCalli = 0, gyroZCalli = 0;
float gyroXPresent = 0, gyroYPresent = 0, gyroZPresent = 0;
float rotX, rotY, rotZ;
float angleX = 0, angleY = 0, angleZ = 0;
float SelfTest[6];
float gRes, aRes;
float passedTime;
long timePast = 0;
long timePresent = 0;
uint8_t Gscale = GFS_2000DPS, Ascale = AFS_2G, Mscale = MFS_16BITS, Mmode = M_100Hz, sampleRate = 0x04;
uint8_t address;
int16_t MPU9250Data[3];
int calIterations = 5000;
};

#endif
