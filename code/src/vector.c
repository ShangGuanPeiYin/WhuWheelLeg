#include "zf_common_headfile.h"

float PointInnerProduct(Vector2f a, Vector2f b)	   // 向量内积
{
	return a.x * b.x + a.y * b.y;
}

float PointModulo(Vector2f a)	 // 向量取模
{
	return sqrt(a.x * a.x + a.y * a.y);
}

Vector2f PointVecDivideNum(Vector2f a, float num)	 // 向量/数
{
	if (num != 0) {
		a.x /= num;
		a.y /= num;
	}
	return a;
}

Vector2f PointVecMultiplyNum(Vector2f a, float num)	   // 向量*数
{
	a.x *= num;
	a.y *= num;
	return a;
}

Vector2f PointVecAdd(Vector2f a, Vector2f b)	// 向量加
{
	Vector2f result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

Vector2f PointVecSub(Vector2f a, Vector2f b)	// 向量减
{
	Vector2f result;
	result.x = b.x - a.x;
	result.y = b.y - a.y;
	return result;
}
