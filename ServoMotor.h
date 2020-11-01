// ServoMotor.h

#ifndef _SERVOMOTOR_h
#define _SERVOMOTOR_h
#include <Servo.h>
#include "eeprom.h"
#include "Serializer.h"
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

const float MIN_ANGLE =0;
const float MAX_ANGLE= 180;
const float DEFAULT_STOW_ANGLE = MIN_ANGLE;

const short MAX_MILLISECONDS_ANGLE = 2500;
const short MIN_MILLISECONDS_ANGLE = 500;

const short MIN_DELAY = 20; // ms

const short FULL_REV_CYCLE = 5000; //Milliseconds
const double ANG_VELOCITY =MAX_ANGLE / (double)FULL_REV_CYCLE; // deg/sec

const short UNUSED_EEPROM_ADDRESS = -1;
class ServoMotor
{
 private:
	 unsigned short current_milli_angle;
	 float current_angle;
	 unsigned short stow_milli_angle;
	 Servo servo_motor;
	 unsigned short eeprom_address;


	 //Dest angle fileds
	 bool pointing;
	 short delta_steps;
	 unsigned short current_step;
	 double angle_steps;
	 unsigned int step_delay;
	 float dest_angle;


	 const unsigned short AngleToMilli(const float& angle) const;
	 const float MilliToAngle(const unsigned short& milli) const;
	 void PrintIniMessage(const int& in_pin) const;
	 float Mapfloat(float x, float in_min, float in_max, float out_min, float out_max) const;
	 void CalcDestParameters(const float& dest_angle);
	 
	 void ApplyAngle(const float angle);
 public:
	 float GetAngle() const;
	 ServoMotor(const int in_pin, const float stow_angle = DEFAULT_STOW_ANGLE,const float start_angle = DEFAULT_STOW_ANGLE);
	 ServoMotor(const int in_pin, const float stow_angle = DEFAULT_STOW_ANGLE, const unsigned short eeprom_address=0);
	 ServoMotor() {}
	 int SetAngle(const float& dest_angle, const bool async=false);
	 bool IsPointing() const;
	 void Stow();
	 void SetAngleStep();
};


#endif

