#ifndef _GETSLOPE_H_
#define _GETSLOPE_H_

#include "zf_common_typedef.h"

extern double Left_Slope[ROW],Right_Slope[ROW],MidLine_Slope[ROW];
extern double RealMidSlope[ROW],RealLeftSlope[ROW],RealRightSlope[ROW];

void GetSlope(void);
void GetRealMidSlope(void);
void GetRealLeftSlope(void);
void GetRealRightSlope(void);

#endif
