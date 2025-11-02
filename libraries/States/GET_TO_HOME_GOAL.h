#ifndef GET_TO_HOME_GOAL_H
# define GET_TO_HOME_GOAL_H

#include <Arduino.h>
#include "Movement.h"
#include "SensorData.h"
#include "State.h"
class State;

class GET_TO_HOME_GOAL: public State {
public:
        GET_TO_HOME_GOAL();
        void act(Machine *m) override;
        void DEBUG() override;
protected:
        void getNextState(Machine *m) override;
        void step() override;
};

#endif
