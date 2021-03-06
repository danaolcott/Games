////////////////////////////////////////////
/*
Image Name: imgAsteroidLG.bmp
MonoChrome Image 1 Bit Per Pixel
Width: 24
Height: 24
Pixel Format: Format32bppArgb
*/
///////////////////////////////////////////////////



#include <stdlib.h>
#include "bitmap.h"

static const uint8_t _acimgAsteroidLGBmp[] =
{
0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x07, 0xE0, 0xF8, 0x07,
0xFF, 0xFC, 0x0F, 0xFF, 0xFE, 0x0F, 0xFF, 0xFE, 0x07, 0xFF,
0xFE, 0x03, 0xFF, 0xFE, 0x03, 0xFF, 0xFE, 0x03, 0xFF, 0xFE,
0x03, 0xFF, 0xFE, 0x03, 0xFF, 0xFE, 0x03, 0xFF, 0xFE, 0x03,
0xFF, 0xFC, 0x03, 0xFF, 0xF8, 0x07, 0xFF, 0xE0, 0x0F, 0xFF,
0xE0, 0x1F, 0xFF, 0xE0, 0x3F, 0x8F, 0xC0, 0x3F, 0x83, 0x80,
0x1F, 0x80, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00};


const ImageData bmimgAsteroidLGBmp = {
24, //xSize
24, //ySize
3, //bytesPerLine
1, //bits per pixel
(uint8_t*)_acimgAsteroidLGBmp,
};
/////////////////// End of File  ///////////////////////////