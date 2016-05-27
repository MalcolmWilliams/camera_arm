#include "Arduino.h"
#include "gcode_parse.h"
#include "motor.h"
#include "utils.h"

gcode_parse *g;
// First thing this machine does on startup. Runs only once.
void setup() {
	g = new gcode_parse();
}

 // After setup() this machine will repeat loop() forever.
void loop() {
  // listen for commands
	if( Serial.available() ) { // if something is available
    	g->data_recieved(Serial.read());
	}
}



/*
 void setup() {
 // put your setup code here, to run once:
 pinMode(X_STEP, OUTPUT);
 pinMode(X_DIR, OUTPUT);
 pinMode(X_EN, OUTPUT);
 pinMode(13, OUTPUT);
 
 digitalWrite(X_DIR, HIGH);
 digitalWrite(X_EN, HIGH);
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
*/




