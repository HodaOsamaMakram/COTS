/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : TIMERS 			*************/
/**********		Version: 1.00			*************/
/**********		Date: 23/03/2023		*************/
/****************************************************/
/****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMERS_interface.h"
#include "TIMERS_config.h"
#include "TIMERS_register.h"
#include "TIMERS_private.h"

/*global pointer to function to hold the callback function address*/
static void (*Timer0_pvOverflowCallBackFunc)(void) =NULL;
static void (*Timer0_pvCompMatchCallBackFunc)(void) =NULL;
static void (*ICU_pvCallBackFunc)(void) =NULL;


void Timer0_voidInit(void)
{
	/*Initialize waveform generation mode to work as normal mode*/
	//	CLR_BIT(TCCR0,TCCR0_WGM00);
	//	CLR_BIT(TCCR0,TCCR0_WGM01);

	/*Initialize waveform generation mode to work as PWM mode*/
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*Output Compare match mode: set on top, clear on compare*/
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);


	//	/*Initialize waveform generation mode to work as CTC mode*/
	//		CLR_BIT(TCCR0,TCCR0_WGM00);
	//		SET_BIT(TCCR0,TCCR0_WGM01);

	/*Set the required Compare match value*/
	OCR0=TIMER0_u8COM_MATCH_VAL;

	/*Set the required preload */
	//TCNT0=TIMER0_u8PRELOAD_VAL;

	/*Timer0 Overflow interrupt enable*/
	//SET_BIT(TIMSK,TIMSK_TOIE0);

	//	/*Timer0 Compare match interrupt enable*/
	//	 SET_BIT(TIMSK,TIMSK_OCIE0);

	/*Set the required prescaler */
	TCCR0 &= TIMER0_PRESCALER_MASK;
	TCCR0 |= TIMER0_u8PRESCALER;
}

u8 Timer0_u8OverflowSetCallBack(void (*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL)
	{
		Timer0_pvOverflowCallBackFunc=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}
void Timer0_voidSetPreload(u8 Copy_u8Preload)
{
	TCNT0 =Copy_u8Preload;
}


u8 Timer0_u8CompMatchSetCallBack(void (*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL)
	{
		Timer0_pvCompMatchCallBackFunc=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}



void Timer1_voidInit(void)
{
	//	/*Compare match Output mode: set on top, clear on compare(non-inverted)*/
	//	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	//	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	//	/*Waveform generation mode: fast PWM with ICR1 as top value*/
	//	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	//	SET_BIT(TCCR1A,TCCR1A_WGM11);
	//	SET_BIT(TCCR1B,TCCR1B_WGM12);
	//	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*Waveform generation mode: normal mode*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);

	//	/*Set top value*/
	//	ICR1=20000;


	//	/*Compare match value: range between 750 to 2500*/
	//	OCR1A=750;

	/*Set prescaler: divided by 8*/
	CLR_BIT(TCCR1B,TCCR1B_CS12);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS10);
}

void Timer1_voidSetChannelACompValue(u16 Copy_u16Value)
{
	OCR1A=Copy_u16Value;
}

void Timer1_voidSetPreloadValue(u16 Copy_u16Value)
{
	TCNT1=Copy_u16Value;
}

u16 Timer1_u16ReadTimerValue(void)
{
	return TCNT1;
}

void ICU_voidInit(void)
{
	/*Set trigger to rising_edge initially*/
	SET_BIT(TCCR1B,TCCR1B_ICES1);

	/*Enable the ICU interrupt*/
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

u8 ICU_u8SetCallBack(void(*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL)
	{
		ICU_pvCallBackFunc=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}

u8 ICU_u8SetTrigger(u8 Copy_u8TriggerSource)
{
	u8  Local_u8ErrorState=OK;
	switch(Copy_u8TriggerSource)
	{
	case FALLING_EDGE : CLR_BIT(TCCR1B,TCCR1B_ICES1);break;
	case RISING_EDGE :SET_BIT(TCCR1B,TCCR1B_ICES1);break;
	default :Local_u8ErrorState=NOK;break;
	}

	return Local_u8ErrorState;
}

u16 ICU_u16ReadInputCapture(void)
{
	return 	ICR1;
}

void ICU_voidInterruptDisable(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

/*ISR of ICU */
void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if(ICU_pvCallBackFunc!=NULL)
	{
		ICU_pvCallBackFunc();
	}
	else
	{
		/*Do nothing*/
	}
}

/*Timer0 Over flow ISR*/
void __vector_11 (void)  __attribute__((signal));
void __vector_11 (void)
{
	if(Timer0_pvOverflowCallBackFunc!=NULL)
	{
		Timer0_pvOverflowCallBackFunc();
	}
	else
	{
		/*Do nothing*/
	}
}
/*Timer0 Compare Match ISR*/
void __vector_10 (void)  __attribute__((signal));
void __vector_10 (void)
{
	if(Timer0_pvCompMatchCallBackFunc!=NULL)
	{
		Timer0_pvCompMatchCallBackFunc();
	}
	else
	{
		/*Do nothing*/
	}
}


