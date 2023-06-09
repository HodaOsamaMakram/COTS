/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HAL				*************/
/**********		SWC	  : Stepper			*************/
/**********		Version: 1.00			*************/
/**********		Date: 15/03/2023		*************/
/****************************************************/
/****************************************************/
#include <util/delay.h>

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "Stepper_config.h"
#include "Stepper_interface.h"
#include "Stepper_private.h"

void Stepper_voidSetAngle_Dir(Stepper_t* Copy_u8Stepper,u32 Copy_u32Angle,u8 Copy_Direction)

{
	u16 Local_u16Steps=(2048UL * (u32) Copy_u32Angle)/360UL;

	u16 Local_u6Counter;

	if (Copy_Direction==CW)
	{
		for(Local_u6Counter=0;Local_u6Counter<Local_u16Steps/4;Local_u6Counter++)
		{

			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Blue,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Pink,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Yellow,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Orange,DIO_u8PIN_HIGH);
			_delay_ms(2);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Blue,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Pink,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Yellow,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Orange,DIO_u8PIN_HIGH);
			_delay_ms(2);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Blue,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Pink,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Yellow,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Orange,DIO_u8PIN_HIGH);
			_delay_ms(2);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Blue,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Pink,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Yellow,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Orange,DIO_u8PIN_LOW);
			_delay_ms(2);
		}
	}else if(Copy_Direction==CCW)
	{
		for(Local_u6Counter=0;Local_u6Counter<Local_u16Steps/4;Local_u6Counter++)
		{
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Blue,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Pink,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Yellow,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Orange,DIO_u8PIN_LOW);
			_delay_ms(2);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Blue,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Pink,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Yellow,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Orange,DIO_u8PIN_HIGH);
			_delay_ms(2);

			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Blue,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Pink,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Yellow,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Orange,DIO_u8PIN_HIGH);
			_delay_ms(2);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Blue,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Pink,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Yellow,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(Copy_u8Stepper->Port,Copy_u8Stepper->Pin_Orange,DIO_u8PIN_HIGH);
			_delay_ms(2);

		}
	}

}
