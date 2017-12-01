/*
Sprite

*/
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "Sprite.h"
#include "Graphics.h"
#include "Memory.h"
#include "Bitmap.h"
#include "TouchPanel.h"
#include "SlidePot.h"		//adc

#include "Sound.h"


static uint16_t spriteGameLevel = 0;
static uint32_t spriteGameScore = 0;
static uint32_t spriteActiveBuffer = 0;
static uint16_t spriteBackColor = BLACK;

static GameMode_t spriteGameMode = GAME_MODE_DEMO;
static GameSpeed_t spriteGameSpeed = GAME_SPEED_LOW;

//players and tiles
static BallStruct mBall;
static TileStruct mTile[NUM_TILES];
static PlayerStruct mPlayer;
static uint8_t spriteBallMissedFlag = 0;


/////////////////////////////////////
//init all sprites in the game
void Sprite_Init(void)
{
	spriteActiveBuffer = 0;
	spriteBackColor = BLACK;
	spriteGameLevel = 0;
	spriteGameSpeed = GAME_SPEED_LOW;

	Sprite_ResetGameScore();
	Sprite_GameMode_SetMode(GAME_MODE_DEMO);
	Sprite_SetGameSpeed(GAME_SPEED_FAST);
	Tile_Init();
	Ball_Init();
	Player_Init();
}

uint8_t Sprite_GetBallMissedFlag(void)
{
	return spriteBallMissedFlag;
}

void Sprite_ClearBallMissedFlag(void)
{
	spriteBallMissedFlag = 0;
}


////////////////////////////////////
//drop a ball..
//pause for a second, write a message
//decrement the player.  resume
//flash dropped ball a few times
void Sprite_DisplayDroppedBall(void)
{
	mPlayer.numLives--;

	if (mPlayer.numLives > 0)
	{
		LCD_SetTextLineColor(WHITE);
		uint8_t buffer = Sprite_GetActiveDisplayBuffer();
		LCD_DrawString(buffer, 5, "Dropped Ball");
		HAL_Delay(1000);

		LCD_SetTextLineColor(BLUE);
		LCD_DrawString(buffer, 5, "Dropped Ball");
		HAL_Delay(1000);

		LCD_SetTextLineColor(WHITE);
		LCD_DrawString(buffer, 5, "Dropped Ball");
		HAL_Delay(1000);

		LCD_SetTextLineColor(BLUE);
		LCD_DrawString(buffer, 5, "Dropped Ball");
		HAL_Delay(1000);

		LCD_SetTextLineColor(WHITE);
	}

}


////////////////////////////////////
//drop a ball..
//pause for a second, write a message
//decrement the player.  resume
void Sprite_DisplayGameOver(void)
{
	LCD_SetTextLineColor(WHITE);
	uint8_t buffer = Sprite_GetActiveDisplayBuffer();
	LCD_DrawString(buffer, 5, "Game Over");
	HAL_Delay(1000);

	LCD_SetTextLineColor(BLUE);
	LCD_DrawString(buffer, 5, "Game Over");
	HAL_Delay(1000);

	LCD_SetTextLineColor(WHITE);
	LCD_DrawString(buffer, 5, "Game Over");
	HAL_Delay(1000);

	LCD_SetTextLineColor(BLUE);
	LCD_DrawString(buffer, 5, "Game Over");
	HAL_Delay(1000);

	LCD_SetTextLineColor(WHITE);
}


void Sprite_DisplayGameStart(void)
{
	uint8_t buffer = Sprite_GetActiveDisplayBuffer();
	LCD_SetTextLineColor(WHITE);
	LCD_DrawString(buffer, 5, "Press Start");

	HAL_Delay(1000);

	LCD_SetTextLineColor(BLUE);
	LCD_DrawString(buffer, 5, "Press Start");


	HAL_Delay(1000);

	LCD_SetTextLineColor(WHITE);

	Tile_Init();
	Player_Init();
	Ball_Init();
	Sprite_ResetGameScore();
	Sprite_SetGameSpeed(GAME_SPEED_LOW);

}

//////////////////////////////////
void Ball_Init(void)
{
	//init the mBall
	mBall.image = &imgBall;		//must be first
	mBall.x = 10;
	mBall.y = 280;
	mBall.sizeX = mBall.image->xSize;
	mBall.sizeY = mBall.image->ySize;
	mBall.angle = SPRITE_DIRECTION_45;
}


void Tile_Init(void)
{
	uint16_t counter = 0x00;
	for (int i = 0 ; i < NUM_TILE_ROWS ; i++)
	{
		for (int j = 0 ; j < NUM_TILE_COLS ; j++)
		{
			mTile[counter].life = 1;
			mTile[counter].image = &imgTile;
			mTile[counter].points = 30;
			mTile[counter].sizeX = 30;
			mTile[counter].sizeY = 30;
			mTile[counter].x = 30 * j;
			mTile[counter].y = (30 * i) + TILE_HEADER;

			counter++;
		}
	}
}

///////////////////////////////
//Player_Init
void Player_Init(void)
{
	mPlayer.numLives = PLAYER_NUM_PLAYERS;
	mPlayer.x = PLAYER_DEFAULT_X;
	mPlayer.y = PLAYER_DEFAULT_Y;
	mPlayer.image = &imgPlayer;
	mPlayer.sizeX = mPlayer.image->xSize;
	mPlayer.sizeY = mPlayer.image->ySize;
}


//////////////////////////////////////////////
//Ball Move
//
void Sprite_Ball_Move(void)
{
	uint32_t bBot, bTop, bLeft, bRight, bX, bY = 0;		//ball
	uint32_t tBot, tTop, tLeft, tRight, tX, tY = 0;		//tile/player

	int dx, dy;
	uint8_t flagTile = 0;
	uint8_t flagBoundary = 0;
	uint8_t tileIndex = 0;
	SpriteDirection_t updated = mBall.angle;

	//evaluate the location of the ball
	bBot = mBall.y + mBall.sizeY;
	bTop = mBall.y;
	bLeft = mBall.x;
	bRight = mBall.x + mBall.sizeX;
	bX = (bLeft + bRight) / 2;
	bY = (bTop + bBot) / 2;

	///////////////////////////////////////////
	//connect with player
	tTop = mPlayer.y;
	tBot = mPlayer.y + mPlayer.sizeY;
	tLeft = mPlayer.x;
	tRight = mPlayer.x + mPlayer.sizeX;
	tY = (tBot + tTop) / 2;

	//ball hit player, with downward direction only
	if ((bX >= tLeft) && (bX <= tRight) && (bBot >= tTop) && (bBot <= (tTop + 4))
			&& (mBall.angle > SPRITE_DIRECTION_180))
	{

		//play sound
		Sound_Play_PlayerBounce();

		//corner - LHS
		if (bLeft <= SCREEN_LEFT)
			updated = SPRITE_DIRECTION_45;
		//corner - RHS
		else if (bRight >= SCREEN_RIGHT)
			updated = SPRITE_DIRECTION_135;
		else
			updated = Sprite_GetReboundAngle(mBall.angle, SURFACE_HORIZONTAL);
	}


	//ball drops out the bottom - set a flag to be evaluated in main
	else if (bTop >= SCREEN_BOTTOM)
		spriteBallMissedFlag = 1;

	//top - lhs corner
	else if ((bTop <= SCREEN_TOP) && (bLeft <= SCREEN_LEFT))
	{
		updated = SPRITE_DIRECTION_315;
		flagBoundary = 1;
	}

	//top - rhs corner
	else if ((bTop <= SCREEN_TOP) && (bRight >= SCREEN_RIGHT))
	{
		updated = SPRITE_DIRECTION_225;
		flagBoundary = 1;
	}

	//top - in the middle somewhere
	else if ((bTop <= SCREEN_TOP) && (bLeft > SCREEN_LEFT) && (bRight < SCREEN_RIGHT))
	{
		updated = Sprite_GetReboundAngle(mBall.angle, SURFACE_HORIZONTAL);
		flagBoundary = 1;
	}


	else if (bLeft <= SCREEN_LEFT)
	{
		//check if it hit it parallel
		if ((mBall.angle == SPRITE_DIRECTION_90) || (mBall.angle == SPRITE_DIRECTION_116))
			updated = SPRITE_DIRECTION_45;
		else if ((mBall.angle == SPRITE_DIRECTION_270) || (mBall.angle == SPRITE_DIRECTION_243))
			updated = SPRITE_DIRECTION_315;
		else
			updated = Sprite_GetReboundAngle(mBall.angle, SURFACE_VERTICAL);

		flagBoundary = 1;

	}

	else if (bRight >= SCREEN_RIGHT)
	{
		//check if it hit it parallel
		if ((mBall.angle == SPRITE_DIRECTION_90) || (mBall.angle == SPRITE_DIRECTION_63))
			updated = SPRITE_DIRECTION_135;
		else if ((mBall.angle == SPRITE_DIRECTION_270) || (mBall.angle == SPRITE_DIRECTION_296))
			updated = SPRITE_DIRECTION_225;
		else
			updated = Sprite_GetReboundAngle(mBall.angle, SURFACE_VERTICAL);

		flagBoundary = 1;

	}

	//hit a tile?
	else
	{
		spriteBallMissedFlag = 0;

		//for each tile....
		for (int i = 0 ; i < NUM_TILES ; i++)
		{
			if (mTile[i].life == 1)
			{
				tBot = mTile[i].y + mTile[i].sizeY;
				tTop = mTile[i].y;
				tLeft = mTile[i].x;
				tRight = mTile[i].x + mTile[i].sizeX;
				tX = (tLeft + tRight) / 2;
				tY = (tTop + tBot) / 2;

				//connect on the top of the ball - bottom of a tile
				if ((bTop <= tBot) && (bTop >= tY) && (bX >= tLeft) && (bX <= tRight))
				{
					//top of ball hit bottom of a tile
					flagTile = 1;
					tileIndex = i;
					i = NUM_TILES - 1;
					updated = Sprite_GetReboundAngle(mBall.angle, SURFACE_HORIZONTAL);
					break;
				}

				//connect on the bottom of ball top of the tile
				else if ((bBot >= tTop) && (bBot <= tY) && (bX >= tLeft) && (bX <= tRight))
				{
					//bottom of ball hit the top of a tile
					flagTile = 1;
					tileIndex = i;
					i = NUM_TILES - 1;
					updated = Sprite_GetReboundAngle(mBall.angle, SURFACE_HORIZONTAL);
					break;
				}

				//connect right side of ball with left side of tile
				else if ((bRight >= tLeft) && (bRight <= tX) && (bY >= tTop) && (bY <= tBot))
				{
					//bottom of ball hit the top of a tile
					flagTile = 1;
					tileIndex = i;
					i = NUM_TILES - 1;
					updated = Sprite_GetReboundAngle(mBall.angle, SURFACE_VERTICAL);
					break;
				}

				//connect left side of ball with right side of tile
				else if ((bLeft <= tRight) && (bLeft >= tX) && (bY >= tTop) && (bY <= tBot))
				{
					//bottom of ball hit the top of a tile
					flagTile = 1;
					tileIndex = i;
					i = NUM_TILES - 1;
					updated = Sprite_GetReboundAngle(mBall.angle, SURFACE_VERTICAL);
					break;
				}

				//don't do anything, and the updated stays as it
				//was at the the top of the function
				else
				{
					flagTile = 0;
				}
			}
		}
	}



	//play only one sound if ball hits tile and boundary
	//at the same time

	//remove the tile
	if (flagTile == 1)
	{
		mTile[tileIndex].life = 0;				//set life to 0
		mTile[tileIndex].image = &imgTileBlank;	//clear the image

		spriteGameScore += mTile[tileIndex].points;

		//play sound
		Sound_Play_PlayerBounce();
	}

	//hit a wall
	else if (flagBoundary == 1)
	{
		Sound_Play_PlayerBounce();
	}

	//compute new x and y position from updated
	//index x and y position by dx and dy
	mBall.angle = updated;
	dx = Sprite_Get_DX_FromAngle(updated);
	dy = Sprite_Get_DY_FromAngle(updated);

	int multiplier = (int)Sprite_GetGameSpeed();


	if ((dx < 0) && (mBall.x <=SCREEN_LEFT))
	{
		mBall.x += ((-1*dx) * multiplier);
		mBall.y += (dy * multiplier);
	}
	else
	{
		mBall.x += (dx * multiplier);
		mBall.y += (dy * multiplier);
	}

}


/////////////////////////////////////
//Move the player to the new
//x and y position.  For now, just
//move the player to follow the x
//position of the ball
//After the slide pot is added, move
//this to ADC
//
//use the touch panel to get the x position
//this function is called in the main loop
//
//touch screen position is updated in the
//interrupt, but the mPlayer is set here.

void Sprite_Player_Move(void)
{
	TouchPanelData data;
	uint16_t adcPosition;


	if (spriteGameMode == GAME_MODE_DEMO)
	{
		if (mBall.x < (mPlayer.sizeX / 2))
			mPlayer.x = 0;
		else if (mBall.x > (SCREEN_RIGHT - mPlayer.sizeX))
			mPlayer.x = SCREEN_RIGHT - mPlayer.sizeX;
		else
			mPlayer.x = mBall.x - (mPlayer.sizeX / 2);
	}
	else if (spriteGameMode == GAME_MODE_TOUCH_SCREEN)
	{
		data = TouchPanel_getPosition();
		Sprite_SetPlayerX(data.xPos);
	}

	else if (spriteGameMode == GAME_MODE_SLIDE_POT)
	{
		adcPosition = SlidePot_ReadPosition();
		Sprite_SetPlayerX(adcPosition);
	}
}


///////////////////////////////////////////
//draw app sprites in the game
//use 2 buffers, always drawing
//in the background and flipping
//
void Sprite_Draw(void)
{
	char buffer[40];
	LCD_SetTextBackColor(BLUE2);
	LCD_SetTextLineColor(WHITE);

	if (!spriteActiveBuffer)
		spriteActiveBuffer = 1;
	else
		spriteActiveBuffer = 0;

	//BUFFER 1 - Draw all items

	//clear the buffer
	LCD_Clear(spriteActiveBuffer, BLUE2);

	//draw the header contents
	memset(buffer, 0x00, 40);
	int n = sprintf(buffer, "S:%04d L:%d P:%d", spriteGameScore, spriteGameLevel, mPlayer.numLives);
	LCD_DrawStringLength(spriteActiveBuffer, 0, buffer, n);

	//draw the game mode if in demo mode
	if (spriteGameMode == GAME_MODE_DEMO)
	{
		LCD_DrawString(spriteActiveBuffer, 9, "   Demo Mode");
		LCD_DrawString(spriteActiveBuffer, 10, "Press To Start");
	}


	//draw the ball
	LCD_DrawBitmapTransparent(spriteActiveBuffer, mBall.x, mBall.y, mBall.image, WHITE);

	//draw the tiles
	for (int i = 0 ; i < NUM_TILES ; i++)
	{
		if (mTile[i].life == 1)
			LCD_DrawBitmapTransparent(spriteActiveBuffer, mTile[i].x, mTile[i].y, mTile[i].image, WHITE);
	}

	//draw the player
	if (mPlayer.numLives > 0)
		LCD_DrawBitmapTransparent(spriteActiveBuffer, mPlayer.x, mPlayer.y, mPlayer.image, WHITE);


	//set the display buffer
	if (!spriteActiveBuffer)
		HAL_LTDC_SetAddress(&hltdc, (uint32_t)SDRAM_LCD_LAYER_0, 0);
	else
		HAL_LTDC_SetAddress(&hltdc, (uint32_t)SDRAM_LCD_LAYER_1, 0);

}

uint8_t Sprite_GetActiveDisplayBuffer(void)
{
	return spriteActiveBuffer;
}


///////////////////////////////////////
uint8_t Sprite_GetNumPlayers(void)
{
	return mPlayer.numLives;
}


////////////////////////////////
//get remaining number of tiles
uint16_t Sprite_GetNumTiles(void)
{
	uint16_t count = 0;
	for (int i = 0 ; i < NUM_TILES ; i++)
	{
		if (mTile[i].life == 1)
			count++;
	}

	return count;
}


void Sprite_ResetGameScore(void)
{
	spriteGameScore = 0;
}

uint16_t Sprite_GetGameScore(void)
{
	return spriteGameScore;
}




void Sprite_GameMode_SetMode(GameMode_t mode)
{
	if ((mode >= GAME_MODE_DEMO) && (mode <= GAME_MODE_SLIDE_POT))
	{
		spriteGameMode = mode;

		switch(spriteGameMode)
		{
			case GAME_MODE_DEMO:

				LCD_DrawString(Sprite_GetActiveDisplayBuffer(), 6, "   GAME MODE");
				LCD_DrawString(Sprite_GetActiveDisplayBuffer(), 7, "   DEMO MODE");
				break;
			case GAME_MODE_TOUCH_SCREEN:
				LCD_DrawString(Sprite_GetActiveDisplayBuffer(), 6, "   GAME MODE");
				LCD_DrawString(Sprite_GetActiveDisplayBuffer(), 7, " TOUCH SCREEN");
				break;

			case GAME_MODE_SLIDE_POT:
				LCD_DrawString(Sprite_GetActiveDisplayBuffer(), 6, "   GAME MODE");
				LCD_DrawString(Sprite_GetActiveDisplayBuffer(), 7, "   SLIDE POT");
				break;

			default:
				LCD_DrawString(Sprite_GetActiveDisplayBuffer(), 6, "   INVALID");
				LCD_DrawString(Sprite_GetActiveDisplayBuffer(), 7, "   GAME MODE");
				break;
		}

		HAL_Delay(2000);

		Tile_Init();
		Player_Init();
		Ball_Init();

		if (spriteGameMode == GAME_MODE_DEMO)
			Sprite_SetGameSpeed(GAME_SPEED_FAST);
		else if (spriteGameMode == GAME_MODE_TOUCH_SCREEN)
			Sprite_SetGameSpeed(GAME_SPEED_LOW);
		else if (spriteGameMode == GAME_MODE_SLIDE_POT)
			Sprite_SetGameSpeed(GAME_SPEED_MEDIUM);
	}
}

void Sprite_GameMode_ToggleMode(void)
{
	switch(spriteGameMode)
	{
		case GAME_MODE_DEMO:
			spriteGameMode = GAME_MODE_TOUCH_SCREEN;
			break;
		case GAME_MODE_TOUCH_SCREEN:
			spriteGameMode = GAME_MODE_SLIDE_POT;
			break;
		case GAME_MODE_SLIDE_POT:
			spriteGameMode = GAME_MODE_DEMO;
			break;
		default:
			spriteGameMode = GAME_MODE_DEMO;
			break;
	}

	Sprite_GameMode_SetMode(spriteGameMode);
}

GameMode_t Sprite_GameMode_GetMode(void)
{
	return spriteGameMode;
}

void Sprite_ResetGameLevel(void)
{
	spriteGameLevel = 0;
}

uint8_t Sprite_GetGameLevel(void)
{
	return spriteGameLevel;
}

void Sprite_SetGameLevel(uint8_t level)
{
	spriteGameLevel = level;
}

void Sprite_IncreaseGameLevel(void)
{
	spriteGameLevel++;
	Sprite_GameSpeedIncrease();
}

void Sprite_GameSpeedIncrease(void)
{
	if (spriteGameSpeed == GAME_SPEED_LOW)
		spriteGameSpeed = GAME_SPEED_MEDIUM;
	else if (spriteGameSpeed == GAME_SPEED_MEDIUM)
		spriteGameSpeed = GAME_SPEED_FAST;
	else
		spriteGameSpeed = GAME_SPEED_FAST;
}

void Sprite_SetGameSpeed(GameSpeed_t speed)
{
	if ((speed >= GAME_SPEED_LOW) && (speed <= GAME_SPEED_FAST))
		spriteGameSpeed = speed;
}

GameSpeed_t Sprite_GetGameSpeed(void)
{
	return spriteGameSpeed;
}


uint16_t Sprite_GetPlayerX(void)
{
	return mPlayer.x;
}

////////////////////////////////////////
//set x position of the player, range
//screen left to right, and adjusted here
//for width of the player
void Sprite_SetPlayerX(uint16_t xPos)
{
	if (xPos < (mPlayer.sizeX / 2))
		mPlayer.x = 0;
	else if (xPos > (SCREEN_RIGHT - mPlayer.sizeX))
		mPlayer.x = SCREEN_RIGHT - mPlayer.sizeX;
	else
		mPlayer.x = xPos - (mPlayer.sizeX / 2);
}


//////////////////////////////////////////////
//compute the rebound direction based on a source
//object direction and a surface.  for now, only
//allow surfaces that are horiz and vertical.
//This is probably the case with all pong objects
SpriteDirection_t Sprite_GetReboundAngle(SpriteDirection_t object, SurfaceOrientation_t orientation)
{
	if (orientation == SURFACE_HORIZONTAL)
	{
		switch(object)
		{

			case SPRITE_DIRECTION_0:	return	SPRITE_DIRECTION_0;
			case SPRITE_DIRECTION_26:	return	SPRITE_DIRECTION_333;
			case SPRITE_DIRECTION_45:	return	SPRITE_DIRECTION_315;
			case SPRITE_DIRECTION_63:	return	SPRITE_DIRECTION_296;
			case SPRITE_DIRECTION_90:	return	SPRITE_DIRECTION_270;
			case SPRITE_DIRECTION_116:	return	SPRITE_DIRECTION_243;
			case SPRITE_DIRECTION_135:	return	SPRITE_DIRECTION_225;
			case SPRITE_DIRECTION_153:	return	SPRITE_DIRECTION_206;
			case SPRITE_DIRECTION_180:	return	SPRITE_DIRECTION_180;
			case SPRITE_DIRECTION_206:	return	SPRITE_DIRECTION_153;
			case SPRITE_DIRECTION_225:	return	SPRITE_DIRECTION_135;
			case SPRITE_DIRECTION_243:	return	SPRITE_DIRECTION_116;
			case SPRITE_DIRECTION_270:	return	SPRITE_DIRECTION_90;
			case SPRITE_DIRECTION_296:	return	SPRITE_DIRECTION_63;
			case SPRITE_DIRECTION_315:	return	SPRITE_DIRECTION_45;
			case SPRITE_DIRECTION_333:	return	SPRITE_DIRECTION_26;
		}
	}
	else if (orientation == SURFACE_VERTICAL)
	{
		switch(object)
		{
			case SPRITE_DIRECTION_0:	return	SPRITE_DIRECTION_180;
			case SPRITE_DIRECTION_26:	return	SPRITE_DIRECTION_153;
			case SPRITE_DIRECTION_45:	return	SPRITE_DIRECTION_135;
			case SPRITE_DIRECTION_63:	return	SPRITE_DIRECTION_116;
			case SPRITE_DIRECTION_90:	return	SPRITE_DIRECTION_90;
			case SPRITE_DIRECTION_116:	return	SPRITE_DIRECTION_63;
			case SPRITE_DIRECTION_135:	return	SPRITE_DIRECTION_45;
			case SPRITE_DIRECTION_153:	return	SPRITE_DIRECTION_26;
			case SPRITE_DIRECTION_180:	return	SPRITE_DIRECTION_0;
			case SPRITE_DIRECTION_206:	return	SPRITE_DIRECTION_333;
			case SPRITE_DIRECTION_225:	return	SPRITE_DIRECTION_315;
			case SPRITE_DIRECTION_243:	return	SPRITE_DIRECTION_296;
			case SPRITE_DIRECTION_270:	return	SPRITE_DIRECTION_270;
			case SPRITE_DIRECTION_296:	return	SPRITE_DIRECTION_243;
			case SPRITE_DIRECTION_315:	return	SPRITE_DIRECTION_225;
			case SPRITE_DIRECTION_333:	return	SPRITE_DIRECTION_206;
		}
	}
	else
	{
		//do nothing
	}

	return SPRITE_DIRECTION_0;
}

int Sprite_Get_DX_FromAngle(SpriteDirection_t angle)
{
	switch(angle)
	{
		case SPRITE_DIRECTION_0:	return 2;
		case SPRITE_DIRECTION_26:	return 2;
		case SPRITE_DIRECTION_45:	return 2;
		case SPRITE_DIRECTION_63:	return 1;
		case SPRITE_DIRECTION_90:	return 0;
		case SPRITE_DIRECTION_116:	return -1;
		case SPRITE_DIRECTION_135:	return -2;
		case SPRITE_DIRECTION_153:	return -2;
		case SPRITE_DIRECTION_180:	return -2;
		case SPRITE_DIRECTION_206:	return -2;
		case SPRITE_DIRECTION_225:	return -2;
		case SPRITE_DIRECTION_243:	return -1;
		case SPRITE_DIRECTION_270:	return	0;
		case SPRITE_DIRECTION_296:	return 1;
		case SPRITE_DIRECTION_315:	return 2;
		case SPRITE_DIRECTION_333:	return 2;
	}

	return 2;
}


//////////////////////////////////////////
//y positive down
int Sprite_Get_DY_FromAngle(SpriteDirection_t angle)
{
	switch(angle)
	{
		case SPRITE_DIRECTION_0:	return 0;
		case SPRITE_DIRECTION_26:	return -1;
		case SPRITE_DIRECTION_45:	return -2;
		case SPRITE_DIRECTION_63:	return -2;
		case SPRITE_DIRECTION_90:	return -2;
		case SPRITE_DIRECTION_116:	return -2;
		case SPRITE_DIRECTION_135:	return -2;
		case SPRITE_DIRECTION_153:	return -1;
		case SPRITE_DIRECTION_180:	return 0;
		case SPRITE_DIRECTION_206:	return 1;
		case SPRITE_DIRECTION_225:	return 2;
		case SPRITE_DIRECTION_243:	return 2;
		case SPRITE_DIRECTION_270:	return 2;
		case SPRITE_DIRECTION_296:	return 2;
		case SPRITE_DIRECTION_315:	return 2;
		case SPRITE_DIRECTION_333:	return 1;
	}

	return 0;
}

