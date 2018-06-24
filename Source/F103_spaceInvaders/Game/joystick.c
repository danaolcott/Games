///////////////////////////////////////////////////
/*
 * joystick.c
 *
 * Created: 6/16/2018 1:14:52 AM
 *  Author: danao
 */ 
///////////////////////////////////////////////////

#include <stdint.h>
#include <stddef.h>

#include "joystick.h"
#include "adc.h"

//ADC raw data
volatile uint32_t rawAdcData[2] = {0x00, 0x00};		//2 channels


///////////////////////////////////////////////////
//Configures the ADC DMA stream
//and the array that holds the joystick data
void Joystick_Config(void)
{
	//init the DMA/ADC transfer
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)rawAdcData, 2);		//start the transfers - A0, A1
}


//////////////////////////////////////////////////
//Read value of ADC - AD6, labeled as A1
//on the board.  It's connected to the A0 on the
//Channel6 is shown on the board as A1
//12 bit value - 0 to 4096
JoystickPosition_t Joystick_GetPosition(void)
{
	uint16_t value = (uint16_t)rawAdcData[0];

	if (value < JOYSTICK_LIMIT_0)
		return JOYSTICK_LEFT;
	else if ((value >= JOYSTICK_LIMIT_0) && (value < JOYSTICK_LIMIT_1))
		return JOYSTICK_PRESS;
	else if ((value >= JOYSTICK_LIMIT_1) && (value < JOYSTICK_LIMIT_2))
		return JOYSTICK_DOWN;
	else if ((value >= JOYSTICK_LIMIT_2) && (value < JOYSTICK_LIMIT_3))
		return JOYSTICK_RIGHT;
	else if ((value >= JOYSTICK_LIMIT_3) && (value < JOYSTICK_LIMIT_4))
		return JOYSTICK_UP;
	else if (value >= JOYSTICK_LIMIT_4)
		return JOYSTICK_NONE;

	return JOYSTICK_NONE;
}

uint16_t Joystick_GetRawData()
{
	uint16_t value = (uint16_t)rawAdcData[0];
	return value;
}


