#include <HC.h>
long test = 0;
long i = 1;
void setup() {
  Serial.begin(9600);
  HC::setEcho(2);
  HC::setTrigger(3);
}
void loop() {

  //test = test + HC::getDistance();   Serial.println(test / i);   i++;
  
  Serial.println(HC::getDistance());
  //Serial.println(HC::getStart());
  //Serial.println(digitalRead(2));
}
