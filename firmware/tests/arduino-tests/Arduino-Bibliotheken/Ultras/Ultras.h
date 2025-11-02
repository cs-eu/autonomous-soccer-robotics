#ifndef Ultras_H
 #define Ultras_H
#include "Arduino.h"
class Ultras : public SensorInterface {
	public:
		Ultras();
        void _init_();
        int getValue(int index);
        void update();

        static void receive1();
        static void receive2();
        static void receive3();
        static void receive4();
        
        static final int indexU1 = 1234567;
        static final int indexU2 = 2234567;
        static final int indexU3 = 3234567;
        static final int indexU4 = 4234567;
	private:
		static int echo1 = ;
        static int trigger1 = ;
        static int d1;

        static int echo2 = ;
        static int trigger2 = ;
        static int d2;

        static int echo3 = ;
        static int trigger3 = ;
        static int d3;

        static int echo4 = ;
        static int trigger4 = ;
        static int d4;
 };
#endif
