// temp.h

#ifndef _TEMP_h
#define _TEMP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class TempClass
{
 protected:


 public:
	void init();
};

extern TempClass Temp;

#endif

