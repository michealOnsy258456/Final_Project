/*
 * LCD.h
 *
 *  Created on: Dec 29, 2019
 *      Author: micheal_onsy
 */

#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"
#include "Micro_Config.h"
#include "common_macros.h"

#define RS PC0
#define RW PC1
#define E  PC2
#define LCD_CTRL_PORT PORTC
#define LCD_CTRL_PORT_DIR DDRC

#define LCD_DATA_PORT PORTB
#define LCD_DATA_PORT_DIR DDRB
#define CLEAR_COMMAND 0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0c
#define SET_CURSOR_LOCATION 0x80


void LCD_VidWriteCommand(uint8 a_command);
void LCD_VidWriteData(uint8 a_data);
void LCD_clearScreen(void);
void LCD_VidInit(void);
void LCD_VidWriteString(const char *Str);
void LCD_VidWriteNumber (uint64 a_Number);
void LCD_VidSetRowColumn(uint8 a_Row,uint8 a_Column);



#endif /* LCD_H_ */
