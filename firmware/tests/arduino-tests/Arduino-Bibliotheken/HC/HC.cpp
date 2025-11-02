
#include "HC.h"

int HC::distance = 0;
int HC::trigger = 0;
int HC::echo = 0;
long HC::start = 0;

int HC::getDistance() {
	return distance;
}

int HC::getEcho() {
	return echo;
}

int HC::getTrigger() {
	return trigger;
}

int HC::getStart() {
	return start;
}

void HC::setEcho(int echoPin) {
	Serial.begin(9600);
	echo = echoPin;
	attachInterrupt(digitalPinToInterrupt(echo), change, FALLING);
	Serial.println("HEY!");
}

void HC::setTrigger(int triggerPin) {
	trigger = triggerPin;
	digitalWrite(trigger, LOW);
	digitalWrite(trigger, HIGH);
	digitalWrite(trigger, LOW);	
}

void HC::setDistance(int Distance) {
	distance = Distance;
}

void HC::setStart(int Start) {
	start = Start;
}

void HC::changeReal() {
	distance = (micros() - start) / 107; /// 5882;
	start = long(micros());
	analogWrite(trigger, 255);
	digitalWrite(trigger, LOW);
}

void HC::change() {
	changeReal();
}