#include <Wire.h>
int bigNum;
byte a,b;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 2);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    a = Wire.read(); // receive a byte as character
    b = Wire.read();
    bigNum = a;
    bigNum = (bigNum << 8) | b;
    Serial.println(bigNum);         // print the character
  }

}
