///////////////////////////////////////////////////////
/*
Sound Header File
Good Source of Example sounds:
http://www.downloadfreesound.com/8-bit-sound-effects/

Sound converter from wav to c code:
http://ccgi.cjseymour.plus.com/wavtocode/wavtocode.htm

Sounds assumed to be sampled at 44khz.  To avoid jamming up the
interrupts, run the output at 11khz, so read every 4th sample

*/
//////////////////////////////////////////////////////////

#ifndef __SOUND_H
#define __SOUND_H

#include <stddef.h>
#include <stdint.h>

typedef struct 
{
	const uint8_t* pSoundData;
	uint32_t length;
}SoundData;


//sound arrays
extern const SoundData wavSoundEnemyExplode;
extern const SoundData wavSoundEnemyFire;
extern const SoundData wavSoundLevelUp;
extern const SoundData wavSoundPlayerExplode;
extern const SoundData wavSoundPlayerFire;


void Sound_Init(void);                  //main
void Sound_InterruptHandler(void);      //main
void Sound_DAC_Write(uint8_t value);

void Sound_Play_PlayerFire(void);       //player fire
void Sound_Play_EnemyFire(void);        //enemy fire
void Sound_Play_PlayerExplode(void);
void Sound_Play_EnemyExplode(void);
void Sound_Play_GameOver(void);
void Sound_Play_LevelUp(void);





#endif
