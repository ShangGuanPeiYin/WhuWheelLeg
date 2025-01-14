#ifndef _LEGCONTROL_H_
#define _LEGCONTROL_H_
#include "vector.h"
#include "zf_common_typedef.h"

// 参数管理
typedef struct _Ctrl {
	uint64_t leftTime;	   // 腿的运行时钟，集中管理
	uint64_t rightTime;	   //

} ParamType;

// 轮腿的运动
typedef struct _Motion {
	float t;

	uint8_t	 degree;		   // 贝塞尔数组长度 = 阶 + 1
	Vector2f CtrlPoint[11];	   // 贝塞尔控制点
} MotionType;

void MotionInit(MotionType* motion);

#endif