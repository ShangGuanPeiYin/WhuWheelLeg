#include "zf_common_headfile.h"

/******************************************** 平面向量计算 ****************************************************** */

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

/*********************************** 贝塞尔曲线数学库 ********************************************** */
/**
 * @brief De Casteljau  德卡斯特里奥算法,递归计算贝塞尔曲线 绘制n阶贝赛尔曲线
 *
 * @param degree 数组长度 = 阶数 + 1
 * @param coeff[] 控制点坐标数组
 * @param t 时间t
 * @return Vector2f 此时的点
 */
Vector2f BezierCalculate(uint8 degree, Vector2f coeff[], float t)
{
	Limit(t, 0, 1);

	// if (Nonlinear != 1.0f)	  // 控制 t 移动速度
	// 	t = pow(t, Nonlinear);

	Vector2f point[13];	   // 最大12阶贝赛尔曲线

	memcpy(point, coeff, degree * sizeof(Vector2f));	// 赋值

	// 递归
	for (size_t r = 1; r < degree; r++)
		for (size_t i = 0; i < degree - r; i++) {
			point[i].x = (1 - t) * point[i].x + t * point[i + 1].x;
			point[i].y = (1 - t) * point[i].y + t * point[i + 1].y;
		}

	return (point[0]);
}

/**
 * @brief  坐标旋转
 *
 * @param point 旋转点
 * @param point0 旋转中心
 * @param angle 旋转弧度 逆时针为正
 */
void Rotate(Vector2f* point, Vector2f point0, float angle)
{
	float x	 = point->x;
	float y	 = point->y;

	point->x = (x - point0.x) * cos(angle) - (y - point0.y) * sin(angle) + point0.x;
	point->y = (y - point0.y) * cos(angle) + (x - point0.x) * sin(angle) + point0.y;
}
