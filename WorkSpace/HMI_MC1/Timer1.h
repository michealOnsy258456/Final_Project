/*
 * Timer1.h
 *
 *  Created on: Jan 15, 2020
 *      Author: micheal_onsy
 */

#ifndef TIMER1_H_
#define TIMER1_H_


#include"micro_config.h"
#include"std_types.h"
#include"common_macros.h"


typedef enum {
	NORMAL,CTC,PWM
}TIM1_Mode;

typedef enum {
	NO_CLK,F_CLK_CPU,F_CLK_8,F_CLK_64,F_CLK_256,F_CLK_1024
}TIM1_Clock;


typedef enum {
	OC1A_OFF,OC1A_TOG,OC1A_CLR,OC1A_SET
}TIM1_OC1A;




typedef struct
{
	TIM1_Mode mode;
	TIM1_Clock Clk;
	TIM1_OC1A Oc1A;
}TIM1_Config;


/*FUNCTIONS PROTOTYPE*/
void TIMER1_VidInit(TIM1_Config * a_ptr,uint16 a_SetInitialValue,uint16 a_SetCompare);
void TIMER1_CTC_setCompValue(uint8 a_SetCompare);
void TIMER1_OVF_setInitialVal(uint16 a_setInitialVal);
void TIMER1_CTC_SetCallBack(void (*a_callBackPtr)(void));
void TIMER1_OVF_SetCallBack(void (*a_callBackPtr)(void));


#endif /* TIMER1_H_ */
