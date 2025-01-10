#include "zf_common_headfile.h"

float PointInnerProduct(PointType a, PointType b)	 // 向量内积
{
	return a.x * b.x + a.y * b.y;
}

float PointModulo(PointType a)	  // 向量取模
{
	return sqrt(a.x * a.x + a.y * a.y);
}

PointType PointVecDivideNum(PointType a, float num)	   // 向量/数
{
	if (num != 0) {
		a.x /= num;
		a.y /= num;
	}
	return a;
}

PointType PointVecMultiplyNum(PointType a, float num)	 // 向量*数
{
	a.x *= num;
	a.y *= num;
	return a;
}

PointType PointVecAdd(PointType a, PointType b)	   // 向量加
{
	PointType result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

PointType PointVecSub(PointType a, PointType b)	   // 向量减
{
	PointType result;
	result.x = b.x - a.x;
	result.y = b.y - a.y;
	return result;
}
