////////////////////////////////////////////
/*

Simple Image Conversion Utility

Image Name: van45.bmp
8 Bit Color Image Array
Width: 48
Height: 48
Pixel Format: Format32bppArgb
*/
///////////////////////////////////////////////////



#include <stdlib.h>
#include "bitmap.h"

static const uint8_t _acvan45Bmp[] =
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0xF4, 0x4D, 0x21,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x21, 0x41, 0x21, 0x20, 0x00, 0x00, 0x00,
0x00, 0x00, 0x49, 0xF4, 0xFD, 0xD5, 0x07, 0x06, 0x21, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x8A, 0xFC, 0x8B, 0x6C, 0x6C, 0x6C, 0x94, 0x6A, 0x41, 0xD3,
0xFC, 0xD5, 0x2F, 0x07, 0x07, 0x06, 0x12, 0x21, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8A, 0xFC, 0xD3,
0xD3, 0x8B, 0x44, 0x24, 0x4D, 0x96, 0xFC, 0xFC, 0xFC, 0x6D,
0x07, 0x0D, 0x06, 0x05, 0x12, 0x12, 0x21, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x8A, 0xFC, 0xB2, 0x6B, 0x6A, 0xD2,
0xF3, 0xAB, 0x4C, 0xD4, 0xFC, 0xFC, 0xFC, 0x73, 0x0D, 0x14,
0x1B, 0x1A, 0x12, 0x12, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00,
0x00, 0x8A, 0xFC, 0xB2, 0x73, 0x6B, 0x4A, 0x21, 0xE9, 0xF3,
0xF3, 0xF4, 0xFC, 0xFC, 0x73, 0x1C, 0x1C, 0x1B, 0x1A, 0x1A,
0x12, 0x12, 0x12, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0xB3, 0x8A, 0xFC,
0x8A, 0x6C, 0x6B, 0x4A, 0x22, 0x22, 0xF1, 0xF4, 0xD3, 0xF3,
0xFC, 0x73, 0x1B, 0x1B, 0x14, 0x0E, 0x0C, 0x12, 0x12, 0x12,
0x12, 0x05, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xD3, 0xFC, 0x8A, 0x6B, 0x6B,
0x4A, 0x23, 0x02, 0x04, 0xD3, 0xD3, 0xF3, 0xF3, 0x73, 0x1C,
0x1C, 0x2E, 0x2F, 0x0F, 0x07, 0x07, 0x04, 0x0B, 0x04, 0x06,
0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x20, 0xD3, 0xFD, 0xFC, 0xB2, 0x6A, 0x4A, 0x22, 0x02,
0x03, 0xD3, 0xFC, 0xFC, 0xF4, 0x73, 0x1C, 0x1B, 0x2F, 0x2F,
0x0F, 0x07, 0x07, 0x06, 0x06, 0x06, 0x05, 0x04, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xD3,
0xFC, 0xFC, 0xFC, 0xFC, 0xAA, 0x21, 0x01, 0x02, 0xF3, 0xFC,
0xFC, 0xFC, 0x73, 0x1C, 0x1C, 0x0C, 0x07, 0x0F, 0x07, 0x06,
0x01, 0x21, 0x21, 0x21, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xD3, 0xFC, 0xFC, 0xFC,
0xFC, 0xFC, 0xFB, 0xB2, 0x01, 0xD3, 0xFC, 0xFC, 0xFC, 0x73,
0x1C, 0x1B, 0x1B, 0x06, 0x07, 0x07, 0x06, 0x01, 0x21, 0xB5,
0xB5, 0x21, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x20, 0xD4, 0xFC, 0xDC, 0xDC, 0xFC, 0xFC, 0xFC,
0xFB, 0xF3, 0xF3, 0xFC, 0xFC, 0xFC, 0x73, 0x1B, 0x1C, 0x1B,
0x0D, 0x07, 0x07, 0x07, 0x03, 0x21, 0xB5, 0xB5, 0x94, 0x6B,
0x21, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
0xD4, 0xFD, 0xDC, 0x9B, 0xDC, 0xFC, 0xFC, 0xFC, 0xFB, 0xF3,
0xF3, 0xFC, 0xFC, 0x73, 0x1C, 0x1C, 0x1B, 0x12, 0x07, 0x07,
0x07, 0x07, 0x02, 0x21, 0xFF, 0xDE, 0x6B, 0x4A, 0x21, 0x21,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xD3, 0xFC, 0x9B,
0x3B, 0xDC, 0xFC, 0xFC, 0xBB, 0xFC, 0xFC, 0xFB, 0xFB, 0xF3,
0x73, 0x1C, 0x1C, 0x1B, 0x1A, 0x0B, 0x07, 0x07, 0x06, 0x07,
0x04, 0x00, 0x94, 0x6B, 0x4A, 0x21, 0x21, 0x21, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x21, 0x00, 0x00, 0xD3, 0xFD, 0x7B, 0x1C, 0x0E, 0x7B,
0xFC, 0x9B, 0x9B, 0x9B, 0xFB, 0xFC, 0xFC, 0x73, 0x1B, 0x1C,
0x1B, 0x1A, 0x1A, 0x0D, 0x07, 0x06, 0x06, 0x06, 0x05, 0x00,
0x00, 0x21, 0x21, 0x21, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x93, 0xD3, 0xFD, 0x7B, 0x1C, 0x0E, 0x14, 0x0E, 0x1B, 0x1B,
0x9B, 0xDB, 0xFC, 0xFC, 0x73, 0x1B, 0x1B, 0x1B, 0x1A, 0x1A,
0x12, 0x07, 0x06, 0x06, 0x05, 0x04, 0x04, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8A, 0xFD,
0x5B, 0x1C, 0x0E, 0x15, 0x0D, 0x07, 0x0D, 0x3A, 0xFB, 0xFC,
0xFC, 0x73, 0x1C, 0x1B, 0x1B, 0x12, 0x0A, 0x12, 0x12, 0x06,
0x06, 0x06, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x8A, 0xDD, 0x3C, 0x1C, 0x0F,
0x15, 0x0E, 0x0D, 0x14, 0x1B, 0xDB, 0xFC, 0xFC, 0x73, 0x1C,
0x1B, 0x1B, 0x1A, 0x12, 0x05, 0x0B, 0x05, 0x06, 0x05, 0x05,
0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x8A, 0xDD, 0x3C, 0x1D, 0x0E, 0x0D, 0x0E, 0x14,
0x14, 0x1B, 0x3B, 0xFC, 0xFC, 0x73, 0x1C, 0x1C, 0x1B, 0x1A,
0x1A, 0x0D, 0x0C, 0x06, 0x06, 0x06, 0x05, 0x03, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8A,
0xBC, 0x3C, 0x1C, 0x0F, 0x0E, 0x15, 0x15, 0x0D, 0x1B, 0x3B,
0xFC, 0xFC, 0x73, 0x1C, 0x1C, 0x1B, 0x1A, 0x1A, 0x1A, 0x04,
0x12, 0x05, 0x06, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8A, 0xFD, 0x3C, 0x3C,
0x1C, 0x14, 0x0D, 0x0E, 0x14, 0x1B, 0x3B, 0xDC, 0xF3, 0x73,
0x1B, 0x1C, 0x1B, 0x1A, 0x12, 0x12, 0x12, 0x0B, 0x05, 0x05,
0x05, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFC, 0xFD, 0xDC, 0x54, 0x0E, 0x15,
0x0D, 0x14, 0x1B, 0x3B, 0xFC, 0xFC, 0x73, 0x1B, 0x1C, 0x0D,
0x1A, 0x12, 0x13, 0x0C, 0x05, 0x06, 0x05, 0x05, 0x03, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xB2, 0xFE, 0xFD, 0x2E, 0x14, 0x1C, 0x1B, 0x1B,
0x9B, 0xDC, 0xFC, 0x73, 0x1C, 0x1B, 0x13, 0x05, 0x06, 0x06,
0x06, 0x06, 0x06, 0x05, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x20, 0xFD, 0xFD, 0x3B, 0x1B, 0xFC, 0xDB, 0xFB, 0xFC, 0xFC,
0x73, 0x1C, 0x1B, 0x14, 0x2D, 0x2E, 0x07, 0x07, 0x07, 0x06,
0x06, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8A,
0xFD, 0xBD, 0xBB, 0xFC, 0xFC, 0xFC, 0xFC, 0x73, 0x1B, 0x1C,
0x1B, 0x5C, 0x55, 0x07, 0x07, 0x06, 0x06, 0x06, 0x05, 0x03,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF4, 0xFD,
0xFC, 0xFB, 0xFC, 0xFC, 0x73, 0x1C, 0x1B, 0x1B, 0x1B, 0x34,
0x27, 0x06, 0x22, 0x21, 0x21, 0x21, 0x22, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xFD, 0xFD, 0xFC,
0xFC, 0x73, 0x1C, 0x1C, 0x1B, 0x1A, 0x1A, 0x2F, 0x06, 0x01,
0x21, 0xB5, 0xB5, 0x21, 0x21, 0x20, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x8A, 0xFD, 0xFD, 0x73, 0x1C,
0x1C, 0x1B, 0x1A, 0x12, 0x13, 0x07, 0x03, 0x00, 0xB5, 0x94,
0x94, 0x6B, 0x20, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xF3, 0xB5, 0x5C, 0x3C, 0x1B, 0x12,
0x12, 0x29, 0x01, 0x07, 0x02, 0x20, 0xFF, 0xB5, 0x6B, 0x4A,
0x21, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x5C, 0x5D, 0x3C, 0x1A, 0x2A, 0x21, 0x01,
0x00, 0x05, 0x04, 0x00, 0x6B, 0x6B, 0x4A, 0x21, 0x21, 0x21,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x33, 0x3B, 0x32, 0x21, 0x21, 0x00, 0x00, 0x01,
0x05, 0x00, 0x00, 0x21, 0x21, 0x21, 0x20, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x32, 0x4A, 0x21, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00};


const ImageData bmvan45Bmp = {
48, //xSize
48, //ySize
48, //bytesPerLine
8, //bits per pixel
(uint8_t*)_acvan45Bmp,
};
/////////////////// End of File  ///////////////////////////