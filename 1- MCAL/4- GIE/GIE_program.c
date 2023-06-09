/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : GIE 			*************/
/**********		Version: 1.00			*************/
/**********		Date: 15/03/2023		*************/
/****************************************************/
/****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE_interface.h"
#include "GIE_register.h"

void GIE_voidEnableGlobal(void)
{
	SET_BIT(SREG,SREG_I);
}
void GIE_voidDisableGlobal(void)
{
	CLR_BIT(SREG,SREG_I);
}