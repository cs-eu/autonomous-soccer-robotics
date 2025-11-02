#include "Arduino.h"
#include "SensorData.h"
#include "Movement.h"
#include "SimpleKalmanFilter.h"

/*
   GOAL_RADIUS:
            Visible   not Visible
   Behind      > 1       0
   Not Behind  1         0

   BALL_RADIUS:
                  Visible   not Visible
   dribbler          1          0
   not in dribbler  > 1         0
 */

boolean inRange(int val, int lower, int upper) {
        return (val > lower) && (val < upper);
}
boolean tolerance(int val, int tol) {
        return inRange(val, -tol, tol);
}
void DEBUG(struct TrackedObject *struct_ptr) {
        Serial.print(" at: ");
        Serial.print((*struct_ptr).at);
        Serial.print(" ad: ");
        Serial.print((*struct_ptr).ad);
        Serial.print(" r: ");
        Serial.print((*struct_ptr).r);
        Serial.print(" x: ");
        Serial.print((*struct_ptr).x);
        Serial.print(" y: ");
        Serial.print((*struct_ptr).y);
        Serial.print(" lx: ");
        Serial.print((*struct_ptr).lx);
        Serial.print(" ly: ");
        Serial.print((*struct_ptr).lx);
        Serial.print(" visible: ");
        Serial.println((*struct_ptr).visible);
}

namespace SensorData {
Receiver RECEIVE;
SWITCH switcher;
Vision EYES;

int BALL_ANGLE = 0;
int BALL_RADIUS = -1;

TrackedObject BALL = {0, 0, 0, 0, 0, 0, 0, false};
double aDalt = 0;
double rDalt = 0;
TrackedObject GOAL_HOME = {0, 0, 0, 0, 0, 0, 0, false};
TrackedObject GOAL_ENEMY = {0, 0, 0, 0, 0, 0, 0, false};

SimpleKalmanFilter ballSpeedXFilter(0.5, 0.5, 0.002);
SimpleKalmanFilter ballSpeedYFilter(0.5, 0.5, 0.002);
SimpleKalmanFilter ghSpeedXFilter(0.5, 0.5, 0.002);
SimpleKalmanFilter ghSpeedYFilter(0.5, 0.5, 0.002);
SimpleKalmanFilter geSpeedXFilter(0.5, 0.5, 0.002);
SimpleKalmanFilter geSpeedYFilter(0.5, 0.5, 0.002);

int GOAL_HOME_ANGLE = 0;
int GOAL_HOME_RADIUS = 0;

int GOAL_ENEMY_ANGLE = 0;
int GOAL_ENEMY_RADIUS = 0;

boolean HAS_BALL = false;
int ballMS = 0;

uint8_t line = 0;

uint16_t error = 0;

boolean switch1 = false;
boolean switch2 = false;
boolean switch3 = false;
boolean switch4 = false;
boolean lastSwitch4 = false;
boolean shotTestFirst = true;
boolean switchProgramOn = false;

boolean calibrated = false;
boolean hascallibed = false;
long hascallibedtime = 0;

long timer = 0;
int delta_t = 0;
int iter_count = 0;


int role = 0;
int whichGoal = 0;

void init() {
        RECEIVE.init();
        EYES.init();
}
void update() {
        iter_count++;
        delta_t = micros() - timer;
        timer = micros();
        updateSwitches();
        updateRaspi();
        updateCOM();
        HAS_BALL = (BALL_RADIUS == 1); // && (BALL_ANGLE > -10) && (BALL_ANGLE < 10);// && (Movement::getCurrentFeedback(3) > 15);//tolerance(BALL_ANGLE, 5);
        if (HAS_BALL) {
                ballMS += delta_t;
        }
        else {
                ballMS = 0;
        }
        if (switch1) {
                RECEIVE.setZeroIMU();
        }
        if ((BALL_RADIUS != -1) && (RECEIVE.getCompass() != 362)) {
                calibrated = true;
        }
        if (lastSwitch4 != switch4 && !shotTestFirst) {
                Movement::kick();
                lastSwitch4 = switch4;
        }
}
void updateSwitches() {
        switch1 = switcher.switch1On();
        switch2 = switcher.switch2On();
        switch3 = switcher.switch3On();
        switch4 = switcher.switch4On();
        if (shotTestFirst) {
                lastSwitch4 = switch4;
                shotTestFirst = false;
        }
        switchProgramOn = switcher.switchProgramOn();
}
void DEBUG() {
        Serial.print("BALL: ");
        DEBUG(&BALL);
        Serial.print("GOAL_HOME: ");
        DEBUG(&GOAL_HOME);
        Serial.print("GOAL_ENEMY: ");
        DEBUG(&GOAL_ENEMY);
}
void updateCOM() {
        RECEIVE.receive();
        if (!switchProgramOn) {
                if (RECEIVE.getTofLeft() < 5 && RECEIVE.getTofRight() < 5) {
                        RECEIVE.setZeroIMU();
                        hascallibed = false;
                        hascallibedtime = millis();
                }
                else {
                        if (!hascallibed) {
                                RECEIVE.setCallibIMU();
                                hascallibed = true;
                        }
                        else {
                                RECEIVE.setGameMode();
                        }
                }
        }
        else {
                RECEIVE.setGameMode();
        }
}
void updateRaspi() {
        if (switch3) {
                EYES.receive(1);
        }
        else {
                EYES.receive(0);
        }
        if (switch4) {
                GOAL_HOME_ANGLE = EYES.getBlueAngle();
                if (EYES.getBlueRadius() > 0) {
                        GOAL_HOME_RADIUS = max(pxTOcm(EYES.getBlueRadius()), 1);
                }
                else {
                        GOAL_HOME_RADIUS = 0;
                }
                GOAL_ENEMY_ANGLE = EYES.getYellowAngle();
                if (EYES.getYellowRadius() > 0) {
                        GOAL_ENEMY_RADIUS = max(pxTOcm(EYES.getYellowRadius()), 1);
                }
                else {
                        GOAL_ENEMY_RADIUS = 0;
                }
        }
        else {
                GOAL_ENEMY_ANGLE = EYES.getBlueAngle();
                if (EYES.getBlueRadius() > 0) {
                        GOAL_ENEMY_RADIUS = max(pxTOcm(EYES.getBlueRadius()), 1);
                }
                else {
                        GOAL_ENEMY_RADIUS = 0;
                }
                GOAL_HOME_ANGLE = EYES.getYellowAngle();
                if (EYES.getYellowRadius() > 0) {
                        GOAL_HOME_RADIUS = max(pxTOcm(EYES.getYellowRadius()), 1);
                }
                else {
                        GOAL_HOME_RADIUS = 0;
                }
        }
        BALL_ANGLE = EYES.getBallAngle();
        if (EYES.getBallRadius() > 1) {
                if (tolerance(EYES.getTrueAngle(), 20)) {
                        BALL_RADIUS = max(pxTOcmFront(EYES.getBallRadius()), 2);
                }
                else {
                        BALL_RADIUS = max(pxTOcm(EYES.getBallRadius()), 2);
                }
        }
        else {
                BALL_RADIUS = EYES.getBallRadius();
        }

        if (abs(GOAL_ENEMY_ANGLE) > 90) {
                GOAL_ENEMY_RADIUS = 0;
        }
        if (abs(GOAL_HOME_ANGLE) < 90) {
                GOAL_HOME_RADIUS = 0;
        }

        BALL.ad = BALL_ANGLE;
        BALL.at = EYES.getTrueAngle();
        BALL.r = BALL_RADIUS;
        BALL.visible = BALL_RADIUS != 0;
        if (BALL.visible) {
                BALL.lx = BALL.x;
                BALL.ly = BALL.y;
                BALL.x = ballSpeedXFilter.updateEstimate(cos(BALL.at * PI / 180) * (BALL_RADIUS + 10)); // + 10
                BALL.y = ballSpeedYFilter.updateEstimate(sin(BALL.at * PI / 180) * (BALL_RADIUS + 10)); // + 10
        }

        GOAL_HOME.ad = GOAL_HOME_ANGLE;
        GOAL_HOME.at = GOAL_HOME_ANGLE + RECEIVE.getCompass();
        GOAL_HOME.r = GOAL_HOME_RADIUS;
        GOAL_HOME.visible = GOAL_HOME_RADIUS != 0;
        if (GOAL_HOME.visible) {
                GOAL_HOME.lx = GOAL_HOME.x;
                GOAL_HOME.ly = GOAL_HOME.y;
                GOAL_HOME.x = ghSpeedXFilter.updateEstimate(cos((GOAL_HOME_ANGLE + RECEIVE.getCompass()) * PI / 180) * (GOAL_HOME_RADIUS + 10));
                GOAL_HOME.y = ghSpeedYFilter.updateEstimate(sin((GOAL_HOME_ANGLE + RECEIVE.getCompass()) * PI / 180) * (GOAL_HOME_RADIUS + 10));
        }

        GOAL_ENEMY.ad = GOAL_ENEMY_ANGLE;
        GOAL_ENEMY.at = GOAL_ENEMY_ANGLE + RECEIVE.getCompass();
        GOAL_ENEMY.r = GOAL_ENEMY_RADIUS;
        GOAL_ENEMY.visible = GOAL_ENEMY_RADIUS != 0;
        if (GOAL_ENEMY.visible) {
                GOAL_ENEMY.lx = GOAL_ENEMY.x;
                GOAL_ENEMY.ly = GOAL_ENEMY.y;
                GOAL_ENEMY.x = geSpeedXFilter.updateEstimate(cos((GOAL_ENEMY_ANGLE + RECEIVE.getCompass()) * PI / 180) * (GOAL_ENEMY_RADIUS + 10));
                GOAL_ENEMY.y = geSpeedYFilter.updateEstimate(sin((GOAL_ENEMY_ANGLE + RECEIVE.getCompass()) * PI / 180) * (GOAL_ENEMY_RADIUS + 10));
        }
}
void showError() {
        if ((iter_count % 100) == 0) {

        }
        else {

        }
}
int pxTOcmFront(int pixels) {
        return pxTOcm(pixels);
        double x = (double) pixels;
        return (int) (4.7759335078+0.2960851569*x+0.0011332149*x*x-0.0000704787*x*x*x+0.0000011296*x*x*x*x);
}
int pxTOcm(int pixels) {
        double x = (double) pixels;
        return (int) (5.636408 - (-0.07177567/ -0.03316989)*(1 - exp(0.03316989*x)));
        return (int) (-15.1193058079+0.7986406062*x+0.0002876976*x*x-0.0001741793*x*x*x+0.0000015565*x*x*x*x);
}
double tangents(double x, double y, boolean down) {
        double r = 0;
        if (down) {
                r = -10 - 3;
        }
        else {
                r = 10 - 3;
        }
        double z = x * x + y * y;
        double d = z - r * r;
        d = sqrt(abs(d));
        double a = ((x * r) + (y * d)) / z;
        double b = ((y * r) - (x * d)) / z;
        return atan2(-a, b) * 180 / PI;
}
}
