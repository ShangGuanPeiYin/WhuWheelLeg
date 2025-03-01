#include "zf_common_headfile.h"

double BarrierLeftSlopeVariance = 0, BarrierRightSlopeVariance = 0;
double Barrier_Stretch = 0.0, in_Barrier_Stretch = 0.0;
int	   Ba_Stretch1 = 75, Ba_Stretch2 = 410, Ba_Stretch3 = 536;
int	   discount = 0, BarrierError = 0;
int	   Barrier_flag = 0, BarrierCount = 0;
int	   Barrier_record = 0, Barrier_record1 = 0;
int	   Length_end_last = 0;
int	   BarrierDir	   = 1;

/**
 * @brief 识别横断路障
 *
 * @return int 0为未识别到路障，1为识别到了路障
 */
int JudgeRoadBarrier(void)
{
	if (Barrier_flag == 0) {
		if (MainCount > 30 && EndRow >= 12 && EndRow <= 80) {
			if (RealWidth >= 35 && RealWidth <= 55 && MidLine[ControlRow] > 35
				&& MidLine[ControlRow] < 116)	 // RealWidth<=55MidLine[ControlRow]>60&&MidLine[ControlRow]<90
			{
				if (Right_Slope[ControlRow] > -0.8 && Right_Slope[ControlRow] <= 0 && Left_Slope[ControlRow] < 0.8
					&& Left_Slope[ControlRow] >= 0) {
					BarrierLeftSlopeVariance = GetLeftVariance(ROW - 2, EndRow + (ROW - EndRow) / 8);
					if (BarrierLeftSlopeVariance < 0.2) {
						BarrierRightSlopeVariance = GetRightVariance(ROW - 2, EndRow + (ROW - EndRow) / 8);
						if (BarrierRightSlopeVariance < 0.2) {
							Barrier_Stretch = Stretch;
							Barrier_flag	= 1;
							discount		= 0;
							BarrierError	= 0;
							return 1;
						} else {
							discount	 = 0;
							BarrierError = 4;
							return 0;
						}
					} else {
						discount	 = 0;
						BarrierError = 3;
						return 0;
					}
				} else {
					discount	 = 0;
					BarrierError = 2;
					return 0;
				}
			} else {
				discount	 = 0;
				BarrierError = 1;
				return 0;
			}
		} else {
			discount	 = 0;
			BarrierError = 3;
			return 0;
		}
	}
	return 0;
}