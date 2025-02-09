#ifndef _LEG_H_
#define _LEG_H_
#include "MasterCtrl.h"
#include "MathLib.h"
#include "Servo.h"
#include "bldc.h"
#include "vector.h"
#include "zf_common_typedef.h"

// 杆长 单位为mm
#define L1	   60
#define L2	   88
#define L3	   88
#define L4	   60
#define L5	   37.5
#define WHEELR 67	 // 直径

typedef struct _leg {
	LegNum num;

	ServoType* front;
	ServoType* behind;

	BldcType* wheel;

	// 五连杆坐标系下的坐标，原点在五连杆的中垂线上
	float angle1Set, angle4Set;	   // 角度设定值，PosSet直接解算得到。弧度

	Vector2f PosNow, PosSet;	// 实际足端坐标 与 设定足端坐标。单位mm。除非线性插值，否则Set就是控制点
	Vector2f PosStart, PosTarget;	 // 直线两端

	float reachTime;	// 设定移动到目标位置的移动时间(ms)

	uint64_t* RunTime;	  // 腿部的运行时钟

	MotionType motion;

} LegType;

extern LegType legLeft;
extern LegType legRight;

void LegInit(void);

bool	 PointLimit(Vector2f* point);
Vector2f InverseKinematics(Vector2f point);				   // 逆解 计算C1 C4
Vector2f ForwardKinematics(float angle1, float angle4);	   // 正解，求（x，y）

void LegReset(void);													// 重置PosZero并移动到Poszero
bool LegDrawLine(LegType* leg, Vector2f PosTarget, float reachTime);	// 足端画曲线（贝塞尔
bool LegDrawCurve(LegType* leg, float reachTime);						// 足端画直线（线性插值

void AngleCalculate(LegType* leg, Vector2f pos);	// 从Pos向下解算至 Servo.angleSet
void AngleLeg2Servo(LegType* leg);

#endif
