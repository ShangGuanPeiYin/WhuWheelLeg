#ifndef _LEG_H_
#define _LEG_H_
#include "Brushless.h"
#include "MathLib.h"
#include "ServoMotor.h"
#include "WheelLegCtrl.h"
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

	BrushlessType* wheel;

	// 五连杆坐标系下的坐标，原点在五连杆的中垂线上
	// float angle1, angle4;		   // 角度真实值，是和图中的一一对应 腿部采用弧度制
	float angle1Set, angle4Set;	   // 角度设定值，PosSet直接解算得到。弧度

	Vector2f PosNow, PosSet;	// 实际足端坐标 与 设定足端坐标。单位mm。除非线性插值，否则Set就是控制点
	// Vector2f PosMov;			//  线性插值计算值

	// Vector2f PosZero;	 //  零点

	float reachTime;	// 设定移动到目标位置的移动时间(ms)

	uint64_t* RunTime;	  // 腿部的运行时钟

	MotionType motion;

} LegType;

extern LegType legLeft;
extern LegType legRight;

Vector2f InverseKinematics(Vector2f point);				   // 逆解 计算C1 C4
Vector2f ForwardKinematics(float angle1, float angle4);	   // 正解，求（x，y）

void LegReset(void);	// 重置PosZero并移动到Poszero

void LegDrawCurve(LegType* leg, float reachTime);					 // 足端画曲线（贝塞尔
void LegDrawLine(LegType* leg, Vector2f PosSet, float reachTime);	 // 足端画直线（线性插值

void AngleCalculate(LegType* leg, Vector2f pos);	// 从Pos向下解算至 Servo.angleSet
void Angle_Leg2Servo(LegType* leg);

#endif
