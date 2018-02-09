/*
angle data file for sin and cos
*/

#ifndef		__ANGLE_H
#define		__ANGLE_H

#include <stdint.h>
#include <stddef.h>


struct AngleData{
	int  angle;
	float cos_val;
	float sin_val;
};

typedef struct AngleData AngleData;

extern const AngleData angleList[];


#endif
