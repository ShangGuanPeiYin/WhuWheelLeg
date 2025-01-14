#ifndef _LEGCONTROL_H_
#define _LEGCONTROL_H_
#include "vector.h"
#include "zf_common_typedef.h"

// 轮腿的运动
typedef struct _Motion {
	float t;

	uint8_t	 degree;	  // 贝塞尔数组长度 = 阶 + 1
	Vector2f Ctrl[11];	  // 贝塞尔控制点
} MotionType;

void MotionInit(MotionType* motion);

#endif