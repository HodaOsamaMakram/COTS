/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HAL				*************/
/**********		SWC	  : Stepper			*************/
/**********		Version: 1.00			*************/
/**********		Date: 15/03/2023		*************/
/****************************************************/
/****************************************************/
#ifndef _STEPPER_INTERFACE_
#define _STEPPER_INTERFACE_

typedef struct {

		u8 Port;
		u8 Pin_Blue;
		u8 Pin_Pink;
		u8 Pin_Yellow;
		u8 Pin_Orange;


				}Stepper_t;
#define CW  0
#define CCW 1

void Stepper_voidSetAngle_Dir(Stepper_t* Copy_u8Stepper,u32 Copy_u32Angle,u8 Copy_Direction);

#endif
