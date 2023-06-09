/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : ADC 			*************/
/**********		Version: 1.00			*************/
/**********		Date: 18/03/2023		*************/
/****************************************************/
/****************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define DIVIDE_BY_128		7

#define PRESCALER_MASK		0b11111000
#define CHANNEL_MASK		0b11100000

#define IDLE				0
#define BUSY				1

#define SINGLE_CONVERSION    0
#define CHAIN_CONVERSION    1

#endif
