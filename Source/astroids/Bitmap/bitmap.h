/*
Header file for sprite images used in the game
Contains an ImageData struct defining the 
image size and pointer to image data
There should be a .c file for each image.

All image files should be 8 bit per pixel RGB 332

A helpful image conversion tool is Bitmap Converter for emWin
by Segger.  Here is a link:

https://www.segger.com/products/user-interface/emwin/tools/tools-overview/


*/

#ifndef BITMAP_H
#define BITMAP_H

//includes 
#include <stddef.h>
#include <stdint.h>


//image data type def
struct ImageData{
    uint16_t xSize;              // pixels in x-direction
    uint16_t ySize;              // pixels in y-direction
    uint16_t bytesPerLine;
    uint16_t bitsPerPixel;
    const uint8_t * const pImageData;
};

typedef struct ImageData ImageData;


extern const ImageData imgTileBlank;

extern const ImageData imgTile;

//minions


//player van
extern const ImageData bmvan0Bmp;
extern const ImageData bmvan26Bmp;
extern const ImageData bmvan45Bmp;
extern const ImageData bmvan63Bmp;
extern const ImageData bmvan90Bmp;
extern const ImageData bmvan116Bmp;
extern const ImageData bmvan135Bmp;
extern const ImageData bmvan153Bmp;
extern const ImageData bmvan180Bmp;
extern const ImageData bmvan206Bmp;
extern const ImageData bmvan225Bmp;
extern const ImageData bmvan243Bmp;
extern const ImageData bmvan270Bmp;
extern const ImageData bmvan296Bmp;
extern const ImageData bmvan315Bmp;
extern const ImageData bmvan333Bmp;





#endif


