//////////////////////////////////////////////////
/*
Dana Olcott - 2018
Astroids Sprite Header File

Defines and prototypes for controlling the player
and astroid sprites.

*/
//////////////////////////////////////////////////

#ifndef __SPRITE_H
#define __SPRITE_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include "Graphics.h"
#include "Bitmap.h"


/////////////////////////////////////////
//defines
#define NUM_ASTROID				12			//num astroids in the game
#define ASTROID_IMAGE_PADDING	2			//padding for eval hit/miss

#define PLAYER_DEFAULT_LIVES    5			//player
#define PLAYER_DEFAULT_X        120
#define PLAYER_DEFAULT_Y        160

#define NUM_MISSILE    8
#define MISSILE_SIZE	6

#define SPRITE_MAX_X        239				//game area
#define SPRITE_MIN_X        0
#define SPRITE_MAX_Y        319
#define SPRITE_MIN_Y        0

#define SPRITE_BACKGROUND_COLOR		BLUE

#define SPRITE_THRUSTER_TIMEOUT_VALUE		50		//engine run timeout

/////////////////////////////////////////
//Direction enum
//support only a few angles to make
//the math easier and keep player movements,
//rotation, and astroid movements easy
//
typedef enum
{
	SPRITE_DIRECTION_0,
	SPRITE_DIRECTION_26,
	SPRITE_DIRECTION_45,
	SPRITE_DIRECTION_63,
	SPRITE_DIRECTION_90,
	SPRITE_DIRECTION_116,
	SPRITE_DIRECTION_135,
	SPRITE_DIRECTION_153,
	SPRITE_DIRECTION_180,
	SPRITE_DIRECTION_206,
	SPRITE_DIRECTION_225,
	SPRITE_DIRECTION_243,
	SPRITE_DIRECTION_270,
	SPRITE_DIRECTION_296,
	SPRITE_DIRECTION_315,
	SPRITE_DIRECTION_333,

}SpriteDirection_t;


///////////////////////////////////////////
//Bearing.  Used for astroids, 5 deg increments
//offset evaluated on % 11 to get dx/dy
//
typedef enum
{
	BEARING_170,		//down
	BEARING_175,
	BEARING_180,
	BEARING_185,
	BEARING_190,
	BEARING_350,		//up
	BEARING_355,
	BEARING_0,
	BEARING_5,
	BEARING_10,
}Bearing_t;


//////////////////////////////////////////
//Astroid Size - small, med, large
//draw appropriate bitmap based on size
typedef enum
{
	ASTROID_SIZE_SMALL,
	ASTROID_SIZE_MEDIUM,
	ASTROID_SIZE_LARGE,
}AstroidSize_t;



////////////////////////////////////////////
//Speed - multipliers for dx/dy in direction
typedef enum
{
	SPRITE_SPEED_STOP = 0,
	SPRITE_SPEED_SLOW = 1,
	SPRITE_SPEED_MEDIUM = 2,
	SPRITE_SPEED_FAST = 3,

}SpriteSpeed_t;

////////////////////////////////////////
//Player Definition
//
typedef struct
{
	uint8_t numLives;
	uint32_t x;
	uint32_t y;
	uint32_t sizeX;
	uint32_t sizeY;
	SpriteDirection_t direction;
	SpriteDirection_t rotation;
	SpriteSpeed_t speed;
	const ImageData* image;
	uint8_t thrusterOn;			//engine on?
	uint8_t thrustTimeout;		//gametick for timeout

}PlayerStruct;

///////////////////////////////////////
//Astroid Defintion
//
typedef struct
{
	uint8_t life;
	uint32_t x;
	uint32_t y;
	uint32_t sizeX;
	uint32_t sizeY;
	uint16_t points;
	Bearing_t bearing;
    SpriteSpeed_t speed;
    AstroidSize_t size;
	const ImageData* image;
}AstroidStruct;


///////////////////////////////////////////
//missile struct
//use a circle for the missle image
typedef struct
{
	uint8_t life;               //active / not active
	uint32_t x;
	uint32_t y;
	uint32_t size;
    SpriteDirection_t direction;
    SpriteSpeed_t speed;

}MissileStruct;



void Sprite_DummyDelay(uint32_t delay);

void Sprite_Init(void);
void Sprite_Player_Init(void);
void Sprite_Astroid_Init(void);
void Sprite_Missile_Init(void);

void Sprite_Player_Move(void);
void Sprite_Astroid_Move(void);
void Sprite_Missile_Move(void);

void Sprite_Missile_Launch(void);
int Sprite_GetNextMissile(void);

void Sprite_SetMissileLaunchFlag(void);
uint8_t Sprite_GetMissileLaunchFlag(void);
void Sprite_ClearMissileLaunchFlag(void);

int Sprite_Missile_ScoreAstroidHit(uint8_t astroidIndex, uint8_t missileIndex);

int Sprite_Astroid_ScorePlayerHit(uint8_t astroidIndex);


int Sprite_Missile_XOffsetFromPlayerRotation(SpriteDirection_t rotation, SpriteSpeed_t speed);
int Sprite_Missile_YOffsetFromPlayerRotation(SpriteDirection_t rotation, SpriteSpeed_t speed);


uint8_t Sprite_GetNumPlayers(void);
int Sprite_GetNumAstroid(void);

int Sprite_GetRandomAstroid(void);

int Sprite_WormHole(void);



void Sprite_UpdateDisplay(void);
uint8_t Sprite_GetNextDisplayLayer(void);
void Sprite_SetDisplayLayer(uint8_t layer);

void Sprite_DisplayGameOver(void);


void Sprite_Player_Draw(uint8_t layer);
void Sprite_Astroid_Draw(uint8_t layer);
void Sprite_Missle_Draw(uint8_t layer);

//player
int Sprite_GetDX_FromDirection(SpriteDirection_t direction, SpriteSpeed_t speed);
int Sprite_GetDY_FromDirection(SpriteDirection_t direction, SpriteSpeed_t speed);

int Sprite_GetDX_FromBearing(Bearing_t bearing, SpriteSpeed_t speed);
int Sprite_GetDY_FromBearing(Bearing_t bearing, SpriteSpeed_t speed);


//player rotate flags
void Sprite_PlayerSetRotateCWFlag(void);
uint8_t Sprite_PlayerGetRotateCWFlag(void);
void Sprite_PlayerClearRotateCWFlag(void);

void Sprite_PlayerSetRotateCCWFlag(void);
uint8_t Sprite_PlayerGetRotateCCWFlag(void);
void Sprite_PlayerClearRotateCCWFlag(void);

void Sprite_PlayerRotateCW(void);
void Sprite_PlayerRotateCCW(void);

void Sprite_PlayerSetRotation(SpriteDirection_t rotation);
SpriteDirection_t Sprite_PlayerGetRotation(void);

void Sprite_PlayerFireThruster(void);
void Sprite_PlayerSetDirection(SpriteDirection_t direction);
SpriteDirection_t Sprite_PlayerGetDirection(void);

void Sprite_PlayerSetThursterFlag(void);
uint8_t Sprite_PlayerGetThrusterFlag(void);
void Sprite_PlayerClearThrusterFlag(void);

void Sprite_PlayerSetSpecialEventFlag(void);
uint8_t Sprite_PlayerGetSpecialEventFlag(void);
void Sprite_PlayerClearSpecialEventFlag(void);

void Sprite_ClearGameOverFlag(void);
void Sprite_SetGameOverFlag(void);
uint8_t Sprite_GetGameOverFlag(void);



#endif