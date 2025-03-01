#include "zf_common_headfile.h"

int	 LeftLine[ROW] = {0}, RightLine[ROW] = {0};
int	 Original_RightLine[ROW], Original_LeftLine[ROW];
int	 LeftLine1[ROW], RightLine1[ROW];
int	 ValidRow = 0;
/**
 * @brief ��ɨ�跨�ұ߽�
 */
void FindBorder(void)
{
	int i, j;
	for (i = ROW - 1; i > ValidRow - 1; i--)	// Ѱ�ұ��ߣ�����
	{
		for (j = Maxcolumn; j > 1; j--) {
			if (videoData[i][j - 2] == 0 && videoData[i][j - 1] == 0 && videoData[i][j] == 0) {
				LeftLine[i] = j + 1;
				break;
			}
			// else if(j == 2) LeftLine[i] = 0;
		}

		if (j == 1) {
			for (; j > -1; j--) {
				if (videoData[i][j] == 0) {
					LeftLine[i] = j + 1;
					break;
				}
			}
		}
		if (j == -1)
			LeftLine[i] = 0;

		for (j = Maxcolumn; j < COLUMN - 2; j++) {
			if (videoData[i][j + 2] == 0 && videoData[i][j + 1] == 0 && videoData[i][j] == 0) {
				RightLine[i] = j - 1;
				break;
			}
			// else if(j == COLUMN - 3) RightLine[i] = COLUMN -1;
		}

		if (j == COLUMN - 2) {
			for (; j < COLUMN; j++) {
				if (videoData[i][j] == 0) {
					RightLine[i] = j - 1;
					break;
				}
			}
		}
		if (j == COLUMN)
			RightLine[i] = COLUMN - 1;

		Original_LeftLine[i]  = LeftLine[i];
		Original_RightLine[i] = RightLine[i];
	}
}

/**
 * @brief �����ұ߽�
 */
void FindBorder1(void)
{
	int i = 0, j = 0;
	/*****************************
	���һ�еı���
	*****************************/
	LeftLine1[ROW - 1]	= 0;
	RightLine1[ROW - 1] = COLUMN - 1;

	/***********************
	������һ�б���λ��Ѱ��
	***********************/
	for (i = ROW - 2; i > -1; i--) {
		// ��һ����߽�ĺ�һ�����Ǻڵ㣬��������
		if (videoData[i][LeftLine1[i + 1]] == 0) {
			for (j = LeftLine1[i + 1] + 1; j < COLUMN - 2; j++) {
				if (videoData[i][j + 2] == 1 && videoData[i][j + 1] == 1 && videoData[i][j] == 1) {
					LeftLine1[i] = j;
					break;
				}
			}
			if (j >= COLUMN - 2)
				LeftLine1[i] = COLUMN / 2;
		}
		// ��һ����߽�ĺ�һ�����ǰ׵㣬��������
		else if (videoData[i][LeftLine1[i + 1]] == 1) {
			LeftLine1[i] = 0;
			for (j = LeftLine1[i + 1] - 1; j > 1; j--) {
				if (videoData[i][j - 2] == 0 && videoData[i][j - 1] == 0 && videoData[i][j] == 0) {
					LeftLine1[i] = j + 1;
					break;
				}
			}
			if (j == 1) {
				for (; j > -1; j--) {
					if (videoData[i][j] == 0) {
						LeftLine1[i] = j + 1;
						break;
					}
					LeftLine1[i] = 0;
				}
			}
		}
		// ��һ���ұ߽�ĺ�һ�����ǰ׵㣬��������
		if (videoData[i][RightLine1[i + 1]] == 1) {
			RightLine1[i] = COLUMN - 1;
			for (j = RightLine1[i + 1] + 1; j < COLUMN - 2; j++) {
				if (videoData[i][j + 2] == 0 && videoData[i][j + 1] == 0 && videoData[i][j] == 0) {
					RightLine1[i] = j;
					break;
				}
			}
			if (j == COLUMN - 2) {
				for (; j < COLUMN; j++) {
					if (videoData[i][j] == 0) {
						RightLine1[i] = j - 1;
						break;
					}
					RightLine1[i] = COLUMN - 1;
				}
			}
		}
		// ��һ���ұ߽�ĺ�һ�����Ǻڵ㣬��������
		else if (videoData[i][RightLine1[i + 1]] == 0) {
			for (j = RightLine1[i + 1] - 1; j > 1; j--) {
				if (videoData[i][j - 2] == 1 && videoData[i][j - 1] == 1 && videoData[i][j] == 1) {
					RightLine1[i] = j;
					break;
				}
			}
			if (j <= 1) {
				RightLine1[i] = COLUMN / 2;
			}
		}
		if (LeftLine1[i] >= RightLine1[i]) {
			ValidRow = i + 1;
			break;
		}
	}
	if (i <= 0) {
		ValidRow = 0;
	}
}
