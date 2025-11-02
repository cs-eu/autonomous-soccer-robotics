#ifndef GET_TO_BALL_H
# define GET_TO_BALL_H

#include <Arduino.h>
#include "Movement.h"
#include "SensorData.h"
#include "State.h"
class State;

class GET_TO_BALL : public State {
public:
GET_TO_BALL();
void act(Machine *m) override;
void DEBUG() override;
protected:
void getNextState(Machine *m) override;
void step() override;
};

#endif
