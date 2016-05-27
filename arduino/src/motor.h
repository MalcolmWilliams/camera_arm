#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

//Motor pin Assignments
//Ramps1.4 X->0
#define MOT_0_DIR 	A1
#define MOT_0_STEP	A0
#define MOT_0_EN	38
#define MOT_0_LIMIT 3

//Ramps1.4 Y->1
#define MOT_1_DIR 	A7
#define MOT_1_STEP	A6
#define MOT_1_EN	A2
#define MOT_1_LIMIT 14

//Ramps1.4 Z->2
#define MOT_2_DIR 	48
#define MOT_2_STEP	46
#define MOT_2_EN	A8
#define MOT_2_LIMIT 18

//Ramps1.4 E0->3
#define MOT_3_DIR 	28
#define MOT_3_STEP	26
#define MOT_3_EN	24

//Ramps1.4 E1->4
#define MOT_4_DIR 	34
#define MOT_4_STEP	36
#define MOT_4_EN	30

const int step_arr[5] 	= {MOT_0_STEP, MOT_1_STEP, MOT_2_STEP, MOT_3_STEP, MOT_4_STEP};
const int dir_arr[5] 	 = {MOT_0_DIR, MOT_1_DIR, MOT_2_DIR, MOT_3_DIR, MOT_4_DIR};
const int en_arr[5]  	 = {MOT_0_EN, MOT_1_EN, MOT_2_EN, MOT_3_EN, MOT_4_EN};
const int limit_arr[3]   = {MOT_0_LIMIT, MOT_1_LIMIT, MOT_2_LIMIT};

class Motor
{
	int step_pin;
	int dir_pin;
	int en_pin;
	int limit_pin;
	//int u_step;
	int home_direction;	//direction to turn the motor in order to hit the limit switch
	float position;	//current rotation of the motor in degrees
	float deg_per_step;
	int direction;
	public:
		Motor(int num, int new_home_direction, float new_deg_per_step);
		void init_pins(int new_step_pin, int new_dir_pin, int new_en_pin, int new_limit_pin);
		void enable();
		void disable();
		void step();
		int* getPins();
		bool home();
		int at_limit();
		void set_direction(int direction);
};

#endif
