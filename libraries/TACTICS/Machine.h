#ifndef MACHINE_H
# define MACHINE_H

class Machine
{
class State *current;
public:
Machine();
void setCurrent(State *s)
{
        delete current;
        current = s;
}
void act();
void DEBUG();
};

#endif
