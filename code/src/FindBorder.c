#include "zf_common_headfile.h"
int LeftLine[ROW] = {0}, RightLine[ROW] = {0};	  // ���ұ߽�洢����
int Original_RightLine[ROW], Original_LeftLine[ROW];
int LeftLine_lost[ROW], RightLine_lost[ROW];
int Valid_Left = 0, Valid_Right = 0;

/*
 ���壺��Ҫ�Լ�дһ���ұ߽纯�����߽羡������LeftLine[ROW]��RightLine[ROW]�У�������
 */
/*
 * FindBorder.c
 * Created on: 2024��10��11��
 * Author: ����
 */
void FindBorder(void)
{
	Valid_Left	= 0;
	Valid_Right = 0;
	for (int row = ROW - 1; row >= RealEndRow; row--)	 // ����ÿһ��
	{
		int leftFound  = 0;	   // ��߽��Ƿ��ҵ�
		int rightFound = 0;	   // �ұ߽��Ƿ��ҵ�

		// ����Ѱ��
		for (int col = Maxcolum; col >= 2; col--) {
			if (videoData[row][col] == WHITE && videoData[row][col - 1] == BLACK
				&& videoData[row][col - 2] == BLACK)	// �ҵ��ںڰ�
			{
				LeftLine[row]	   = col;	 // ��߽�λ��
				leftFound		   = 1;		 // ����ҵ���߽�
				LeftLine_lost[row] = 0;
				break;	  // �˳�ѭ������߽����ҵ�
			} else if (col < 2) {
				LeftLine[row]	   = col;
				LeftLine_lost[row] = 1;
				break;
			}
			Original_LeftLine[row] = LeftLine[row];	   // ԭʼ��߽�
		}

		// ����Ѱ��
		for (int col = Maxcolum; col <= COL - 1 - 2; col++) {
			if (videoData[row][col] == WHITE && videoData[row][col + 1] == BLACK
				&& videoData[row][col + 2] == BLACK)	// �ҵ��׺ں�
			{
				RightLine[row]		= col;	  // �ұ߽�λ��
				rightFound			= 1;	  // ����ҵ��ұ߽�
				RightLine_lost[row] = 0;
				break;	  // �˳�ѭ�����ұ߽����ҵ�
			} else if (col > COL - 1 - 2) {
				RightLine[row]		= col;
				RightLine_lost[row] = 1;
				break;
			}
			Original_RightLine[row] = RightLine[row];	 // ԭʼ�ұ߽�
		}

		// ������ұ߽綼�ҵ��ˣ�ͳ��Ϊ��Ч��
		if (leftFound) {
			Valid_Left++;
		}
		if (rightFound) {
			Valid_Right++;
		}
	}
}
