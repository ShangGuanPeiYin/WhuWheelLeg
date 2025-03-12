#include "zf_common_headfile.h"
double LeftLineSlopeVariance;
double RightLineSlopeVariance;

/**
 * @brief 求方差
 *
 * @param row0 开始行
 * @param row1 结束行
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
 * @brief 求校正后中线斜率的方差
 *
 * @param row0 开始行
 * @param row1 结束行
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
 * @brief 求校正后左边界斜率的方差
 *
 * @param row0 开始行
 * @param row1 结束行
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
 * @brief 求校正后右边界斜率的方差
 *
 * @param row0 开始行
 * @param row1 结束行
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
 * @brief 求校正前左边界斜率的方差
 *
 * @param row0 开始行
 * @param row1 结束行
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
 * @brief 求校正前右边界斜率的方差
 *
 * @param row0 开始行
 * @param row1 结束行
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
