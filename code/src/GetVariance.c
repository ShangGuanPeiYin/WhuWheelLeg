#include "zf_common_headfile.h"
double LeftLineSlopeVariance;
double RightLineSlopeVariance;

/**
 * @brief �󷽲�
 *
 * @param row0 ��ʼ��
 * @param row1 ������
 */
double GetVariance(int row0, int row1)
{
	int	   i;
	double count			 = 0;
	double MidLine_Slope_Sum = 0, MidLine_Slope_Avg = 0, Variance = 0;

	if (row1 >= row0)
		return 0;
	for (i = row0; i > row1; i -= 2) {
		MidLine_Slope_Sum += MidLine_Slope[i];
		count++;
	}
	MidLine_Slope_Avg = MidLine_Slope_Sum / (double) count;
	for (i = row0; i > row1; i--) { Variance += (MidLine_Slope[i] - MidLine_Slope_Avg) * (MidLine_Slope[i] - MidLine_Slope_Avg); }
	Variance = Variance / (double) (row0 - row1);
	return Variance;
}

/**
 * @brief ��У��������б�ʵķ���
 *
 * @param row0 ��ʼ��
 * @param row1 ������
 */
double GetVariance1(int row0, int row1)
{
	int	   i;
	double count			 = 0;
	double MidLine_Slope_Sum = 0, MidLine_Slope_Avg = 0, Variance = 0;
	for (i = row0; i > row1; i -= 2) {
		MidLine_Slope_Sum += RealMidSlope[i];
		count++;
	}
	MidLine_Slope_Avg = MidLine_Slope_Sum / count;
	for (i = row0; i > row1; i -= 2) { Variance += (RealMidSlope[i] - MidLine_Slope_Avg) * (RealMidSlope[i] - MidLine_Slope_Avg); }
	Variance = Variance / count;
	return Variance;
}

/**
 * @brief ��У������߽�б�ʵķ���
 *
 * @param row0 ��ʼ��
 * @param row1 ������
 */
double GetLeftVariance1(int row0, int row1)
{
	int	   i;
	double count			  = 0;
	double LeftLine_Slope_Sum = 0, LeftLine_Slope_Avg = 0, Variance = 0;

	if (row1 <= ValidRow + 1) {
		row1 = ValidRow + 1;
	}

	for (i = row0; i > row1; i -= 2) {
		LeftLine_Slope_Sum += RealLeftSlope[i];
		count++;
	}
	LeftLine_Slope_Avg = LeftLine_Slope_Sum / count;
	for (i = row0; i > row1; i -= 2) {
		Variance += (RealLeftSlope[i] - LeftLine_Slope_Avg) * (RealLeftSlope[i] - LeftLine_Slope_Avg);
	}
	Variance = Variance / count;
	return Variance;
}

/**
 * @brief ��У�����ұ߽�б�ʵķ���
 *
 * @param row0 ��ʼ��
 * @param row1 ������
 */
double GetRightVariance1(int row0, int row1)
{
	int	   i;
	double count			   = 0;
	double RightLine_Slope_Sum = 0, RightLine_Slope_Avg = 0, Variance = 0;

	if (row1 <= ValidRow + 1) {
		row1 = ValidRow + 1;
	}

	for (i = row0; i > row1; i -= 2) {
		RightLine_Slope_Sum += RealRightSlope[i];
		count++;
	}
	RightLine_Slope_Avg = RightLine_Slope_Sum / count;
	for (i = row0; i > row1; i -= 2) {
		Variance += (RealRightSlope[i] - RightLine_Slope_Avg) * (RealRightSlope[i] - RightLine_Slope_Avg);
	}
	Variance = Variance / count;
	return Variance;
}

/**
 * @brief ��У��ǰ��߽�б�ʵķ���
 *
 * @param row0 ��ʼ��
 * @param row1 ������
 */
double GetLeftVariance(int row0, int row1)
{
	int	   i;
	double count			  = 0;
	double LeftLine_Slope_Sum = 0, LeftLine_Slope_Avg = 0, Variance = 0;

	if (row1 <= ValidRow + 1) {
		row1 = ValidRow + 1;
	}

	for (i = row0; i > row1; i -= 2) {
		LeftLine_Slope_Sum += Left_Slope[i];
		count++;
	}
	LeftLine_Slope_Avg = LeftLine_Slope_Sum / count;
	for (i = row0; i > row1; i -= 2) { Variance += (Left_Slope[i] - LeftLine_Slope_Avg) * (Left_Slope[i] - LeftLine_Slope_Avg); }
	Variance = Variance / count;
	return Variance;
}

/**
 * @brief ��У��ǰ�ұ߽�б�ʵķ���
 *
 * @param row0 ��ʼ��
 * @param row1 ������
 */
double GetRightVariance(int row0, int row1)
{
	int	   i;
	double count			   = 0;
	double RightLine_Slope_Sum = 0, RightLine_Slope_Avg = 0, Variance = 0;

	if (row1 <= ValidRow + 1) {
		row1 = ValidRow + 1;
	}

	for (i = row0; i > row1; i -= 2) {
		RightLine_Slope_Sum += Right_Slope[i];
		count++;
	}
	RightLine_Slope_Avg = RightLine_Slope_Sum / count;
	for (i = row0; i > row1; i -= 2) {
		Variance += (Right_Slope[i] - RightLine_Slope_Avg) * (Right_Slope[i] - RightLine_Slope_Avg);
	}
	Variance = Variance / count;
	return Variance;
}
