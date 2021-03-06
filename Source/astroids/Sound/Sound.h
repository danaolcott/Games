/*
////////////////////////////////////////////////////
Dana Olcott - 2018
Sound Header File

Controller file for sound data output DAC Ch2
How it works:
Sound on starts TIM7 to run at 11khz
Reset sound data pointer to beginning of sound array
On timeout, output sound data to the 8 bit dac
Increment sound data pointer +=4 (sound file generated
at 44khz but played at 11khz)
Sound off when data pointer reaches the end of the sound array.

Example sounds:
http://www.downloadfreesound.com/8-bit-sound-effects/

Sound converter from wav to c code:
http://ccgi.cjseymour.plus.com/wavtocode/wavtocode.htm

Sounds assumed to be sampled at 44khz.  To avoid jamming up the
interrupts, run the output at 11khz, so read every 4th sample


*/

#ifndef __SOUND_H
#define __SOUND_H

#include <stddef.h>
#include <stdint.h>


typedef struct 
{
	uint8_t* soundData;
	uint32_t length;
	uint8_t bitDepth;
	uint32_t sampleRate;
}SoundData;


//sound arrays
//extern const SoundData sound_gameover;			//ok

extern const SoundData sound_levelUp;			//ok
extern const SoundData sound_enemyExplode;
extern const SoundData sound_playerExplode;
extern const SoundData sound_playerShoot;
extern const SoundData sound_thruster;


void Sound_Init(void);                  //main
void Sound_InterruptHandler(void);      //main







void Sound_Play_PlayerFire(void);       //player fire
void Sound_Play_PlayerExplode(void);
void Sound_Play_EnemyExplode(void);
void Sound_Play_GameOver(void);
void Sound_Play_LevelUp(void);
void Sound_Play_Thruster(void);


#endif
