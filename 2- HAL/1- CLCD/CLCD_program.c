/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HCAL			*************/
/**********		SWC	  : CLCD			*************/
/**********		Version: 1.00			*************/
/**********		Date: 29/12/2022		*************/
/****************************************************/
/****************************************************/

#include"STD_TYPES.h"
#include<util/delay.h>

#include"DIO_interface.h"

#include"CLCD_config.h"
#include"CLCD_interface.h"
#include"CLCD_private.h"

void CLCD_voidSendCommand(u8 copy_u8command)
{
	/*1- set RS to low: for command */
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);

	/*2- set RW pin to low: for write */
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*3- Send the command*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8command);

	/*4- Send the enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);



}

void CLCD_voidSendData(u8 copy_u8Data)
{
	/*1- set RS to high: for data */
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);

	/*2- set RW pin to low: for write */
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*3- Send the data*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8Data);

	/*4- Send the enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	/*delay for execution time*/
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}

void CLCD_voidInit(void)
{
	/*1- wait for more than 30ms*/
	_delay_ms(40);

	/*2- Function set command: 2 Lines_pin3, 5x7 Font size_pin2 */
	CLCD_voidSendCommand(0b00111000);

	/*3- Display on/off control_last 3 pins : display on, cursor on, blink cursor off */
	CLCD_voidSendCommand(0b00001110);

	/*4- Display clear */
	CLCD_voidSendCommand(1);

}

void CLCD_voidSendString(const char* copy_pchString )
{
	u8 Local_u8Counter=0;
	while(copy_pchString[Local_u8Counter]!='\0')//or *copy_pchString!=\0
	{
		CLCD_voidSendData(copy_pchString[Local_u8Counter]);
		Local_u8Counter++;
	}

}

void CLCD_voidGoToXY(u8 Copy_u8XPos, u8 Copy_u8Ypos)
{
	u8 Local_u8DDRAMAddress;
	if(Copy_u8Ypos==0)
	{
		/*if first line*/
		Local_u8DDRAMAddress=Copy_u8XPos;
	}
	else if(Copy_u8Ypos==1)
	{
		/*if second line*/
		Local_u8DDRAMAddress=0x40+Copy_u8XPos;
	}

//	Local_u8DDRAMAddress=ox40*Copy_u8Ypos+Copy_u8XPos;

	/*set bit no.7 for setDDRAM address command then send the address*/

	CLCD_voidSendCommand(Local_u8DDRAMAddress+128); //128 = 0b0100 0000 to set bit7 by 1

}

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPos, u8 Copy_u8Ypos)//pointer because of array
{
	u8 Local_u8CGRAMAddress,Local_u8Counter;
	/*1- calculate CGRAM address knowing that every pattern consumes 8 bytes*/
	Local_u8CGRAMAddress=Copy_u8PatternNumber *8;

	/*2- send set CGRAM address command with bit 6 being set, bit 7 cleared*/
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);//64 to set bit6 by 1 as data sheet

	/*3- write the pattern into CGRAM*/
	for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
	}
	/*4- Back to DDRAM to display the pattern*/
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8Ypos);//in data sheet it want the same command we used in go to function

	/*5- Display the required pattern in CGRAM*/
	CLCD_voidSendData(Copy_u8PatternNumber);//if we wrote no from 0 to 7 it will take the pattern from CGRAM
}



void CLCD_voidWriteNumber(u32 Copy_u32Number)
{
	u32 Local_u8Reserved=1;

	if(Copy_u32Number>9)
	{
		while(Copy_u32Number!=0)
		{
			Local_u8Reserved=Local_u8Reserved*10+Copy_u32Number%10;
			Copy_u32Number/=10;

		}
		do
		{
			CLCD_voidSendData((Local_u8Reserved%10)+'0');
			Local_u8Reserved/=10;

		}
		while(Local_u8Reserved!=1);

	}
	else
	{
		CLCD_voidSendData(Copy_u32Number +'0');
	}


}

/*
static u32 Power(u16 Copy_u16Num,u8 Copy_u8Exponent)
{
	u32 Local_u32Result=1;
	while(Copy_u8Exponent!=0)
	{
		Local_u32Result*=Copy_u16Num;
		Copy_u8Exponent--;
	}
	return Local_u32Result;
}

*/





