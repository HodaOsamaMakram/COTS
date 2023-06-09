/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : TIMERS 			*************/
/**********		Version: 1.00			*************/
/**********		Date: 23/03/2023		*************/
/****************************************************/
/****************************************************/

#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

#define FALLING_EDGE	0
#define RISING_EDGE	1


void Timer0_voidInit(void);

u8 Timer0_u8OverflowSetCallBack(void (*Copy_pvCallBackFunc)(void));

void Timer0_voidSetPreload(u8 Copy_u8Preload);

u8 Timer0_u8CompMatchSetCallBack(void (*Copy_pvCallBackFunc)(void));

void Timer1_voidInit(void);

void Timer1_voidSetChannelACompValue(u16 Copy_u16Value);

void Timer1_voidSetPreloadValue(u16 Copy_u16Value);

u16 Timer1_u16ReadTimerValue(void);

void ICU_voidInit(void);

u8 ICU_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));

u8 ICU_u8SetTrigger(u8 Copy_u8TriggerSource);

u16 ICU_u16ReadInputCapture(void);

void ICU_voidInterruptDisable(void);

#endif
