#include "Arduino.h"
#include "gcode_parse.h"





 // prepares the input buffer to receive a new message and 
 // tells the serial connected device it is ready for more.
void gcode_parse::ready() {
  sofar=0; // clear input buffer
  Serial.print(F("> ")); // signal ready to receive input
}

 // display helpful information
void gcode_parse::help() {
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

float gcode_parse::parsenumber(char code,float val) {
  char *ptr=buffer;
  while(ptr && *ptr && ptr<buffer+sofar) {
    if(*ptr==code) {
      return atof(ptr+1);
    }
    ptr=strchr(ptr,' ')+1;
  }
  return val;
}

void gcode_parse::data_recieved(char c) {    
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

gcode_parse::gcode_parse() 
{
  Serial.begin(BAUD); // open coms
  help(); // say hello
  //set_feedrate(200); // set default speed
  ready();
}


// Read the input buffer and find any recognized commands. One G or M command per line.
void gcode_parse::processCommand() {
  // look for commands that start with 'G'
  int cmd=parsenumber('G',-1);
  switch(cmd) {
  case 0: Serial.print("G0"); // move in a line
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
