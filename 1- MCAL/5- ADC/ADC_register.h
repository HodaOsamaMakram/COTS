/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : ADC 			*************/
/**********		Version: 1.00			*************/
/**********		Date: 18/03/2023		*************/
/****************************************************/
/****************************************************/

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX			*((volatile u8*)0x27)	/*ADC multiplexer selection register*/
#define ADMUX_RESFS1	7						/*Reference selection bit1*/
#define ADMUX_RESFS0	6						/*Reference selection bit0*/
#define ADMUX_ADLAR		5						/*Left adjust result*/

#define ADCSRA			*((volatile u8*)0x26)	/*ADC control and status registerA*/
#define ADCSRA_ADEN		7						/*Enable*/
#define ADCSRA_ADSC		6						/*Start Conversion*/
#define ADCSRA_ADATE	5						/*Auto trigger enable*/
#define ADCSRA_ADIF		4						/*Interrupt flag*/
#define ADCSRA_ADIE		3						/*Interrupt enable*/


#define ADCH	*((volatile u8*)0x25)			/*Data high register*/
#define ADCL	*((volatile u8*)0x24)			/*Data low register*/

#define ADC 	*((volatile u16*)0x24)

#endif
