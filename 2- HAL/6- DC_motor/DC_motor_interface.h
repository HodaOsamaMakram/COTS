/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HAL				*************/
/**********		SWC	  : DC_motor		*************/
/**********		Version: 1.00			*************/
/**********		Date: 13/3/2023			*************/
/****************************************************/
/****************************************************/

#ifndef DC_MOTOR_INTERFACE_H_
#define DC_MOTOR_INTERFACE_H_

typedef struct {

	u8 Port;
	u8 PinA;
	u8 PinB;

}MOTOR_t;


void DC_MotorVoidCW(MOTOR_t* Copy_u8Motor);
void DC_MotorVoidCCW(MOTOR_t* Copy_u8Motor);
void DC_MotorVoidStop(MOTOR_t* Copy_u8Motor);


#endif
