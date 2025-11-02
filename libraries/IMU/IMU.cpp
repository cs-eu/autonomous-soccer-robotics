#include "Arduino.h"
#include "IMU.h"
#include "i2c_t3.h"
#include "MPU9250.h"

MPU9250 MPU9250(9);

IMU::IMU()
{

}

bool IMU::init()
{
								IMUavailable = MPU9250.I2Cscan();
								if (!IMUavailable) {
																return false;
								}
								address = MPU9250.getMPU9250ID();
								delay(100);

								if (address == 0x71)
								{
																MPU9250.resetMPU9250(); // start by resetting MPU9250

																// get sensor resolutions, only need to do this once
																aRes = MPU9250.getAres(Ascale);
																gRes = MPU9250.getGres(Gscale);

																MPU9250.initMPU9250(Ascale, Gscale, sampleRate);
								}
								else {
																return false;
								}
								callibrate(calIterations);
								timePresent = micros();
								return true;
}

uint16_t IMU::getAngle() {
								timePast = timePresent;
								timePresent = micros();
								IMUavailable = getGyroValues();
								getAngularVelocity();
								calculateAngle();
								if (angleY >= 360) {
																angleY = angleY - 360;
								}
								else if (angleY < 0) {
																angleY = angleY + 360;
								}
								angle = floor(angleY);
								if (!IMUavailable) {
																angle = 361;
								}
								return angle;
}

void IMU::setZero() {
								angleY = 0;
}

bool IMU::callibrate(int calibrationVals) {
								gyroXCalli = 0;
								gyroYCalli = 0;
								gyroZCalli = 0;
								for (int i = 0; i < calibrationVals; i++) {
																IMUavailable = getGyroValues();
																gyroXCalli = gyroXCalli + gyroXPresent;
																gyroYCalli = gyroYCalli + gyroYPresent;
																gyroZCalli = gyroZCalli + gyroZPresent;
								}
								gyroXCalli = gyroXCalli / calibrationVals;
								gyroYCalli = gyroYCalli / calibrationVals;
								gyroZCalli = gyroZCalli / calibrationVals;
								return IMUavailable;
}

bool IMU::getGyroValues() {
								MPU9250.readGyroData(MPU9250Data);
								gyroXPresent = (float) MPU9250Data[0] * gRes;
								gyroYPresent = (float) MPU9250Data[1] * gRes;
								gyroZPresent = (float) MPU9250Data[2] * gRes;
								return IMUavailable;
}

void IMU::getAngularVelocity() {
								rotX = gyroXPresent / 131.0;
								rotY = gyroYPresent / 131.0;
								rotZ = gyroZPresent / 131.0;
}

void IMU::calculateAngle() {
								passedTime = (float) (timePresent - timePast) / 1000000;
								if (abs(rotY) > 0.02)   {
																angleY += (passedTime * (gyroYPresent - gyroYCalli));
								}
								/*if (abs(rotX) > 0.02)   {
								   angleX = angleX + (passedTime*(gyroXPresent - gyroXCalli));
								   }
								   if (abs(rotZ) > 0.02)   {
								   angleZ = angleZ + (passedTime*(gyroZPresent - gyroZCalli));
								   }*/
}
