#ifndef _POINT_H_
#define _POINT_H_

#include "zf_common_typedef.h"

typedef struct _PointType	 // 二维点以及其角度，比向量Vector多一个角度和贝塞尔控制值t∈[0,1]，但没有用到
{
    float	  x;
	float	  y;
	float t;
} PointType;

float	  PointInnerProduct(PointType a, PointType b);	  // 向量内积
float	  PointModulo(PointType a);						  // 向量取模
PointType PointVecDivideNum(PointType a, float num);	  // 向量/数
PointType PointVecMultiplyNum(PointType a, float num);	  // 向量*数
PointType PointVecAdd(PointType a, PointType b);		  // 向量加
PointType PointVecSub(PointType a, PointType b);		  // 向量减

#endif
