#include <i2c_t3.h>
#include <MPU9250.h>

float accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

float gyroXCalli = 0, gyroYCalli = 0, gyroZCalli = 0;
float gyroXPresent = 0, gyroYPresent = 0, gyroZPresent = 0;
float gyroXPast = 0, gyroYPast = 0, gyroZPast = 0;
float rotX, rotY, rotZ;

float angelX = 0, angelY = 0, angelZ = 0;

long timePast = 0;
long timePresent = 0;
float passedTime;

uint8_t Gscale = GFS_250DPS, Ascale = AFS_2G, Mscale = MFS_16BITS, Mmode = M_100Hz, sampleRate = 0x04;
int16_t MPU9250Data[7];
float SelfTest[6];
float gRes, aRes;

MPU9250 MPU9250(9);

void setup() {
  Serial.begin(115200);
  delay(10000);
  while(!Serial)  {}
  setUpMPU();
  callibrateGyroValues();
  timePresent = micros();
}

void loop() {
  readAndProcessGyroData();
  printData();
  delay(100);
}

void setUpMPU() {
  Wire2.begin(I2C_MASTER, 0x00, I2C_PINS_3_4, I2C_PULLUP_EXT, 400000);
  delay(1000);
  MPU9250.I2Cscan();
  Serial.println("MPU9250 9-axis motion sensor...");
  uint8_t c = MPU9250.getMPU9250ID();
  Serial.print("MPU9250 "); Serial.print("I AM "); Serial.print(c, HEX); Serial.print(" I should be "); Serial.println(0x71, HEX);
  delay(1000);

  if (c == 0x71 )   // WHO_AM_I should always be 0x71 for MPU9250, 0x73 for MPU9255
  {
          Serial.println("MPU9250 is online...");

          MPU9250.resetMPU9250(); // start by resetting MPU9250

          MPU9250.SelfTest(SelfTest); // Start by performing self test and reporting values
          Serial.print("x-axis self test: acceleration trim within : "); Serial.print(SelfTest[0],1); Serial.println("% of factory value");
          Serial.print("y-axis self test: acceleration trim within : "); Serial.print(SelfTest[1],1); Serial.println("% of factory value");
          Serial.print("z-axis self test: acceleration trim within : "); Serial.print(SelfTest[2],1); Serial.println("% of factory value");
          Serial.print("x-axis self test: gyration trim within : "); Serial.print(SelfTest[3],1); Serial.println("% of factory value");
          Serial.print("y-axis self test: gyration trim within : "); Serial.print(SelfTest[4],1); Serial.println("% of factory value");
          Serial.print("z-axis self test: gyration trim within : "); Serial.print(SelfTest[5],1); Serial.println("% of factory value");
          delay(1000);

          // get sensor resolutions, only need to do this once
          aRes = MPU9250.getAres(Ascale);
          gRes = MPU9250.getGres(Gscale);

          MPU9250.initMPU9250(Ascale, Gscale, sampleRate);
          Serial.println("MPU9250 initialized for active data mode...."); // Initialize device for active mode read of acclerometer, gyroscope, and temperature

  }
  else
  {
          Serial.print("Could not connect to MPU9250: 0x");
          Serial.println(c, HEX);
          while(1); // Loop forever if communication doesn't happen
  }
}

void callibrateGyroValues() {
    for (int i=0; i<5000; i++) {
      getGyroValues();
      gyroXCalli = gyroXCalli + gyroXPresent;
      gyroYCalli = gyroYCalli + gyroYPresent;
      gyroZCalli = gyroZCalli + gyroZPresent;
      Serial.print("X: ");
      Serial.println(gyroXPresent);
      Serial.print("Y: ");
      Serial.println(gyroYPresent);
      Serial.print("Z: ");
      Serial.println(gyroZPresent);
    }
    gyroXCalli = gyroXCalli/5000;
    gyroYCalli = gyroYCalli/5000;
    gyroZCalli = gyroZCalli/5000;
}

void readAndProcessGyroData() {
  gyroXPast = gyroXPresent;                                   // Assign Present gyro reaging to past gyro reading
  gyroYPast = gyroYPresent;                                   // Assign Present gyro reaging to past gyro reading
  gyroZPast = gyroZPresent;                                   // Assign Present gyro reaging to past gyro reading
  timePast = timePresent;                                     // Assign Present time to past time
  timePresent = micros();                                     // get the current time in milli seconds, it is the present time
  
  getGyroValues();                                            // get gyro readings
  getAngularVelocity();                                       // get angular velocity
  calculateAngle();                                           // calculate the angle  
}

void getGyroValues() {
  MPU9250.readMPU9250Data(MPU9250Data);                            
  gyroXPresent = (float)MPU9250Data[4]*gRes;
  gyroYPresent = (float)MPU9250Data[5]*gRes;
  gyroZPresent = (float)MPU9250Data[6]*gRes;
}

void getAngularVelocity() {
  rotX = gyroXPresent / 131.0;                                
  rotY = gyroYPresent / 131.0; 
  rotZ = gyroZPresent / 131.0;
}

void calculateAngle() {  
  // same equation can be written as 
  // angelZ = angelZ + ((timePresentZ - timePastZ)*(gyroZPresent + gyroZPast - 2*gyroZCalli)) / (2*1000*131);
  // 1/(1000*2*131) = 0.00000382
  // 1000 --> convert milli seconds into seconds
  // 2 --> comes when calculation area of trapezium
  // substacted the callibated result two times because there are two gyro readings
  /*angelX = angelX + ((timePresent - timePast)*(gyroXPresent + gyroXPast - 2*gyroXCalli)) * 0.00000382;
  angelY = angelY + ((timePresent - timePast)*(gyroYPresent + gyroYPast - 2*gyroYCalli)) * 0.00000382;
  angelZ = angelZ + ((timePresent - timePast)*(gyroZPresent + gyroZPast - 2*gyroZCalli)) * 0.00000382;*/
  passedTime = (float)(timePresent - timePast) / 1000000;
  if (abs(rotY) > 0.02)   {
    angelY = angelY + (passedTime*(gyroYPresent - gyroYCalli));
  }
  if (abs(rotX) > 0.02)   {
    angelX = angelX + (passedTime*(gyroXPresent - gyroXCalli));
  }
  if (abs(rotZ) > 0.02)   {
    angelZ = angelZ + (passedTime*(gyroZPresent - gyroZCalli));
  }
}

void printData() {
  Serial.println("Gyro (deg/sec)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.println(rotY); 
  Serial.print("Angle (deg)");
  Serial.print(" Z=");
  Serial.println(rotZ);

  Serial.println("Angular displacement wrt started position (deg)");
  Serial.print("angel of X axis=");
  Serial.print(angelX);
  Serial.print(" angel of Y axis=");
  Serial.print(angelY);
  Serial.print(" angel of Z axis=");
  Serial.println(angelZ);
}
