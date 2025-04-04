#ifndef SEEKFREE_H
#define SEEKFREE_H
#include "zf_common_typedef.h"
void   ShowImage(void);
void   ShowTorque(void);
float* ReceivePID(void);
void   AdjustPID(PIDType* pid);
float  AdjustTarget();

#endif