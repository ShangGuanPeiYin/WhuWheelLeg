#ifndef _LEGCONTROL_H_
#define _LEGCONTROL_H_
#include "vector.h"
#include "zf_common_typedef.h"

typedef struct _Ctrl {
	uint64_t leftTime;	   // 腿的运行时钟，集中管理
	uint64_t rightTime;	   //

} CtrlType;

// 轮腿的运动
typedef struct _Motion {
	float t;

	uint8_t	 degree;	  // 贝塞尔数组长度 = 阶 + 1
	Vector2f Ctrl[11];	  // 贝塞尔控制点
} MotionType;

extern CtrlType ctrl;	 // 整体控制

void MotionInit(MotionType* motion);

#endif