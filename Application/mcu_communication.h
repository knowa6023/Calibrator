/*
 * mcu_communication.h
 *
 *  Created on: 27 авг. 2020 г.
 *      Author: PC
 */
#include "main.h"
#ifndef MCU_COMMUNICATION_H_
#define MCU_COMMUNICATION_H_

#define MAX_STRING_BUF 30

typedef enum {
	MCUSTAT_OK = 0,
	MCUSTAT_ERR
}MCU_Status;

typedef enum CMD_Type{
	CMD_BEGIN = 0,
	CMD_END,
	CMD_GET_STAT,
	CMD_STOP_MOTOR,
	CMD_SET_STEP,
	CMD_SET_STEP_,
	CMD_NONE
}CMD_Type;


typedef struct CAMARG_Laser{
	uint16_t Laser[1];
}CAMARG_Laser;

typedef struct CAMARG_Int32{
	int32_t par_int32;
}CAMARG_Int32;

typedef struct CAMARG_ValueParametr{
	uint16_t ValueParametr[1];
}CAMARG_ValueParametr;


typedef enum{
	STATE_NONE 				= 0,
	STATE_CMD_DECODE_CMD	= 1,
	STATE_GET_ARGS			= 2,
	STATE_WAIT_EXEC			= 3
}CMD_STATE;

typedef struct{
	unsigned char buf[MAX_STRING_BUF];
	uint8_t cnt;
	uint8_t argCnt;
	union{
		//CAMARG_Light light;
		//CAMARG_Motor motor;
		CAMARG_Laser laser;
		CAMARG_ValueParametr parametr;
		CAMARG_Int32 parameter32;
	};
}CAMARG;

typedef struct CAMCMD{
	CMD_Type type;
	uint8_t cnt;
	const char *cmd;
	int32_t (*parse_arg)( unsigned char c, CAMARG *arg );
}CAMCMD;

typedef struct{
	CAMARG arg;
	CMD_STATE state;
	CMD_Type foundCmd;
	CAMCMD cmd[6];
} CAM_COM;




typedef void (* CMD_HANDL_CALLBACK)(CMD_Type cmd, const CAMARG *args );
MCU_Status CAMCMD_Init( CMD_HANDL_CALLBACK callback );//Инициализация, связывание с коллбэком для обработки команды
MCU_Status MCU_HandleByte(unsigned char data); //Разбирает входной поток байт за байтом и ищет в нем команды
void CAMCMD_ProcessMessages( void ); //Обработка поступившых команд


#endif /* MCU_COMMUNICATION_H_ */
