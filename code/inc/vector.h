#ifndef _POINT_H_
#define _POINT_H_

#include "zf_common_typedef.h"

typedef struct _PointType	 // ��ά���Լ���Ƕȣ�������Vector��һ���ǶȺͱ���������ֵt��[0,1]����û���õ�
{
	float x;
	float y;
} Vector2f;

float	 PointInnerProduct(Vector2f a, Vector2f b);		// �����ڻ�
float	 PointModulo(Vector2f a);						// ����ȡģ
Vector2f PointVecDivideNum(Vector2f a, float num);		// ����/��
Vector2f PointVecMultiplyNum(Vector2f a, float num);	// ����*��
Vector2f PointVecAdd(Vector2f a, Vector2f b);			// ������
Vector2f PointVecSub(Vector2f a, Vector2f b);			// ������

#endif
