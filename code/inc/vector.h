#ifndef _POINT_H_
#define _POINT_H_

#include "zf_common_typedef.h"

typedef struct _Vector3fType	// ��ά���Լ���Ƕȣ�������Vector��һ���ǶȺͱ���������ֵt��[0,1]����û���õ�
{
	float x;
	float y;
	float z;
} Vector3f;

typedef struct _Vector2fType	// ��ά���Լ���Ƕȣ�������Vector��һ���ǶȺͱ���������ֵt��[0,1]����û���õ�
{
	float x;
	float y;
} Vector2f;

float	 Vector2fInnerProduct(Vector2f a, Vector2f b);	  // �����ڻ�
float	 Vector2fMagnitude(Vector2f a);					  // ����ȡģ
Vector2f Vector2fDivideNum(Vector2f a, float num);		  // ����/��
Vector2f Vector2fXNum(Vector2f a, float num);			  // ����*��
Vector2f Vector2fAdd(Vector2f a, Vector2f b);			  // ������
Vector2f Vector2fSub(Vector2f a, Vector2f b);			  // ������

Vector2f BezierCalculate(uint8 degree, Vector2f coeff[], float t);
void	 Rotate(Vector2f* point, Vector2f point0, float angle);

#endif
