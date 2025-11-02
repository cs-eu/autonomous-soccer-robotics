#ifndef STAND_STILL_H
# define STAND_STILL_H

#include <Arduino.h>
#include "Movement.h"
#include "SensorData.h"
#include "State.h"
class State;

class STAND_STILL : public State {
public:
STAND_STILL();
void act(Machine *m) override;
void DEBUG() override;
protected:
void getNextState(Machine *m) override;
void step() override;
};

#endif
