/*
 * How to configure and pair two HC-05 Bluetooth Modules
 * by Dejan Nedelkovski, www.HowToMechatronics.com
 * 
 *                 == MASTER CODE ==
 */
int value;
void setup() {
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}
void loop() {
  if(value<256) {
    value++;
  }
  else  {
    value=0;
  }
 Serial.write(value); // Sends potValue to servo motor
 delay(10);
}
