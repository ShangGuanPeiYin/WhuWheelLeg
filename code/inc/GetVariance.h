#ifndef _GETVARIANCE_H_
#define _GETVARIANCE_H_

#include "zf_common_typedef.h"

extern double RightLineSlopeVariance,LeftLineSlopeVariance;
double GetVariance(int row0,int row1);
double GetVariance1(int row0,int row1);
double GetLeftVariance(int row0,int row1);
double GetRightVariance(int row0,int row1);
double GetRightVariance1(int row0,int row1);
double GetLeftVariance1(int row0,int row1);

#endif