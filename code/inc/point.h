#ifndef _POINT_H_
#define _POINT_H_

#include "zf_common_typedef.h"

typedef struct _POINT	 // ��ά���Լ���Ƕȣ�������Vector��һ���ǶȺͱ���������ֵt��[0,1]
{
	s16	  x;
	s16	  y;
	float t;
} POINT;

float PointInnerProduct(POINT a, POINT b);		  // �����ڻ�
float PointModulo(POINT a);						  // ����ȡģ
POINT PointVecDivideNum(POINT a, float num);	  // ����/��
POINT PointVecMultiplyNum(POINT a, float num);	  // ����*��
POINT PointVecAdd(POINT a, POINT b);			  // ������
POINT PointVecSub(POINT a, POINT b);			  // ������

#endif