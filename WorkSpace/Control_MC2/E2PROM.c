/*
 * E2PROM.c
 *
 *  Created on: Jan 20, 2020
 *      Author: micheal_onsy
 */

#include "E2PROM.h"
#include "I2C.h"


void E2PROM_VidInit()
{
	I2C_VidInit();
}

void E2PROM_VidWrite(uint16 a_u16Address,uint8 a_u8Data)
{
	I2C_VidStartCondition();
	if (I2C_u8GetStatus()!=TW_START)
		return ;
	I2C_vidWrite((uint8) (0xA0|((a_u16Address& 0x0700)>>7)));
	if (I2C_u8GetStatus()!=TW_MT_SLA_W_ACK)
		return ;
	I2C_vidWrite((uint8)( a_u16Address));
	if (I2C_u8GetStatus()!=TW_MT_DATA_ACK)
		return ;
	I2C_vidWrite(a_u8Data);
	if (I2C_u8GetStatus()!=TW_MT_DATA_ACK)
		return ;
	I2C_VidStopCondition();
}


void E2PROM_VidRead(uint16 a_u16Address,uint8 * a_u8Data)
{

	I2C_VidStartCondition();
	if (I2C_u8GetStatus()!=TW_START)
		return ;

	I2C_vidWrite((uint8) 0xA0|((a_u16Address& 0x0700)>>7));
	if (I2C_u8GetStatus()!=TW_MT_SLA_W_ACK)
		return ;

	I2C_vidWrite((uint8)( a_u16Address));
	if (I2C_u8GetStatus()!=TW_MT_DATA_ACK)
		return ;

	I2C_VidStartCondition();
	if (I2C_u8GetStatus()!=TW_REP_START)
		return ;

	I2C_vidWrite((uint8) 0xA0|(((a_u16Address& 0x0700)>>7)|1));
	if (I2C_u8GetStatus()!=TW_MT_SLA_R_ACK)
		return ;

	*a_u8Data=I2C_VidReadWithNoAcknowledge();
	if (I2C_u8GetStatus()!=TW_MR_DATA_NACK)
		return ;

	I2C_VidStopCondition();
}

