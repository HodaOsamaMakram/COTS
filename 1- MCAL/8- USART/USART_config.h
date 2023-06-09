/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : USART   		*************/
/**********		Version: 1.00			*************/
/**********		Date: 04/04/2023		*************/
/****************************************************/
/****************************************************/
#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_


#define USART_TRANSMITTER_STATE  ENABLED	 /*USART_TRANSMITTER_STATE Options:   1- ENABLED
 	 	 	 	 	 	 	 	 	 	      * 								  2- DISABLED*/

#define USART_RECEIVER_STATE     ENABLED	/*USART_RECEIVER_STATE Options:       1- ENABLED
 	 	 	 	 	 	 	 	 	 	 	 * 							          2- DISABLED*/

#define USART_MODE_SELECT	     ASYNCH		/* USART_MODE_SELECT Options:         1- SYNCH
 	 	 	 	 	 	 	 	 	 	 	 * 					        		  2- ASYNCH */

#define USART_PARITY_MODE	     DISABLED	/* USART_PARITY_MODE  Options:		  1- DISABLED
											 * 					         		  2- EVEN_PARITY
											 * 					       		      3- ODD_PARAITY*/

#define USART_STOP_BIT         	ONE_BIT		/* USART_STOP_BIT     Options:		  1- ONE_BIT
											 * 					                  2- TWO_BIT  */

#define USART_CHARACTER_SIZE	FIVE_BIT	/*USART_CHARACTER_SIZE Options:		  1- FIVE_BIT
																		          2- SIX_BIT
																		          3- SEVEN_BIT
																		          4- EGHIT_BIT
																		          5- NINE_BIT  */

#define USART_SPEED_MODE	   SINGLE      /* USART_MODE_SELECT Options:         1- SINGLE
 	 	 	 	 	 	 	 	 	 	 	* 					        		 2- DOUBLE */




#endif
