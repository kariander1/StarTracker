// 
// 
// 

#include "Antenna.h"
#include "Serializer.h"
Antenna::Antenna(const int in1_pin, const int in2_pin, const int in3_pin, const int in4_pin, const unsigned short az_epprom_add) :
	stepper_az(StepperMotor(in1_pin, in2_pin, in3_pin, in4_pin,az_epprom_add)),
	coordinates(Point(stepper_az.GetAngle(),0))
{
	
}
void Antenna::Stow()
{

	setCoordinates(Point(DEFAULT_STOW_ANGLE_AZ, DEFAULT_STOW_ANGLE_EL));
}


void Antenna::init( const int in_pin_el,const unsigned short &address)
{
	this->servo_el = ServoMotor(in_pin_el, 0, address);
	coordinates.y = servo_el.GetAngle();
	Serializer::Serialize("Initialized antenna");
	Serializer::Serialize("Azimuth:", coordinates.x);
	Serializer::Serialize("Elevation:", coordinates.y);	
	

}

void Antenna::setCoordinates(const Point& coordinates)
{
	servo_el.SetAngle(coordinates.y);
	this->coordinates.y = coordinates.y;
	stepper_az.SetAngle(coordinates.x);
	this->coordinates.x = coordinates.x;
	

}
void Antenna::setCoordinatesAsync(const Point& coordinates)
{

	int el_count = servo_el.SetAngle(coordinates.y,true);
	int az_count = stepper_az.SetAngle(coordinates.x,true);
	if (az_count == 0 || el_count == 0)
	{
		setCoordinates(coordinates);
		return;
	}

	const double count_ratio = (double)el_count / (double)az_count;
	Serializer::SerializeDebug("Ratio is", count_ratio);
	while (servo_el.IsPointing() || stepper_az.IsPointing())
	{
		for (int i = 0; ((double)i)*((double)1/count_ratio) <1 ; i++)
		{
			servo_el.SetAngleStep();
			this->coordinates.y = servo_el.GetAngle();
		}
	
		for (int i = 0; (double)i * (count_ratio) < 1; i++)
		{
			stepper_az.SetAngleStep();
			this->coordinates.x = stepper_az.GetAngle();
		}
	}
	


}
