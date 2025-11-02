#ifndef KICKER_H
# define KICKER_H

#include <Arduino.h>
#include "PIN_NAMES.h"

#define ON_TIME_MS 20
#define COOLDOWN_MS 2000

class Kicker {
public:
Kicker();
void kick();
private:
long lastShot;
};

#endif
