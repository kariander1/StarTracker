// 
// 
// 

#include "ServoMotor.h"
ServoMotor::ServoMotor(const int in_pin, const float stow_angle = DEFAULT_STOW_ANGLE, const unsigned short eeprom_address) :
	servo_motor(Servo()), stow_milli_angle(AngleToMilli(stow_angle)), eeprom_address(eeprom_address)
{
	const unsigned short milli_angle = EepromClass::readShort(eeprom_address);
	this->current_milli_angle = milli_angle;
	this->current_angle = MilliToAngle(current_milli_angle);
	this->servo_motor.writeMicroseconds(milli_angle);
	this->servo_motor.attach(in_pin);
	PrintIniMessage(in_pin);
}
void ServoMotor::PrintIniMessage(const int &in_pin) const
{
	Serializer::SerializeDebug("initialized Servo with pin:", in_pin);
	Serializer::SerializeDebug("Servo starting angle is:", current_angle);
	Serializer::SerializeDebug("Milli angle is:", current_milli_angle);
}
ServoMotor::ServoMotor(const int in_pin, const float stow_angle, const float start_angle) :
	servo_motor(Servo()), stow_milli_angle(AngleToMilli(stow_angle)), current_milli_angle(AngleToMilli(start_angle))
	, eeprom_address(UNUSED_EEPROM_ADDRESS),current_angle(start_angle)
{
	this->servo_motor.writeMicroseconds(AngleToMilli( start_angle));
	this->servo_motor.attach(in_pin);
	PrintIniMessage(in_pin);
}

void ServoMotor::ApplyAngle(const float angle)
{
	this->current_angle = angle;
	current_milli_angle = AngleToMilli(this->current_angle);

	servo_motor.writeMicroseconds(current_milli_angle);
	if (eeprom_address != UNUSED_EEPROM_ADDRESS)
		EepromClass::writeShort(eeprom_address, current_milli_angle);
}
void ServoMotor::CalcDestParameters(const float& dest_angle)
{
	if (dest_angle<MIN_ANGLE || dest_angle>MAX_ANGLE)
	{
		Serial.print("Invalid angle: ");
		Serial.println(dest_angle);
		return;
	}

	this->dest_angle = dest_angle;
	const float angle_delta = ((dest_angle)-current_angle);
	const int sweep_time = abs((ANG_VELOCITY * angle_delta) * 1000); // In milliseconds
	delta_steps = (sweep_time / (10)) + 1;
	angle_steps = (double)angle_delta / (double)delta_steps; // TODO define steps more clearer
	step_delay = abs(angle_steps) * ANG_VELOCITY * 1000; // In milli
	current_step = 0;
	Serializer::SerializeDebug("Current angle:", current_angle);
	Serializer::SerializeDebug("Dest angle is:", dest_angle);
	Serializer::SerializeDebug("Angle delta is:", angle_delta);
	Serializer::SerializeDebug("Sweep time is:", sweep_time);
	Serializer::SerializeDebug("Angle steps are:", angle_steps);
	Serializer::SerializeDebug("Starting steps with delays of:", step_delay);
}
int ServoMotor::SetAngle(const float& dest_angle,const bool async) {
	
	CalcDestParameters(dest_angle);
	pointing = true;
	

	if (!async)
	{
		for (unsigned short i = 0; i < delta_steps; i++)
		{
			ApplyAngle(this->current_angle + angle_steps);
			delay(step_delay);
		}
		ApplyAngle(dest_angle);
		pointing = false;

	}
	return delta_steps;
}
void ServoMotor::SetAngleStep() {
	if (current_step < delta_steps)
	{		
		ApplyAngle(this->current_angle + angle_steps);
		
		delay(step_delay);
		current_step++;
	}
	else
	{
		ApplyAngle(dest_angle);
		pointing = false;
	}
	
}
bool ServoMotor::IsPointing() const
{
	return pointing;
}
float ServoMotor::GetAngle() const
{
	return (current_angle);
}
float ServoMotor::Mapfloat(float x, float in_min, float in_max, float out_min, float out_max) const
{
	return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}
const unsigned short ServoMotor::AngleToMilli(const float& angle) const
{
	const unsigned short mapped_milli_angle = Mapfloat(angle, MIN_ANGLE
		, MAX_ANGLE, MIN_MILLISECONDS_ANGLE, MAX_MILLISECONDS_ANGLE); // 
	return mapped_milli_angle;
}
const float ServoMotor::MilliToAngle(const unsigned short & milli) const
{
	const float mapped_angle= Mapfloat(milli, MIN_MILLISECONDS_ANGLE
		, MAX_MILLISECONDS_ANGLE, MIN_ANGLE, MAX_ANGLE); // 
	return mapped_angle;
}
void ServoMotor::Stow() {
	SetAngle(DEFAULT_STOW_ANGLE);
}


