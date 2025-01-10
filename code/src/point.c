#include "zf_common_headfile.h"

float PointInnerProduct(POINT a, POINT b)	 // �����ڻ�
{
	return a.x * b.x + a.y * b.y;
}

float PointModulo(POINT a)	  // ����ȡģ
{
	return sqrt(a.x * a.x + a.y * a.y);
}

POINT PointVecDivideNum(POINT a, float num)	   // ����/��
{
	if (num != 0) {
		a.x /= num;
		a.y /= num;
	}
	return a;
}

POINT PointVecMultiplyNum(POINT a, float num)	 // ����*��
{
	a.x *= num;
	a.y *= num;
	return a;
}

POINT PointVecAdd(POINT a, POINT b)	   // ������
{
	POINT result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

POINT PointVecSub(POINT a, POINT b)	   // ������
{
	POINT result;
	result.x = b.x - a.x;
	result.y = b.y - a.y;
	return result;
}
