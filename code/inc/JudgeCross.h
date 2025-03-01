#ifndef JUDGE_CROSS_H
#define JUDGE_CROSS_H

#include "zf_common_typedef.h"

extern int InflexionNear, InflexionFar;
extern int LeftFound, RightFound;
extern int CrossFlag;
int		   Judge_Cross(void);
void	   CrossDeal(void);
uint8	   Judge_Curve_Cross(void);
void	   Curve_Cross_Deal(void);

#endif