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
CENTER PUSH - Interrupt falling edge on PE2


*/
//////////////////////////////////////////////////////////

#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include <stdint.h>

#define JOYSTICK_LEFT_TRIGGER_VALUE				((uint32_t)1365)
#define JOYSTICK_RIGHT_TRIGGER_VALUE			((uint32_t)2730)

#define JOYSTICK_DOWN_TRIGGER_VALUE				((uint32_t)1365)
#define JOYSTICK_UP_TRIGGER_VALUE				((uint32_t)2730)


void Joystick_init(void);
void Joystick_GetRawData(uint32_t* data);
void Joystick_ButtonHandler(void);



#endif
