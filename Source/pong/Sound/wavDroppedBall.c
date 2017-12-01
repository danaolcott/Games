/*
wavDroppedBall.c
*/
#include <stddef.h>
#include <string.h>

#include "Sound.h"


static const uint8_t soundData[] =
{
	0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00,
};


const SoundData sound_droppedball = 
{
	(uint8_t*)soundData,		//pointer to sound array
	10,							//length
};
