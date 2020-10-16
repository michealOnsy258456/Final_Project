/*
 * Timer1.c
 *
 *  Created on: Jan 15, 2020
 *      Author: micheal_onsy
 */
#include "Timer1.h"
static void (*g_timer1ctcCallBackPtr)(void)=NULL_PTR;
static void (*g_timer1ovfCallBackPtr)(void)=NULL_PTR;

ISR(TIMER1_OVF_vect)
{
	if(g_timer1ovfCallBackPtr!=NULL_PTR)
	{
		(*g_timer1ovfCallBackPtr)();
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_timer1ctcCallBackPtr!=NULL_PTR)
	{
		(*g_timer1ctcCallBackPtr)();
	}
}
void TIMER1_VidInit(TIM1_Config * a_ptr,uint16 a_SetInitialValue,uint16 a_SetCompare)
{
	if((a_ptr->mode)==NORMAL)
	{
		TCNT1=a_SetInitialValue;
		TCCR1A=(1<<FOC1A)|(1<<FOC1B);
		TCCR1B=(TCCR1B & 0xF8)|(a_ptr->Clk);
		TIMSK=(1<<TOIE1);
	}
	else if((a_ptr->mode)==CTC)
	{
		if (a_ptr->Oc1A==OC1A_OFF)
		{
			TCCR1A &= ~(1<<COM1A1)&(~(1<<COM1A0))&(~(1<<COM1B1))&(~(1<<COM1B0));
		}
		else if(a_ptr->Oc1A==OC1A_TOG)
		{
			TCCR1A &= ~(1<<COM1A1)&(~(1<<COM1B1));
			TCCR1A |= (1<<COM1A0)|(1<<COM1B0);
		}
		else if(a_ptr->Oc1A==OC1A_CLR)
		{
			TCCR1A &= ~(1<<COM1A0)&(~(1<<COM1B0));
			TCCR1A |= (1<<COM1A1)|(1<<COM1B1);
		}
		else if(a_ptr->Oc1A==OC1A_CLR)
		{
			TCCR1A |= (1<<COM1A1)|(1<<COM1A0)|(1<<COM1B1)|(1<<COM1B0);
		}
		TCCR1A|=(1<<FOC1A)|(1<<FOC1B);
		TCCR1B=(TCCR1B & 0xF8)|(a_ptr->Clk);
		TCNT1=a_SetInitialValue;
		SET_BIT(TIMSK,OCIE1A);
		SET_BIT(DDRD,PD5);
		TCCR1B|=(1<<WGM12);
		OCR1A=a_SetCompare;
		TIMSK= (1<<OCIE1A);
	}
	else if((a_ptr->mode)==PWM)
	{
		if (a_ptr->Oc1A==OC1A_OFF)
		{
			TCCR1A &= ~(1<<COM1A1)&(~(1<<COM1A0))&(~(1<<COM1B1))&(~(1<<COM1B0));
		}
		else if(a_ptr->Oc1A==OC1A_TOG)
		{
			TCCR1A &= ~(1<<COM1A1)&(~(1<<COM1B1));
			TCCR1A |= (1<<COM1A0)|(1<<COM1B0);
		}
		else if(a_ptr->Oc1A==OC1A_CLR)
		{
			TCCR1A &= ~(1<<COM1A0)&(~(1<<COM1B0));
			TCCR1A |= (1<<COM1A1)|(1<<COM1B1);
		}
		else if(a_ptr->Oc1A==OC1A_SET)
		{
			TCCR1A |= (1<<COM1A1)|(1<<COM1A0)|(1<<COM1B1)|(1<<COM1B0);
		}
		TCCR1B=(TCCR1B & 0xF8)|(a_ptr->Clk);
		OCR1A=a_SetCompare;
		TCNT1=a_SetInitialValue;
		TCCR1A |=(1<<WGM11)|(1<<WGM10);
		TCCR1B|=(1<<WGM12)|(1<<WGM13);
		DDRD|=(1<<PD5);

	}
}


void TIMER1_OVF_setInitialVal(uint16 a_setInitialVal)
{
	TCNT1= a_setInitialVal;
}

void TIMER1_CTC_setCompValue(uint8 a_SetCompare)
{
	OCR1A=a_SetCompare;
}


void TIMER1_CTC_SetCallBack(void (*a_callBackPtr)(void))
{
	g_timer1ctcCallBackPtr=a_callBackPtr;
}

void TIMER1_OVF_SetCallBack(void (*a_callBackPtr)(void))
{
	g_timer1ovfCallBackPtr=a_callBackPtr;
}
