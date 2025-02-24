#include "zf_common_headfile.h"

int16 Maxcolum = 0, EndRow = 0;
int	  RealEndRow = 0, CorrectedEndRow = 0;
int	  StopFlag = 0;

// 截止行既白点最多的那一列的最前方白点所在的行
/*
 刘沐：寻找最长白列，并获取截止行
 这个EndRow对于优化找边界算法很有用处
 大家可以自行考虑一下
 */
void Find_EndRow(void)
{
	int16 i, j, num, max = 0;

	for (j = 0; j < COL; j++) {
		num = 0;
		for (i = ROW - 1; i > 0; i--) {
			if (videoData[i][j] == BLACK)
				break;
			num++;
		}
		if (num >= max) {
			EndRow	 = i;
			max		 = num;
			Maxcolum = j;
			if (Maxcolum >= COL - 3)
				Maxcolum = COL - 3;
			if (Maxcolum <= 2)
				Maxcolum = 2;
		}
	}
	if (EndRow > 95)
		StopFlag = 1;
}

void CorrectEndRow(void)
{
	if (EndRow < 2) {
		EndRow = 2;
	}
	CorrectedEndRow = EndRow;
	return;
}
