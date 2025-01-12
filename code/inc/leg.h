#ifndef _LEG_H_
#define _LEG_H_
#include "Brushless.h"
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
	ServoType* front;
	ServoType* behind;

	BrushlessType* wheel;

	// ����������ϵ�µ����꣬ԭ���������˵��д�����
	float angle1, angle4;		   // �Ƕ���ʵֵ���Ǻ�ͼ�е�һһ��Ӧ �Ȳ����û�����
	float angle1set, angle4set;	   // �Ƕ��趨ֵ�����ڳ�ʼ�Ƕ�֮�ϵ��趨ֵ ����

	Vector2f PosNow;	// ʵ��������� ��λmm
	Vector2f PosSet;	// �趨�������

	float t_MoveToPos;	  // �趨�ƶ���Ŀ��λ�õ��ƶ�ʱ��(ms)

} LegType;

void InverseKinematics(LegType* leg);	 // ��� ����C1 C4
void ForwardKinematics(LegType* leg);	 // ���⣬��x��y��

#endif
