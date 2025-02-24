/*
 * FindMidline.c
 * Created on: 2024��10��11��
 * Author: ����
 */

#include "zf_common_headfile.h"

int32 MidLine[ROW] = {0};
int32 Error[ROW]   = {0};
int Original_MidLine[ROW] = {0}, Original_Error[ROW] = {0};	   // ����·���޸�Error�󣬿��ܻ���Ҫԭ����Error���ڼ�����ж�

void Find_MidLine(void)
{
	int i;
	for (i = ROW - 1; i > CorrectedEndRow; i--)	   // Ѱ�ұ��ߣ�����
	{
		MidLine[i]			= (RightLine[i] + LeftLine[i]) / 2;
		Original_MidLine[i] = MidLine[i];
		Error[i]			= MidLine[i] - COL / 2;	   // error��0��ʾ��ƫ
		Original_Error[i]	= Error[i];
	}
}
