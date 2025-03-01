#ifndef SPEED_PLANNING_H
#define SPEED_PLANNING_H

#include "zf_common_typedef.h"

extern double straightDistance;
extern double TurningRadius;
extern int Speed_s,Speed_s1,Speed_c,speed_cmin;
extern int LK_Diff,RK_Diff;
extern int SingleSpeedFlag,SpeedGet;
extern int StraightFlag; 
extern int RampSpeed,CrossSpeed,SnakeSpeed;
extern double Deltav;
extern int my_Circle_Speed;
extern int my_Circle_Speed1,in_Circle_Speed1,in_Circle_Speed2,in_Circle_Speed3,in_Circle_Speed4;
extern int BarrierSpeed;
extern int BrokenRoadFirstSpeedSetEndRowFlag;
extern int BrokenRoadSpeedL,BrokenRoadEndRowH;
extern double Angle;

#endif