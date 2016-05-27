//parse the incoming code and act upon it
#include "Arduino.h"
#define BAUD (115200) // How fast is the Arduino talking?
#define MAX_BUF (64) // What is the longest message Arduino can store?

class gcode_parse
{
	private:
		char buffer[MAX_BUF]; // where we store the message until we get a ';'
		int sofar; // how much is in the buffer
	public:
		gcode_parse();
		void help();
		float parsenumber(char code,float val); 
		void data_recieved(char c);
		void ready();
		void processCommand();
};
