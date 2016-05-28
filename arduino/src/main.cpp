#include "Arduino.h"
//#include "gcode_parse.h"
#include "motor.h"
#include "utils.h"


//gcode parsing variables
#define BAUD (115200) // How fast is the Arduino talking?
#define MAX_BUF (64) // What is the longest message Arduino can store?

char buffer[MAX_BUF]; // where we store the message until we get a ';'
int sofar; // how much is in the buffer

void gcode_parse_init();
void help();
float parsenumber(char code,float val); 
void data_recieved(char c);
void ready();
void processCommand();


//motor command variables
#define NUM_MOTOR 3 
#define DEG_PER_STEP 1.8/32
void home_all();
void motors_off();
void motors_on();
void goto_position(float pos_0, float pos_1, float pos_2);

Motor *motor[NUM_MOTOR];


// First thing this machine does on startup. Runs only once.
void setup() {
	int i;
	//motor[0] = new Motor(0, 1, 1.8/16);
	for(i=0; i < NUM_MOTOR; i++) motor[i] = new Motor(i, 1,DEG_PER_STEP); 
	//g = new gcode_parse();
	gcode_parse_init();
	motors_on();
	//motor[0]->enable();
}

 // After setup() this machine will repeat loop() forever.
void loop() {
	// listen for commands

	if( Serial.available() ) { // if something is available
		data_recieved(Serial.read());
	}

}



// Read the input buffer and find any recognized commands. One G or M command per line.
void processCommand() {
	// look for commands that start with 'G'
  	int cmd=parsenumber('G',-1);
  	switch(cmd) {
  	case 0: 
		goto_position(parsenumber('X',motor[0]->get_position()),  parsenumber('Y',motor[1]->get_position()), parsenumber('Z', motor[2]->get_position()));
		//motor[0]->home();
		//Serial.print("G0"); // move in a line
		break;
  	case 1: // move in a line
   		//set_feedrate(parsenumber('F',fr));
   		//line( parsenumber('X',(mode_abs?px:0)) + (mode_abs?0:px),
   		//parsenumber('Y',(mode_abs?py:0)) + (mode_abs?0:py) );
  	  	break;
 	// case 2: // clockwise arc
 	// case 3: // counter-clockwise arc
  	case 4: 
    	//pause(parsenumber('P',0)*1000); 
	case 28:	//home
		home_all();	
    	break; // wait a while
  	case 90: 
    	//mode_abs=1; 
    	//break; // absolute mode
  	case 91: 
    	//mode_abs=0; 
    	break; // relative mode
  	case 92: // set logical position
    	//position( parsenumber('X',0),
    	//parsenumber('Y',0) );
    	break;
  	default: break;
	}

  	// look for commands that start with 'M'
  	cmd=parsenumber('M',-1);
 	switch(cmd) {
  	case 18: // turns off power to steppers (releases the grip)
    	motors_off();
		break;
  	case 100: 
		help();
		break;
  	case 114: 
    	//where(); 
    	break; // prints px, py, fr, and mode.
  	default: break;
  	}

// if the string has no G or M commands it will get here and the Arduino will silently ignore it
}



 // prepares the input buffer to receive a new message and 
 // tells the serial connected device it is ready for more.
void ready() {
  sofar=0; // clear input buffer
  Serial.print(F("> ")); // signal ready to receive input
}

 // display helpful information
void help() {
  Serial.print(F("CNC Robot "));
  //Serial.println(VERSION);
  Serial.println(F("Commands:"));
  Serial.println(F("G00 [X(steps)] [Y(steps)] [F(feedrate)]; - linear move"));
  Serial.println(F("G01 [X(steps)] [Y(steps)] [F(feedrate)]; - linear move"));
  Serial.println(F("G04 P[seconds]; - delay"));
  Serial.println(F("G90; - absolute mode"));
  Serial.println(F("G91; - relative mode"));
  Serial.println(F("G92 [X(steps)] [Y(steps)]; - change logical position"));
  Serial.println(F("M18; - disable motors"));
  Serial.println(F("M100; - this help message"));
  Serial.println(F("M114; - report position and feedrate"));
}


/**
 * Look for character /code/ in the buffer and read the float that immediately follows it.
 * @return the value found.  If nothing is found, /val/ is returned.
 * @input code the character to look for.
 * @input val the return value if /code/ is not found.
 **/
float parsenumber(char code,float val) {
  char *ptr=buffer;
  while(ptr && *ptr && ptr<buffer+sofar) {
    if(*ptr==code) {
      return atof(ptr+1);
    }
    ptr=strchr(ptr,' ')+1;
  }
  return val;
}

void data_recieved(char c) {    
	//char c = Serial.read(); // get it
    //Serial.print(c); // optional: repeat back what I got for debugging

    // store the byte as long as there's room in the buffer.
    // if the buffer is full some data might get lost
    if(sofar < MAX_BUF) buffer[sofar++]=c;
    // if we got a return character (\n) the message is done.
    if(c=='\n') {
      Serial.print(F("\r\n")); // optional: send back a return for debugging

      // strings must end with a \0.
      buffer[sofar]=0;
      processCommand(); // do something with the command
      ready();
	}
}

void gcode_parse_init() 
{
  Serial.begin(BAUD); // open coms
  //help(); // say hello
  //set_feedrate(200); // set default speed
  ready();
}


//gcode commands
void home_all()
{
	int i;
	for(i=0;i<NUM_MOTOR;i++) motor[i]->home();
}

void motors_off()
{
	int i;
	for(i=0;i<NUM_MOTOR;i++) motor[i]->disable();
}

void goto_position(float pos_0, float pos_1, float pos_2)
{
	float pos[3] = {pos_0, pos_1, pos_2};
	int i;
	for(i=0;i<NUM_MOTOR;i++) motor[i]->goto_position(pos[i]);
}

void motors_on()
{
	int i;
	for(i=0;i<NUM_MOTOR;i++) motor[i]->enable();
}
