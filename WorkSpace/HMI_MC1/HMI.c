/*
 * main.c
 *
 *  Created on: Jan 14, 2020
 *      Author: micheal_onsy
 */

#include "UART.h"
#include "Keypad.h"
#include "lcd.h"
#include "Timer1.h"
#define M2_READY 0x10
#define M3_READY 0x15
/**********************************PROTOTYPE**************************************/
void  APP_U8_Print_Number();
void APP_U8_Enter_PassWord (uint8 a_U8Flag);
uint8 App_Vid_Check_Password(uint8 a_U8CheckPassWord,uint8 a_U8Flag);
void APP_VidTIMER(void);
/**********************************Global Variables ******************************/
uint8 g_flag=0;
uint8 g_flag1=0;
int main(void)
{
	/*****************************Local Variables************************************/
	uint8 LOC_U8Flag=0;
	uint8 LOC_U8Flag1=0;
	uint8 LOC_u8BuzzerFlag=0;
	uint8 LOC_U8Receive_Data_From_Uart=0;


	/***************************Configuration*********************************/
	/*UART*/
	UART_Config config={UART_2StopBit,UART_8Bit,UART_AsyncDouble,UART_Disable};
	UART_VidInit(&config,9600); // initialize UART driver
	/*LCD*/
	LCD_VidInit(); // initialize LCD driver
	/*Timer*/
	TIM1_Config Config={CTC,F_CLK_1024,OC1A_OFF};
	TIMER1_VidInit(&Config ,0,62500);
	TIMER1_CTC_SetCallBack(APP_VidTIMER);
/*****************************wait until MC2 is ready************************/
	while(UART_u8Recive() != M2_READY){} // wait until MC2 is ready

	while(1)
	{
		/*Enter First Number And Second Number And Go To Next Step*/
		while(LOC_U8Flag==0)
		{
			APP_U8_Enter_PassWord(0);
			APP_U8_Print_Number();//1LOOP
			APP_U8_Enter_PassWord(1);
			APP_U8_Print_Number();//2LOOP
			LOC_U8Flag=1;
		}
		/*1-Receive Data From UART
		 *2-Check Data IF True Go Next Step Else Repeat
		 * */
		while(LOC_U8Flag==1)
		{
			LOC_U8Receive_Data_From_Uart=UART_u8Recive();//3
			LOC_U8Flag=App_Vid_Check_Password(LOC_U8Receive_Data_From_Uart,0);
			if(LOC_U8Flag==2)
				UART_VidSend(1);//4
			else
				UART_VidSend(0);//4
		}
		/*
		 *1-Choose OPen Door Or Change Password
		 **/
		while(LOC_U8Flag==2)
		{
			LCD_clearScreen();
			LCD_VidSetRowColumn(1,1);
			LCD_VidWriteString("* Open Door");
			LCD_VidSetRowColumn(2,1);
			LCD_VidWriteString("# Change PassWord");
			LOC_U8Flag1=KeyPad_getPressedKey();
			LCD_VidWriteNumber(LOC_U8Flag1);
			/*1-if Pressed '*' Enter Your Password To Open The Door
			 *2-True Go Next Step
			 *3-False Repeat To choose Open Door Or Change Password
			 **/
			if(LOC_U8Flag1=='*')
			{
				UART_VidSend('*');//5
				LCD_clearScreen();
				LCD_VidWriteString("Please Enter Pass ");
				APP_U8_Print_Number();//6LOOP
				_delay_ms(60);
				LOC_U8Receive_Data_From_Uart=UART_u8Recive();//7
				LOC_U8Flag1=App_Vid_Check_Password(LOC_U8Receive_Data_From_Uart,0);
				if(LOC_U8Flag1==2)
				{
					UART_VidSend(1);//8
					LOC_U8Flag=3;
				}
				else
				{
					UART_VidSend(0);//8
					LOC_U8Flag=2;
				}
			}
			/*1-if Pressed '#' Enter Your Old Password To Change Password
			 *2-True -> Go Next Step
			 *3-else -> Repeat And When The Counter Is To 3 Make The Alarm
			 **/
			else if(LOC_U8Flag1=='#')
			{
				UART_VidSend('#');//5
				LCD_clearScreen();
				LCD_VidWriteString("Please Enter Old PassWord");
				APP_U8_Print_Number();//10LOOP
				_delay_ms(60);
				LOC_U8Receive_Data_From_Uart=UART_u8Recive();//11
				LOC_U8Flag1=App_Vid_Check_Password(LOC_U8Receive_Data_From_Uart,0);
				if(LOC_U8Flag1==2)
				{
					UART_VidSend(1);//12
					LOC_U8Flag=4;
					LOC_u8BuzzerFlag=0;

				}
				else
				{
					UART_VidSend(0);//12
					LOC_U8Flag=2;
					LOC_u8BuzzerFlag++;
				}
				if(LOC_u8BuzzerFlag==3)
				{
					LCD_clearScreen();
					LCD_VidSetRowColumn(1,6);
					LCD_VidWriteString("burglar");
					for(LOC_U8Flag1=1;LOC_U8Flag1<=10;LOC_U8Flag1++)
						_delay_ms(6000);
					LOC_u8BuzzerFlag=0;
					LOC_U8Flag1=0;
				}
			}
		}
		/*
		 *1-Will OPen Door To 15 Second And Close 15 Second
		 **/
		while(LOC_U8Flag==3)
		{
			TCNT1=0;
			sei();
			while(g_flag1==0)
			{

			}
			g_flag1=0;
			CLEAR_BIT(SREG,7);
			LOC_U8Flag=2;
		}
		/*
		 *1-Will Enter The New Password Twice And Save The New Password
		 **/
		while(LOC_U8Flag==4)
		{
			LOC_U8Flag=5;
			while(LOC_U8Flag==5)
			{
				APP_U8_Enter_PassWord(0);
				APP_U8_Print_Number();//13LOOP
				APP_U8_Enter_PassWord(0);
				APP_U8_Print_Number();//14LOOP
				LOC_U8Flag=6;
			}
			while(LOC_U8Flag==6)
			{
				LOC_U8Receive_Data_From_Uart=UART_u8Recive();//15
				LOC_U8Flag=App_Vid_Check_Password(LOC_U8Receive_Data_From_Uart,1);
				if(LOC_U8Flag==2)
					UART_VidSend(1);//16
				else
					UART_VidSend(0);//16

				LOC_U8Flag=2;

			}
		}
	}
}


/*****************************Function***********************************/
/*Function To Take Number From Keypad */
void  APP_U8_Print_Number()
{
	uint8 i ,LOC_U8Pass;
	for(i =0;i<5;i++)
	{
		LCD_VidSetRowColumn(2,i+1);
		LOC_U8Pass=KeyPad_getPressedKey();
		LCD_VidWriteString("*");
		UART_VidSend(LOC_U8Pass);
		while(i==4)
		{
			if(KeyPad_getPressedKey()=='+')
				return;
		}

	}
}
/*Function Write On LCD "Please Enter Password"*/
void APP_U8_Enter_PassWord (uint8 a_U8Flag)
{
	if(a_U8Flag==0)
	{
		LCD_clearScreen();
		LCD_VidWriteString("Please Enter Pass ");
	}
	else if (a_U8Flag==1)
	{
		LCD_clearScreen();
		LCD_VidWriteString("Please Renter Same Pass ");
	}
}
/*Function To Chick Password If True  Return '2' else Return 0*/
uint8 App_Vid_Check_Password(uint8 a_U8CheckPassWord,uint8 a_U8Flag)
{
	if(a_U8CheckPassWord==25)
	{
		LCD_clearScreen();
		LCD_VidSetRowColumn(1,1);
		LCD_VidWriteString("PassWord Is Success");
		_delay_ms(2000);
		a_U8CheckPassWord=2;
	}
	else if (a_U8CheckPassWord!=25)
	{
		LCD_clearScreen();
		LCD_VidSetRowColumn(1,4);
		LCD_VidWriteString("Not Success");
		if(a_U8Flag==0)
		{
			LCD_VidSetRowColumn(2,2);
			LCD_VidWriteString("Repeat PassWord");
			_delay_ms(2000);
		}
		a_U8CheckPassWord=0;
	}
	return a_U8CheckPassWord;
}
/*Function To Count Timer*/
void APP_VidTIMER(void)
{
	g_flag++;
	if(g_flag==5)
	{
		g_flag=0;
		g_flag1=1;
	}
	if(g_flag==1)
	{
		LCD_clearScreen();
		LCD_VidSetRowColumn(1,5);
		LCD_VidWriteString("Door UNLOCK");
	}
	else if (g_flag==3)
	{
		LCD_clearScreen();
		LCD_VidSetRowColumn(1,5);
		LCD_VidWriteString("Door LOCK");

	}
}

