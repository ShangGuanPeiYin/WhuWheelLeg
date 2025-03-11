#ifndef FIND_ENDROW_H
#define FIND_ENDROW_H

#include "zf_common_typedef.h"

extern int EndRow,Maxcolumn;
extern int RealEndRow,CorrectedEndRow;
extern int ControlRow;

void Find_EndRow(void);
void CorrectEndRow(void);
#endif