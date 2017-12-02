/*
Sprite header file

*/

#ifndef __SPRITE_H
#define __SPRITE_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include "Graphics.h"
#include "Memory.h"


///////////////////////////////////
//defines
#define TILE_HEADER		30		//pixel offset from top
#define NUM_TILES		40
#define NUM_TILE_ROWS	5
#define NUM_TILE_COLS	8

#define SCREEN_TOP		8
#define SCREEN_BOTTOM	311
#define SCREEN_LEFT		8
#define SCREEN_RIGHT	231

#define PLAYER_NUM_PLAYERS	2
#define PLAYER_DEFAULT_X	100
#define PLAYER_DEFAULT_Y	290


////////////////////////////////
//Direction enum
//support only a few angles to make
//the math easier and keep ball movements
//at max pixels in any direction
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

typedef enum
{
	SURFACE_HORIZONTAL,
	SURFACE_VERTICAL,
}SurfaceOrientation_t;


typedef enum
{
	GAME_SPEED_LOW = 1,
	GAME_SPEED_MEDIUM = 2,
	GAME_SPEED_FAST = 3
}GameSpeed_t;

typedef enum
{
	GAME_MODE_DEMO,
	GAME_MODE_TOUCH_SCREEN,
	GAME_MODE_SLIDE_POT
}GameMode_t;

//structs
typedef struct 
{
	uint32_t x;
	uint32_t y;
	uint32_t sizeX;
	uint32_t sizeY;
	SpriteDirection_t angle;
	const ImageData* image;

}BallStruct;


//tiles
typedef struct
{
	uint8_t life;
	uint32_t x;
	uint32_t y;
	uint32_t sizeX;
	uint32_t sizeY;
	uint16_t points;
	void (*tileHandler)(void);
	const ImageData* image;
}TileStruct;

//player
typedef struct
{
	uint8_t numLives;
	uint32_t x;
	uint32_t y;
	uint32_t sizeX;
	uint32_t sizeY;
	const ImageData* image;
}PlayerStruct;





void Sprite_Init(void);
void Ball_Init(void);
void Tile_Init(void);
void Player_Init(void);

void Sprite_Ball_Move(void);
void Sprite_Player_Move(void);

void Sprite_Draw(void);

uint8_t Sprite_GetActiveDisplayBuffer(void);

void Sprite_ClearBallMissedFlag(void);
uint8_t Sprite_GetBallMissedFlag(void);
void Sprite_DisplayDroppedBall(void);
void Sprite_DisplayGameOver(void);
void Sprite_DisplayGameStart(void);



uint16_t Sprite_GetNumTiles(void);
uint8_t Sprite_GetNumPlayers(void);

void Sprite_ResetGameScore(void);
uint16_t Sprite_GetGameScore(void);

void Sprite_GameMode_SetMode(GameMode_t mode);
void Sprite_GameMode_ToggleMode(void);
GameMode_t Sprite_GameMode_GetMode(void);


void Sprite_ResetGameLevel(void);
uint8_t Sprite_GetGameLevel(void);
void Sprite_SetGameLevel(uint8_t level);
void Sprite_IncreaseGameLevel(void);

void Sprite_GameSpeedIncrease(void);
void Sprite_SetGameSpeed(GameSpeed_t speed);
GameSpeed_t Sprite_GetGameSpeed(void);

uint16_t Sprite_GetPlayerX(void);
void Sprite_SetPlayerX(uint16_t xPos);


SpriteDirection_t Sprite_GetReboundAngle(SpriteDirection_t object, SurfaceOrientation_t orientation);
int Sprite_Get_DX_FromAngle(SpriteDirection_t angle);	//base 2
int Sprite_Get_DY_FromAngle(SpriteDirection_t angle);	//base 2


#endif
