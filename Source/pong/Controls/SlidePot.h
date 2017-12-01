///////////////////////////////////////////////////////
/*
Dana Olcott 2017
Slide pot controller connected to the ADC channel 13


*/
//////////////////////////////////////////////////////////

#ifndef __SLIDE_POT_H
#define __SLIDE_POT_H

#include <stdint.h>




void SlidePot_init(void);
uint32_t SlidePot_ReadRawData(void);
uint16_t SlidePot_ReadPosition(void);


#endif
