#include "Arduino.h"

#include "command.h"
#define MAX_READ 20

void setup(){
	/*Active la liaison serie*/
  	Serial.begin(SERIAL_BAUD);

//TODO : pins
	pinMode(PIN_TODO, OUTPUT); 
	digitalWrite(PIN_TODO, LOW);

	// LED qui n'en est pas une
	pinMode(16,OUTPUT);
}

void loop(){
	/* La del est allumee pendant le traitement */
	digitalWrite(16, HIGH);
	int max_read = 20;

	/* zone programmation libre */
	
	int available = Serial.available();
	if (available > MAX_READ) {
		available = MAX_READ;
	}
	for(int i = 0; i < available; i++) {
		// recuperer l'octet courant
		char data = Serial.read();
		cmd(data);
	}

	/* On eteint la del */
	digitalWrite(16, LOW);
}


