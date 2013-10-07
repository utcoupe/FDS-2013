#include "Arduino.h"
#include "command.h"

void cmd(char cmd){
    /* On analyse le message en fonction de son type */
    switch(cmd){
	case SCRIPT_1:
		//Avance 1s
		set_pwm_left(255);
		set_pwm_right(255);
		delay(1000);

		//tourne vers la droite une demi seconde
		set_pwm_left(255);
		set_pwm_right(-255);
		delay(500);

		//recule lentement 2 secondes	
		set_pwm_left(-100);
		set_pwm_right(-100);
		delay(2000);

		set_pwm_left(0);
		set_pwm_right(0);
		break;

	case SCRIPT_2:
		break;
    }
}
