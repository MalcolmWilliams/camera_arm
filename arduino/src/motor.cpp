//hold the code for the motors. it will be stepper motors to start
#include "utils.h"
#include "motor.h"
#include "Arduino.h"	//Not sure if needed

Motor::Motor(int new_step_pin, int new_dir_pin, int new_en_pin)
{
	step_pin = new_step_pin;
	dir_pin  = new_dir_pin;
	en_pin   = new_en_pin;

	pinMode(step_pin, OUTPUT);
	pinMode(dir_pin,  OUTPUT);
	pinMode(en_pin,   OUTPUT);
}

void Motor::step()
{
}

void Motor::enable()
{
	digitalWrite(en_pin, LOW);
}

void Motor::disable()
{
	digitalWrite(en_pin, HIGH);
}


