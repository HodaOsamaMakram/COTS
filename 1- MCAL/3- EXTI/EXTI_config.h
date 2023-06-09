/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : MCAL			*************/
/**********		SWC	  : EXTI			*************/
/**********		Version: 1.00			*************/
/**********		Date: 15/03/2023		*************/
/****************************************************/
/****************************************************/

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/*Choose INT0 OR INT1 Sense control(interrupt trigger)
 	 Options:	1- LOW_LEVEL
 	 	 	 	2- ON_CHANGE
 	 	 	 	3- FALLING_EDGE
 	 	 	 	4- RISING_EDGE
  */
#define EXTI_INT0_SENSE 			FALLING_EDGE  	//D2
#define EXTI_INT1_SENSE 			FALLING_EDGE	//D3

/*Choose INT2 Sense control(interrupt trigger)
 	 Options: 	1- FALLING_EDGE
 	 	 	 	2- RISING_EDGE
  */

#define EXTI_INT2_SENSE 			FALLING_EDGE	//B2

/*Choose INT0 or INT1 or INT2 peripheral interrupt enable initial state
 * Options:  1-ENABLED
 * 			 2-DISABLED
 * 			 */

#define EXTI_INT0_INITIAL_STATE		ENABLED
#define EXTI_INT1_INITIAL_STATE		ENABLED
#define EXTI_INT2_INITIAL_STATE		ENABLED

#endif
