/*////////////////////////////////////////////////////
Sound - DAC output




*/////////////////////////////////////////////////////
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "main.h"

#include "Sound.h"
#include "dac.h"
#include "tim.h"


static uint8_t* waveData;
static uint32_t waveCounter;
static void Sound_PlaySound(const SoundData *sound);


////////////////////////////////
//
void Sound_Init(void)
{
	//start the dac
	HAL_TIM_Base_Stop_IT(&htim7);
	HAL_DAC_Start(&hdac, DAC1_CHANNEL_2);
	HAL_DAC_SetValue(&hdac, DAC1_CHANNEL_2, DAC_ALIGN_8B_R, 0x00);
}

/////////////////////////////////////////////
//Sound_InterruptHandler
//Called from Timer TIM7 interrupt handler function
//in main, period elapsed callback
//
//4 is from reading every 4th element.
//since the sample rate on input file is 44khz
//and output is 11khz
void Sound_InterruptHandler(void)
{
	//down counter complete?
	if (waveCounter > 4)
	{
		//output deref waveData ptr to the dac
		HAL_DAC_SetValue(&hdac, DAC1_CHANNEL_2, DAC_ALIGN_8B_R, *waveData);
		waveData+=4;				//increment the pointer
		waveCounter-=4;			//decrement the downcounter
	}

	else
	{
		//stop the timer
		HAL_DAC_SetValue(&hdac, DAC1_CHANNEL_2, DAC_ALIGN_8B_R, 0x00);
		HAL_TIM_Base_Stop_IT(&htim7);
	}
}


////////////////////////////////////////////////
void Sound_PlaySound(const SoundData *sound)
{
	waveData = (uint8_t*)sound->pSoundData;		//set the pointer
	waveCounter = sound->length;

	//start the timer - calls Sound_InterruptHandler
	HAL_TIM_Base_Start_IT(&htim7);
}



void Sound_Play_PlayerFire(void)
{
	Sound_PlaySound(&sound_shootPlayer);
}
void Sound_Play_EnemyFire(void)
{
	Sound_PlaySound(&sound_shootEnemy);
}

void Sound_Play_PlayerExplode(void)
{
	Sound_PlaySound(&sound_explodePlayer);
}

void Sound_Play_EnemyExplode(void)
{
	Sound_PlaySound(&sound_explodePlayer);
}


void Sound_Play_GameOver(void)
{
	Sound_PlaySound(&sound_gameover);
}

void Sound_Play_LevelUp(void)
{
	Sound_PlaySound(&sound_levelup);
}

