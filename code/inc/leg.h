#ifndef _LEG_H_
#define _LEG_H_

#include "Brushless.h"
#include "ServoMotor.h"
#include "zf_common_typedef.h"

typedef struct _leg {
	ServoType* front;
	ServoType* behind;

	BrushlessType* wheel;

	// 五连杆坐标系下的坐标，原点在五连杆的中垂线上
	float angle0, angle1, angle2, angle4;	 // 角度真实值，是和图中的一一对应
	float angle1set, angle4set;				 // 角度设定值，是在初始角度之上的设定值

	int a;
} LegType;

#endif
