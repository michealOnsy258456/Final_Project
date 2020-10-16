/*
 * UART.c
 *
 *  Created on: Jan 14, 2020
 *      Author: micheal_onsy
 */
#include "UART.h"

void UART_VidInit(UART_Config *a_ptr,uint16 a_BoudRate)
{
	// Enable Transmit
	SET_BIT(UCSRB,TXEN);
	//Enable Receive
	SET_BIT(UCSRB,RXEN);
	/*
	 * if
	 * Synchronous & ClockParity
	 * else
	 * No code in UART_AsyncNormal U2x=0 UMSEL=0
	 * else
	 * in UART_AsyncDouble set bit U2X
	 *  */
	UCSRC|= (1<<URSEL);//To Write in Register UCSRC
	/*
	 if (a_ptr->Mode==UART_Sync)
	{
		UCSRC|=(1<<UMSEL);
		UCSRC= (UCSRC & 0xFE) | ((a_ptr->Clock)<<UCPOL);
		// Character Size
		UCSRC=(UCSRC & 0xF9)|(((a_ptr->DataSize) & 0x03)<<UCSZ0);
		UCSRB=(UCSRB & 0xFB)|((((a_ptr->DataSize) & 0x04)>>2)<<UCSZ2);

	}
	 */
	if (a_ptr->Mode==UART_AsyncDouble)
	{
		UCSRA |=  (1<<U2X);
	}

	if (a_ptr->Mode != UART_Sync)
	{
		//parity
		UCSRC=(UCSRC & 0xCF)|((a_ptr->Parity)<<UPM0);
		//StopBit
		UCSRC|=(a_ptr->StopBit)<<USBS;
		// Character Size
		UCSRC=(UCSRC & 0xF9)|(((a_ptr->DataSize) & 0x03)<<UCSZ0);
		UCSRB=(UCSRB & 0xFB)|(((a_ptr->DataSize) & 0x04)<<UCSZ2);
	}
	/*
	if (a_ptr->Mode != UART_Sync)
	{
		//StopBit
		UCSRC|=(a_ptr->StopBit)<<USBS;
	}
	if (a_ptr->Mode != UART_Sync)
	{
		// Character Size
		UCSRC=(UCSRC & 0xF9)|(((a_ptr->DataSize) & 0x03)<<UCSZ0);
		UCSRB=(UCSRB & 0xFB)|(((a_ptr->DataSize) & 0x04)<<UCSZ2);
	}
	 */

	//BoudRate
	if (a_ptr->Mode == UART_AsyncNormal)
	{
		a_BoudRate= ((float32)F_CPU/(16*a_BoudRate))-1;
	}
	else if (a_ptr->Mode == UART_AsyncDouble)
	{
		a_BoudRate= ((float32)F_CPU/(8*a_BoudRate))-1;
	}
	else if (a_ptr->Mode == UART_Sync)
	{
		a_BoudRate= ((float32)F_CPU/(2*a_BoudRate))-1;
	}

	UCSRC&=~(1<<URSEL);
	UBRRL=a_BoudRate;
	UBRRH=(a_BoudRate>>8);

}
uint8 UART_u8Recive(void)
{
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}
void UART_VidSend(uint8 a_Data)
{
	UDR=a_Data;
	while(!(UCSRA & (1<<UDRE)));
}

