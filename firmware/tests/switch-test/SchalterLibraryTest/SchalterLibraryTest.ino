#include <SWITCH.h>

SWITCH sw;
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(sw.switchProgramOff());
  Serial.print(", ");
  Serial.println(sw.switchProgramOn());
  Serial.print(sw.switch1Off());
  Serial.print(", ");
  Serial.println(sw.switch1On());
  Serial.print(sw.switch2Off());
  Serial.print(", ");
  Serial.println(sw.switch2On());
  Serial.print(sw.switch3Off());
  Serial.print(", ");
  Serial.println(sw.switch3On());
  Serial.print(sw.switch4Off());
  Serial.print(", ");
  Serial.println(sw.switch4On());
  Serial.println();
  delay(500);
}
