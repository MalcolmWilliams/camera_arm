//hold the code for the motors. it will be stepper motors to start
#include "utils.h"
#include "motor.h"
#include "Arduino.h"	//Not sure if needed

Motor::Motor(int num, int new_home_direction, float new_deg_per_step, float new_lim_max)
{
	init_pins(step_arr[num], dir_arr[num], en_arr[num], limit_arr[num]);
	home_direction = new_home_direction;	
	deg_per_step = new_deg_per_step;
	set_direction(1);
	lim_max = new_lim_max;
}

void Motor::init_pins(int new_step_pin, int new_dir_pin, int new_en_pin, int new_limit_pin)
{
	step_pin = new_step_pin;
	dir_pin  = new_dir_pin;
	en_pin   = new_en_pin;
	limit_pin = new_limit_pin;

	pinMode(step_pin, OUTPUT);
	pinMode(dir_pin,  OUTPUT);
	pinMode(en_pin,   OUTPUT);
	pinMode(limit_pin, INPUT_PULLUP);

	//digitalWrite(dir_pin, HIGH);
}

void Motor::step()
{
	position += deg_per_step*direction;
	if(position < lim_max && position > 0)
	{
		//steps the motor once, with minimum ammount of delay
		digitalWrite(step_pin, HIGH);
		delayMicroseconds(3);
		digitalWrite(step_pin, LOW);
		delayMicroseconds(3);
	} 
}

void Motor::enable()
{
	digitalWrite(en_pin, LOW);
}

void Motor::disable()
{
	digitalWrite(en_pin, HIGH);
}

int* Motor::getPins()
{
	static int pins[3];
	pins[0] = step_pin;
	pins[1] = dir_pin;
	pins[2] = en_pin;

	return pins;
}

bool Motor::home()
{
	position = lim_max;	//initially set the position to the max limit. if it needs to go further then this, something is bad	
	set_direction(home_direction);
	while(!at_limit())
	{
		step();
		//delay(1);
		delayMicroseconds(100);
	}
	if(at_limit())
	{
		position = 0;
		return true;
	} else {
	return false;
	}
}

void Motor::set_direction(int new_direction)
{
	direction = new_direction;
	if(direction ==  1) digitalWrite(dir_pin, LOW);
	if(direction == -1) digitalWrite(dir_pin, HIGH);
}

int Motor::at_limit()
{
	//return 1 if at limit. since it is a pullup we thus invert it. 
	return digitalRead(limit_pin)-1;
}

float Motor::get_position()
{
	return position;
}

void Motor::goto_position(float new_pos)
{
	float relative_pos = new_pos - position;
	if(relative_pos == 0) return;
	if(relative_pos < 0) direction = -1;
	else direction = 1;
	
	set_direction(direction);

	while( abs(get_position() - new_pos) > deg_per_step) 
	{
		step();
		delayMicroseconds(100);
		//delay(2);
	}
}
