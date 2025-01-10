#ifndef _POINT_H_
#define _POINT_H_

#include "zf_common_typedef.h"

typedef struct _PointType	 // ��ά���Լ���Ƕȣ�������Vector��һ���ǶȺͱ���������ֵt��[0,1]����û���õ�
{
    float	  x;
	float	  y;
	float t;
} PointType;

float	  PointInnerProduct(PointType a, PointType b);	  // �����ڻ�
float	  PointModulo(PointType a);						  // ����ȡģ
PointType PointVecDivideNum(PointType a, float num);	  // ����/��
PointType PointVecMultiplyNum(PointType a, float num);	  // ����*��
PointType PointVecAdd(PointType a, PointType b);		  // ������
PointType PointVecSub(PointType a, PointType b);		  // ������

#endif
