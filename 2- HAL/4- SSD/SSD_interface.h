/****************************************************/
/****************************************************/
/**********		Author: Hoda Osama		*************/
/**********		Layer : HAL 			*************/
/**********		SWC	  : SSD				*************/
/**********		Version: 1.00			*************/
/**********		Date: 17/02/2023		*************/
/****************************************************/
/****************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define ANODE   0
#define CATHODE 1

typedef struct {
	u8 type;
	u8 port;
	u8 en_port;
	u8 en_pin;
}SSD_t;

u8 SSD_u8SetNum(SSD_t* Copy_u8SSD,u8 num );
u8 SSD_u8On(SSD_t* Copy_u8SSD);
u8 SSD_u8Off(SSD_t* Copy_u8SSD);

#endif
