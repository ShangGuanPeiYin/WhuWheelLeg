#ifndef JUDGE_STARTLINE_H
#define JUDGE_STARTLINE_H

#include "zf_common_typedef.h"

extern int RaceFlag,StartRow,BCtSFlag,StartDir,StartDis,StartWidth,BWcount;
extern double StartStretch;
extern int OutStartLineRow;
extern int StartFlag1;
extern int StartFlag;
extern int temp16,startsum;
int Judge_StartLine(void);
void StartLineDeal(void);
#endif