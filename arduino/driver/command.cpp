#include "Arduino.h"
#include "command.h"

void cmd(char cmd){
    /* On analyse le message en fonction de son type */
    switch(cmd){
	case AVANCER:
		set_pwm_left(255);
		set_pwm_right(255);
		break;
	
	case RECULER:
		set_pwm_left(-255);
		set_pwm_right(-255);
		break;

	case TOURNER_DROITE:
		set_pwm_left(255);
		set_pwm_right(-255);
		break;

	case TOURNER_GAUCHE:
		set_pwm_left(-255);
		set_pwm_right(255);
		break;

	case STOP:
		set_pwm_left(0);
		set_pwm_right(0);
		break;

	case BLABLABLA:
		break;
    }
}
