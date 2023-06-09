/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : TWI     		*************/
/**********		Version: 1.00			*************/
/**********		Date: 16/04/2023		*************/
/****************************************************/
/****************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "TWI_register.h"
#include "TWI_interface.h"
#include "TWI_config.h"
#include "TWI_private.h"

void TWI_voidInitMaster(u8 Copy_u8Address)
{
	/*Generate Clock Speed = 400khz, with 8MHz System frequency */
	/*1- Set bitrate register to 2 from the equation result when butting prescaler =0 */
	TWBR=2;

	/*2- Clear the Prescaler bits*/
	CLR_BIT(TWSR,TWSR_TWPS0);
	CLR_BIT(TWSR,TWSR_TWPS1);

	/*Enable Acknowledge bit generator */
	SET_BIT(TWCR,TWCR_TWEA);

	/*Check if the node will be addressed*/
	if(Copy_u8Address!=0)
	{
		/*Assign the required node address in the 7 MSB in The Address Register */
		TWAR=Copy_u8Address<<1;
	}
	else
	{
		/*Master will not be Addressed during communication*/
		/*do nothing*/
	}

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);



}

void TWI_voidInitSlave(u8 Copy_u8Address)
{

	/*Enable Acknowledge bit generator */
	SET_BIT(TWCR,TWCR_TWEA);


	/*Assign the required node address in the 7 MSB in The Address Register */
	TWAR=Copy_u8Address<<1;


	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}

TWI_ErrStatus TWI_SendStartCondition (void)
{
	TWI_ErrStatus Local_Error= NoError;

	/*Send Start Condition on the bus*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear The interrupt flag to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the operation complete and the flag is raised again*/

	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the operation Status*/
	if((TWSR & 0xF8)!=START_ACK)
	{
		Local_Error=StartConditionErr;
	}
	else
	{
		/*Do Nothing*/
	}
	return Local_Error;
}

TWI_ErrStatus TWI_SendRepeatedStart(void)
{
	TWI_ErrStatus Local_Error= NoError;

	/*Send Start Condition on the bus*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear The interrupt flag to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the operation complete and the flag is raised again*/

	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the operation Status*/
	if((TWSR & 0xF8)!=REP_START_ACK)
	{
		Local_Error=RepeatedStartErr;
	}
	else
	{
		/*Do Nothing*/
	}
	return Local_Error;
}
TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_Error= NoError;

	/*Clear Start Condition bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*SET the required Slave Address in the 7 MSB on the bus*/
	TWDR=Copy_u8SlaveAddress<<1;

	/*Set the write required */
	CLR(TWDR,0);

	/*Clear The interrupt flag to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the operation complete and the flag is raised again*/

	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the operation Status*/
	if((TWSR & 0xF8)!=SLAVE_ADD_AND_WR_ACK)
	{
		Local_Error=SlaveAddressWithWriteErr;
	}
	else
	{
		/*Do Nothing*/
	}
	return Local_Error;
}

TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_Error= NoError;

	/*Clear Start Condition bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*SET the required Slave Address in the 7 MSB on the bus*/
	TWDR=Copy_u8SlaveAddress<<1;

	/*Set the Read required */
	SET(TWDR,0);

	/*Clear The interrupt flag to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the operation complete and the flag is raised again*/

	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the operation Status*/
	if((TWSR & 0xF8)!=SLAVE_ADD_AND_RD_ACK)
	{
		Local_Error=SlaveAddressWithReadErr;
	}
	else
	{
		/*Do Nothing*/
	}
	return Local_Error;

}

TWI_ErrStatus TWI_MasterSendDataByte(u8 Copy_u8DataByte)
{
	TWI_ErrStatus Local_Error= NoError;
	/*Send the Data on the bus*/
	TWDR=Copy_u8DataByte;

	/*Clear The interrupt flag to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the operation complete and the flag is raised again*/

	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the operation Status*/
	if((TWSR & 0xF8)!=MSTR_WR_BYTE_ACK)
	{
		Local_Error=MasterWriteByteErr;
	}
	else
	{
		/*Do Nothing*/
	}

	return Local_Error;
}

TWI_ErrStatus TWI_MasterReadDataByte(u8* Copy_u8DataByte)
{
	TWI_ErrStatus Local_Error= NoError;

	/*Clear The interrupt flag to Allow the Slave Send The Data */
	SET_BIT(TWCR,TWCR_TWINT);


	/*Clear The interrupt flag to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the operation complete and the flag is raised again*/

	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the operation Status*/
	if((TWSR & 0xF8)!=MSTR_RD_BYTE_WITH_ACK)
	{
		Local_Error=MasterReadByteErr;
	}
	else
	{
		*Copy_u8DataByte=TWDR;
	}


	return Local_Error;
}

void TWI_voidSendStopCondition(void)
{
	/*Set The Stop Condition Bit*/
	SET_BIT(TWCR,TWCR_TWSTO);

	/*Clear The interrupt flag to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

}
