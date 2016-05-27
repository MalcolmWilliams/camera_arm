//hold the code for the motors. it will be stepper motors to start
#include "utils.h"
#include "motor.h"
#include "Arduino.h"	//Not sure if needed

Motor::Motor(int num, int new_home_direction, float new_deg_per_step)
{
	init_pins(step_arr[num], dir_arr[num], en_arr[num], limit_arr[num]);
	home_direction = new_home_direction;	
	deg_per_step = new_deg_per_step;
	direction = 1;
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
	pinMode(limit_pin, INPUT);

	//digitalWrite(dir_pin, HIGH);
}

void Motor::step()
{
	//steps the motor once, with minimum ammount of delay
	digitalWrite(step_pin, HIGH);
	delayMicroseconds(3);
	digitalWrite(step_pin, LOW);
	delayMicroseconds(3);
	position += deg_per_step*direction;
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
	position = 0;
	set_direction(home_direction);
	while(!at_limit() && position < 360 && position > -360)//exit early if the motor makes a full turn in either direction (likely means something is wrong)
	{
		step();
		delay(1);
	}
	if(at_limit())
	{
		position = 0;
		return true;
	} else {
	return false;
	}
}

void Motor::set_direction(int direction)
{
	if(direction == -1) digitalWrite(dir_pin, LOW);
	if(direction ==  1) digitalWrite(dir_pin, HIGH);
}

int Motor::at_limit()
{
	return digitalRead(limit_pin);
}
