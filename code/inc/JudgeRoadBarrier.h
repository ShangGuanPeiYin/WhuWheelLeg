#ifndef JUDGE_BARRIER_H
#define JUDGE_BARRIER_H

#include "zf_common_typedef.h"

extern int	  BarrierError, Barrier_flag, BarrierCount;
extern int	  Ba_Stretch1, Ba_Stretch2, Ba_Stretch3;
extern double Barrier_Stretch, in_Barrier_Stretch;
extern int	  Barrier_record, Barrier_record1;
extern int	  BarrierDir;
int			  JudgeRoadBarrier(void);

#endif