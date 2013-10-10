#ifndef COMMAND_H_
#define COMMAND_H_

#include "ax12.h"
#include "motor.h"
#include "controle_ax12.h"

#define SERIAL_BAUD 115200

#define SCRIPT_1 '1'
#define SCRIPT_2 '2'
#define SCRIPT_3 '3'
#define SCRIPT_4 '4'
#define SCRIPT_5 '5'

void cmd(char cmd); // msg_uid, id_cmd, sizeArgs, *args

#endif /* COMMAND_H_ */
