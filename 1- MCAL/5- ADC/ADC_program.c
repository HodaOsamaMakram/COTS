/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : ADC 			*************/
/**********		Version: 1.00			*************/
/**********		Date: 18/03/2023		*************/
/****************************************************/
/****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_register.h"
#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"

/*Global pointer to hold the conversion result accessed by ISR*/
static u16* ADC_pu16ConversionResult=NULL;

/*Global pointer to function to hold the notification function called by ISR */
static void(*ADC_pvNotificationFunc)(void)=NULL;

/*Global variable to indicate for ADC peripheral state */
static u8 ADC_u8BusyState= IDLE;

/*Global Flag to indicate for the reason why ISR comes*/
static u8 ADC_u8ISRSourse;

/*Global pointer to carry the Channel array*/
static u8* ADC_pu8ChainChannel=NULL;

/*Global variable to carry the chain number of channels */
static u8 ADC_u8ChainSize;

/*Global variable to carry the current conversion index */
static u8 ADC_u8ChainIndex;

void ADC_voidInit(void)
{
	/*Set reference voltage*/
	SET_BIT(ADMUX,ADMUX_RESFS0);
	CLR_BIT(ADMUX,ADMUX_RESFS1);
#if RESELUTION == 8
	/*Activate left adjust result for 8bit resolution*/
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif RESELUTION==10
	/*Activate left adjust result for 10bit resolution*/
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "wrong select reselution "
#endif
	/*Set the configured prescaler*/
	ADCSRA&=PRESCALER_MASK;
	ADCSRA|=ADC_u8PRESCALER;


	/*ADC enable*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);

}
u8 ADC_u8StartSingleConversionSynch(u8 Copy_u8Channel,u16* Copy_pu16Result)
{
	u8 Local_u8ErrorState=OK;
	u32 Local_u8Counter=0;

	if (Copy_pu16Result==NULL)
	{
		/*Check ADC peripheral is busy with another conversion or idle(not busy)*/
		if(ADC_u8BusyState==IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyState=BUSY;

			/*Set the required channel*/
			ADMUX&= CHANNEL_MASK;
			ADMUX|=Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Polling with blocking(Busy waiting) on the conversion complete event or until the timeout is reached*/
			while(((GET_BIT(ADCSRA,ADCSRA_ADIF))==0) && (Local_u8Counter < ADC_u32TIMEOUT))
			{
				Local_u8Counter++;
			}
			/*check the reason why while loop is broken*/
			if (Local_u8Counter==ADC_u32TIMEOUT)
			{
				/*Loop is broken because Timeout is reached*/
				Local_u8ErrorState=TIMEOUT_STATE;
			}
			else

			{


				/*Loop is broken because Complete flag is raised*/
				/*Clear the conversion complete flag*/
				SET_BIT(ADCSRA,ADCSRA_ADIF);

				/*Read the result*/
				/*#if & #elif for choose 8 or 10 bit*/

#if RESELUTION==8
				*Copy_pu16Result= ADCH;
#elif RESELUTION==10
				*Copy_pu16Result= ADC;
#else
#error "wrong select reselution "
#endif
			}
			/*Release the ADC busy state, ADC is now IDLE */
			ADC_u8BusyState= IDLE;
		}
		else
		{
			/*ADC peripheral is busy with another conversion */
			Local_u8ErrorState=BUSY_STATE;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;

}


u8 ADC_u8StartSingleConversionAsynch(u8 Copy_u8Channel,u16* Copy_pu16Result, void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if((Copy_pu16Result!=NULL) && (Copy_pvNotificationFunc!=NULL))
	{
		/*Check ADC peripheral is busy with another conversion or idle(not busy)*/
		if(ADC_u8BusyState==IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyState=BUSY;

			/*ISR will come because of single conversion function*/
			ADC_u8ISRSourse=SINGLE_CONVERSION;

			/*Initialize the global pointer to the result address*/
			ADC_pu16ConversionResult=Copy_pu16Result;

			/*Initialize the global pointer to Function to point to notification function address*/
			ADC_pvNotificationFunc=Copy_pvNotificationFunc;

			/*Set required channel*/
			ADMUX&= CHANNEL_MASK;
			ADMUX|=Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable ADC Conversion Complete interrupt */
			SET_BIT(ADCSRA,ADCSRA_ADIE);
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

u8 ADC_u8StartChainConversionAsynch(Chain_t * Copy_Chain)
{
	u8 Local_u8ErrorState=OK;
	if((Copy_Chain!= NULL)&&(Copy_Chain->ChainChannel!= NULL)&&(Copy_Chain->ChainResult!= NULL)&&(Copy_Chain->ChainNotificationFunc!= NULL))
	{
		/*Check ADC busy State*/
		if(ADC_u8BusyState==IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyState=BUSY;

			/*ISR will come because of chain conversion function*/
			ADC_u8ISRSourse=CHAIN_CONVERSION;

			/*Initialize the Chain data globally*/
			ADC_pu8ChainChannel=Copy_Chain->ChainChannel;
			ADC_pu16ConversionResult=Copy_Chain->ChainResult;
			ADC_u8ChainSize=Copy_Chain->ChainSize;
			ADC_pvNotificationFunc=Copy_Chain->ChainNotificationFunc;

			ADC_u8ChainIndex=0;

			/*Set required channel*/
			ADMUX&= CHANNEL_MASK;
			ADMUX|=ADC_pu8ChainChannel[ADC_u8ChainIndex];

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable ADC Conversion Complete interrupt */
			SET_BIT(ADCSRA,ADCSRA_ADIE);
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



/*ADC ISR*/
void vector_16 (void) __attribute__((signal));
void vector_16 (void)
{
	if(ADC_u8ISRSourse==SINGLE_CONVERSION)
	{
		/*Read the conversion result*/
		/*#if 8 or 10 bit*/
#if RESELUTION == 8
		*ADC_pu16ConversionResult=ADCH;
#elif RESELUTION == 10
		*ADC_pu16ConversionResult=ADC;
#else
#error "wrong select reselution "
#endif
		/*Release the ADC busy state, ADC is now IDLE */
		ADC_u8BusyState= IDLE;
		/*Disable the ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);

		/*Invoke the callback notification function  */
		if(ADC_pvNotificationFunc!=NULL)
		{
			ADC_pvNotificationFunc();
		}


	}
	else // ISR source is chain conversion
	{
		/*Read the conversion result*/
		/*#if 8 or 10 bit*/
#if RESELUTION == 8
		ADC_pu16ConversionResult[ADC_u8ChainIndex]=ADCH;
#elif RESELUTION == 10
		ADC_pu16ConversionResult[ADC_u8ChainIndex]=ADC;
#else
#error "wrong select reselution "
#endif
		/*Increment the index*/
		ADC_u8ChainIndex++;
		if(ADC_u8ChainIndex==ADC_u8ChainSize)
		{
			/*Chain is finished*/
			/*ADc is now IDEL*/
			ADC_u8BusyState=IDLE;

			/*Disable the ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);

			/*Invoke the callback notification function  */
			if(ADC_pvNotificationFunc!=NULL)
			{
				ADC_pvNotificationFunc();
			}
		}
		else
		{
			/*Chain is not finished*/

			/*Set required channel*/
			ADMUX&= CHANNEL_MASK;
			ADMUX|=ADC_pu8ChainChannel[ADC_u8ChainIndex];

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

		}
	}

}


