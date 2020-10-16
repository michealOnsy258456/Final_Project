/*
 * I2C.c
 *
 *  Created on: Jan 20, 2020
 *      Author: micheal_onsy
 */

#include "I2C.h"

void I2C_VidInit()
{
	/*Bit Rate = 400 kbps   TWPS=00   F_CPU=8MHZ*/
	TWSR = 0;
	TWBR=0x02;
	/* address when he become slave 0b00000010*/
	TWAR=0b00000010;
	/*enable I2C*/
	TWCR=(1<<TWEN);
}

void I2C_VidStartCondition()
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT));
}

void I2C_VidStopCondition()
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void I2C_vidWrite(uint8 a_Data)
{
	TWDR=a_Data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 I2C_VidReadWithAcknowledge()
{
	TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

uint8 I2C_VidReadWithNoAcknowledge()
{
	TWCR=(1<<TWINT)|(1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

uint8 I2C_u8GetStatus()
{
	uint8 Status;
	Status = TWSR & 0xF8;
	return Status;
}


