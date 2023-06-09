/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HAL 			*************/
/**********		SWC	  : SSD				*************/
/**********		Version: 1.00			*************/
/**********		Date: 17/02/2023		*************/
/****************************************************/
/****************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "SSD_config.h"
#include "SSD_interface.h"
#include "SSD_private.h"

u8 SSD_u8SetNum(SSD_t* Copy_u8SSD,u8 num )
{
static u8 SSDARR[10]={0b00111111,  	// 0
					0b000000110,	// 1
					0b01011011,		// 2
					0b01001111,		// 3
					0b01100110,		// 4
					0b01101101,		// 5
					0b01111101,		// 6
					0b00000111,		// 7
					0b01111111,		// 8
					0b01101111};	// 9

	u8 Local_u8ErrorState=OK;

	if(Copy_u8SSD->type==CATHODE)
	{
		DIO_u8SetPortValue(Copy_u8SSD->port,~SSDARR[num]);
	}
	else if(Copy_u8SSD->type==ANODE)
	{
		DIO_u8SetPortValue(Copy_u8SSD->port,SSDARR[num]);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;

}

u8 SSD_u8On(SSD_t* Copy_u8SSD)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_u8SSD->type==CATHODE)
		{
			DIO_u8SetPinValue(Copy_u8SSD->en_port,Copy_u8SSD->en_pin,DIO_u8PIN_LOW);
		}
		else if(Copy_u8SSD->type==ANODE)
		{
			DIO_u8SetPinValue(Copy_u8SSD->en_port,Copy_u8SSD->en_pin,DIO_u8PIN_HIGH);
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	return Local_u8ErrorState;
}

u8 SSD_u8Off(SSD_t* Copy_u8SSD)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_u8SSD->type==CATHODE)
		{
			DIO_u8SetPinValue(Copy_u8SSD->en_port,Copy_u8SSD->en_pin,DIO_u8PIN_HIGH);
		}
		else if(Copy_u8SSD->type==ANODE)
		{
			DIO_u8SetPinValue(Copy_u8SSD->en_port,Copy_u8SSD->en_pin,DIO_u8PIN_LOW);
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	return Local_u8ErrorState;
}
