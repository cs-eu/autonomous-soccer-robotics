#ifndef GET_TO_MID_H
# define GET_TO_MID_H

#include <Arduino.h>
#include "Movement.h"
#include "SensorData.h"
#include "State.h"
class State;

class GET_TO_MID : public State {
public:
GET_TO_MID();
void act(Machine *m) override;
void DEBUG() override;
protected:
void getNextState(Machine *m) override;
void step() override;
private:
int dx;
int dy;
int midAngle;
int midRadius;
int midTime;
};

#endif
