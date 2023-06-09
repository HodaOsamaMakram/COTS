/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : WATCHDOG 		*************/
/**********		Version: 1.00			*************/
/**********		Date: 26/03/2023		*************/
/****************************************************/
/****************************************************/
#ifndef WATCHDOG_REGISTER_H_
#define WATCHDOG_REGISTER_H_

#define WDTCR			*((volatile u8*)0x41)		/*Watch dog timer control register*/
#define WDTCR_WDTDE			4						/*Watchdog turn off enable*/
#define WDTCR_WDE			3						/*Watchdog enable*/

#endif
