#ifndef _ROADJUDGE_H_
#define _ROADJUDGE_H_

#include "zf_common_typedef.h"

#define ROAD_KINDS 9
#define RowStep	   2

extern int	  ValidRow1;
extern double RealWarp;
extern double MidLineSlopeVariance;
extern int	  RoadFlag[ROAD_KINDS];
extern int	  CircleNumber;
extern int	  Temp0, Temp1, Temp2, Temp3, Temp4, Temp5, Temp6, Temp7;
extern int	  SnakePathFlag;
extern int	  Ba_RealWarp1, Ba_RealWarp2, Ba_RealWarp3;
extern int	  OutBrokenMidAddStretch;
extern int	  My_Round_Open_Flag;

typedef enum {
	NORMAL,
	SNAKEBENDING,
	LOOP,
	CROSS,
	CURVECROSS,
	//  BARRIER,
	BROKENROAD,
	RAMP,
	STARTLINE,
	STRANGE
} RoadConditions;
extern RoadConditions roadCondition;

void RawDeal();
void Image_To_Warp(void);

#endif