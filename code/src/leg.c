#include "zf_common_headfile.h"

/// @brief 逆解。（x，y），求∠1和4
/// @param leg
void InverseKinematics(LegType* leg)
{
	// AE坐标不变
	Vector2f pointA, pointE;
	pointA.x = -L5 / 2;
	pointA.y = 0.f;

	pointE.x = L5 / 2;
	pointE.y = 0.f;

	// 求Angle1
	float A	 = (leg->PosSet.x - pointA.x) * (leg->PosSet.x - pointA.x) + (leg->PosSet.y - pointA.y) * (leg->PosSet.y - pointA.y)
			  + L1 * L1 - L2 * L2;
	float B		= -2 * (leg->PosSet.x - pointA.x) * L1;
	float C		= -2 * (leg->PosSet.y - pointA.y) * L1;

	leg->angle1 = 2 * atan2f((-C + sqrtf(C * C + B * B - A * A)), (A - B));
	if (leg->angle1 < 0)	// 限定在0-2PI
		leg->angle1 += 2 * PI;

	// 求Angle4
	A = (leg->PosSet.x - pointE.x) * (leg->PosSet.x - pointE.x) + (leg->PosSet.y - pointE.y) * (leg->PosSet.y - pointE.y) + L4 * L4
		- L3 * L3;
	B			= -2 * (leg->PosSet.x - pointE.x) * L4;
	C			= -2 * (leg->PosSet.y - pointE.y) * L4;
	leg->angle4 = 2 * atan2f((C - sqrtf(C * C + B * B - A * A)), (A - B));	  // -PI/2 ~ +PI/2
};

/// @brief 正解。∠1和4，求（x，y）
/// @param leg
void ForwardKinematics(LegType* leg)
{
	// 直接计算ABDE的坐标
	Vector2f pointA, pointB, pointD, pointE;
	pointA.x	  = -L5 / 2;
	pointA.y	  = 0.f;

	pointB.x	  = -L5 / 2 + L1 * cosf(leg->angle1);
	pointB.y	  = L1 * sinf(leg->angle1);

	pointD.x	  = L5 / 2 + L4 * cosf(leg->angle4);
	pointD.y	  = L4 * sinf(leg->angle4);

	pointE.x	  = L5 / 2;
	pointE.y	  = 0.f;

	// 求解angle2
	float A		  = 2 * L2 * (pointD.x - pointB.x);
	float B		  = 2 * L2 * (pointD.y - pointB.y);
	float LBD_2	  = (pointD.y - pointB.y) * (pointD.y - pointB.y) + (pointD.x - pointB.x) * (pointD.x - pointB.x);
	float C		  = L2 * L2 - L3 * L3 + LBD_2;

	float angle2  = 2 * atan2f((B + sqrtf(A * A + B * B - C * C)), (A + C));

	// 计算C点坐标
	leg->PosSet.x = -L5 / 2 + L1 * cosf(leg->angle1) + L2 * cosf(angle2);
	leg->PosSet.y = L1 * sinf(leg->angle1) + L2 * sinf(angle2);
};
