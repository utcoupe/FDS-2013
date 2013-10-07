#ifndef COMMAND_H_
#define COMMAND_H_

#define SERIAL_BAUD 115200

#define AVANCER 0x01
#define RECULER 0x02
#define TOURNER_DROITE 0x03
#define TOURNER_GAUCHE 0x04
#define STOP 0x05
#define BLABLABLA 0x06

void cmd(char cmd); // msg_uid, id_cmd, sizeArgs, *args

#endif /* COMMAND_H_ */
