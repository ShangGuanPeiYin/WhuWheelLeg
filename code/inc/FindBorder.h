#ifndef FIND_BORDER_H
#define FIND_BORDER_H

#include "zf_common_typedef.h"

extern int LeftLine[ROW], RightLine[ROW];
extern int LeftLine1[ROW], RightLine1[ROW];
extern int Original_RightLine[ROW], Original_LeftLine[ROW];
extern int ValidRow;
void	   FindBorder(void);
void	   FindBorder1(void);

#endif