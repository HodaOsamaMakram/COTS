/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : DIO				*************/
/**********		Version: 1.00			*************/
/**********		Date: 25/12/2022		*************/
/****************************************************/
/****************************************************/

#ifndef DIO_REGISTER_H
#define DIO_REGISTER_H

#define	PORTA		*((volatile u8*)0x3B)
#define PINA		*((volatile u8*)0x39)

#define PORTB		*((volatile u8*)0x38)
#define PINB		*((volatile u8*)0x36)

#define PORTC		*((volatile u8*)0x35)
#define PINC		*((volatile u8*)0x33)

#define PORTD		*((volatile u8*)0x32)
#define PIND		*((volatile u8*)0x30)
/*
#define DDRA		*((volatile u8*)0x3A)
#define DDRB		*((volatile u8*)0x37)
#define DDRC		*((volatile u8*)0x34)
#define DDRD		*((volatile u8*)0x31)
*/
#endif  
