/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : WATCHDOG 		*************/
/**********		Version: 1.00			*************/
/**********		Date: 26/03/2023		*************/
/****************************************************/
/****************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include "WATCHDOG_register.h"
#include "WATCHDOG_interface.h"
#include"WATCHDOG_private.h"
#include"WATCHDOG_config.h"

void WDT_voidEnable(void)
{
	SET_BIT(WDTCR,WDTCR_WDE);
}

void WDT_voidDisable(void)
{
	WDTCR= (1<<WDTCR_WDTDE) | (1<<WDTCR_WDE);
	WDTCR=0;
}

u8 WDT_u8Sleep(u8 Copy_u8SleepTime)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_u8SleepTime<8)
	{
		WDTCR &= WDT_PRESCALER_MASK;
		WDTCR |=Copy_u8SleepTime;

	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
