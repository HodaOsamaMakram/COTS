/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : WATCHDOG 		*************/
/**********		Version: 1.00			*************/
/**********		Date: 26/03/2023		*************/
/****************************************************/
/****************************************************/
#ifndef WATCHDOG_INTERFACE_H_
#define WATCHDOG_INTERFACE_H_

void WDT_voidEnable(void);

void WDT_voidDisable(void);

u8 WDT_u8Sleep(u8 Copy_u8SleepTime);


#endif