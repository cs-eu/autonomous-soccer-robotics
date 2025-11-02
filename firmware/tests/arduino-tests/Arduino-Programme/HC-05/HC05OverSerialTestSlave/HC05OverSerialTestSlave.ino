/*
 * How to configure and pair two HC-05 Bluetooth Modules
 * by Dejan Nedelkovski, www.HowToMechatronics.com
 * 
 *                 == SLAVE CODE ==
 */
 
int state;
void setup() {
  Serial.begin(38400);
  Serial3.begin(38400); // Default communication rate of the Bluetooth module
}
void loop() {
 if(Serial3.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial3.read(); // Reads the data from the serial port
 }
 // Controlling the servo motor
 Serial.println(state);
 delay(10);
}
