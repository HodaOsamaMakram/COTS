/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : SPI     		*************/
/**********		Version: 1.00			*************/
/**********		Date: 12/04/2023		*************/
/****************************************************/
/****************************************************/
#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_voidInit(void);

void SPI_voidInitMaster(void);

void SPI_voidInitSlave(void);

u8 SPI_u8TransceiveDataSynch(u8 Copy_u8Data,u8 *Copy_pu8Val);
u8 SPI_u8TransceiveBufferSynch(u8 *Copy_pu8SendBuffer,u8 Copy_pu8ReceiveBuffer,u8 Copy_u8BufferSize);
u8 SPI_u8TransceiveBufferASynch(u8 *Copy_pu8SendBuffer,u8 *Copy_pu8ReceiveBuffer,u8 Copy_u8BufferSize,void(*Copy_pvNotificationFunc(void)));

#endif
