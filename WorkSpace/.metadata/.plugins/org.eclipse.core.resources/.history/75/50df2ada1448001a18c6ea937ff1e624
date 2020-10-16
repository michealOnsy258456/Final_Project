/*
 * LCD.c
 *
 *  Created on: Dec 29, 2019
 *      Author: micheal_onsy
 */
#include "LCD.h"

void LCD_VidInit(void)
{
	LCD_DATA_PORT_DIR=0xff;
	LCD_CTRL_PORT_DIR |=(1<<RS)|(1<<RW)|(1<<E);

	LCD_VidWriteCommand(TWO_LINE_LCD_Eight_BIT_MODE);
	LCD_VidWriteCommand(CURSOR_OFF);
	LCD_clearScreen();
}
void LCD_VidWriteCommand(uint8 a_command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT=a_command;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}
void LCD_VidWriteData(uint8 a_data)
{
	SET_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT=a_data;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}

void LCD_clearScreen(void)
{
	LCD_VidWriteCommand(CLEAR_COMMAND);
}

void LCD_VidWriteString(const char *Str)
{
	while((*Str) != '\0')
	{
		LCD_VidWriteData(*Str);
		Str++;
	}
}
void LCD_VidSetRowColumn(uint8 a_Row,uint8 a_Column)
{
	uint8 LOC_u8Address ;
	switch(a_Row)
	{
	case 1:
		LOC_u8Address=a_Column-1;
		break;
	case 2:
		LOC_u8Address=0x40+a_Column-1;
		break;
	case 3:
		LOC_u8Address=0x10+a_Column-1;
		break;
	case 4:
		LOC_u8Address=0x50+a_Column-1;
		break;


	}
	LCD_VidWriteCommand(SET_CURSOR_LOCATION|LOC_u8Address);
}
void LCD_VidWriteNumber (uint64 a_Number)
{
	uint64 reversed=1;
	if(a_Number==0)
	{
		LCD_VidWriteData('0');
	}
	while(a_Number != 0)
	{
		reversed = (reversed * 10)+(a_Number%10);

		a_Number/=10;
	}
	while(reversed != 1)
	{
		LCD_VidWriteData((reversed%10)+48);
		reversed /= 10;
	}
}
