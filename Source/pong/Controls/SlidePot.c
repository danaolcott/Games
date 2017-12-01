///////////////////////////////////////////////////////
/*
Dana Olcott 2017
SlidePot controller file
Slide pot controller connected to the ADC channel 13
Pin PC3


*/
/////////////////////////////////////////////////

#include "SlidePot.h"
#include "adc.h"

static uint32_t adcRawData = 0x00;
static uint16_t adcPosition = 0x00;

void SlidePot_init(void)
{
	adcRawData = 0x00;
	adcPosition = 0x00;

	//start the dma transfer - continuous
	HAL_ADC_Start_DMA(&hadc1, &adcRawData, 1);

}

uint32_t SlidePot_ReadRawData(void)
{
	return adcRawData;
}

uint16_t SlidePot_ReadPosition(void)
{
	return (uint16_t)adcPosition;
}


//////////////////////////////////////////
//DMA Complete Callback function
//Compute the position and reset the dma
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	uint32_t temp;

	if (hadc == &hadc1)
	{
		temp = ((1000 * adcRawData) / 4095) * 240;
		temp = temp / 1000;

		//set x in a valid range
		if (temp > 240)
		temp = 240;

		adcPosition = temp;

	}

	HAL_ADC_Start_DMA(&hadc1, &adcRawData, 1);

}
