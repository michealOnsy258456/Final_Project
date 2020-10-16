/*
 * UART.h
 *
 *  Created on: Jan 14, 2020
 *      Author: micheal_onsy
 */

#ifndef UART_H_
#define UART_H_
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

//stop bit
typedef enum {
	UART_1StopBit,UART_2StopBit
}UART_StopBit;

// data size
typedef enum {
	UART_5Bit,UART_6Bit,UART_7Bit,UART_8Bit,UART_9Bit=7
}UART_DataSize;

//mode syn or asyn
//0 asyn
//1 syn
typedef enum {
	UART_AsyncNormal,UART_AsyncDouble,UART_Sync
}UART_Mode;

//clock
typedef enum {
	UART_RisingTxD_FallingRxD,UART_RisingRxD_FallingTxD
}UART_ClockPolar;

//parity
typedef enum {
	UART_Disable,Reserved,UART_EvenPar,UART_OddPar
}UART_Parity;


typedef struct{
	UART_StopBit	StopBit;
	UART_DataSize	DataSize;
	UART_Mode		Mode;
	UART_Parity		Parity;


}UART_Config;
void UART_VidInit(UART_Config *a_ptr,uint16 a_BoudRate);
uint8 UART_u8Recive(void);
void UART_VidSend(uint8 a_Data);


#endif /* UART_H_ */
