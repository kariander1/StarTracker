// 
// 
// 
#include "StepperMotor.h"
double StepperMotor::Mod360(const double& num) const
{
	//const double  fmod(num, (double)DEGREES_FOR_REVOLUTION)
	return fmod(num,(double)DEGREES_FOR_REVOLUTION);
}
bool StepperMotor::IsPointing() const
{
	return pointing;
}
void StepperMotor::MotorStep(const short& step_count, const bool async)
{
	abs_step_count = abs(step_count);
	step_sign = ((0) < step_count) - (step_count < (0));
	current_step = 0;
	pointing = true;
	if (!async)
	{
		for (unsigned short i = 0; i < abs_step_count; i++)
		{
			this->step_motor.step(step_sign);
			this->step_count = (this->step_count + step_sign) % STEPS_PER_REVOLUTION;
			EepromClass::writeShort(eeprom_address, this->step_count);
			this->current_angle = Mod360(current_angle + step_sign * DEGRESS_TO_STEPS);
		}
		pointing = false;
	}
}
void StepperMotor::SetAngleStep() {
	if (current_step < abs_step_count)
	{
		this->step_motor.step(step_sign);
		this->step_count = (this->step_count + step_sign) % STEPS_PER_REVOLUTION;
		EepromClass::writeShort(eeprom_address, this->step_count);
		this->current_angle = Mod360(current_angle + step_sign * DEGRESS_TO_STEPS);

		current_step++;
	}
	else
	{
		//ApplyAngle(dest_angle);
		pointing = false;
	}

}
double StepperMotor::GetAngle() const
{
	return (this->current_angle);
}
StepperMotor::StepperMotor(const int in1_pin, const int in2_pin, const int in3_pin, const int in4_pin
	, const unsigned short address):
	step_motor(Stepper(STEPS_PER_REVOLUTION, in1_pin, in2_pin, in3_pin, in4_pin)),
	speed(MOTOR_DEFAULT_SPEED),
	step_count(EepromClass::readShort(address)), 
	current_angle(step_count/STEP_TO_DEGREES),
	eeprom_address(address)
{
	
}
void StepperMotor::Stow() {
	SetAngle(STOW_ANGLE);
}
int StepperMotor::SetAngle(const double& dest_angle, const bool async) {
	double angle_delta = Mod360(dest_angle) - current_angle;
	
	const double opposite_delta = (angle_delta>0) ? (angle_delta- DEGREES_FOR_REVOLUTION) : (angle_delta+DEGREES_FOR_REVOLUTION);
	angle_delta = (abs(angle_delta) <= abs(opposite_delta)) ? angle_delta : opposite_delta;
	const short steps =round(angle_delta * STEP_TO_DEGREES);	
	MotorStep(steps,async);
	return abs_step_count;
}
void StepperMotor::ChangeSpeed(const short speed)
{
	this->step_motor.setSpeed(speed);
	this->speed = speed;
}

