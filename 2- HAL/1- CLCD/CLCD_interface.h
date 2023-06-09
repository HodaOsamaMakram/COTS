/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HCAL			*************/
/**********		SWC	  : CLCD			*************/
/**********		Version: 1.00			*************/
/**********		Date: 29/12/2022		*************/
/****************************************************/
/****************************************************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendCommand(u8 copy_u8command);

void CLCD_voidSendData(u8 copy_u8Data);

void CLCD_voidInit(void);

void CLCD_voidSendString(const char* copy_pchString );

void CLCD_voidGoToXY(u8 Copy_u8XPos, u8 Copy_u8Ypos);

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPos, u8 Copy_u8Ypos);

void CLCD_voidWriteNumber(u32 Copy_u32Number);

#endif
