#include "zf_common_headfile.h"

float Correct_Offset_x = 0;
float Correct_Offset_y = 0;

float Trans_Form[8]	   = 
						   {-2.8392,
						   0.1506,
						   223.3433,
						   0.0696,
						   0.0409,
						   -265.5322,
						   0.0010,
						   -0.1537};

						//   {1.98033099303538,
						//   -0.0311372797647050,
						//   -149.962278873731,
						//   -1.83351615321276e-16,
						//   -0.798671225964742,
						//   221.131230504030,
						//   -6.95870761865348e-18,
						//   0.0526220028023551};
/**
 * @brief  ����ת��
 * @param  coordinate_x  ��������x
 * @param  coordinate_y  ��������y
 * @param  Coordinate    ת���������
 */
void  Real_Location(int coordinate_x, int coordinate_y, float Coordinate[1][2])
{
	float Correct_Coordinate_x, Correct_Coordinate_y;
	Correct_Coordinate_x = (Trans_Form[0] * coordinate_x + Trans_Form[1] * coordinate_y + Trans_Form[2])
						   / (Trans_Form[6] * coordinate_x + Trans_Form[7] * coordinate_y + 1.0);
	Correct_Coordinate_y = (Trans_Form[3] * coordinate_x + Trans_Form[4] * coordinate_y + Trans_Form[5])
						   / (Trans_Form[6] * coordinate_x + Trans_Form[7] * coordinate_y + 1.0);
	Coordinate[0][0] = Correct_Coordinate_x;
	Coordinate[0][1] = Correct_Coordinate_y;
}

/**
 * @brief  ��������֮��ľ���
 * @param  coordinate1  ��һ���������
 * @param  coordinate2  �ڶ����������
 * @retval ����֮��ľ���
 */
float GetDistance(float coordinate1[1][2], float coordinate2[1][2])
{
	float distance;
	distance = InvSqrt((coordinate1[0][0] - coordinate2[0][0]) * (coordinate1[0][0] - coordinate2[0][0])
					   + (coordinate1[0][1] - coordinate2[0][1]) * (coordinate1[0][1] - coordinate2[0][1]));
	return distance;
}
