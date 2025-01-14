#ifndef _LEGCONTROL_H_
#define _LEGCONTROL_H_
#include "vector.h"
#include "zf_common_typedef.h"

// ��������
typedef struct _Ctrl {
	uint64_t leftTime;	   // �ȵ�����ʱ�ӣ����й���
	uint64_t rightTime;	   //

} ParamType;

// ���ȵ��˶�
typedef struct _Motion {
	float t;

	uint8_t	 degree;		   // ���������鳤�� = �� + 1
	Vector2f CtrlPoint[11];	   // ���������Ƶ�
} MotionType;

void MotionInit(MotionType* motion);

#endif