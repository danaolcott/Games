///////////////////////////////////////////////////////
/*
Dana Olcott 2015 +/-

Graphics Lib for the 240 x 320 display on the STM32f429i disco board.
Assumes the SDRAM is properly configured prior to writing
anything to the display.

Layer addresses defined in Memory.h

*/

//////////////////////////////////////////////////////////

#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include "ltdc.h"
#include "bitmap.h"

/* Includes ------------------------------------------------------------------*/


#define LCD_HEIGHT				((uint32_t)320)
#define LCD_WIDTH				((uint32_t)240)
#define DISP_ORIENTATION		0
#define CHAR_HEIGHT				24
#define CHAR_WIDTH				16
#define MAX_ROWS				((uint16_t)(LCD_HEIGHT / CHAR_HEIGHT) - 1)
#define MAX_COLS				((uint16_t)(LCD_WIDTH / CHAR_WIDTH) - 1)


///////////////////////////////////////
//color defines
#define BLACK                   (0x0000)
#define NAVY                    (0x000F)
#define DGREEN                  (0x03E0)
#define DCYAN                   (0x03EF)
#define MAROON                  (0x7800)
#define PURPLE                  (0x780F)
#define OLIVE                   (0x7BE0)
#define GREY                    (0xF7DE)
#define LGRAY                   (0xC618)
#define DGRAY                   (0x7BEF)
#define BLUE                    (0x001F)
#define BLUE2                   (0x051F)
#define GREEN                   (0x07E0)
#define CYAN                    (0x07FF)
#define RED                     (0xF800)
#define MAGENTA                 (0xF81F)
#define YELLOW                  (0xFFE0)
#define WHITE                   (0xFFFF)
#define ORANGE                  (0xF3E4)


/////////////////////////////////////////////
//pallets for use with 8bit color.  These
//values in pallets come from the Segger image
//conversion utility when output as 8bit color
//with pallet table.
//
extern uint32_t colorPalletRGB332[256];
extern uint32_t colorPalletRGB323[256];

/////////////////////////////////////////
//Font color
#define DEFAULT_TEXT_LINE_COLOR 	WHITE
#define DEFAULT_TEXT_BACK_COLOR 	BLACK


/////////////////////////////////////////////////
//function prototypes

void LCD_SetTextLineColor(uint16_t color);
void LCD_SetTextBackColor(uint16_t color);
uint16_t LCD_GetTextLineColor(void);
uint16_t LCD_GetTextBackColor(void);

uint8_t LCD_GetRGB332PalletValue(uint16_t color);
void LCD_Clear(uint32_t layer, uint16_t color);
void LCD_PutPixel(uint32_t layer, uint32_t x, uint32_t y, uint16_t color);
void LCD_DrawLine(uint32_t layer, int x0, int y0, int x1, int y1, uint16_t color);
void LCD_DrawRadius(uint32_t layer, int x0, int y0, int length, int angle, uint16_t color);
void LCD_RotateBuffer(uint32_t sourceLayer, uint32_t destinationLayer, uint16_t angle, int xc, int yc);

void LCD_DrawBox(uint32_t layer, uint32_t x0, uint32_t y0, uint32_t sizeX, uint32_t sizeY, uint16_t color);

//text functions - 16x24 characters
void LCD_DrawChar(uint8_t layer, uint8_t row, uint8_t col, uint8_t letter);
void LCD_DrawString(uint8_t layer, uint8_t row, char* output);
void LCD_DrawStringLength(uint8_t layer, uint8_t row, char output[], uint8_t length);

//bitmaps
void LCD_DrawBitmap(uint32_t layer, uint32_t x0, uint32_t y0, const ImageData* image);
void LCD_DrawBitmapTransparent(uint32_t layer, uint32_t x0, uint32_t y0, const ImageData* image, uint16_t transparentColor);




#endif
