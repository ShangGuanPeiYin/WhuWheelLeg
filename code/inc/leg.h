#ifndef _LEG_H_
#define _LEG_H_
#include "Brushless.h"
#include "LegCtrl.h"
#include "ServoMotor.h"
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
	float angle1set, angle4set;	   // 角度设定值，是在初始角度之上的设定值 弧度

	Vector2f PosNow, PosSet;	// 实际足端坐标 与 设定足端坐标。单位mm
	Vector2f PosMov;			//  线性插值计算值

	float reachTime;	// 设定移动到目标位置的移动时间(ms)

	MotionType motion;

} LegType;

extern LegType legLeft;
extern LegType legRight;

Vector2f InverseKinematics(Vector2f point);				   // 逆解 计算C1 C4
Vector2f ForwardKinematics(float angle1, float angle4);	   // 正解，求（x，y）
void	 LegMoveToPoint(LegType* leg, Vector2f PosSet, float reachTime);
void	 Angle_Leg2Servo(LegType* leg);

#endif
