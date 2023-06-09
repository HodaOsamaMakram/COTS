/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HAL				*************/
/**********		SWC	  : DC_motor		*************/
/**********		Version: 1.00			*************/
/**********		Date: 13/3/2023			*************/
/****************************************************/
/****************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "DC_motor_config.h"
#include "DC_motor_interface.h"
#include "DC_motor_private.h"


void DC_MotorVoidCW(MOTOR_t* Copy_u8Motor)
{
	DIO_u8SetPinValue(Copy_u8Motor->Port,Copy_u8Motor->PinA,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(Copy_u8Motor->Port,Copy_u8Motor->PinB,DIO_u8PIN_HIGH);
}
void DC_MotorVoidCCW(MOTOR_t* Copy_u8Motor)
{
	DIO_u8SetPinValue(Copy_u8Motor->Port,Copy_u8Motor->PinB,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(Copy_u8Motor->Port,Copy_u8Motor->PinA,DIO_u8PIN_HIGH);
}
void DC_MotorVoidStop(MOTOR_t* Copy_u8Motor)
{
	DIO_u8SetPinValue(Copy_u8Motor->Port,Copy_u8Motor->PinA,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(Copy_u8Motor->Port,Copy_u8Motor->PinB,DIO_u8PIN_LOW);
}
