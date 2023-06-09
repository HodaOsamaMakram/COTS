/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HCAL			*************/
/**********		SWC	  : SWITCH			*************/
/**********		Version: 1.00			*************/
/**********		Date: 16/02/2023		*************/
/****************************************************/
/****************************************************/

#ifndef SWITCH_INTERFACE_H_
#define SWITCH_INTERFACE_H_

#define PRESSED     1
#define NOT_PRESSED 0

#define PULL_UP       1
#define PULL_DOWN     0


typedef struct {
	u8 pull_type;
	u8 port;
	u8 pin;
}SW_t;

u8 SW_u8GetState(SW_t* Copy_sw);

#endif
