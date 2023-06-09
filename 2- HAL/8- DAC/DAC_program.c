/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HAL				*************/
/**********		SWC	  : DAC				*************/
/**********		Version: 1.00			*************/
/**********		Date: 18/03/2023		*************/
/****************************************************/
/****************************************************/


#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "DAC_config.h"
#include "DAC_interface.h"
#include "DAC_private.h" 

u8 DAC_u8SetAnalogVolt(u16 Copy_u16AnalogVolt)
{
	u8 Local_u8Digital;
	Local_u8Digital = Copy_u16AnalogVolt/STEP;
}