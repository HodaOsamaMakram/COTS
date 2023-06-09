/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : ADC 			*************/
/**********		Version: 1.00			*************/
/**********		Date: 18/03/2023		*************/
/****************************************************/
/****************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


#define RESELUTION	8  //OR 18 Bits

typedef struct
{
	u8* ChainChannel;
	u16* ChainResult;
	u8 ChainSize;
	void (*ChainNotificationFunc)(void);

}Chain_t;

void ADC_voidInit(void);

u8 ADC_u8StartSingleConversionSynch(u8 Copy_u8Channel,u16* Copy_pu16Result);
/*
 * preconditions: Function needs enabling the global interrupts
 * */
u8 ADC_u8StartSingleConversionAsynch(u8 Copy_u8Channel,u16* Copy_pu16Result, void (*Copy_pvNotificationFunc)(void));

/*
 * preconditions: Function needs enabling the global interrupts
 * */
u8 ADC_u8StartChainConversionAsynch(Chain_t * Copy_Chain);

#endif
