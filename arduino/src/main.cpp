#include "Arduino.h"
#include "gcode_parse.h"
#include "Motor.h"



// First thing this machine does on startup. Runs only once.
void setup() {
	gcode_parse g = gcode_parse();
}

 // After setup() this machine will repeat loop() forever.
void loop() {
  // listen for commands
  if( Serial.available() ) { // if something is available
    	g.dataRecieved(Serial.read());
	}
  }
}






