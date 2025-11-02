#ifndef SENSORDATA_H
# define SENSORDATA_H

#include <Arduino.h>
#include "COM.h"
#include "SWITCH.h"

boolean inRange(int val, int lower, int upper);
boolean tolerance(int val, int tol);
void DEBUG(struct TrackedObject *struct_ptr);

struct TrackedObject {
        double x;
        double y;
        double lx;
        double ly;
        double ad;
        double at;
        double r;
        boolean visible;
};

namespace SensorData {
extern Receiver RECEIVE;
extern SWITCH switcher;
extern Vision EYES;

extern int BALL_ANGLE;
extern int BALL_RADIUS;
extern int GOAL_HOME_ANGLE;
extern int GOAL_HOME_RADIUS;
extern int GOAL_ENEMY_ANGLE;
extern int GOAL_ENEMY_RADIUS;
extern boolean HAS_BALL;
extern int ballMS;
extern double bSpeedx;
extern double bSpeedy;
extern double bPosx;
extern double bPosy;

extern TrackedObject BALL;
extern TrackedObject GOAL_HOME;
extern TrackedObject GOAL_ENEMY;

extern boolean switch1;
extern boolean switch2;
extern boolean switch3;
extern boolean switch4;
extern boolean switchProgramOn;

extern uint8_t line;

extern uint16_t error;

extern long timer;
extern int delta_t; //delta_t in microsecs
extern int iter_count;

extern boolean calibrated;
extern long hascallibedtime;
extern Receiver RECEIVE;
extern SWITCH switcher;

extern int role;
extern int whichGoal;

void update();
void updateRaspi();
void updateCOM();
void updateSwitches();
void showError();
void DEBUG();
int pxTOcmFront(int pixels);
int pxTOcm(int pixels);
double tangents(double x, double y, boolean down);
void init();
};

#endif
