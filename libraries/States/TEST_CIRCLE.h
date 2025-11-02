#ifndef TEST_CIRCLE_H
# define TEST_CIRCLE_H

#include <Arduino.h>
#include "Movement.h"
#include "SensorData.h"
#include "State.h"
class State;

class TEST_CIRCLE : public State {
public:
TEST_CIRCLE();
void act(Machine *m) override;
void DEBUG() override;
protected:
void getNextState(Machine *m) override;
void step() override;
private:
int circleTime = 3000;
int circleSpeed = 255;
int dir = -180;
boolean done = false;
long lastTime = 0;
};

#endif
