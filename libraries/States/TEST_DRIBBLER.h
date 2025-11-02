#ifndef TEST_DRIBBLER_H
# define TEST_DRIBBLER_H

#include <Arduino.h>
#include "Movement.h"
#include "SensorData.h"
#include "State.h"
class State;

class TEST_DRIBBLER: public State {
public:
        TEST_DRIBBLER();
        void act(Machine *m) override;
        void DEBUG() override;
protected:
        void getNextState(Machine *m) override;
        void step() override;
};

#endif
