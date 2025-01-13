#include "zf_common_headfile.h"

LegType legLeft;
LegType legRight;

/**
 * @brief �������ƶ���PosSet��Ҫ�󵥸��ȿ��Ե�������
 *
 * @param leg
 */
void LegMoveToPoint(LegType* leg)
{
	// TODO ���ߣ�����������ϵĵ�
	// TODO leg->PosMov = ��

	InverseKinematics(leg->PosMov);	   // Pos  -> angle1,4
	Angle_Leg2Servo(leg);
};

void Angle_Leg2Servo(LegType* leg)
{
	switch (leg->num) {
		case Left:
			Servo[Fl].angleLeg = leg->angle1;
			Servo[Bl].angleLeg = leg->angle4;
			break;

		case Right:
			Servo[Fr].angleLeg = leg->angle1;
			Servo[Br].angleLeg = leg->angle4;
			break;

		default:
			break;
	};
};

/// @brief ��⡣��x��y�������1��4 ��������ʵֵ��Ŀ��ֵ
/// @param leg
Vector2f InverseKinematics(Vector2f point)
{
	Vector2f angle;				// ���ö�ά��������angle1��4 ��Ӧxy
	Vector2f pointA, pointE;	// AE���겻��

	pointA.x = -L5 / 2;
	pointA.y = 0.f;

	pointE.x = L5 / 2;
	pointE.y = 0.f;

	// ��Angle1
	float A	 = (point.x - pointA.x) * (point.x - pointA.x) + (point.y - pointA.y) * (point.y - pointA.y) + L1 * L1 - L2 * L2;
	float B	 = -2 * (point.x - pointA.x) * L1;
	float C	 = -2 * (point.y - pointA.y) * L1;

	angle.x	 = 2 * atan2f((-C + sqrtf(C * C + B * B - A * A)), (A - B));
	if (angle.x < 0)	// �޶���0-2PI
		angle.x += 2 * PI;

	// ��Angle4
	A		= (point.x - pointE.x) * (point.x - pointE.x) + (point.y - pointE.y) * (point.y - pointE.y) + L4 * L4 - L3 * L3;
	B		= -2 * (point.x - pointE.x) * L4;
	C		= -2 * (point.y - pointE.y) * L4;
	angle.y = 2 * atan2f((C - sqrtf(C * C + B * B - A * A)), (A - B));	  // -PI/2 ~ +PI/2

	return angle;
};

/// @brief ���⡣��1��4����x��y��
/// @param leg
Vector2f ForwardKinematics(float angle1, float angle4)
{
	// ֱ�Ӽ���ABDE������
	Vector2f pointA, pointB, pointD, pointE;
	pointA.x	 = -L5 / 2;
	pointA.y	 = 0.f;

	pointB.x	 = -L5 / 2 + L1 * cosf(angle1);
	pointB.y	 = L1 * sinf(angle1);

	pointD.x	 = L5 / 2 + L4 * cosf(angle4);
	pointD.y	 = L4 * sinf(angle4);

	pointE.x	 = L5 / 2;
	pointE.y	 = 0.f;

	// ���angle2
	float A		 = 2 * L2 * (pointD.x - pointB.x);
	float B		 = 2 * L2 * (pointD.y - pointB.y);
	float LBD_2	 = (pointD.y - pointB.y) * (pointD.y - pointB.y) + (pointD.x - pointB.x) * (pointD.x - pointB.x);
	float C		 = L2 * L2 - L3 * L3 + LBD_2;

	float angle2 = 2 * atan2f((B + sqrtf(A * A + B * B - C * C)), (A + C));

	// ����C������
	Vector2f pointC;
	pointC.x = -L5 / 2 + L1 * cosf(angle1) + L2 * cosf(angle2);
	pointC.y = L1 * sinf(angle1) + L2 * sinf(angle2);
	return pointC;
};
