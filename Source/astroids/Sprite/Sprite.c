/*
/////////////////////////////////////////////////
Sprite Controller File
Dana Olcott 2/2018

Function definitions for all sprite control functions.
Main sprites in the program consist of:

Player - Move, rotate, and fire
Missle - Move, hit, remove astroids on impact
Astroids - Move, when hit by missile, removed

Player - 48x48 image captured at various rotation angles
Missle - A simple block to draw
Astroids - 30x30 image

Player and astroids wrap to other side of the screen
if it goes off the LCD.

Hopefully the functions are not too messed up to follow.

/////////////////////////////////////////////////////////
*/
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "Sprite.h"
#include "Graphics.h"
#include "adc.h"
#include "Bitmap.h"
#include "Sound.h"

//player, astroid, missiles
static PlayerStruct mPlayer;
static AstroidStruct mAstroid[NUM_ASTROID];
static MissileStruct mMissile[NUM_MISSILE];

//flags - polled in main loop
static uint8_t mMissileLaunchFlag;			//missile launch
static uint8_t mPlayerRotateCWFlag;			//rotate player clockwise
static uint8_t mPlayerRotateCCWFlag;		//rotate player clockwise
static uint8_t mPlayerThrustFlag;			//fire thrusters
static uint8_t mPlayerSpecialEventFlag;		//special event flag

static uint8_t mActiveDisplayLayer;			//flip btw 2 layers for drawing

static uint32_t mGameScore;
static uint8_t mGameLevel;
static uint8_t mGameOverFlag;


///////////////////////////////////////////
//Local delay not linked to a timer
//
void Sprite_DummyDelay(uint32_t delay)
{
    volatile uint32_t time = delay;

    while (time > 0)
        time--;
}

/////////////////////////////////////
//init all sprites in the game
void Sprite_Init(void)
{
	//init the random number generator.  For use in computing
	//initial positions of the astroids
	//rand() % (max_number + 1 - minimum_number) + minimum_number
	//random enemy array index.
	uint32_t tempLeft = rand() % (79 + 1 - 0) + 0;
	uint32_t tempRight = rand() % (200 + 1 - 160) + 160;

	//init flags
    mMissileLaunchFlag = 0x00;			//missile launch
    mPlayerRotateCWFlag = 0x00;			//rotate player clockwise
    mPlayerRotateCCWFlag = 0x00;		//rotate player clockwise
    mPlayerThrustFlag = 0x00;			//fire thrusters
    mPlayerSpecialEventFlag = 0x00;		//special event flag

    mActiveDisplayLayer = 0x00;			//initial display layer

    mGameScore = 0x00;
    mGameLevel = 1;

    mGameOverFlag = 0x00;


    Sprite_Player_Init();				//init sprites
    Sprite_Astroid_Init();
    Sprite_Missile_Init();
}




////////////////////////////////////////////
//Player init - sets up the mPlayer struct
//at an initial position on the screen, lives,
//movement, etc
void Sprite_Player_Init(void)
{

	mPlayer.numLives = PLAYER_DEFAULT_LIVES;
    mPlayer.image = &bmvan0Bmp;
	mPlayer.x = PLAYER_DEFAULT_X;
	mPlayer.y = PLAYER_DEFAULT_Y;
	mPlayer.sizeX = bmvan0Bmp.xSize;
	mPlayer.sizeY = bmvan0Bmp.ySize;
	mPlayer.direction = SPRITE_DIRECTION_0;
	mPlayer.rotation = SPRITE_DIRECTION_0;
	mPlayer.speed = SPRITE_SPEED_STOP;
	mPlayer.thrusterOn = 0x00;		//off
	mPlayer.thrustTimeout = SPRITE_THRUSTER_TIMEOUT_VALUE;		//reset timeout
}


////////////////////////////////////////////////
//Astroid init
//Sets up the mAstroid array with 1/2 of the
//astroids on one side of the screen and 1/2 on
//the other.  Offset left and right are random
//they start out moving up and down, but the
//directions get altered in the main loop.
//
void Sprite_Astroid_Init(void)
{
    uint8_t count = 0;
    for (int i = 0 ; i < NUM_ASTROID / 2 ; i++)
    {
    	uint32_t left = rand() % (39 + 1 - 0) + 0;			//random offset
    	uint32_t offset = rand() % (19 + 1 - 10) + 10;		//random offset

		mAstroid[count].life = 1;                           //life - 1 = alive, 0 = dead
		mAstroid[count].image = &imgTile;             		//pointer to image data
		mAstroid[count].points = 30;                        //points
		mAstroid[count].x = left;              				//x position
		mAstroid[count].y = i * (imgTile.ySize + offset); 	//y position
		mAstroid[count].sizeX = imgTile.xSize;        		//image width
		mAstroid[count].sizeY = imgTile.ySize;        		//image height
		mAstroid[count].bearing = BEARING_0;   				//initial direction
		mAstroid[count].speed = SPRITE_SPEED_SLOW;			//initial speed
		mAstroid[count].size = ASTROID_SIZE_SMALL;     		//moving down

		count++;
    }

    for (int i = 0; i < NUM_ASTROID / 2 ; i++)
    {
    	uint32_t right = rand() % (200 + 1 - 160) + 160;	//random offset
    	uint32_t offset = rand() % (19 + 1 - 10) + 10;		//random offset

		mAstroid[count].life = 1;                           //life - 1 = alive, 0 = dead
		mAstroid[count].image = &imgTile;             		//pointer to image data
		mAstroid[count].points = 30;                        //points
		mAstroid[count].x = right;              			//x position
		mAstroid[count].y = i * (imgTile.ySize + offset); 	//y position
		mAstroid[count].sizeX = imgTile.xSize;        		//image width
		mAstroid[count].sizeY = imgTile.ySize;        		//image height
		mAstroid[count].bearing = BEARING_180;   			//initial direction
		mAstroid[count].speed = SPRITE_SPEED_SLOW;			//initial speed
		mAstroid[count].size = ASTROID_SIZE_SMALL;     		//moving down

		count++;
    }
}


///////////////////////////////////////
//Missile Init
//Setup the missile array with initial
//position, speed, directin, etc.
//
void Sprite_Missile_Init(void)
{
    for (int i = 0 ; i < NUM_MISSILE ; i++)
    {
        mMissile[i].life = 0;                          //life - 1 = alive, 0 = dead
        mMissile[i].x = 0;
        mMissile[i].y = 0;
        mMissile[i].size = 10;
        mMissile[i].direction = SPRITE_DIRECTION_0;		//should be heading of player
        mMissile[i].speed = SPRITE_SPEED_STOP;
    }
}



///////////////////////////////////////////
//Player move.
//player moves in direction, not rotation
//for each call to player move, the thruster
//timeout tick decrements by 1.  timeout
//and thrusters on are stored in player sturct
//one timeout complete, the speed goes
//to 0
//Player can move multiple pixels on a single move,
//not like astroids.
//
void Sprite_Player_Move(void)
{

	if ((mPlayer.thrustTimeout > 0) && (mPlayer.speed != SPRITE_SPEED_STOP))
	{
		if (mPlayer.numLives > 0)
		{
			//move player according to direction not rotation.
			int dx = Sprite_GetDX_FromDirection(mPlayer.direction, mPlayer.speed);
			int dy = Sprite_GetDY_FromDirection(mPlayer.direction, mPlayer.speed);

			//move the ship and wrap, just like the astroids.
			//x-direction

			if ((dx  >  0) && ((mPlayer.x + dx) < (LCD_WIDTH - 1)))
				mPlayer.x += dx;

			//moving right, wrap
			else if ((dx  >  0) && ((mPlayer.x + dx) >= (LCD_WIDTH - 1)))
				mPlayer.x = (mPlayer.x + dx) - LCD_WIDTH;

			//moving left - no wrap
			else if ((dx  <  0) && (((int)mPlayer.x + dx) >= 0 ))
				mPlayer.x -= (uint32_t)(-1 * dx);

			//moving left - wrap
			else if ((dx  <  0) && (((-1*dx) > mPlayer.x)))
				mPlayer.x = LCD_WIDTH - 1 - (uint32_t)(-1 * dx);

			////////////////////////////////////////////////////
			//y-direction
			//moving down - dy > 0
			if (dy > 0)
			{
				if ((mPlayer.y + dy) <= (LCD_HEIGHT - 1))
					mPlayer.y += dy;

				else
					mPlayer.y = (mPlayer.y + dy) - LCD_HEIGHT;
			}

			else if (!dy)
				mPlayer.y = mPlayer.y;

			//moving up
			else
			{
				uint32_t delta = (uint32_t)(-1*dy);

				if (mPlayer.y >= delta)
					mPlayer.y -= delta;
				else
					mPlayer.y = LCD_HEIGHT - 1 - delta;
			}

		}
		else
		{
			//no other lives.
		}

		//decrement the timeout
		mPlayer.thrustTimeout--;

		//after decrementing, check if it timed out and
		//speed reduces to slow
		if (!mPlayer.thrustTimeout)
		{
			if (mPlayer.speed == SPRITE_SPEED_MEDIUM)
			{
				mPlayer.speed = SPRITE_SPEED_SLOW;						//reduce speed
				mPlayer.thrustTimeout = SPRITE_THRUSTER_TIMEOUT_VALUE;	//reset
			}
			else if (mPlayer.speed == SPRITE_SPEED_SLOW)
			{
				mPlayer.speed = SPRITE_SPEED_STOP;
				mPlayer.thrustTimeout = 0;
			}
		}

	}

	else
	{
		//thruster = 0, so set speed to stop, timeout
		//is reset in the thruster event.
		mPlayer.speed = SPRITE_SPEED_STOP;
	}

}

/////////////////////////////////////////////////////
//Astroid Move
//Loop over all astroid.  If the life == 1,
//move the astroid based on speed and bearing.
//
//
void Sprite_Astroid_Move(void)
{
	int dx, dy;
	uint32_t pX, pY, aTop, aBot, aLeft, aRight = 0x00;


	for (int i = 0 ; i < NUM_ASTROID ; i++)
	{
		if (mAstroid[i].life == 1)
		{
			dx = Sprite_GetDX_FromBearing(mAstroid[i].bearing, mAstroid[i].speed);
			dy = Sprite_GetDY_FromBearing(mAstroid[i].bearing, mAstroid[i].speed);

			//////////////////////////////////////////////////
			//x-direction
			if ((dx  >  0) && ((mAstroid[i].x + dx) <= (LCD_WIDTH - 1)))
				mAstroid[i].x += dx;

			//moving right, wrap
			else if ((dx  >  0) && ((mAstroid[i].x + dx) > (LCD_WIDTH - 1)))
				mAstroid[i].x = (mAstroid[i].x + dx) - LCD_WIDTH;

			//moving left
			else if (dx < 0)
			{
				uint32_t delta = (uint32_t)(-1 * dx);

				//moving left, no wrap
				if (mAstroid[i].x >= delta)
					mAstroid[i].x -= delta;
				else
				{
					mAstroid[i].x = LCD_WIDTH - 1 - delta;
				}
			}


			//////////////////////////////////////////////////
			//y-direction
			//moving down, no wrap
			if ((dy  >  0) && ((mAstroid[i].y < (LCD_HEIGHT -1))))
				mAstroid[i].y += dy;

			else if ((dy  >  0) && ((mAstroid[i].y >= (LCD_HEIGHT -1))))
				mAstroid[i].y = 0;

			//moving down, wrap
			else if ((dy  >  0) && ((mAstroid[i].y + dy) >= (LCD_HEIGHT - 1)))
				mAstroid[i].y = (mAstroid[i].y + dy) - LCD_HEIGHT;

			//moving up - no wrap - these are all 1, so..
			else if ((dy  <  0) && (mAstroid[i].y > 0))
				mAstroid[i].y = ((int)mAstroid[i].y + dy);

			//moving up - wrap
			else if ((dy  <  0) && (!mAstroid[i].y))
				mAstroid[i].y = LCD_HEIGHT - 1;


			//Did the astroid hit the player?? - astroid index
			//is i, mPlayer.  current index i is alive and already moved
			//
			//get the player x, y, ... etc.  Center of the astroid + padding?
			//has to be in the edge of the player
			//uint32_t pX, pY, aTop, aBot, aLeft, aRight = 0x00;
			pX = mPlayer.x + mPlayer.sizeX / 2;
			pY = mPlayer.y + mPlayer.sizeY / 2;

			//center of the player has to be in the footprint of the astroid
			aTop = mAstroid[i].y;
			aBot = mAstroid[i].y + mAstroid[i].sizeY;
			aLeft = mAstroid[i].x;
			aRight = mAstroid[i].x + mAstroid[i].sizeX;

			if ((pX >= aLeft) && (pX <= aRight) && (pY >= aTop) && (pY <= aBot))
			{
				//astroid hit player - remove a player and astroid
				//play sound, increment score, etc.
				//repositions the player
				int rem = Sprite_Astroid_ScorePlayerHit(i);

				//if !rem, all astroid is cleared and reset
				if (!rem)
				{
					Sound_Play_LevelUp(); 	//play a sound
					Sprite_Astroid_Init();  //reset the astroid
					mGameLevel++;
				}

			}


		}
	}
}


////////////////////////////////////////////
//loop over all player missile and 
//enemy missile.  if life == 1
//move it.  Player missiles move up (y-)
//and enemy missiles move down (y+)  
void Sprite_Missile_Move(void)
{
    uint16_t mX, mY, bot, top, left, right = 0x00;
    uint32_t delta = 0x00;

    for (int i = 0 ; i < NUM_MISSILE ; i++)
    {
    	//alive and moving - moving the missiles
    	if ((mMissile[i].life == 1) && (mMissile[i].speed != SPRITE_SPEED_STOP))
    	{
        	//get dx and dy from direction and speed and move
        	int dx = Sprite_GetDX_FromDirection(mMissile[i].direction, mMissile[i].speed);
        	int dy = Sprite_GetDY_FromDirection(mMissile[i].direction, mMissile[i].speed);

        	//x direction
        	if (dx < 0)
        	{
        		delta = (-1*dx);

        		if (mMissile[i].x >= delta)
        			mMissile[i].x -= delta;
        		else
        		{
        			//delta is greater than x....  its moving off the screen, so kill it
        			mMissile[i].life = 0;
        			mMissile[i].speed = SPRITE_SPEED_STOP;
        			mMissile[i].direction = SPRITE_DIRECTION_0;
        		}
        	}

        	//positive dx - moving right
        	else
        	{
        		delta = dx;

        		if ((mMissile[i].x + delta) <= (LCD_WIDTH - 1))
        			mMissile[i].x += delta;

        		else
        		{
        			//delta is greater than x....  its moving off the screen, so kill it
        			mMissile[i].life = 0;
        			mMissile[i].speed = SPRITE_SPEED_STOP;
        			mMissile[i].direction = SPRITE_DIRECTION_0;
        		}
        	}


        	//y direction
			if (dy < 0)
			{
				delta = (-1*dy);

				if (mMissile[i].y >= delta)
					mMissile[i].y -= delta;
				else
				{
					//delta is greater than y....  its moving off the screen, so kill it
					mMissile[i].life = 0;
					mMissile[i].speed = SPRITE_SPEED_STOP;
					mMissile[i].direction = SPRITE_DIRECTION_0;
				}
			}

			//positive dy - moving down or nothing
			else
			{
				delta = dy;

				if ((mMissile[i].y + delta) <= (LCD_HEIGHT - 1))
					mMissile[i].y += delta;

				else
				{
					//delta is greater than y - it's moving off bottom of screen
					mMissile[i].life = 0;
					mMissile[i].speed = SPRITE_SPEED_STOP;
					mMissile[i].direction = SPRITE_DIRECTION_0;
				}
			}
    	}

    	//done moving and leaving the screen.... now, check
    	//to see if it hit anything
    	if ((mMissile[i].life == 1) && (mMissile[i].speed != SPRITE_SPEED_STOP))
		{
    		for (int j = 0 ; j < NUM_ASTROID ; j++)
    		{
    			//hit a live astroid...
    			if (mAstroid[j].life == 1)
    			{
    				mX = mMissile[i].x + mMissile[i].size / 2;	//use center of the blob
    				mY = mMissile[i].y + mMissile[i].size / 2;	//use center of the blob

					bot = mAstroid[j].y + mAstroid[j].sizeY - ASTROID_IMAGE_PADDING;
					top = mAstroid[j].y + ASTROID_IMAGE_PADDING;
					left = mAstroid[j].x + ASTROID_IMAGE_PADDING;
					right = mAstroid[j].x + mAstroid[j].sizeX - ASTROID_IMAGE_PADDING;

					//tip of the missile in the enemy box?
					if ((mX >= left) && (mX <= right) && (mY <= bot) && (mY >= top))
					{
						//score hit!! - pass astroid index and missile index and
						//returns remaining astroids

						int rem = Sprite_Missile_ScoreAstroidHit(j, i);

						//if !rem, all astroid is cleared and reset
						if (!rem)
						{
							Sound_Play_LevelUp(); 	//play a sound
							Sprite_Astroid_Init();  //reset the astroid
							mGameLevel++;
						}
					}
    			}
    		}		//end of astroid loop
		}
    }
}


/////////////////////////////////////////////
//get the array index of the next available
//missile and set life = 1, direction and
//speed same as player
void Sprite_Missile_Launch(void)
{
    int nextMissile = Sprite_GetNextMissile();

    if (nextMissile >= 0)
    {
    	//play launch sound....
    	Sound_Play_PlayerFire();

    	int dx = Sprite_Missile_XOffsetFromPlayerRotation(mPlayer.rotation, mPlayer.speed);
    	int dy = Sprite_Missile_YOffsetFromPlayerRotation(mPlayer.rotation, mPlayer.speed);

        //set the missile in the array as live
    	mMissile[nextMissile].life = 1;
    	mMissile[nextMissile].size = MISSILE_SIZE;
    	mMissile[nextMissile].direction = mPlayer.rotation;		//fire in direction of player rotation
    	mMissile[nextMissile].speed = SPRITE_SPEED_MEDIUM;

    	//set the x
    	if (dx >= 0)
    		mMissile[nextMissile].x = mPlayer.x + dx;
    	else
    	{
    		uint32_t d = (uint32_t)(-1* dx);
    		if (d <= mPlayer.x)
    			mMissile[nextMissile].x = mPlayer.x - d;
    		else
    			mMissile[nextMissile].x = mPlayer.x;
    	}

    	//set the y
    	if (dy >= 0)
    		mMissile[nextMissile].y = mPlayer.y + dy;
    	else
    	{
    		uint32_t d = (uint32_t)(-1* dy);
    		if (d <= mPlayer.y)
    			mMissile[nextMissile].y = mPlayer.y - d;
    		else
    			mMissile[nextMissile].y = mPlayer.y;
    	}
    }
}


////////////////////////////////////////
//returns the index of the array element
//containing the next missile with live = 0
//returns -1 for no available missiles
int Sprite_GetNextMissile(void)
{
    for (int i = 0 ; i < NUM_MISSILE ; i++)
    {
        if (!(mMissile[i].life))
            return i;
    }

    return - 1;
}



/////////////////////////////////////////////
void Sprite_SetMissileLaunchFlag(void)
{
    mMissileLaunchFlag = 1;
}

/////////////////////////////////////////////
uint8_t Sprite_GetMissileLaunchFlag(void)
{
    return mMissileLaunchFlag;
}

void Sprite_ClearMissileLaunchFlag(void)
{
	mMissileLaunchFlag = 0;
}





////////////////////////////////////////////////
//Score hit from player missile to the astroid.
//Play sound, reset the astroid to default values
//reset missile to default values.
//get the number of astroids remaining and return
//num remaining
int Sprite_Missile_ScoreAstroidHit(uint8_t astroidIndex, uint8_t missileIndex)
{
	Sound_Play_EnemyExplode();

	mGameScore += mAstroid[astroidIndex].points;	//get points if you get hit

	//remove astroid and set x and y 0
	mAstroid[astroidIndex].life = 0;
	mAstroid[astroidIndex].x = 0;
	mAstroid[astroidIndex].y = 0;

	//remove the missile
	mMissile[missileIndex].life = 0;
	mMissile[missileIndex].x = 0;
	mMissile[missileIndex].y = 0;

	int rem = Sprite_GetNumAstroid();

	return rem;
}


//////////////////////////////////////////////////
//Score - Astroid Hits Player
//Remove one player life.
//remove astroid.
//play explosion and image sequence.
//use dummy delay
//set game over flag if it's the last player
int Sprite_Astroid_ScorePlayerHit(uint8_t astroidIndex)
{
	Sound_Play_PlayerExplode();

	//show a sequence of images at player x and y
	LCD_DrawBitmapWrap(mActiveDisplayLayer, mPlayer.x, mPlayer.y, &bmvan0_exp0Bmp, BLACK);

	Sprite_DummyDelay(2000000);
	LCD_DrawBox(mActiveDisplayLayer, mPlayer.x, mPlayer.y, mPlayer.sizeX, mPlayer.sizeY, SPRITE_BACKGROUND_COLOR);
	LCD_DrawBitmapWrap(mActiveDisplayLayer, mPlayer.x, mPlayer.y, &bmvan0_exp1Bmp, BLACK);
	Sprite_DummyDelay(2000000);
	LCD_DrawBox(mActiveDisplayLayer, mPlayer.x, mPlayer.y, mPlayer.sizeX, mPlayer.sizeY, SPRITE_BACKGROUND_COLOR);
	LCD_DrawBitmapWrap(mActiveDisplayLayer, mPlayer.x, mPlayer.y, &bmvan0_exp2Bmp, BLACK);
	Sprite_DummyDelay(2000000);
	LCD_DrawBox(mActiveDisplayLayer, mPlayer.x, mPlayer.y, mPlayer.sizeX, mPlayer.sizeY, SPRITE_BACKGROUND_COLOR);
	LCD_DrawBitmapWrap(mActiveDisplayLayer, mPlayer.x, mPlayer.y, &bmvan0_exp3Bmp, BLACK);
	Sprite_DummyDelay(2000000);
	LCD_DrawBox(mActiveDisplayLayer, mPlayer.x, mPlayer.y, mPlayer.sizeX, mPlayer.sizeY, SPRITE_BACKGROUND_COLOR);
	LCD_DrawBitmapWrap(mActiveDisplayLayer, mPlayer.x, mPlayer.y, &bmvan0_exp4Bmp, BLACK);
	Sprite_DummyDelay(2000000);
	LCD_DrawBox(mActiveDisplayLayer, mPlayer.x, mPlayer.y, mPlayer.sizeX, mPlayer.sizeY, SPRITE_BACKGROUND_COLOR);
	LCD_DrawBitmapWrap(mActiveDisplayLayer, mPlayer.x, mPlayer.y, &bmvan0_exp5Bmp, BLACK);
	Sprite_DummyDelay(2000000);
	LCD_DrawBox(mActiveDisplayLayer, mPlayer.x, mPlayer.y, mPlayer.sizeX, mPlayer.sizeY, SPRITE_BACKGROUND_COLOR);
	LCD_DrawBitmapWrap(mActiveDisplayLayer, mPlayer.x, mPlayer.y, &bmvan0_exp6Bmp, BLACK);
	Sprite_DummyDelay(2000000);

	//remove the astroid
	mGameScore += mAstroid[astroidIndex].points;		//get points if you get hit
	mAstroid[astroidIndex].life = 0;					//dead
	mAstroid[astroidIndex].x = 0;						//default x
	mAstroid[astroidIndex].y = 0;						//default y
	mAstroid[astroidIndex].speed = SPRITE_SPEED_STOP;	//speed

	//remove the player
	mPlayer.numLives--;

	//reset the position of the player
	uint8_t lives = mPlayer.numLives;
	Sprite_Player_Init();
	mPlayer.numLives = lives;

	//game over??
	if (!mPlayer.numLives)
		mGameOverFlag = 1;

	int rem = Sprite_GetNumAstroid();
	return rem;

}






/////////////////////////////////////////////////
//Position the starting point of the missile
//from the player based on rotation and speed
//x offset
int Sprite_Missile_XOffsetFromPlayerRotation(SpriteDirection_t rotation, SpriteSpeed_t speed)
{
	int offset = 0x00;
	int dx = 0x00;

	///////////////////////////////////////
	//set the multiplier based on the speed
	switch(speed)
	{
		case SPRITE_SPEED_STOP: 	offset = 8;		break;
		case SPRITE_SPEED_SLOW: 	offset = 8;		break;
		case SPRITE_SPEED_MEDIUM: 	offset = 8;		break;
		case SPRITE_SPEED_FAST: 	offset = 8;		break;
		default:					offset = 8;		break;
	}

	//////////////////////////////////////
	//set the dx from direction
	switch(rotation)
	{
		case SPRITE_DIRECTION_0:	dx =  mPlayer.sizeX;				break;
		case SPRITE_DIRECTION_26:	dx =  mPlayer.sizeX + offset;		break;
		case SPRITE_DIRECTION_45:	dx =  mPlayer.sizeX;				break;
		case SPRITE_DIRECTION_63:	dx =  mPlayer.sizeX /2 + offset;	break;
		case SPRITE_DIRECTION_90:	dx =  mPlayer.sizeX /2;				break;
		case SPRITE_DIRECTION_116:	dx = offset;						break;
		case SPRITE_DIRECTION_135:	dx = offset;						break;
		case SPRITE_DIRECTION_153:	dx = -1 * offset;					break;
		case SPRITE_DIRECTION_180:	dx = -1 * offset;					break;
		case SPRITE_DIRECTION_206:	dx = -1 * offset / 2;				break;
		case SPRITE_DIRECTION_225:	dx = -1 * offset;					break;
		case SPRITE_DIRECTION_243:	dx = 0;								break;
		case SPRITE_DIRECTION_270:	dx = mPlayer.sizeX / 2;				break;
		case SPRITE_DIRECTION_296:	dx = mPlayer.sizeX - offset;		break;
		case SPRITE_DIRECTION_315:	dx = mPlayer.sizeX - offset;		break;
		case SPRITE_DIRECTION_333:	dx = mPlayer.sizeX;					break;
		default:					dx = 0;								break;
	}

	return dx;
}

/////////////////////////////////////////////////
//Position the starting point of the missile
//from the player based on rotation and speed
//y offset
int Sprite_Missile_YOffsetFromPlayerRotation(SpriteDirection_t rotation, SpriteSpeed_t speed)
{
	int offset = 0x00;
	int dy = 0x00;

	///////////////////////////////////////
	//set the multiplier based on the speed
	switch(speed)
	{
		case SPRITE_SPEED_STOP: 	offset = 8;		break;
		case SPRITE_SPEED_SLOW: 	offset = 8;		break;
		case SPRITE_SPEED_MEDIUM: 	offset = 8;		break;
		case SPRITE_SPEED_FAST: 	offset = 8;		break;
		default:					offset = 8;		break;
	}

	//////////////////////////////////////
	//set the dx from direction
	switch(rotation)
	{
		case SPRITE_DIRECTION_0:	dy =  mPlayer.sizeY / 2;			break;
		case SPRITE_DIRECTION_26:	dy =  mPlayer.sizeY / 4;			break;
		case SPRITE_DIRECTION_45:	dy =  0;							break;
		case SPRITE_DIRECTION_63:	dy =  -1 * offset;					break;
		case SPRITE_DIRECTION_90:	dy =  -1 * offset;					break;
		case SPRITE_DIRECTION_116:	dy =  -1 * offset;					break;
		case SPRITE_DIRECTION_135:	dy =  -1 * offset;					break;
		case SPRITE_DIRECTION_153:	dy =   0;							break;
		case SPRITE_DIRECTION_180:	dy =  mPlayer.sizeY / 2;			break;
		case SPRITE_DIRECTION_206:	dy = mPlayer.sizeY / 2;				break;
		case SPRITE_DIRECTION_225:	dy = mPlayer.sizeY;					break;
		case SPRITE_DIRECTION_243:	dy = mPlayer.sizeY;					break;
		case SPRITE_DIRECTION_270:	dy = mPlayer.sizeY;					break;
		case SPRITE_DIRECTION_296:	dy = mPlayer.sizeY;					break;
		case SPRITE_DIRECTION_315:	dy = mPlayer.sizeY - offset;		break;
		case SPRITE_DIRECTION_333:	dy = (mPlayer.sizeY / 2) + offset;	break;
		default:					dy = 0;								break;
	}

	return dy;
}










////////////////////////////////////
//Get remaining number of players
uint8_t Sprite_GetNumPlayers(void)
{
    return mPlayer.numLives;
}

////////////////////////////////////
//Get number of live astroids
int Sprite_GetNumAstroid(void)
{
    int num = 0;
    for (int i = 0 ; i < NUM_ASTROID ; i++)
    {
        if (mAstroid[i].life == 1)
            num++;
    }

    return num;
}


///////////////////////////////////////////////
//GetRandomAstroid
//Returns the index of a randomly selected
//astroid from a collection of live astroids.
//
int Sprite_GetRandomAstroid(void)
{
    int num = Sprite_GetNumAstroid();

    if (num > 0)
    {
        //get the random index
        //rand() % (max_number + 1 - minimum_number) + minimum_number
        //index is the count within a set of live astroids.
        int index = rand() % (num - 1 + 1 - 0) + 0;
        int counter = 0;

        for (int i = 0 ; i < NUM_ASTROID ; i++)
        {
            if (mAstroid[i].life == 1)
            {
                if (index == counter)
                    return counter;

                counter++;      //increment only for live enemy
            }
        }
    }

    return -1;
}

//////////////////////////////////////////
//Change the trajectory of a randomly selected
//astroid.  Change by one enum value in Bearing,
//randomly move increase or decrease in bearing
//offset from true/vertical.  Keep in range
//
int Sprite_WormHole(void)
{
	int index = Sprite_GetRandomAstroid();
    int shift = rand() % (2) + 1;		//1 or 2

	//valid??
	if (index >= 0)
	{
		Bearing_t bearing = mAstroid[index].bearing;

		//bearing shift clockwise or ccw based on shift
		if (shift == 1)
		{
			switch (bearing)
			{
				case BEARING_0: 	mAstroid[index].bearing = BEARING_5;		break;
				case BEARING_5: 	mAstroid[index].bearing = BEARING_10;		break;
				case BEARING_10: 	mAstroid[index].bearing = BEARING_5;		break;
				case BEARING_355: 	mAstroid[index].bearing = BEARING_0;		break;
				case BEARING_350: 	mAstroid[index].bearing = BEARING_355;		break;
				case BEARING_170: 	mAstroid[index].bearing = BEARING_175;		break;
				case BEARING_175: 	mAstroid[index].bearing = BEARING_180;		break;
				case BEARING_180: 	mAstroid[index].bearing = BEARING_185;		break;
				case BEARING_185: 	mAstroid[index].bearing = BEARING_190;		break;
				case BEARING_190: 	mAstroid[index].bearing = BEARING_185;		break;
				//represents an error, so make it obvious
				default:			mAstroid[index].bearing = BEARING_180;		break;
			}
		}
		else
		{
			switch (bearing)
			{
				case BEARING_0: 	mAstroid[index].bearing = BEARING_355;		break;
				case BEARING_5: 	mAstroid[index].bearing = BEARING_0;		break;
				case BEARING_10: 	mAstroid[index].bearing = BEARING_5;		break;
				case BEARING_355: 	mAstroid[index].bearing = BEARING_350;		break;
				case BEARING_350: 	mAstroid[index].bearing = BEARING_355;		break;

				case BEARING_170: 	mAstroid[index].bearing = BEARING_175;		break;
				case BEARING_175: 	mAstroid[index].bearing = BEARING_170;		break;
				case BEARING_180: 	mAstroid[index].bearing = BEARING_175;		break;
				case BEARING_185: 	mAstroid[index].bearing = BEARING_180;		break;
				case BEARING_190: 	mAstroid[index].bearing = BEARING_185;		break;
				//represents an error, so make it obvious
				default:			mAstroid[index].bearing = BEARING_0;		break;
			}
		}
	}

	return index;
}

/////////////////////////////////////////////////////
//Update the display.
//Get the next available display layer (one not
//being currently displayed), clear it, draw items on
//it, and flip as active display layer
//
void Sprite_UpdateDisplay(void)
{
	char buffer[40];

	uint8_t nextLayer = Sprite_GetNextDisplayLayer();

	//clear the page
	LCD_Clear(nextLayer, SPRITE_BACKGROUND_COLOR);

	Sprite_Player_Draw(nextLayer);			//draw player
	Sprite_Astroid_Draw(nextLayer);			//draw astroids
	Sprite_Missle_Draw(nextLayer);			//draw missiles

	//draw the score, number of players, level... etc
	memset(buffer, 0x00, 40);
	int n = sprintf(buffer, "S:%04d L:%d P:%d", (int)mGameScore, mGameLevel, mPlayer.numLives);

	///draw with transparent color = back ground for text
	LCD_DrawStringLengthTransparent(nextLayer, 0, BLACK, buffer, n);

	//set the current display layer to look at nextLayer
	LCD_SetDisplayLayer0(nextLayer);
}



////////////////////////////////////////////////
//Get Next Active Display Layer
//Sets and returns the active layer.
//See Sprite_SetActiveDisplayLayer to point
//LCD at the layer.
//
uint8_t Sprite_GetNextDisplayLayer(void)
{
	if (!mActiveDisplayLayer)
		mActiveDisplayLayer = 1;
	else
		mActiveDisplayLayer = 0;

	return mActiveDisplayLayer;
}



///////////////////////////////////////////////
//Sprite_SetActiveDisplayLayer
//Set the active display layer on LCD
//Layer 0.  Points the LCD framebuffer to
//appropriate address in SDRAM
//
void Sprite_SetActiveDisplayLayer(uint8_t layer)
{
	LCD_SetDisplayLayer0(layer);
}


/////////////////////////////////////////////
//Draws game over on the lcd
//
void Sprite_DisplayGameOver(void)
{
	uint8_t nextLayer = Sprite_GetNextDisplayLayer();

	LCD_Clear(nextLayer, BLACK);
	LCD_DrawString(nextLayer, 3, "  Press Button");
	LCD_DrawString(nextLayer, 5, "    To Start");

	LCD_SetDisplayLayer0(nextLayer);
}




/////////////////////////////////////////////
//Draw the player icon at the player x,y
//position.  Transparent color arg (in this
//case black) is based on the background of the
//player image.  Set to an obscure value if
//one does not want to use transparent color.
//Transparent color is not drawn.  (ie, pointer
//simply skips over it).
//
void Sprite_Player_Draw(uint8_t layer)
{
    if (mPlayer.numLives > 0)
    {
    	LCD_DrawBitmapWrap(layer, mPlayer.x, mPlayer.y, mPlayer.image, BLACK);
    }
}

////////////////////////////////////////////
//Draw Astroid
//Draw all astroids with life = 1
//
void Sprite_Astroid_Draw(uint8_t layer)
{
    for (int i = 0 ; i < NUM_ASTROID ; i++)
    {
        if (mAstroid[i].life == 1)
        {
        	LCD_DrawBitmapWrap(layer, mAstroid[i].x, mAstroid[i].y, mAstroid[i].image, WHITE);
        }
    }
}



/////////////////////////////////////////////////
//Draw Missile.
//Draw all inflight missiles - red circles
//
void Sprite_Missle_Draw(uint8_t layer)
{
    for (int i = 0 ; i < NUM_MISSILE ; i++)
    {
        //check enemy missile
        if (mMissile[i].life == 1)
        {
        	LCD_DrawCircleFill(layer, mMissile[i].x, mMissile[i].y, mMissile[i].size / 2, RED);
        }
    }
}


////////////////////////////////////////////
//Helper - Get dX from direction and speed
//All dx and dy based on 2 pixel minimum delta.
//ie, 45 deg angle is 2 pixels up and 2 over
//for a multiplier of 1
//
int Sprite_GetDX_FromDirection(SpriteDirection_t direction, SpriteSpeed_t speed)
{
	int multiplier = 0x00;
	int dx = 0x00;

	///////////////////////////////////////
	//set the multiplier based on the speed
	switch(speed)
	{
		case SPRITE_SPEED_STOP: 	multiplier = 0;		break;
		case SPRITE_SPEED_SLOW: 	multiplier = 1;		break;
		case SPRITE_SPEED_MEDIUM: 	multiplier = 2;		break;
		case SPRITE_SPEED_FAST: 	multiplier = 3;		break;
		default:					multiplier = 1;		break;
	}

	//////////////////////////////////////
	//set the dx from direction
	switch(direction)
	{
		case SPRITE_DIRECTION_0:	dx =  2 * multiplier;	break;
		case SPRITE_DIRECTION_26:	dx =  2 * multiplier;	break;
		case SPRITE_DIRECTION_45:	dx =  2 * multiplier;	break;
		case SPRITE_DIRECTION_63:	dx =  1 * multiplier;	break;
		case SPRITE_DIRECTION_90:	dx =  0 * multiplier;	break;
		case SPRITE_DIRECTION_116:	dx = -1 * multiplier;	break;
		case SPRITE_DIRECTION_135:	dx = -2 * multiplier;	break;
		case SPRITE_DIRECTION_153:	dx = -2 * multiplier;	break;
		case SPRITE_DIRECTION_180:	dx = -2 * multiplier;	break;
		case SPRITE_DIRECTION_206:	dx = -2 * multiplier;	break;
		case SPRITE_DIRECTION_225:	dx = -2 * multiplier;	break;
		case SPRITE_DIRECTION_243:	dx = -1 * multiplier;	break;
		case SPRITE_DIRECTION_270:	dx = 0 * multiplier;	break;
		case SPRITE_DIRECTION_296:	dx = 1 * multiplier;	break;
		case SPRITE_DIRECTION_315:	dx = 2 * multiplier;	break;
		case SPRITE_DIRECTION_333:	dx = 2 * multiplier;	break;
		default:					dx = 2 * multiplier;	break;
	}

	return dx;
}

/////////////////////////////////////////////
//Helper - Get dY from direction and speed
//All dy base on 2 pixel minimum delta.
//ie, 45 deg angle is 2 up and 2 over for a
//multiplier of 1.
//
int Sprite_GetDY_FromDirection(SpriteDirection_t direction, SpriteSpeed_t speed)
{
	int multiplier = 0x00;
	int dy = 0x00;

	///////////////////////////////////////
	//set the multiplier based on the speed
	switch(speed)
	{
		case SPRITE_SPEED_STOP: 	multiplier = 0;		break;
		case SPRITE_SPEED_SLOW: 	multiplier = 1;		break;
		case SPRITE_SPEED_MEDIUM: 	multiplier = 2;		break;
		case SPRITE_SPEED_FAST: 	multiplier = 3;		break;
		default:					multiplier = 1;		break;
	}

	//////////////////////////////////////
	//set the dx from direction
	switch(direction)
	{
		case SPRITE_DIRECTION_0:	dy =  0 * multiplier;	break;
		case SPRITE_DIRECTION_26:	dy =  -1 * multiplier;	break;
		case SPRITE_DIRECTION_45:	dy =  -2 * multiplier;	break;
		case SPRITE_DIRECTION_63:	dy =  -2 * multiplier;	break;
		case SPRITE_DIRECTION_90:	dy =  -2 * multiplier;	break;
		case SPRITE_DIRECTION_116:	dy =  -2 * multiplier;	break;
		case SPRITE_DIRECTION_135:	dy =  -2 * multiplier;	break;
		case SPRITE_DIRECTION_153:	dy =  -1 * multiplier;	break;
		case SPRITE_DIRECTION_180:	dy =  0 * multiplier;	break;
		case SPRITE_DIRECTION_206:	dy =  1 * multiplier;	break;
		case SPRITE_DIRECTION_225:	dy =  2 * multiplier;	break;
		case SPRITE_DIRECTION_243:	dy =  2 * multiplier;	break;
		case SPRITE_DIRECTION_270:	dy =  2 * multiplier;	break;
		case SPRITE_DIRECTION_296:	dy =  2 * multiplier;	break;
		case SPRITE_DIRECTION_315:	dy =  2 * multiplier;	break;
		case SPRITE_DIRECTION_333:	dy =  1 * multiplier;	break;
		default:					dy =  0 * multiplier;	break;
	}

	return dy;
}


//////////////////////////////////////////////////////////
//Get DX from Bearing.
//Used for computing movements to astroid array.
//Increment is 5 degrees and evaluated every 11 game
//cycles. ie, tan -1 (1/11) about 5 deg.
//
int Sprite_GetDX_FromBearing(Bearing_t bearing, SpriteSpeed_t speed)
{
	int multiplier = 0x00;
	int dx = 0x00;

	//static counter for tracking modulus
	static uint32_t dxCounter = 0x00;

	///////////////////////////////////////
	//set the multiplier based on the speed
	switch(speed)
	{
		case SPRITE_SPEED_STOP: 	multiplier = 0;		break;
		case SPRITE_SPEED_SLOW: 	multiplier = 1;		break;
		case SPRITE_SPEED_MEDIUM: 	multiplier = 2;		break;
		case SPRITE_SPEED_FAST: 	multiplier = 3;		break;
		default:					multiplier = 1;		break;
	}

	//////////////////////////////////////
	//set the dx from bearing
	switch(bearing)
	{
		case BEARING_170:	dx =  -2 * multiplier;	break;
		case BEARING_175:	dx =  -1 * multiplier;	break;
		case BEARING_180:	dx =  0 * multiplier;	break;
		case BEARING_185:	dx =  1 * multiplier;	break;
		case BEARING_190:	dx =  2 * multiplier;	break;
		case BEARING_350:	dx =  -2 * multiplier;	break;
		case BEARING_355:	dx =  -1 * multiplier;	break;
		case BEARING_0:		dx =  0 * multiplier;	break;
		case BEARING_5:		dx =  1 * multiplier;	break;
		case BEARING_10:	dx =  2 * multiplier;	break;
		default:			dx =  0 * multiplier;	break;
	}


	//only return values on %11 to get 5 deg increments
	if ((dxCounter % 11) > 0)
		dx = 0;

	dxCounter++;

	return dx;
}


//////////////////////////////////////////////////////////
//Get DY from Bearing.
//Used for computing movements to astroid array.
//Increment is 5 degrees.  Restricted  to vertically
//oriented movements.  y direction is therefore always
//one pixel in the general direction.  x direction evaluated
//every 11 cycles.
//
int Sprite_GetDY_FromBearing(Bearing_t bearing, SpriteSpeed_t speed)
{
	int multiplier = 0x00;
	int dy = 0x00;

	///////////////////////////////////////
	//set the multiplier based on the speed
	switch(speed)
	{
		case SPRITE_SPEED_STOP: 	multiplier = 0;		break;
		case SPRITE_SPEED_SLOW: 	multiplier = 1;		break;
		case SPRITE_SPEED_MEDIUM: 	multiplier = 2;		break;
		case SPRITE_SPEED_FAST: 	multiplier = 3;		break;
		default:					multiplier = 1;		break;
	}

	//////////////////////////////////////
	//set the dy from bearing
	switch(bearing)
	{
		case BEARING_170:	dy =  1 * multiplier;	break;
		case BEARING_175:	dy =  1 * multiplier;	break;
		case BEARING_180:	dy =  1 * multiplier;	break;
		case BEARING_185:	dy =  1 * multiplier;	break;
		case BEARING_190:	dy =  1 * multiplier;	break;

		case BEARING_350:	dy =  -1 * multiplier;	break;
		case BEARING_355:	dy =  -1 * multiplier;	break;
		case BEARING_0:		dy =  -1 * multiplier;	break;
		case BEARING_5:		dy =  -1 * multiplier;	break;
		case BEARING_10:	dy =  -1 * multiplier;	break;
		default:			dy =  0 * multiplier;	break;
	}

	return dy;
}



/////////////////////////////////////////
//Player rotate flag = CW.  Called in
//Joystick ADC conversion complete callback,
//
void Sprite_PlayerSetRotateCWFlag(void)
{
	mPlayerRotateCWFlag = 1;
}

/////////////////////////////////////////
//Player rotate flag = CW.
//return flag status
//
uint8_t Sprite_PlayerGetRotateCWFlag(void)
{
	return mPlayerRotateCWFlag;
}

/////////////////////////////////////////
//Player rotate flag = CW.
//Function called in the main loop.
void Sprite_PlayerClearRotateCWFlag(void)
{
	mPlayerRotateCWFlag = 0;
}

/////////////////////////////////////////
//Player rotate flag = CCW.  Called in
//Joystick ADC conversion complete callback,
//
void Sprite_PlayerSetRotateCCWFlag(void)
{
	mPlayerRotateCCWFlag = 1;
}

/////////////////////////////////////////
//Player rotate flag = CCW.
//return flag status
//
uint8_t Sprite_PlayerGetRotateCCWFlag(void)
{
	return mPlayerRotateCCWFlag;
}

/////////////////////////////////////////
//Player rotate flag = CCW.
//Function called in main()
void Sprite_PlayerClearRotateCCWFlag(void)
{
	mPlayerRotateCCWFlag = 0;
}


/////////////////////////////////////////////
//Rotate player CW and set the image pointer
//
void Sprite_PlayerRotateCW(void)
{
	SpriteDirection_t current = Sprite_PlayerGetRotation();
	SpriteDirection_t next = current;

	switch(current)
	{
		case SPRITE_DIRECTION_0:	next = SPRITE_DIRECTION_26;		break;
		case SPRITE_DIRECTION_26:	next = SPRITE_DIRECTION_45;		break;
		case SPRITE_DIRECTION_45:	next = SPRITE_DIRECTION_63;		break;
		case SPRITE_DIRECTION_63:	next = SPRITE_DIRECTION_90;		break;
		case SPRITE_DIRECTION_90:	next = SPRITE_DIRECTION_116;	break;
		case SPRITE_DIRECTION_116:	next = SPRITE_DIRECTION_135;	break;
		case SPRITE_DIRECTION_135:	next = SPRITE_DIRECTION_153;	break;
		case SPRITE_DIRECTION_153:	next = SPRITE_DIRECTION_180;	break;
		case SPRITE_DIRECTION_180:	next = SPRITE_DIRECTION_206;	break;
		case SPRITE_DIRECTION_206:	next = SPRITE_DIRECTION_225;	break;
		case SPRITE_DIRECTION_225:	next = SPRITE_DIRECTION_243;	break;
		case SPRITE_DIRECTION_243:	next = SPRITE_DIRECTION_270;	break;
		case SPRITE_DIRECTION_270:	next = SPRITE_DIRECTION_296;	break;
		case SPRITE_DIRECTION_296:	next = SPRITE_DIRECTION_315;	break;
		case SPRITE_DIRECTION_315:	next = SPRITE_DIRECTION_333;	break;
		case SPRITE_DIRECTION_333:	next = SPRITE_DIRECTION_0;		break;
		default:					next = SPRITE_DIRECTION_90;		break;
	}

	Sprite_PlayerSetRotation(next);

}



//////////////////////////////////////////////
//Rotate player CCW and set the image pointer
//
void Sprite_PlayerRotateCCW(void)
{
	SpriteDirection_t current = Sprite_PlayerGetRotation();
	SpriteDirection_t next = current;

	switch(current)
	{
		case SPRITE_DIRECTION_0:	next = SPRITE_DIRECTION_333;	break;
		case SPRITE_DIRECTION_26:	next = SPRITE_DIRECTION_0;		break;
		case SPRITE_DIRECTION_45:	next = SPRITE_DIRECTION_26;		break;
		case SPRITE_DIRECTION_63:	next = SPRITE_DIRECTION_45;		break;
		case SPRITE_DIRECTION_90:	next = SPRITE_DIRECTION_63;		break;
		case SPRITE_DIRECTION_116:	next = SPRITE_DIRECTION_90;		break;
		case SPRITE_DIRECTION_135:	next = SPRITE_DIRECTION_116;	break;
		case SPRITE_DIRECTION_153:	next = SPRITE_DIRECTION_135;	break;
		case SPRITE_DIRECTION_180:	next = SPRITE_DIRECTION_153;	break;
		case SPRITE_DIRECTION_206:	next = SPRITE_DIRECTION_180;	break;
		case SPRITE_DIRECTION_225:	next = SPRITE_DIRECTION_206;	break;
		case SPRITE_DIRECTION_243:	next = SPRITE_DIRECTION_225;	break;
		case SPRITE_DIRECTION_270:	next = SPRITE_DIRECTION_243;	break;
		case SPRITE_DIRECTION_296:	next = SPRITE_DIRECTION_270;	break;
		case SPRITE_DIRECTION_315:	next = SPRITE_DIRECTION_296;	break;
		case SPRITE_DIRECTION_333:	next = SPRITE_DIRECTION_315;	break;
		default:					next = SPRITE_DIRECTION_90;		break;
	}

	Sprite_PlayerSetRotation(next);

}


/////////////////////////////////////////////////
//Sprite_PlayerSetRotation
//Set rotation and update the image pointer.  Rotation
//refers to the orientation of the ship and affects
//firing and direction changes when thrusters are on.
//
void Sprite_PlayerSetRotation(SpriteDirection_t rotation)
{
	ImageData* ptr = (ImageData*)&bmvan0Bmp;
	mPlayer.rotation = rotation;

	//set the image pointer
	switch(rotation)
	{
		case SPRITE_DIRECTION_0:	ptr = (ImageData*)&bmvan0Bmp; 		break;
		case SPRITE_DIRECTION_26:	ptr = (ImageData*)&bmvan26Bmp; 		break;
		case SPRITE_DIRECTION_45:	ptr = (ImageData*)&bmvan45Bmp; 		break;
		case SPRITE_DIRECTION_63:	ptr = (ImageData*)&bmvan63Bmp; 		break;
		case SPRITE_DIRECTION_90:	ptr = (ImageData*)&bmvan90Bmp; 		break;
		case SPRITE_DIRECTION_116:	ptr = (ImageData*)&bmvan116Bmp; 	break;
		case SPRITE_DIRECTION_135:	ptr = (ImageData*)&bmvan135Bmp; 	break;
		case SPRITE_DIRECTION_153:	ptr = (ImageData*)&bmvan153Bmp; 	break;
		case SPRITE_DIRECTION_180:	ptr = (ImageData*)&bmvan180Bmp; 	break;
		case SPRITE_DIRECTION_206:	ptr = (ImageData*)&bmvan206Bmp; 	break;
		case SPRITE_DIRECTION_225:	ptr = (ImageData*)&bmvan225Bmp; 	break;
		case SPRITE_DIRECTION_243:	ptr = (ImageData*)&bmvan243Bmp; 	break;
		case SPRITE_DIRECTION_270:	ptr = (ImageData*)&bmvan270Bmp; 	break;
		case SPRITE_DIRECTION_296:	ptr = (ImageData*)&bmvan296Bmp; 	break;
		case SPRITE_DIRECTION_315:	ptr = (ImageData*)&bmvan315Bmp; 	break;
		case SPRITE_DIRECTION_333:	ptr = (ImageData*)&bmvan333Bmp; 	break;
		default:					ptr = (ImageData*)&bmvan90Bmp; 		break;
	}

	//image data
	mPlayer.image = ptr;			//image data
	mPlayer.sizeX = ptr->xSize;		//sizeX
	mPlayer.sizeY = ptr->ySize;		//sizeY

}


SpriteDirection_t Sprite_PlayerGetRotation(void)
{
	return mPlayer.rotation;
}


/////////////////////////////////////////
//Player Fire Thruster.
//Increases player speed.  For now, only one
//speed is implemented.  Sets a gametick
//timeout on player move.  This is stored in the
//player move function.  Sets a thruster
//on flag that is evaluated in the main loop
//
void Sprite_PlayerFireThruster(void)
{
	static uint8_t thrustCount = SPRITE_ACCELERATION_TIMEOUT_VALUE;

	//play sound
	Sound_Play_Thruster();

	//enable thrusters and reset the timeout
	//timeout counts down in player move function
	//velocity decreases when thrustTimeout = 0
	//
	mPlayer.thrusterOn = 1;
	mPlayer.thrustTimeout = SPRITE_THRUSTER_TIMEOUT_VALUE;

	//TODO: Make this more detailed, allowing ship
	//to slide in one direction with thrusters an other
	//with direction set as average of the two.
	//This is a simplification for now.

	if (mPlayer.speed == SPRITE_SPEED_STOP)
	{
		mPlayer.speed = SPRITE_SPEED_SLOW;
		thrustCount = SPRITE_ACCELERATION_TIMEOUT_VALUE;
	}
	else if (mPlayer.speed == SPRITE_SPEED_SLOW)
	{
		//hold slow for thruster timeout value
		if (thrustCount > 0)
			thrustCount--;
		else
		{
			thrustCount = SPRITE_ACCELERATION_TIMEOUT_VALUE;
			mPlayer.speed = SPRITE_SPEED_MEDIUM;
		}

	}

	//set the direction based on the current rotation.
	Sprite_PlayerSetDirection(mPlayer.rotation);

}

void Sprite_PlayerSetDirection(SpriteDirection_t direction)
{
	mPlayer.direction = direction;
}

SpriteDirection_t Sprite_PlayerGetDirection(void)
{
	return mPlayer.direction;
}



///////////////////////////////////////
//Set Thruster Flag
//Called from ADC Conversion Complete callback
//on a joystick event.  This flag is polled
//in the main loop.
void Sprite_PlayerSetThursterFlag(void)
{
	mPlayerThrustFlag = 1;
}

//////////////////////////////////////////
//Get Thruster Flag
//Polled in the main loop
uint8_t Sprite_PlayerGetThrusterFlag(void)
{
	return mPlayerThrustFlag;
}

//////////////////////////////////////////
//Clear Thruster Flag
//Cleared in the main loop
void Sprite_PlayerClearThrusterFlag(void)
{
	mPlayerThrustFlag = 0;
}

//////////////////////////////////////////
//Special Event Flag
//Function called in the ADC Conversion
//Complete callback.  Special event is
//called from a joystick back movement
//it's supposed to represent the special
//function in astroids (ie, rotate 180 deg,
//shields, relocate...)
void Sprite_PlayerSetSpecialEventFlag(void)
{
	mPlayerSpecialEventFlag = 1;
}

/////////////////////////////////////////////
//Called in the main loop
uint8_t Sprite_PlayerGetSpecialEventFlag(void)
{
	return mPlayerSpecialEventFlag;
}


///////////////////////////////////////////
//Called in the main loop.
void Sprite_PlayerClearSpecialEventFlag(void)
{
	mPlayerSpecialEventFlag = 0;
}


////////////////////////////////////////////
//
void Sprite_ClearGameOverFlag(void)
{
	mGameOverFlag = 0x00;
}

void Sprite_SetGameOverFlag(void)
{
	mGameOverFlag = 1;
}

uint8_t Sprite_GetGameOverFlag(void)
{
	return mGameOverFlag;
}





