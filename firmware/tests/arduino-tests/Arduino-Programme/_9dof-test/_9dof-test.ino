#include <MPU9250.h>
MPU9250 IMU(Wire, 0x68);
boolean on = true;
long i = 0;
unsigned long periode = 100;
void setup() {
  IMU.begin();
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  //IMU.calibrateMag();
}
void loop() {
  i++;
  IMU.readSensor();
  Serial.println(IMU.getMagZ_uT());
  //Serial.println(dir);
  //Serial.println(IMU.getMagY_uT());
  //Serial.println(IMU.getMagZ_uT());
  if (i == 5) {
    i = 0;
    on = !on;
  }
  if (on) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, HIGH);
  }
  delay(100);
}
