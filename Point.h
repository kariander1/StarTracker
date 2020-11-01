// Point.h

#ifndef _POINT_h
#define _POINT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Point
{

public:
	float x, y;
	Point() : x(0), y(0) {}
	Point(const float x, const float y) : x(x), y(y) {}
};

#endif

