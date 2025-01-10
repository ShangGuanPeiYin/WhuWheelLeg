#ifndef _LEG_H_
#define _LEG_H_

#include "Brushless.h"
#include "ServoMotor.h"
#include "zf_common_typedef.h"

typedef struct _leg {
	ServoType* front;
	ServoType* behind;

	BrushlessType* wheel;

	// ����������ϵ�µ����꣬ԭ���������˵��д�����
	float angle0, angle1, angle2, angle4;	 // �Ƕ���ʵֵ���Ǻ�ͼ�е�һһ��Ӧ
	float angle1set, angle4set;				 // �Ƕ��趨ֵ�����ڳ�ʼ�Ƕ�֮�ϵ��趨ֵ

	int a;
} LegType;

#endif
