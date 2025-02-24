#include "zf_common_headfile.h"

int16 Maxcolum = 0, EndRow = 0;
int	  RealEndRow = 0, CorrectedEndRow = 0;
int	  StopFlag = 0;

// ��ֹ�мȰ׵�������һ�е���ǰ���׵����ڵ���
/*
 ���壺Ѱ������У�����ȡ��ֹ��
 ���EndRow�����Ż��ұ߽��㷨�����ô�
 ��ҿ������п���һ��
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
