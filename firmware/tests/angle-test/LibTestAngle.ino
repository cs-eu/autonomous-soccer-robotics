#include <IMU.h>
IMU IMU;
void setup() {
  Serial.println(9600);
  IMU.init();
}

void loop() {
  Serial.println(IMU.getAngle());
  if (Serial.available() > 0) {
    IMU.callibrate(3000);
    IMU.setZero();
    Serial.println("Nullpunkt gesetzt");
    Serial.read();
  }
}
