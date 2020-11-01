// StepperMotor.h

#ifndef _STEPPERMOTOR_h
#define _STEPPERMOTOR_h

#include <Stepper.h>
#include "eeprom.h"
#include "Serializer.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

const int STEPS_PER_REVOLUTION = 2048;
const short DEGREES_FOR_REVOLUTION = 360;
const short MOTOR_DEFAULT_SPEED= 5;
const double STOW_ANGLE = 0;

const double STEP_TO_DEGREES = (double)STEPS_PER_REVOLUTION / (double)DEGREES_FOR_REVOLUTION;
const double DEGRESS_TO_STEPS = (double)DEGREES_FOR_REVOLUTION / (double)STEPS_PER_REVOLUTION;
class StepperMotor
{
private:
	Stepper step_motor;
	unsigned short speed;
	unsigned short step_count;
	unsigned short eeprom_address;
	double current_angle;
	
	// Dest fields
	bool pointing;
	unsigned short abs_step_count;
	unsigned short current_step;
	short step_sign;
	double Mod360(const double &num) const;

 protected:


 public:
	 StepperMotor(const int in1_pin, const int in2_pin, const int in3_pin, const int in4_pin,const unsigned short address=0);
	 int SetAngle(const double &dest_angle,const bool async = false);
	 void ChangeSpeed(const short speed);
	 void Stow();
	 void MotorStep(const short& step_count, const bool async = false);
	 double GetAngle() const;
	 bool IsPointing() const;
	 void SetAngleStep();
};


#endif

