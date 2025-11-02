#include <VL53L1X.h>
#include <i2c_t3.h>

#define XToF1 31
#define XToF2 32
#define XToF3 33
#define XToF4 34

VL53L1X TOF1;
VL53L1X TOF2;
VL53L1X TOF3;
VL53L1X TOF4;

void setup()
{
  pinMode(XToF1, OUTPUT);
  pinMode(XToF2, OUTPUT);
  pinMode(XToF3, OUTPUT);
  pinMode(XToF4, OUTPUT);
  
  digitalWrite(XToF1, LOW);
  digitalWrite(XToF2, LOW);
  digitalWrite(XToF3, LOW);
  digitalWrite(XToF4, LOW);

  
  Serial.begin(115200);
  Wire2.begin();
  Wire2.setClock(400000);

  //TOF.setTimeout(500);
  /*if (!TOF.init())
  {
    Serial.println("Failed to detect and initialize TOF!");
    while (1);
  }*/

  digitalWrite(XToF1, HIGH);
  delay(150);
  TOF1.init();
  TOF1.setAddress(0x31);

  digitalWrite(XToF2, HIGH);
  delay(150);
  TOF2.init();
  TOF2.setAddress(0x32);

  digitalWrite(XToF3, HIGH);
  delay(150);
  TOF3.init();
  TOF3.setAddress(0x33);

  digitalWrite(XToF4, HIGH);
  delay(150);
  TOF4.init();
  TOF4.setAddress(0x34);
  
  
  TOF1.setDistanceMode(VL53L1X::Long);
  TOF1.setMeasurementTimingBudget(50000);
  TOF1.startContinuous(50);
  TOF1.setTimeout(100);

  TOF2.setDistanceMode(VL53L1X::Long);
  TOF2.setMeasurementTimingBudget(50000);
  TOF2.startContinuous(50);
  TOF2.setTimeout(100);

  TOF3.setDistanceMode(VL53L1X::Long);
  TOF3.setMeasurementTimingBudget(50000);
  TOF3.startContinuous(50);
  TOF3.setTimeout(100);

  TOF4.setDistanceMode(VL53L1X::Long);
  TOF4.setMeasurementTimingBudget(50000);
  TOF4.startContinuous(50);
  TOF4.setTimeout(100);
}

void loop()
{
  Serial.print("Sensor Rechts:  ");
  Serial.print(TOF1.read());
  if (TOF1.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();

  Serial.print("Sensor Links:  ");
  Serial.print(TOF2.read());
  if (TOF2.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();

  Serial.print("Sensor Vorne:  ");
  Serial.print(TOF3.read());
  if (TOF3.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();

  Serial.print("Sensor Hinten:  ");
  Serial.print(TOF4.read());
  if (TOF4.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();
  
  delay(1000);
}
