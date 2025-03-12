#ifndef CORRECT_H
#define CORRECT_H

#include "zf_common_typedef.h"

extern int ImageFlag;

void  Real_Location(int coordinate_x, int coordinate_y, float Coordinate[1][2]);
float GetDistance(float coordinate1[1][2], float coordinate2[1][2]);
#endif