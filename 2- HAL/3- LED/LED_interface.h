/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HCAL			*************/
/**********		SWC	  : LED				*************/
/**********		Version: 1.00			*************/
/**********		Date: 16/02/2023		*************/
/****************************************************/
/****************************************************/

#ifndef LED_INTERFASE_H_
#define LED_INTERFASE_H_

#define SINK	1
#define SOURCE  0

typedef struct {

	u8 Port;
	u8 Pin;
	u8 Type;

}LED_t;

u8 LED_u8On(LED_t* Copy_u8Led);
u8 LED_u8Off(LED_t* Copy_u8Led);
u8 LED_u8Tgl(LED_t* Copy_u8Led);

#endif
