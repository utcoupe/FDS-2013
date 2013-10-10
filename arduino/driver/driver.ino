#include "Arduino.h"

#include "command.h"
#define MAX_READ 4 

void setup(){
	/*Active la liaison serie*/
  	Serial.begin(SERIAL_BAUD);

	cherche_moteurs();
	// LED qui n'en est pas une
	pinMode(16,OUTPUT);
}

void loop(){
	/* La del est allumee pendant le traitement */
	digitalWrite(16, HIGH);

	/* zone programmation libre */
	
	int available = Serial.available();
	if (available > MAX_READ) {
		available = MAX_READ;
	}
	for(int i = 0; i < available; i++) {
		// recuperer l'octet courant
		char data = Serial.read();
		cmd(data);
		Serial.write(data);
	}

	/* On eteint la del */
	digitalWrite(16, LOW);
}


