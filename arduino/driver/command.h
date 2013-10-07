#ifndef COMMAND_H_
#define COMMAND_H_

#include "ax12.h"
#include "motor.h"
#include "controle_ax12.h"

#define SERIAL_BAUD 115200

#define SCRIPT_1 0x01
#define SCRIPT_2 0x02

void cmd(char cmd); // msg_uid, id_cmd, sizeArgs, *args

#endif /* COMMAND_H_ */
