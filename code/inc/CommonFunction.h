#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H

#include "zf_common_typedef.h"

int GetMax(int x1,int x2);
int GetMin(int x1,int x2);
int  AssertEndRow(int endrow,int min,int max);
int AssertLength(int x1,int y1,int x2,int y2,int min,int max,float *length);
float GetLength(int x1,int y1,int x2,int y2);
float InvSqrt(float x);
int abs_int(int x);
float abs_float(float x);
float LimitMax(float a,float max);
float LimitMin(float a,float min);
float LimitBothSides(float a,float min,float max);
void Draw_a_Line(int Start_Row,int End_Row,int line[ROW]);

#endif