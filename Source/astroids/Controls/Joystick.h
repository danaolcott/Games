///////////////////////////////////////////////////////
/*
Dana Olcott 2018
Joystick Controller File

Targets the analog joystick from Sparkfun.  Has
two ADC channels with idle position at half adc 
reading.  Also contains center push button.  Hardware
configured to run on ADC3, channels 4 and 13.  Link
to DMA stream, continous.

Connections:
UP/DOWN - CH4 - PF6
LEFT/RIGHT - CH13 - PC3

Alternate Joystick - PE2, PE3, PE4 to
use digital signal for left, right, thruster

*/
//////////////////////////////////////////////////////////

#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include <stdint.h>

#define JOYSTICK_LEFT_TRIGGER_VALUE				((uint32_t)1365)
#define JOYSTICK_RIGHT_TRIGGER_VALUE			((uint32_t)2730)

#define JOYSTICK_DOWN_TRIGGER_VALUE				((uint32_t)1365)
#define JOYSTICK_UP_TRIGGER_VALUE				((uint32_t)2730)

//comment this out if you want to use digital
#define JOYSTICK_USE_ANALOG				1



void Joystick_init(void);
void Joystick_GetRawData(uint32_t* data);
void Joystick_Digital_Read(void);



#endif
