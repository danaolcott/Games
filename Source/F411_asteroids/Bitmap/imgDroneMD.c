////////////////////////////////////////////
/*
Image Name: imgDroneMD.bmp
MonoChrome Image 1 Bit Per Pixel
Width: 16
Height: 16
Pixel Format: Format32bppArgb
*/
///////////////////////////////////////////////////



#include <stdlib.h>
#include "bitmap.h"

static const uint8_t _acimgDroneMDBmp[] =
{
0x00, 0x00, 0x07, 0xE0, 0x08, 0x10, 0x10, 0x08, 0x20, 0x04,
0x44, 0x24, 0x41, 0x02, 0x41, 0x82, 0x40, 0x82, 0x41, 0x82,
0x44, 0x24, 0x26, 0x64, 0x11, 0x88, 0x0C, 0x30, 0x03, 0xC0,
0x00, 0x00};


const ImageData bmimgDroneMDBmp = {
16, //xSize
16, //ySize
2, //bytesPerLine
1, //bits per pixel
(uint8_t*)_acimgDroneMDBmp,
};
/////////////////// End of File  ///////////////////////////