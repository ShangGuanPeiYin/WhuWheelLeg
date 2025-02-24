#include "zf_common_headfile.h"
int LeftLine[ROW] = {0}, RightLine[ROW] = {0};	  // 左右边界存储数组
int Original_RightLine[ROW], Original_LeftLine[ROW];
int LeftLine_lost[ROW], RightLine_lost[ROW];
int Valid_Left = 0, Valid_Right = 0;

/*
 刘沐：需要自己写一份找边界函数，边界尽量放在LeftLine[ROW]和RightLine[ROW]中，加油捏
 */
/*
 * FindBorder.c
 * Created on: 2024年10月11日
 * Author: 刘沐
 */
void FindBorder(void)
{
	Valid_Left	= 0;
	Valid_Right = 0;
	for (int row = ROW - 1; row >= RealEndRow; row--)	 // 遍历每一行
	{
		int leftFound  = 0;	   // 左边界是否找到
		int rightFound = 0;	   // 右边界是否找到

		// 向左寻找
		for (int col = Maxcolum; col >= 2; col--) {
			if (videoData[row][col] == WHITE && videoData[row][col - 1] == BLACK
				&& videoData[row][col - 2] == BLACK)	// 找到黑黑白
			{
				LeftLine[row]	   = col;	 // 左边界位置
				leftFound		   = 1;		 // 标记找到左边界
				LeftLine_lost[row] = 0;
				break;	  // 退出循环，左边界已找到
			} else if (col < 2) {
				LeftLine[row]	   = col;
				LeftLine_lost[row] = 1;
				break;
			}
			Original_LeftLine[row] = LeftLine[row];	   // 原始左边界
		}

		// 向右寻找
		for (int col = Maxcolum; col <= COL - 1 - 2; col++) {
			if (videoData[row][col] == WHITE && videoData[row][col + 1] == BLACK
				&& videoData[row][col + 2] == BLACK)	// 找到白黑黑
			{
				RightLine[row]		= col;	  // 右边界位置
				rightFound			= 1;	  // 标记找到右边界
				RightLine_lost[row] = 0;
				break;	  // 退出循环，右边界已找到
			} else if (col > COL - 1 - 2) {
				RightLine[row]		= col;
				RightLine_lost[row] = 1;
				break;
			}
			Original_RightLine[row] = RightLine[row];	 // 原始右边界
		}

		// 如果左右边界都找到了，统计为有效行
		if (leftFound) {
			Valid_Left++;
		}
		if (rightFound) {
			Valid_Right++;
		}
	}
}
