#ifndef _LEGCONTROL_H_
#define _LEGCONTROL_H_
#include "vector.h"
#include "zf_common_typedef.h"

// ��������
typedef struct _Ctrl {
	uint64_t leftTime;	   // �ȵ�����ʱ�ӣ����й���
	uint64_t rightTime;	   //

} ParamType;

typedef struct _BoundParamType	  // ��Ծʱ�õĲ���������debug���Σ�
{
	float x0, y0, H0;						 // �������������ĵ� �趨
	float H_KICK, L_KICK, H_BUFF, L_BUFF;	 // �ŵظ߶�  �ŵض��˶�����   ����θ߶�   ������˶�����
	float T_KICK, T_WAIT_1, T_WAIT_2, T_WAIT_3, T_BUFF;	   // �ŵ���(ms)  ������(ms)123   �����(ms)
	float Rotation;
	float NonLinear;
} BoundParamType;

// ���ȵ��˶�
typedef struct _Motion {
	float t;

	uint8_t	 degree;		   // ���������鳤�� = �� + 1
	Vector2f CtrlPoint[11];	   // ���������Ƶ�

	BoundParamType boundParam;
} MotionType;

void MotionInit(MotionType* motion);
void BoundCtrlInit(BoundParamType* boundParam);	   // ��ʼ��boundParam
void BoundCtrlCal(BoundParamType boundParam);	   // ����CtrlPoint

#endif