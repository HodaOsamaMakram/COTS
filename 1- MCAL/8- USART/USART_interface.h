/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : USART   		*************/
/**********		Version: 1.00			*************/
/**********		Date: 04/04/2023		*************/
/****************************************************/
/****************************************************/
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#define FOSC        		8000000UL
#define USART_BUAD_RATE     9600UL
#define USART_TIMEOUT		1000UL


void USART_voidInit(void);
u8 USART_u8SendDataSynch(u8 Copy_u8Data);
u8 USART_u8ReceiveDataSynch(u8 *Copy_u8Result);
u8 USART_u8SendStringSynch(const char *Copy_pchString);
u8 USART_u8SendStringAsynch(const char *Copy_pchString,void(*Copy_pvNotificationFunc)(void));
u8 USART_u8ReceiveBufferSynch(u8 *Copy_pu8Data,u8 Copy_u8Size);
u8 USART_u8ReceiveBufferAsynch(u8 *Copy_pu8Data,u8 Copy_u8Size,void(*Copy_pvNotificationFunc)(void));

#endif
