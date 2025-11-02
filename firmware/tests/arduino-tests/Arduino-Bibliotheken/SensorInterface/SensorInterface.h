#ifndef SensorInterface_H

 #define SensorInterface_H
  

#include "Arduino.h"

class SensorInterface {
	public:
		SensorInterface();
		virtual void _init_();
        virtual int getValue(int index);
        virtual void update();

 };

#endif
