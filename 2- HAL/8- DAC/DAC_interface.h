/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HAL				*************/
/**********		SWC	  : DAC				*************/
/**********		Version: 1.00			*************/
/**********		Date: 18/03/2023		*************/
/****************************************************/
/****************************************************/

#ifndef DAC_INTERFACE_H_
#define DAC_INTERFACE_H_

#define res 	8	//8 bit resultion
#define ref 	5	//5 volt reference



#define STEP 	19.53125 	//(ref/2^res)*1000 to accept mv

u8 DAC_u8SetAnalogVolt(u16 Copy_u16AnalogVolt);

#endif
