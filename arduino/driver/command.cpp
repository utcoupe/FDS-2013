#include "Arduino.h"
#include "command.h"

void cmd(char cmd){
    /* On analyse le message en fonction de son type */
    switch(cmd){
	case SCRIPT_1:
		//Avance 1s
		set_pwm_left(100);
		set_pwm_right(-100);
		delay(1000);

		//tourne vers la droite une demi seconde
		set_pwm_left(100);
		set_pwm_right(-100);
		delay(1500);

		//recule lentement 2 secondes	
		set_pwm_left(-70);
		set_pwm_right(-70);
		delay(2000);
		set_pwm_left(-70);
		set_pwm_right(70);
		delay(2000);
		set_pwm_left(70);
		set_pwm_right(70);
		delay(1500);

		set_pwm_left(0);
		set_pwm_right(0);
		break;

	case SCRIPT_D:
		set_pwm_left(-80);
		set_pwm_right(-80);
		delay(500);

		set_pwm_left(0);
		set_pwm_right(0);
		break;
	case SCRIPT_Q:
		set_pwm_left(70);
		set_pwm_right(70);
		delay(500);

		set_pwm_left(0);
		set_pwm_right(0);
		break;
	case SCRIPT_S:
		set_pwm_left(70);
		set_pwm_right(-70);
		delay(500);

		set_pwm_left(0);
		set_pwm_right(0);
		break;
	case SCRIPT_Z:
		set_pwm_left(-70);
		set_pwm_right(70);
		delay(500);

		set_pwm_left(0);
		set_pwm_right(0);
		break;
	case SCRIPT_5:
		set_pwm_left(-70);
		set_pwm_right(70);
		delay(2000);
		set_pwm_left(70);
		set_pwm_right(70);
		delay(2000);
		set_pwm_left(-70);
		set_pwm_right(70);
		delay(2000);
		set_pwm_left(70);
		set_pwm_right(70);
		delay(500);
		set_pwm_left(-70);
		set_pwm_right(-70);
		delay(500);
		set_pwm_left(70);
		set_pwm_right(70);
		delay(200);
		set_pwm_left(0);
		set_pwm_right(0);
		delay(750);
		set_pwm_left(70);
		set_pwm_right(70);
		delay(500);
		set_pwm_left(-70);
		set_pwm_right(70);
		delay(1000);
		set_pwm_left(70);
		set_pwm_right(-70);
		delay(1000);

		set_pwm_left(0);
		set_pwm_right(0);
		break;
    }
}
