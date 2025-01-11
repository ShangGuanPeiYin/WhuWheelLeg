#ifndef _POINT_H_
#define _POINT_H_

#include "zf_common_typedef.h"

typedef struct _PointType	 // 二维点以及其角度，比向量Vector多一个角度和贝塞尔控制值t∈[0,1]，但没有用到
{
	float x;
	float y;
} Vector2f;

float	 PointInnerProduct(Vector2f a, Vector2f b);		// 向量内积
float	 PointModulo(Vector2f a);						// 向量取模
Vector2f PointVecDivideNum(Vector2f a, float num);		// 向量/数
Vector2f PointVecMultiplyNum(Vector2f a, float num);	// 向量*数
Vector2f PointVecAdd(Vector2f a, Vector2f b);			// 向量加
Vector2f PointVecSub(Vector2f a, Vector2f b);			// 向量减

#endif
