/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : SPI     		*************/
/**********		Version: 1.00			*************/
/**********		Date: 12/04/2023		*************/
/****************************************************/
/****************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "SPI_register.h"
#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"
u8 *SPI_u8SendBuffer=NULL;
u8 *SPI_u8ReceiveBuffer=NULL;

void (*SPI_pvNotificationFunk)(void);
u8 SPI_u8Size;

void SPI_voidInitMaster(void)
{
	/*Set master node*/
	SET_BIT(SPCR,SPCR_MSTR);

	/*clock speed: system frequency divided by 16*/
	SET_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);

	/*SPI enable*/
	SET_BIT(SPCR,SPCR_SPE);
}

void SPI_voidInitSlave(void)
{
	/*Set Salve node*/
	CLR_BIT(SPCR,SPCR_MSTR);

	/*SPI enable*/
	SET_BIT(SPCR,SPCR_SPE);
}

u8 SPI_u8TransceiveDataSynch(u8 Copy_u8Data,u8 *Copy_pu8Val)
{
	u8 Local_u8ErrorState=OK;
	/*Send the data*/
	SPDR = Copy_u8Data;
	if(Copy_pu8Val!=NULL)
	{
		/*wait until transfer is complete*/
		while((GET_BIT(SPSR,SPSR_SPIF))==0);

		/*return the received data*/
		*Copy_pu8Val=SPDR;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}
u8 SPI_u8TransceiveBufferSynch(u8 *Copy_pu8SendBuffer,u8 *Copy_pu8ReceiveBuffer,u8 Copy_u8BufferSize)
{
	u8 Local_u8ErrorState=OK;
	u8 Local_u8Counter=0;
	if((Copy_pu8SendBuffer!=NULL)&&(Copy_pu8ReceiveBuffer!=NULL))
	{
		while(Local_u8Counter<Copy_u8BufferSize)
		{
			SPI_u8TransceiveDataSynch( Copy_pu8SendBuffer[Local_u8Counter],&Copy_pu8ReceiveBuffer);
			Local_u8Counter++;
		}

	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;

}

u8 SPI_u8TransceiveBufferASynch(u8 *Copy_pu8SendBuffer,u8 *Copy_pu8ReceiveBuffer,u8 Copy_u8BufferSize,void(*Copy_pvNotificationFunc(void)))
{
	u8 Local_u8ErrorState=OK;
	if((Copy_pu8SendBuffer!=NULL)&&(Copy_pu8ReceiveBuffer!=NULL)&&(Copy_pvNotificationFunc!=NULL))
	{
		 SPI_u8SendBuffer=Copy_pu8SendBuffer;
		SPI_u8ReceiveBuffer=Copy_pu8ReceiveBuffer;

		SPI_pvNotificationFunk=Copy_pvNotificationFunc;
		SPI_u8Size=Copy_u8BufferSize;
		SET_BIT(SPCR,SPCR_SPIE);
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;

}

void _vector_12 (void) __attribute__((signal));
void _vector_12 (void)
{
	static volatile u8 Local_u8Counter=0;
	if((SPI_u8SendBuffer!=NULL)&&(SPI_u8ReceiveBuffer!=NULL)&&(SPI_pvNotificationFunk!=NULL))
	{
		SPI_u8ReceiveBuffer[Local_u8Counter]=SPDR;
		Local_u8Counter++;
		if(Local_u8Counter==SPI_u8Size)
		{
			Local_u8Counter=0;
			CLR_BIT(SPCR,SPCR_SPIE);
			SPI_pvNotificationFunk();

		}
		else
		{
			SPDR=SPI_u8SendBuffer[Local_u8Counter];
		}
	}


}
