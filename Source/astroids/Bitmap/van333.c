////////////////////////////////////////////
/*

Simple Image Conversion Utility

Image Name: van333.bmp
8 Bit Color Image Array
Width: 48
Height: 48
Pixel Format: Format32bppArgb
*/
///////////////////////////////////////////////////



#include <stdlib.h>
#include "bitmap.h"

static const uint8_t _acvan333Bmp[] =
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
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xFD, 0xD4,
0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x8A, 0xFD, 0xFD, 0xBC, 0xDD, 0xFD,
0x41, 0x00, 0x00, 0x21, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x49, 0xFD, 0xFD, 0xFC, 0x3C, 0x3C, 0x5C, 0xFD, 0xFC,
0xB3, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xFD,
0xFD, 0xBC, 0x4E, 0x53, 0x1C, 0x3C, 0x3C, 0x5C, 0xFD, 0xFC,
0x6A, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF4, 0xFD, 0x9C, 0x1B,
0x14, 0x0E, 0x15, 0x0E, 0x16, 0x1C, 0x1C, 0x9C, 0xFC, 0xFC,
0xF3, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xB2, 0xFD, 0xFD, 0xFC, 0xFC, 0x5B, 0x1C,
0x14, 0x0D, 0x15, 0x0E, 0x0E, 0x1C, 0x3C, 0xBC, 0xFC, 0xFD,
0xD3, 0x6A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x49, 0xFD, 0xFD, 0xFC, 0xFC, 0xFC, 0x9B, 0x1C, 0x0E, 0x0E,
0x0E, 0x15, 0x0E, 0x06, 0x15, 0x1C, 0x3B, 0xDC, 0xFC, 0xFD,
0xD3, 0x6A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0xB4,
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x3B, 0x1B, 0x14, 0x0D, 0x0E,
0x14, 0x15, 0x15, 0x0E, 0x0E, 0x1B, 0xDC, 0xDC, 0xFC, 0xFD,
0xD3, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x5D, 0x5D, 0x1C, 0x73,
0xF3, 0xFC, 0xFC, 0xFC, 0x1B, 0x1B, 0x1B, 0x14, 0x05, 0x15,
0x15, 0x0E, 0x7B, 0xFC, 0xBB, 0xFC, 0x9B, 0xFC, 0xFC, 0xFD,
0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x33, 0x3C, 0x5D, 0x1B, 0x1C, 0x1C, 0x53,
0xF3, 0xFC, 0xFC, 0xDB, 0x1B, 0x1B, 0x1B, 0x14, 0x0E, 0x07,
0xDC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFD,
0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x32, 0x3B, 0x1A, 0x1B, 0x3C, 0x1B, 0x1B, 0x1C, 0x53,
0xF3, 0xFC, 0xFC, 0x9B, 0x3B, 0x1B, 0x1B, 0x1B, 0x1B, 0xDC,
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x8A, 0x6B, 0xAA, 0xF4, 0xFD,
0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x4A,
0x4A, 0x2A, 0x2A, 0x12, 0x1B, 0x3C, 0x1B, 0x1C, 0x1C, 0x53,
0xF3, 0xFC, 0xFC, 0xFC, 0xDB, 0x7B, 0x7B, 0xBB, 0x9B, 0xFC,
0xFC, 0xFC, 0xFB, 0x4A, 0x6B, 0x93, 0x6B, 0xAA, 0xF4, 0xFD,
0xB2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x21, 0x21, 0x21,
0x21, 0x12, 0x1A, 0x1A, 0x1B, 0x3C, 0x1B, 0x1B, 0x1B, 0x53,
0xD3, 0xFC, 0xFC, 0xFC, 0xF3, 0x9B, 0xFC, 0xFC, 0xFB, 0xFC,
0x8A, 0x21, 0x22, 0x4A, 0x6B, 0x8B, 0x6B, 0xD3, 0xFC, 0x69,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x21, 0x21,
0x12, 0x33, 0x5B, 0x5B, 0x34, 0x3B, 0x1C, 0x1C, 0x1C, 0x53,
0xD3, 0xFC, 0xFC, 0xFC, 0xFB, 0xFC, 0xFB, 0xF3, 0x21, 0x01,
0x02, 0x22, 0x22, 0x4A, 0x6B, 0xD3, 0x4A, 0x8A, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x07,
0x27, 0x2E, 0x34, 0x34, 0x06, 0x15, 0x1C, 0x1B, 0x1C, 0x53,
0xD3, 0xFC, 0xFC, 0xFB, 0xFB, 0xFC, 0xD3, 0x23, 0x03, 0x03,
0x02, 0x22, 0x21, 0xF3, 0x6B, 0x8C, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x05, 0x04, 0x05, 0x07,
0x27, 0x27, 0x06, 0x1A, 0x1B, 0x3B, 0x3C, 0x1B, 0x1C, 0x33,
0xD3, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xD3, 0x4C, 0x03, 0x61,
0x61, 0xF3, 0x43, 0x4C, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x05, 0x06, 0x01, 0x00, 0x00, 0x00, 0x02, 0x07, 0x07,
0x07, 0x0B, 0x1A, 0x1A, 0x1A, 0x3B, 0x3C, 0x1B, 0x1B, 0x33,
0xD3, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF3, 0xF2, 0xFB, 0xF1,
0x04, 0x4D, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xB5, 0xFF, 0xB5, 0x00, 0x22, 0x07, 0x07, 0x07,
0x12, 0x1A, 0x1A, 0x1A, 0x1A, 0x3B, 0x1C, 0x1B, 0x1C, 0x33,
0xD3, 0xFC, 0xFC, 0xFC, 0xFB, 0xD3, 0xF3, 0xF3, 0x44, 0x6D,
0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21,
0x4A, 0xDE, 0xDE, 0x94, 0x21, 0x06, 0x06, 0x06, 0x0D, 0x12,
0x1A, 0x12, 0x1A, 0x1A, 0x1A, 0x3B, 0x3C, 0x1B, 0x1C, 0x33,
0xB3, 0xFC, 0xFC, 0xF3, 0xD3, 0xFB, 0xF4, 0xB5, 0x69, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x6B, 0x6B,
0x6B, 0x94, 0x21, 0x05, 0x06, 0x06, 0x06, 0x12, 0x13, 0x05,
0x06, 0x0C, 0x12, 0x1A, 0x1A, 0x1B, 0x3C, 0x1B, 0x1C, 0x33,
0xB3, 0xF4, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x4A, 0x6B, 0x21,
0x21, 0x04, 0x04, 0x05, 0x06, 0x06, 0x0B, 0x12, 0x05, 0x0B,
0x12, 0x1A, 0x1A, 0x1A, 0x1A, 0x1B, 0x3C, 0x1B, 0x1C, 0x33,
0xB3, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x41, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x00,
0x02, 0x04, 0x05, 0x05, 0x06, 0x06, 0x06, 0x05, 0x12, 0x13,
0x0B, 0x0C, 0x0B, 0x13, 0x13, 0x1C, 0x3C, 0x1B, 0x1C, 0x33,
0x93, 0xFC, 0xF4, 0xD5, 0xFC, 0x69, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x21, 0x21, 0x21, 0x00, 0x00, 0x00, 0x00,
0x02, 0x04, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07,
0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x34, 0x1B, 0x1C, 0x33,
0x26, 0x07, 0x95, 0xFD, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x02, 0x04, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06,
0x07, 0x07, 0x0F, 0x2F, 0x2F, 0x0E, 0x3C, 0x1B, 0x05, 0x14,
0x07, 0x95, 0xB4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x04, 0x04, 0x05, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07,
0x07, 0x07, 0x07, 0x2F, 0x0D, 0x1B, 0x34, 0x05, 0x07, 0x07,
0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x04, 0x04, 0x05, 0x06, 0x07, 0x05, 0x02, 0x03, 0x07,
0x07, 0x07, 0x07, 0x12, 0x1A, 0x0C, 0x26, 0x0C, 0x41, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x04, 0x06, 0x02, 0x00, 0x00, 0x00, 0x21, 0x05, 0x07,
0x07, 0x12, 0x1A, 0x1A, 0x13, 0x1B, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x94, 0xFF, 0x94, 0x4A, 0x21, 0x06, 0x07, 0x12,
0x12, 0x12, 0x1A, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x4A, 0xDE, 0xDE, 0xFF, 0x21, 0x04, 0x06, 0x12, 0x12, 0x12,
0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4A, 0x4A,
0x6B, 0x94, 0x21, 0x03, 0x06, 0x12, 0x12, 0x0A, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x21, 0x21, 0x6B, 0x4A,
0x21, 0x02, 0x05, 0x06, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x21, 0x21, 0x21, 0x21, 0x21, 0x00,
0x01, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x21, 0x21, 0x21, 0x00, 0x00, 0x00, 0x00,
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
0x00, 0x00, 0x00, 0x00};


const ImageData bmvan333Bmp = {
48, //xSize
48, //ySize
48, //bytesPerLine
8, //bits per pixel
(uint8_t*)_acvan333Bmp,
};
/////////////////// End of File  ///////////////////////////