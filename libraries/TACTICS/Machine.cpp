#include "Machine.h"
#include "State.h"

Machine::Machine(){
}

void Machine::act() {
        current->act(this);
}
void Machine::DEBUG() {
        current->DEBUG();
}
