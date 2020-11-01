// Serial.h

#ifndef _SERIAL_h
#define _SERIAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "WString.h"

#include "Point.h"

const bool DEBUG = true;
const String START_SEND_COORDINATES_STRING = "START_TRANSMISSION";
const String END_SEND_COORDINATES_STRING = "END_TRANSMISSION";
const String COORDINATES_PREFIX = "CO";
const String AZIMUTH_PREFIX = "AZ";
const String ELEVATION_PREFIX = "EL";
class Serializer
{
private:
	bool recevied_start = false;
 protected:


 public:
	static void SerializeDebug(const String &text) ;
	template <class T>
	static void SerializeDebug(const String &text,const T &value)
	{
		if (DEBUG)
			Serialize(text, value);
	}
	static void Serialize(const String& text);
	template <class T>
	static void Serialize(const String& text, const T& value)
	{
		Serial.print(text + " ");
		Serial.println(value);
	}
	static bool ListenForCoordinates(Point& dest_coordinates);
	//static bool ListenForEEPROMcommand();
};

#endif

