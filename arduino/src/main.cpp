#include "Arduino.h"
//#include "gcode_parse.h"
#include "motor.h"
#include "utils.h"



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

/**/
//gcode_parse *g;
Motor *motor[3];
// First thing this machine does on startup. Runs only once.
void setup() {
	int i;
	//motor[0] = new Motor(0, 1, 1.8/16);
	for(i=0; i < 3; i++) motor[i] = new Motor(i, 1, 1.8/16);
	//g = new gcode_parse();
	gcode_parse_init();
	motor[0]->enable();
	//int* pins = motor[0]->getPins();
	//Serial.println( String(pins[0]) + ", " + String(pins[1]) + ", " + String(pins[2]) );
	//motor[0] -> home();
}

 // After setup() this machine will repeat loop() forever.
void loop() {
    //motor[0]->step();
	// listen for commands

	if( Serial.available() ) { // if something is available
    	//Serial.println("HEELOOO\n\n\n");
		data_recieved(Serial.read());
	}

}



// Read the input buffer and find any recognized commands. One G or M command per line.
void processCommand() {
  // look for commands that start with 'G'
  int cmd=parsenumber('G',-1);
  switch(cmd) {
  case 0: 
	motor[0]->home();
	Serial.print("G0"); // move in a line
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
    //m1.release();
    //m2.release();
    break;
  case 100: //help();
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
  //Serial.print(F("> ")); // signal ready to receive input
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






/**/


/**
 void setup() {
 // put your setup code here, to run once:
 pinMode(X_STEP, OUTPUT);
 pinMode(X_DIR, OUTPUT);
 pinMode(X_EN, OUTPUT);
 pinMode(13, OUTPUT);
 
 digitalWrite(X_DIR, HIGH);
 digitalWrite(X_EN, LOW);
}
 
 void loop() {
 // put your main code here, to run repeatedly:
 digitalWrite(X_STEP, HIGH);
 digitalWrite(13, HIGH);
 delay(1);
 digitalWrite(X_STEP, LOW);
 digitalWrite(13, LOW);
 delay(1);
}

/**/



