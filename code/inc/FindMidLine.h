#ifndef FIND_MIDLINE_H
#define FIND_MIDLINE_H

#include "zf_common_typedef.h"

extern int MidLine[ROW],Width[ROW],Error[ROW],Original_MidLine[ROW],Original_Error[ROW];
extern float RealMidLine1[ROW-1],RealMidLine2[ROW-1],RealLeftLine1[ROW-1],RealRightLine1[ROW-1],RealLeftLine2[ROW-1],RealRightLine2[ROW-1];
extern float RealWidth1[ROW];
extern int BrokenRoad2chooseADFlag;
extern int MySetBrokenRoad2Dir[15];
void Find_MidLine(void);
void DrawMidLine_Simple(void);
void DrawScreenMidLine(void);
void GetRealMidLine(void);

#endif