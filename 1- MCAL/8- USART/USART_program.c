/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : USART   		*************/
/**********		Version: 1.00			*************/
/**********		Date: 04/04/2023		*************/
/****************************************************/
/****************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include "USART_register.h"
#include "USART_interface.h"
#include "USART_config.h"
#include "USART_private.h"

static void(*USART_pvNotificationFunc)(void)=NULL;
static const char *USART_pchString=NULL;
static void(*USART_pvReceiveNotificationFunc)(void)=NULL;
static u8* USART_pu8ReceiveData=NULL;
static u8 USART_u8Size;
static u8 USART_u8ReceiveBusyState=IDLE;
static u8 USART_u8SendBusyState=IDLE;



void USART_voidInit(void)
{
	/*Local variable to hold the required value of UCSRC register*/
	u8 Local_u8UCSRCVal=0;

	/*Local variable to hold the required value of UBRRL&UBRRH registers*/
	u16 Local_u16BuadVal=0;

	/*Choose the UCSRC register*/
	SET_BIT(Local_u8UCSRCVal,UCSRC_URSEL);
#if USART_MODE_SELECT==SYNCH
	CLR_BIT(UCSRC,UCSRC_UMSEL);
#elif USART_MODE_SELECT==ASYNCH
	SET_BIT(UCSRC,UCSRC_UMSEL);
#else
#error "wrong USART_MODE_SELECT configuration option"
#endif
	Local_u8UCSRCVal&=USART_PARITY_MASK;
	Local_u8UCSRCVal|=USART_PARITY_MODE;
#if USART_STOP_BIT==ONE_BIT
	CLR_BIT(Local_u8UCSRCVal,UCSRC_USBS);
#elif USART_STOP_BIT==TWO_BIT
	SET_BIT(Local_u8UCSRCVal,UCSRC_USBS);
#else
#error "wrong USART_STOP_BIT configuration option"
#endif

#if USART_CHARACTER_SIZE <=EGHIT_BIT
	Local_u8UCSRCVal&=USART_CHARACTER_SIZE_MASK;
	Local_u8UCSRCVal|=USART_CHARACTER_SIZE;
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif USART_CHARACTER_SIZE==NINE_BIT
	/*Character size 9 bits*/
	SET_BIT(Local_u8UCSRCVal,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCVal,UCSRC_UCSZ1);
	SET_BIT(UCSRB,UCSRB_UCSZ2);
#else
#error "wrong USART_CHARACTER_SIZE configuration option"
#endif
	/*Assign the UCSRC required value in one operation*/
	UCSRC=Local_u8UCSRCVal;

	/*set BaudRate to 9600 bit per swc for 8MHz system frequency*/
#if USART_MODE_SELECT==ASYNCH
#if USART_SPEED_MODE==SINGLE
	CLR_BIT(UCSRA,UCSRA_U2X);
	Local_u16BuadVal=((FOSC)/(16UL*(u32) USART_BUAD_RATE ))-1;
	UBRRL=(u8)Local_u16BuadVal;
	UBRRH=(u8)(Local_u16BuadVal>>8);
#elif USART_SPEED_MODE==DOUBLE
	SET_BIT(UCSRA,UCSRA_U2X);
	Local_u16BuadVal=((FOSC)/(8UL*(u32) USART_BUAD_RATE ))-1;
	UBRRL=(u8)Local_u16BuadVal;
	UBRRH=(u8)(Local_u16BuadVal>>8);
#else
#error "wrong USART_SPEED_MODE configuration option"

#endif
#elif USART_MODE_SELECT==SYNCH
	CLR_BIT(UCSRA,UCSRA_U2X);
	Local_u16BuadVal=((FOSC)/(16UL*(u32) USART_BUAD_RATE ))-1;
	UBRRL=(u8)Local_u16BuadVal;
	UBRRH=(u8)(Local_u16BuadVal>>8);
#else
#error "wrong USART_MODE_SELECT configuration option"

#endif

	/*Transmitter enable*/
#if USART_TRANSMITTER_STATE==ENABLED
	SET_BIT(UCSRB,UCSRB_TXEN);
#elif USART_TRANSMITTER_STATE == DISABLED
	CLR_BIT(UCSRB,UCSRB_TXEN);
#else
#error "wrong USART_TRANSMITTER_STATE configuration option"
#endif

	/*Receiver enable*/
#if USART_RECEIVER_STATE==ENABLED
	SET_BIT(UCSRB,UCSRB_RXEN);
#elif USART_RECEIVER_STATE == DISABLED
	CLR_BIT(UCSRB,UCSRB_RXEN);
#else
#error "wrong USART_RECEIVER_STATE configuration option"
#endif


}

u8 USART_u8SendDataSynch(u8 Copy_u8Data)
{
	u8 Local_u8ErrorState=OK;
	u8 Local_u8Counter=0;
	if(USART_u8SendBusyState==IDLE)
	{
		USART_u8SendBusyState=BUSY;
		/*Wait until the Transmit buffer is empty and ready*/
		while(((GET_BIT(UCSRA,UCSRA_UDRE))==0)&&(Local_u8Counter<USART_TIMEOUT))
		{
			Local_u8Counter++;
		}
		if(Local_u8Counter==USART_TIMEOUT)
		{
			Local_u8ErrorState=TIMEOUT_STATE;
		}
		else
		{
			/*Send The Data*/
			UDR=Copy_u8Data;
		}

		USART_u8SendBusyState=IDLE;
	}
	else
	{
		Local_u8ErrorState=BUSY_STATE;
	}
	return Local_u8ErrorState;
}

u8 USART_u8ReceiveDataSynch(u8 *Copy_u8Result)
{
	u8 Local_u8ErrorState=OK;
	u8 Local_u8Counter=0;
	if(Copy_u8Result!=NULL)
	{
		if(USART_u8ReceiveBusyState==IDLE)
		{
			USART_u8ReceiveBusyState=BUSY;

			/*wait until receive complete event happens*/
			while(((GET_BIT(UCSRA,UCSRA_RXC))==0)&&(Local_u8Counter<USART_TIMEOUT))
			{
				Local_u8Counter++;
			}
			if(Local_u8Counter==USART_TIMEOUT)
			{
				Local_u8ErrorState=TIMEOUT_STATE;
			}
			else
			{
				/*return the data*/
				*Copy_u8Result= UDR;
			}
			USART_u8ReceiveBusyState=IDLE;
		}
		else
		{
			Local_u8ErrorState=BUSY_STATE;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}


u8 USART_u8SendStringSynch(const char *Copy_pchString)
{
	u8 Local_u8ErrorState=OK;
	u8 Local_u8Counter=0;
	if(Copy_pchString==NULL)
	{
		while(Copy_pchString[Local_u8Counter]!='\0')
		{
			USART_u8SendDataSynch(Copy_pchString[Local_u8Counter]);
			Local_u8Counter++;
		}


	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;
}


u8 USART_u8ReceiveBufferSynch(u8 *Copy_pu8Data,u8 Copy_u8Size)
{
	u8 Local_u8ErrorState=OK;
	u8 Local_u8Counter=0;
	if(Copy_pu8Data!=NULL)
	{
		while(Local_u8Counter<Copy_u8Size)
		{
			USART_u8ReceiveDataSynch(&Copy_pu8Data[Local_u8Counter]);
			Local_u8Counter++;
		}

	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

u8 USART_u8SendStringAsynch(const char *Copy_pchString,void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if((Copy_pchString!=NULL)&&(Copy_pvNotificationFunc!=NULL))
	{
		if(USART_u8SendBusyState==IDLE)
		{
			USART_pvNotificationFunc=Copy_pvNotificationFunc;
			USART_pchString=Copy_pchString;
			SET_BIT(UCSRB,UCSRB_UDRIE);
		}


		else
		{
			Local_u8ErrorState=BUSY_STATE;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;

}

u8 USART_u8ReceiveBufferAsynch(u8 *Copy_pu8Data,u8 Copy_u8Size,void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if((Copy_pu8Data!=NULL)&&(Copy_pvNotificationFunc!=NULL))
	{
		if(USART_u8ReceiveBusyState==IDLE)
		{
			USART_u8ReceiveBusyState=BUSY;
			USART_pvReceiveNotificationFunc=Copy_pvNotificationFunc;
			USART_pu8ReceiveData=Copy_pu8Data;
			USART_u8Size=Copy_u8Size;
			SET_BIT(UCSRB,UCSRB_RXCIE);
		}
		else
		{
			Local_u8ErrorState=BUSY_STATE;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;

}

void vector_13 (void) __attribute__((signal));
void vector_13 (void)
{
	static u8 Local_u8Counter=0;
	if((USART_pvReceiveNotificationFunc!=NULL) &&(USART_pu8ReceiveData!=NULL))
	{
		UDR=USART_pchString[Local_u8Counter];
		Local_u8Counter++;
		if(Local_u8Counter==USART_u8Size)
		{
			CLR_BIT(UCSRB,UCSRB_RXCIE);
			USART_u8ReceiveBusyState=IDLE;
			Local_u8Counter=0;
			USART_pvReceiveNotificationFunc();

		}
	}
}


void vector_14 (void) __attribute__((signal));
void vector_14 (void)
{
	static u8 Local_u8Counter=0;
	if((USART_pvNotificationFunc!=NULL) &&(USART_pchString!=NULL))
	{
		if(USART_pchString[Local_u8Counter]!='\0')
		{
			UDR=USART_pchString[Local_u8Counter];
			Local_u8Counter++;
		}
		else
		{
			CLR_BIT(UCSRB,UCSRB_UDRIE);
			USART_u8SendBusyState=IDLE;
			Local_u8Counter=0;
			USART_pvNotificationFunc();

		}
	}
}





