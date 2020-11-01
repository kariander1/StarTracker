// Antenna.h

#ifndef _ANTENNA_h
#define _ANTENNA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "ServoMotor.h"
#include "StepperMotor.h"
#include <EEPROM.h>

#include "Point.h"


const float DEFAULT_STOW_ANGLE_AZ = 0;
const float DEFAULT_STOW_ANGLE_EL = 0;

class Antenna
{
 private:
	 StepperMotor stepper_az;
	// ServoMotor servo_az;  // create servo object to control a servo
	 ServoMotor servo_el;  // create servo object to control a servo
	 


 public:
	 Point coordinates;
	Antenna(const int in1_pin, const int in2_pin, const int in3_pin, const int in4_pin,const unsigned short az_epprom_add);
	void init(const int in_pin_el, const unsigned short &address);
	void setCoordinates(const Point& coordinates);
	void setCoordinatesAsync(const Point& coordinates);
	void Stow();
};

#endif

