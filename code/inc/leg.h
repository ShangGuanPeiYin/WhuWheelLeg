#ifndef _LEG_H_
#define _LEG_H_
#include "Brushless.h"
#include "LegCtrl.h"
#include "ServoMotor.h"
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
	float angle1set, angle4set;	   // �Ƕ��趨ֵ�����ڳ�ʼ�Ƕ�֮�ϵ��趨ֵ ����

	Vector2f PosNow, PosSet;	// ʵ��������� �� �趨������ꡣ��λmm
	Vector2f PosMov;			//  ���Բ�ֵ����ֵ

	float reachTime;	// �趨�ƶ���Ŀ��λ�õ��ƶ�ʱ��(ms)

	MotionType motion;

} LegType;

extern LegType legLeft;
extern LegType legRight;

Vector2f InverseKinematics(Vector2f point);				   // ��� ����C1 C4
Vector2f ForwardKinematics(float angle1, float angle4);	   // ���⣬��x��y��
void	 LegMoveToPoint(LegType* leg, Vector2f PosSet, float reachTime);
void	 Angle_Leg2Servo(LegType* leg);

#endif
