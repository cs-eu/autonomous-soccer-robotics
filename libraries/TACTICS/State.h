#ifndef STATE_H
# define STATE_H
#include "Machine.h"

class State {
public:
virtual void act(Machine *m) {
};
virtual void DEBUG() {
};
virtual ~State() {
};
protected:
virtual void getNextState(Machine *m) {
};
virtual void step() {
};
};

#endif
