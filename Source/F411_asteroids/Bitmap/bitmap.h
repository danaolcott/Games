/*
Bitmap - Listing of all images in the project

*/

#ifndef __BITMAP_C
#define __BITMAP_C

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>


//image data
struct ImageData{
    uint8_t xSize;              // pixels in x-direction
    uint8_t ySize;              // pixels in y-direction
    uint8_t bytesPerLine;
    uint8_t bitsPerPixel;
    const uint8_t * const pImageData;
};

typedef struct ImageData ImageData;


//bitmaps
extern const ImageData imageEnemy1;

extern const ImageData bmimgPlayer0Bmp;
extern const ImageData bmimgPlayer26Bmp;
extern const ImageData bmimgPlayer45Bmp;
extern const ImageData bmimgPlayer63Bmp;
extern const ImageData bmimgPlayer90Bmp;
extern const ImageData bmimgPlayer116Bmp;
extern const ImageData bmimgPlayer135Bmp;
extern const ImageData bmimgPlayer153Bmp;
extern const ImageData bmimgPlayer180Bmp;
extern const ImageData bmimgPlayer206Bmp;
extern const ImageData bmimgPlayer225Bmp;
extern const ImageData bmimgPlayer243Bmp;
extern const ImageData bmimgPlayer270Bmp;
extern const ImageData bmimgPlayer296Bmp;
extern const ImageData bmimgPlayer315Bmp;
extern const ImageData bmimgPlayer333Bmp;

extern const ImageData bmimgPlayerExp1Bmp;
extern const ImageData bmimgPlayerExp2Bmp;
extern const ImageData bmimgPlayerExp3Bmp;
extern const ImageData bmimgPlayerExp4Bmp;
extern const ImageData bmimgPlayerExp5Bmp;
extern const ImageData bmimgPlayerExp6Bmp;

extern const ImageData bmimgAsteroidSMBmp;
extern const ImageData bmimgAsteroidMDBmp;
extern const ImageData bmimgAsteroidLGBmp;

extern const ImageData bmimgDroneSMBmp;
extern const ImageData bmimgDroneMDBmp;
extern const ImageData bmimgDroneLGBmp;



#endif
