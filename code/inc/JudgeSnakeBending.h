#ifndef _JUDEGESNAKEBENDING_H_
#define _JUDEGESNAKEBENDING_H_

#include "zf_common_typedef.h"

extern double  SnakeSafeDis;
extern int SnakeFlag1;
extern double OutSnakeStretch,InSnakeStretch;

int AssertInterSectionPoint(void);
int AssertWidth1(void);
int OutAssertWidth1(void);
int AssertWidth2(void);
int OutAssertWidth2(void);
int Judge_SnakeBending(void);
void OutSnake(void);

#endif