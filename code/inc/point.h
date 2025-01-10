#ifndef _POINT_H_
#define _POINT_H_

#include "zf_common_typedef.h"

typedef struct _POINT	 // 二维点以及其角度，比向量Vector多一个角度和贝塞尔控制值t∈[0,1]
{
	s16	  x;
	s16	  y;
	float t;
} POINT;

float PointInnerProduct(POINT a, POINT b);		  // 向量内积
float PointModulo(POINT a);						  // 向量取模
POINT PointVecDivideNum(POINT a, float num);	  // 向量/数
POINT PointVecMultiplyNum(POINT a, float num);	  // 向量*数
POINT PointVecAdd(POINT a, POINT b);			  // 向量加
POINT PointVecSub(POINT a, POINT b);			  // 向量减

#endif