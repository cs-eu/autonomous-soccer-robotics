#include <SWITCH.h>
#include <Arduino.h>
#include <PIN_NAMES.h>

SWITCH::SWITCH()
{
	pinMode(SWITCH_PROGRAM, INPUT_PULLUP);
	pinMode(SWITCH1, INPUT_PULLUP);
	pinMode(SWITCH2, INPUT_PULLUP);
	pinMode(SWITCH3, INPUT_PULLUP);
	pinMode(SWITCH4, INPUT_PULLUP);
}

bool SWITCH::switchProgramOn()
{
	if (digitalRead(SWITCH_PROGRAM) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool SWITCH::switchProgramOff()
{
	if (digitalRead(SWITCH_PROGRAM) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool SWITCH::switch1On()
{
	if (digitalRead(SWITCH1) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool SWITCH::switch1Off()
{
	if (digitalRead(SWITCH1) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool SWITCH::switch2On()
{
	if (digitalRead(SWITCH2) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool SWITCH::switch2Off()
{
	if (digitalRead(SWITCH2) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool SWITCH::switch3On()
{
	if (digitalRead(SWITCH3) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool SWITCH::switch3Off()
{
	if (digitalRead(SWITCH3) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool SWITCH::switch4On()
{
	if (digitalRead(SWITCH4) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool SWITCH::switch4Off()
{
	if (digitalRead(SWITCH4) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}