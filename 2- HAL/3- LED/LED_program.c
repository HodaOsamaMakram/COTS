/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HCAL			*************/
/**********		SWC	  : LED				*************/
/**********		Version: 1.00			*************/
/**********		Date: 16/02/2023		*************/
/****************************************************/
/****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "LED_interface.h"
#include "LED_config.h"
#include "LED_private.h"

u8 LED_u8On(LED_t* Copy_u8Led)
{
	u8 Local_u8ErrorState=OK;

	if(Copy_u8Led->Type==SOURCE)
	{
		DIO_u8SetPinValue(Copy_u8Led->Port,Copy_u8Led->Pin,DIO_u8PIN_HIGH);
	}
	else if(Copy_u8Led->Type==SINK)
	{
		DIO_u8SetPinValue(Copy_u8Led->Port,Copy_u8Led->Pin,DIO_u8PIN_LOW);

	}
	else Local_u8ErrorState=NOK;

	return Local_u8ErrorState;

}

u8 LED_u8Off(LED_t* Copy_u8Led)
{
	u8 Local_u8ErrorState=OK;

	if(Copy_u8Led->Type==SOURCE)
	{
		DIO_u8SetPinValue(Copy_u8Led->Port,Copy_u8Led->Pin,DIO_u8PIN_LOW);
	}
	else if(Copy_u8Led->Type==SINK)
	{
		DIO_u8SetPinValue(Copy_u8Led->Port,Copy_u8Led->Pin,DIO_u8PIN_HIGH);

	}
	else Local_u8ErrorState=NOK;

	return Local_u8ErrorState;

}

u8 LED_u8Tgl(LED_t* Copy_u8Led)
{
	u8 Local_u8ErrorState=OK;

	Local_u8ErrorState=DIO_u8TgLPinValue(Copy_u8Led->Port,Copy_u8Led->Pin);

	return Local_u8ErrorState;

}
