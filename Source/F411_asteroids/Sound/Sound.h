///////////////////////////////////////////////////////
/*
Sound Header File
Good Source of Example sounds:
http://www.downloadfreesound.com/8-bit-sound-effects/

Sound converter from wav to c code:
http://ccgi.cjseymour.plus.com/wavtocode/wavtocode.htm

Sounds assumed to be sampled at 44khz.  To avoid jamming up the
interrupts, run the output at 11khz and read every 4th sample

NOTE: initially, this read every 4th sample.  I ran out of code
space, so compressed files down to be sampled at 11khz and read
every sample.  The test program for doing this should be in the
linux repository. (still under construction?)

*/
//////////////////////////////////////////////////////////

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
