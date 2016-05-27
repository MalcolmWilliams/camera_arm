#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

//Motor pin Assignments
//Ramps1.4 X->0
#define MOT_0_DIR 	A0
#define MOT_0_STEP	A1
#define MOT_0_EN	38

//Ramps1.4 Y->1
#define MOT_1_DIR 	A6
#define MOT_1_STEP	A7
#define MOT_1_EN	A2

//Ramps1.4 Z->2
#define MOT_2_DIR 	48
#define MOT_2_STEP	46
#define MOT_2_EN	A8

//Ramps1.4 E0->3
#define MOT_3_DIR 	28
#define MOT_3_STEP	26
#define MOT_3_EN	24

//Ramps1.4 E1->4
#define MOT_4_DIR 	34
#define MOT_4_STEP	36
#define MOT_4_EN	30

class Motor
{
	public:
		Motor(int new_step_pin, int new_dir_pin, int new_en_pin);
		void enable();
		void disable();
		void step();
	private:
		int step_pin, dir_pin, en_pin;
		int u_step;
};

#endif
