/*////////////////////////////////////////////////////
Sound Function Definitions
Sound Output from home-brew binary weighted DAC
(missing the opamp component, just the resistors)

Good Source of Example sounds:
http://www.downloadfreesound.com/8-bit-sound-effects/

Sound converter from wav to c code:
http://ccgi.cjseymour.plus.com/wavtocode/wavtocode.htm

Sounds assumed to be sampled at 44khz.  To avoid jamming up the
interrupts, run the output at 11khz, so read every 4th sample

To use:
Configure a timer to run at 11khz.  Put 
Sound_InterrruptHandler in the timer isr
Timer is running anytime the sound is on, not running
with the sound is complete

Atmel SAME70 M7-series board -
Uses Timer0 - 11khz
DAC - DACC_CHANNEL_0

STM32F103 Nucleo board:  Built DAC out of IO
pins and resistors.  Uses Timer TIM3
to read the sound file.

Sound Bits and resistor values:
PB13 - Bit0 - 4.7k
PB14 - Bit1 - 2.2k
PB15 - Bit2 - 1k
PB1 - Bit3 - 470
PB2 - Bit4 - 220
GND -



*/////////////////////////////////////////////////////
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "Sound.h"
#include "tim.h"

static uint8_t* waveData;
static uint32_t waveCounter;
static void Sound_PlaySound(const SoundData *sound);
static void Sound_DAC_Write(uint8_t value);

//////////////////////////////////////////////
//Configure a timer to run at 11khz and shut it off.
//NOTE: STM code all init are in main.  Use
//Start_IT and Stop_IT functions for starting
//and stopping the timer.
//
void Sound_Init(void)
{
	HAL_TIM_Base_Stop_IT(&htim3);		//timer3 off
	Sound_DAC_Write(0x00);				//set all bits low
}

/////////////////////////////////////////////
//Sound_InterruptHandler
//Put this function call in the Timer ISR.
//Typically wave files are 44khz.  Therefore, 
//play every 4th element with timer running
//at 11khz.  Or, if files are compressed to
//11khz, then play every sample with 11khz timer.
//
void Sound_InterruptHandler(void)
{
	if (waveCounter > 1)
	{
		Sound_DAC_Write(*waveData);
		waveData++;            //increment the pointer
		waveCounter--;			//decrement the down counter
	}

	else
	{
		HAL_TIM_Base_Stop_IT(&htim3);		//timer3 off
		Sound_DAC_Write(0x00);
	}
}


////////////////////////////////////////////////
//Play sound.  Takes pointer to a SoundData file
//point waveData to the sound array and counter
//to the size of the sound array.  Also, start
//the timer.  Sound data is played in the timer
//ISR until the sound array is finished playing.
//
void Sound_PlaySound(const SoundData *sound)
{
	waveData = (uint8_t*)sound->pSoundData;		//set the pointer
	waveCounter = sound->length;				//init counter
	HAL_TIM_Base_Start_IT(&htim3);				//start the timer
}



/////////////////////////////////////////////////
//Dump sound data to DAC bits
//DAC_Bit0 - DAC_Bit4, located on the following
//pins (should be all in the same row on the
//Nucleo board:
//PB13, PB14, PB15, PB1, PB2
//capture the top 5 bits in value
void Sound_DAC_Write(uint8_t value)
{
	HAL_GPIO_WritePin(DAC_Bit4_GPIO_Port, DAC_Bit4_Pin, (GPIO_PinState)((value >> 7) & 0x01));
	HAL_GPIO_WritePin(DAC_Bit3_GPIO_Port, DAC_Bit3_Pin, (GPIO_PinState)((value >> 6) & 0x01));
	HAL_GPIO_WritePin(DAC_Bit2_GPIO_Port, DAC_Bit2_Pin, (GPIO_PinState)((value >> 5) & 0x01));
	HAL_GPIO_WritePin(DAC_Bit1_GPIO_Port, DAC_Bit1_Pin, (GPIO_PinState)((value >> 4) & 0x01));
	HAL_GPIO_WritePin(DAC_Bit0_GPIO_Port, DAC_Bit0_Pin, (GPIO_PinState)((value >> 3) & 0x01));
}


void Sound_Play_PlayerFire(void)
{
	Sound_PlaySound(&wavSoundPlayerFire);
}
void Sound_Play_EnemyFire(void)
{
	Sound_PlaySound(&wavSoundEnemyFire);
}

void Sound_Play_PlayerExplode(void)
{
	Sound_PlaySound(&wavSoundPlayerExplode);
}

void Sound_Play_EnemyExplode(void)
{
	Sound_PlaySound(&wavSoundEnemyExplode);
}

void Sound_Play_GameOver(void)
{
	Sound_PlaySound(&wavSoundPlayerExplode);
}

void Sound_Play_LevelUp(void)
{
	Sound_PlaySound(&wavSoundLevelUp);
}


