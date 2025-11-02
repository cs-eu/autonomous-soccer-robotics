void setup() {
 Serial.begin(9600);
}

void loop() {
  
}

void serialEvent() {
  if (Serial.read() > 10) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
  }
}

