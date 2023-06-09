/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : USART   		*************/
/**********		Version: 1.00			*************/
/**********		Date: 04/04/2023		*************/
/****************************************************/
/****************************************************/
#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define SYNCH	0
#define ASYNCH 	1

#define ENABLED		1
#define DISABLED	0

#define USART_PARITY_MASK  0b11001111

#define USART_CHARACTER_SIZE_MASK 0b1111001

#define EVEN_PARITY  0b00100000
#define ODD_PARITY   0b00110000

#define ONE_BIT	0
#define TWO_BIT 1

#define FIVE_BIT	0
#define SIX_BIT	    0b00000010
#define SEVEN_BIT	0b00000100
#define EGHIT_BIT	0b00000110
#define NINE_BIT    9

#define SINGLE     0
#define DOUBLE	   1

#define IDLE				0
#define BUSY				1

#endif
