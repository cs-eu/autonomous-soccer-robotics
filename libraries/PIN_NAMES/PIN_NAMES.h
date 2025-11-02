#ifndef PIN_NAMES_H
#define PIN_NAMES_H

#include <Arduino.h>

#define BODENADRESS1 24
#define BODENADRESS2 25
#define BODENADRESS3 28
#define BODENADRESS4 40
#define BODENADRESS5 41
#define BODENADRESS6 42
#define BODENADRESS7 43
#define BODENADRESS8 46

#define BODENINTERRUPT_FRONT1 55
#define BODENINTERRUPT_FRONT2 28
#define BODENINTERRUPT_FRONT3 54
#define BODENINTERRUPT_FRONT4 25
#define BODENINTERRUPT_RIGHT1 53
#define BODENINTERRUPT_RIGHT2 24
#define BODENINTERRUPT_RIGHT3 51
#define BODENINTERRUPT_RIGHT4 46
#define BODENINTERRUPT_LEFT1 49
#define BODENINTERRUPT_LEFT2 41
#define BODENINTERRUPT_LEFT3 15
#define BODENINTERRUPT_LEFT4 40
#define BODENINTERRUPT_BACK1 45
#define BODENINTERRUPT_BACK2 43
#define BODENINTERRUPT_BACK3 44
#define BODENINTERRUPT_BACK4 42


// 4 -> 5 -> sda
// 3 -> 7 -> scl
// 33 (scl) -> conv -> 8 -> XTOF_FRONT
// 34 (sda) -> conv -> 10 -> XTOF_BACK

//   2 4 6 8 10
//  1 3 5 7 9

// => 8 und 7, 10 und 5 vertauschen

#define XTOF_RIGHT 31 // 31
#define XTOF_LEFT 32 //
#define XTOF_FRONT 4 // 33 // 33 SCL
#define XTOF_BACK 3 // 34 // 34 SDA

#define SWITCH_PROGRAM 31
#define SWITCH1 32
#define SWITCH2 33
#define SWITCH3 34
#define SWITCH4 35

#define KICKER 29

#define LED_PIN_TOP 47
#define LED_PIN_BOT 48


#define M1D1 16
#define M1D2 17
#define M1PWM 2
#define M1SF 4
#define M1FB 36

#define M2D1 18
#define M2D2 19
#define M2PWM 6
#define M2SF 7
#define M2FB 37

#define M3D1 21
#define M3D2 22
#define M3PWM 14
#define M3SF 11
#define M3FB 38

#define M4D1 23
#define M4D2 26
#define M4PWM 20
#define M4SF 13
#define M4FB 39

#endif
