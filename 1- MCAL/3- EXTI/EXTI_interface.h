/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : EXTI			*************/
/**********		Version: 1.00			*************/
/**********		Date: 15/03/2023		*************/
/****************************************************/
/****************************************************/


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define	EXTI_INT0		0
#define	EXTI_INT1		1
#define	EXTI_INT2		2


#define LOW_LEVEL		1
#define ON_CHANGE		2
#define	FALLING_EDGE	3
#define	RISING_EDGE		4



void EXTI_voidINT0Init(void);
void EXTI_voidINT1Init(void);
void EXTI_voidINT2Init(void);

/*Description: Change Sense Control of require Interrupt
  Inputs: 1- Copy_u8Number : the required interrupt number to change sense control
  				Options 1- EXTI_INT0
  						2- EXTI_INT1
  						3- EXTI_INT2
  		  2- Copy_u8Sense : the required sense control for external interrupt
 		  		Options 1- LOW_LEVEL
						2- ON_CHANGE
						3- FALLING_EDGE
						4- RISING_EDGE
Outputs : Error state
				Options 1- OK
						2- NOK
 */
u8 EXTI_u8SetSenseControl(u8 Copy_u8IntNumber,u8 Copy_u8Sense);

u8 EXTI_u8EnableInterrupt(u8 Copy_u8IntNumber);
u8 EXTI_u8DisableInterrupt(u8 Copy_u8IntNumber);

u8 EXTI_u8SetCallBack(void (*Copy_pvCallBackFunc) (void),u8 Copy_u8IntNumber);


#endif 
