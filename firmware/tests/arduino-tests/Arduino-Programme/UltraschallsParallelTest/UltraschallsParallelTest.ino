volatile long start = 0;
volatile double distance = 0;
void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(3), Measure, FALLING);
}

void loop() {
  updateU();
}

void Measure() {
  Serial.println((micros() - start) / 100.0);
  start = micros();
}

void updateU() {
  digitalWrite(2, HIGH);
  //delayMicroseconds(10);
  digitalWrite(2, LOW);
  //start = micros();
}

