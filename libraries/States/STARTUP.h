#ifndef STARTUP_H
# define STARTUP_H

#include <Arduino.h>
#include "Movement.h"
#include "SensorData.h"
#include "State.h"
class State;

class STARTUP: public State {
public:
        STARTUP();
        void act(Machine *m) override;
        void DEBUG() override;
protected:
        void getNextState(Machine *m) override;
        void step() override;
};

#endif
