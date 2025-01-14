#include "zf_common_headfile.h"

/******************************************** ƽ���������� ****************************************************** */

float Vector2fInnerProduct(Vector2f a, Vector2f b)	  // �����ڻ�
{
	return a.x * b.x + a.y * b.y;
}

float Vector2fMagnitude(Vector2f a)	   // ����ȡģ
{
	return sqrt(a.x * a.x + a.y * a.y);
}

Vector2f Vector2fDivideNum(Vector2f a, float num)	 // ����/��
{
	if (num != 0) {
		a.x /= num;
		a.y /= num;
	}
	return a;
}

Vector2f Vector2fXNum(Vector2f a, float num)	// ����*��
{
	a.x *= num;
	a.y *= num;
	return a;
}

Vector2f Vector2fAdd(Vector2f a, Vector2f b)	// ������
{
	Vector2f result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

Vector2f Vector2fSub(Vector2f a, Vector2f b)	// ������
{
	Vector2f result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return result;
}

/*********************************** ������������ѧ�� ********************************************** */
/**
 * @brief De Casteljau  �¿�˹������㷨,�ݹ���㱴�������� ����n�ױ���������
 *
 * @param degree ���鳤�� = ���� + 1
 * @param coeff[] ���Ƶ���������
 * @param t ʱ��t 0 -1
 * @return Vector2f ��ʱ�ĵ�
 */
Vector2f BezierCalculate(uint8 degree, Vector2f coeff[], float t)
{
	Limit(t, 0, 1);

	// if (Nonlinear != 1.0f)	  // ���� t �ƶ��ٶ�
	// 	t = pow(t, Nonlinear);

	Vector2f point[13];	   // ���12�ױ���������

	memcpy(point, coeff, degree * sizeof(Vector2f));	// ��ֵ

	// �ݹ�
	for (size_t r = 1; r < degree; r++)
		for (size_t i = 0; i < degree - r; i++) {
			point[i].x = (1 - t) * point[i].x + t * point[i + 1].x;
			point[i].y = (1 - t) * point[i].y + t * point[i + 1].y;
		}

	return (point[0]);
}

/**
 * @brief  ������ת
 *
 * @param point ��ת��
 * @param point0 ��ת����
 * @param angle ��ת���� ��ʱ��Ϊ��
 */
void Rotate(Vector2f* point, Vector2f point0, float angle)
{
	float x	 = point->x;
	float y	 = point->y;

	point->x = (x - point0.x) * cos(angle) - (y - point0.y) * sin(angle) + point0.x;
	point->y = (y - point0.y) * cos(angle) + (x - point0.x) * sin(angle) + point0.y;
}
