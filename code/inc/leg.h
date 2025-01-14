#ifndef _LEG_H_
#define _LEG_H_
#include "Brushless.h"
#include "MathLib.h"
#include "ServoMotor.h"
#include "WheelLegCtrl.h"
#include "vector.h"
#include "zf_common_typedef.h"

// �˳� ��λΪmm
#define L1	   60
#define L2	   88
#define L3	   88
#define L4	   60
#define L5	   37.5
#define WHEELR 67	 // ֱ��

typedef struct _leg {
	LegNum num;

	ServoType* front;
	ServoType* behind;

	BrushlessType* wheel;

	// ����������ϵ�µ����꣬ԭ���������˵��д�����
	// float angle1, angle4;		   // �Ƕ���ʵֵ���Ǻ�ͼ�е�һһ��Ӧ �Ȳ����û�����
	float angle1Set, angle4Set;	   // �Ƕ��趨ֵ��PosSetֱ�ӽ���õ�������

	Vector2f PosNow, PosSet;	// ʵ��������� �� �趨������ꡣ��λmm���������Բ�ֵ������Set���ǿ��Ƶ�
	// Vector2f PosMov;			//  ���Բ�ֵ����ֵ

	// Vector2f PosZero;	 //  ���

	float reachTime;	// �趨�ƶ���Ŀ��λ�õ��ƶ�ʱ��(ms)

	uint64_t* RunTime;	  // �Ȳ�������ʱ��

	MotionType motion;

} LegType;

extern LegType legLeft;
extern LegType legRight;

Vector2f InverseKinematics(Vector2f point);				   // ��� ����C1 C4
Vector2f ForwardKinematics(float angle1, float angle4);	   // ���⣬��x��y��

void LegReset(void);	// ����PosZero���ƶ���Poszero

void LegDrawCurve(LegType* leg, float reachTime);					 // ��˻����ߣ�������
void LegDrawLine(LegType* leg, Vector2f PosSet, float reachTime);	 // ��˻�ֱ�ߣ����Բ�ֵ

void AngleCalculate(LegType* leg, Vector2f pos);	// ��Pos���½����� Servo.angleSet
void Angle_Leg2Servo(LegType* leg);

#endif
