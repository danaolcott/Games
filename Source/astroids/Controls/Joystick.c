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
/////////////////////////////////////////////////

#include "Joystick.h"
#include "adc.h"
#include <string.h>

#include "Sprite.h"

static volatile uint32_t adcRawData[2] = {0x00, 0x00};	//raw reading

void Joystick_init(void)
{
	memset((uint32_t*)adcRawData, 0x00, 2);

	//start the dma transfer - continuous
	HAL_ADC_Start_DMA(&hadc3, (uint32_t*)adcRawData, 2);
}

////////////////////////////////////////////////
//returns adc raw data pointer, 32bit, 2 elements
void Joystick_GetRawData(uint32_t *data)
{
	data[0] = adcRawData[0];
	data[1] = adcRawData[1];
}


//////////////////////////////////////////
//DMA Complete Callback function
//Compute the position and reset the dma
//Check the values read on the ADC, if in range
//to trigger a joystick event, set the appropriate flag
//a joystick event is one that  the raw data falls
//in the upper or lower 1/3 out of 4095....so,
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{

	if (hadc == &hadc3)
	{
		//left right
		if (adcRawData[0] < JOYSTICK_DOWN_TRIGGER_VALUE)
		{
			Sprite_PlayerSetSpecialEventFlag();
		}
		else if (adcRawData[0] > JOYSTICK_UP_TRIGGER_VALUE)
		{
			Sprite_PlayerSetThursterFlag();
		}
		else if (adcRawData[1] < JOYSTICK_LEFT_TRIGGER_VALUE)
		{
			Sprite_PlayerSetRotateCCWFlag();
		}
		else if (adcRawData[1] > JOYSTICK_RIGHT_TRIGGER_VALUE)
		{
			Sprite_PlayerSetRotateCWFlag();
		}

	}

	HAL_ADC_Start_DMA(&hadc3, (uint32_t*)adcRawData, 2);
}


///////////////////////////////////////////
//Interrupt handler for center button
//
void Joystick_ButtonHandler(void)
{

}

