#ifndef _LEGCONTROL_H_
#define _LEGCONTROL_H_
#include "vector.h"
#include "zf_common_typedef.h"

// 参数管理
typedef struct _Ctrl {
	uint64_t leftTime;	   // 腿的运行时钟，集中管理
	uint64_t rightTime;	   //

} ParamType;

typedef struct _BoundParamType	  // 跳跃时用的参数（用于debug调参）
{
	float x0, y0, H0;						 // 贝塞尔曲线中心点 设定
	float H_KICK, L_KICK, H_BUFF, L_BUFF;	 // 蹬地高度  蹬地段运动长度   缓冲段高度   缓冲段运动长度
	float T_KICK, T_WAIT_1, T_WAIT_2, T_WAIT_3, T_BUFF;	   // 蹬地相(ms)  空中相(ms)123   缓冲段(ms)
	float Rotation;
	float NonLinear;
} BoundParamType;

// 轮腿的运动
typedef struct _Motion {
	float t;

	uint8_t	 degree;		   // 贝塞尔数组长度 = 阶 + 1
	Vector2f CtrlPoint[11];	   // 贝塞尔控制点

	BoundParamType boundParam;
} MotionType;

void MotionInit(MotionType* motion);
void BoundCtrlInit(BoundParamType* boundParam);	   // 初始化boundParam
void BoundCtrlCal(BoundParamType boundParam);	   // 计算CtrlPoint

#endif