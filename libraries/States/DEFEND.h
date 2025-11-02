#ifndef DEFEND_H
# define DEFEND_H

#include <Arduino.h>
#include "Movement.h"
#include "SensorData.h"
#include "State.h"
class State;

class DEFEND : public State {
public:
DEFEND();
void act(Machine *m) override;
void DEBUG() override;
protected:
void getNextState(Machine *m) override;
void step() override;
};

#endif
