///////////////////////////////////////////////////
/*
 * joystick.c
 *
 * Created: 6/16/2018 1:14:52 AM
 *  Author: danao
 *
 *  Configures the DMA transfer from ADC peripheral
 *  to memory.  Once DMA starts, the ADC values from
 *  channels A0 and A1 (see pinout) are available at
 *  any time.  See joystick.h for joystick limits
 *  for up, down... etc.
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
//Read value of ADC - Channel 0.  It's labeled as
//A0 on the headers.  Note that this file was also
//used with the Atmel SAME70 board, which required
//connecting channels A0 and A1 together and reading
//A1 (in case there are discrepancies in the text)
//
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


