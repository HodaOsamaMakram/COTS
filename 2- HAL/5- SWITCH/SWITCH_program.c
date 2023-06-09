/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HCAL			*************/
/**********		SWC	  : SWITCH			*************/
/**********		Version: 1.00			*************/
/**********		Date: 16/02/2023		*************/
/****************************************************/
/****************************************************/
#include "STD_TYPES.h"

#include "DIO_interface.h"


#include "SWITCH_config.h"
#include "SWITCH_interface.h"
#include "SWITCH_private.h"

u8 SW_u8GetState(SW_t* Copy_sw)
{
	u8 Local_u8State,Local_u8Result;
	DIO_u8GetPinValue(Copy_sw->port,Copy_sw->pin,&Local_u8State);
	if(Copy_sw->pull_type==PULL_UP)
	{
		if(Local_u8State==DIO_u8PIN_HIGH)
		{
			Local_u8Result=NOT_PRESSED;
		}
		else Local_u8Result=PRESSED;

	}
	else if(Copy_sw->pull_type==PULL_DOWN)
	{
		if(Local_u8State==DIO_u8PIN_LOW)
		{
			Local_u8Result=NOT_PRESSED;
		}
		else Local_u8Result=PRESSED;

	}
	return Local_u8Result;
}
