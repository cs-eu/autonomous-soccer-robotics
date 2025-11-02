/*
* Sketch: Arduino2Arduino_example2_RemoteTemp_Slave
* By Martyn Currey
* 11.05.2016
* Written in Arduino IDE 1.6.3
*
* Send a temperature reading by Bluetooth
* Uses the following pins
*
* D8 - software serial RX
* D9 - software serial TX
* A0 - single wire temperature sensor
*
*
* AltSoftSerial uses D9 for TX and D8 for RX. While using AltSoftSerial D10 cannot be used for PWM.
* Remember to use a voltage divider on the Arduino TX pin / Bluetooth RX pin
* Download from https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
*/
#include <AltSoftSerial.h>
AltSoftSerial BTserial; 
 
// Set DEBUG to true to output debug information to the serial monitor
boolean DEBUG = true;
 
 
// Variables used for incoming data
const byte maxDataLength = 20;
char receivedChars[21] ;
boolean newData = false;
 
int serialdata;
 
 
void setup()  
{
    if (DEBUG)
    {
        // open serial communication for debugging
        Serial.begin(9600);
        Serial.println(__FILE__);
        Serial.println(" ");
    }
 
    //  open a software serial connection to the Bluetooth module.
    BTserial.begin(9600); 
    if (DEBUG)  {   Serial.println(F("AltSoftSerial started at 9600"));     }
    newData = false;
 
} // void setup()
 
 
 
 
void loop()  
{
    recvWithStartEndMarkers(); 
    if (newData)  {   processCommand();  }    
}
 
 
 
 
/*
****************************************
* Function getTemp
* read a analogue pin and converts the value to a temperature
* based on the adafruit thermistor guide https://learn.adafruit.com/thermistor/testing-a-thermistor 
* 
* passed:
*  
* global: 
*
* Returns:
*        float temp  
* Sets:
*
*/
int getSerialData()
{
    serialdata = serialdata + 1;
    return serialdata;
}
 
 
 
/*
****************************************
* Function processCommand
* parses data commands contained in receivedChars[]
* receivedChars[] has not been checked for errors
* 
* passed:
*  
* global: 
*       receivedChars[]
*       newData
*
* Returns:
*          
* Sets:
*       receivedChars[]
*       newData
*
*/
void processCommand()
{
 
     Serial.println(receivedChars);
 
     if (strcmp ("sendTemp",receivedChars) == 0) 
     { 
         int data = getSerialData();
         BTserial.print("<");  BTserial.print( data ); BTserial.print(">");
         if (DEBUG) { Serial.print("Value is ");   Serial.println(data); }
     }
 
     newData = false;
     receivedChars[0]='\0'; 
 
}
 
 
 
 
 
// function recvWithStartEndMarkers by Robin2 of the Arduino forums
// See  http://forum.arduino.cc/index.php?topic=288234.0
/*
****************************************
* Function recvWithStartEndMarkers
* reads serial data and returns the content between a start marker and an end marker.
* 
* passed:
*  
* global: 
*       receivedChars[]
*       newData
*
* Returns:
*          
* Sets:
*       newData
*       receivedChars
*
*/
void recvWithStartEndMarkers()
{
     static boolean recvInProgress = false;
     static byte ndx = 0;
     char startMarker = '<';
     char endMarker = '>';
     char rc;
 
     if (BTserial.available() > 0) 
     {
          rc = BTserial.read();
          if (recvInProgress == true) 
          {
               if (rc != endMarker) 
               {
                    receivedChars[ndx] = rc;
                    ndx++;
                    if (ndx > maxDataLength) { ndx = maxDataLength; }
               }
               else 
               {
                     receivedChars[ndx] = '\0'; // terminate the string
                     recvInProgress = false;
                     ndx = 0;
                     newData = true;
               }
          }
          else if (rc == startMarker) { recvInProgress = true; }
     }
 
}
