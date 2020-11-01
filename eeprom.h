// eeprom.h

#ifndef _EEPROM_h
#define _EEPROM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <EEPROM.h>

class EepromClass
{
 protected:


 public:
	static short readShort(const unsigned short &address);
	static void writeShort(const unsigned short &address, const unsigned short &value);
};

#endif

