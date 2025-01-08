#include "zf_common_headfile.h"

uint8 videoData[ROW][COL];	  // ͼ��洢����
int16 dynamicBinary;		  // ͼ��̬��ֵ����ֵ
int16 staticBinary = 0;		  // ͼ��̶���ֵ����ֵ

int LightPoint	   = 20;	// ��ֵ����
int trans		   = -5;	// ͼ��ü�����ƫ�� 5
// int trans		   = -4;	// ͼ��ü�����ƫ�� 3
// int trans		   = 0;	   // ͼ��ü�����ƫ�� 5

/*
*��������Binary_Img
*���ܣ���ֵ��ͼ�񣬱��浽videoData�У�����ʶ��
*��ע���ɼ�ͼ��
	=========================================       ---
	|                                        |        *
	|                                        |        |
	|--------+---------------------+----------        |
	|        |                     |         |        |
	|        |ROW    ����ͼ��      |            |  MT9V03X_H
	|        |                     |         |        |
	|--------+---------------------+----------        |
	|        |<--------COL-------->|         |        |
	|                                        |        *
	==========================================       ---
	|<------------MT9V03X_W------------->|
*/
void Binary_Img(void)
{
	if (LightPoint >= 10000)
		LightPoint = -(LightPoint - 10000);

	if (0 == staticBinary)	  // ���õľ�̬��ֵΪ0�����������̬��ֵ������Ӧ�Ը�ǿ��
	{
		dynamicBinary = Fast_OTSU(mt9v03x_image[0], MT9V03X_H, MT9V03X_W) + LightPoint;	   // ��򷨼���ͼ���ֵ����ֵ
	} else	  // �����ù̶���ֵ��ֵ������ʱ��̶���ֵ��Ч�����ã�
	{
		dynamicBinary = staticBinary;	 // ��̬��ֵ
	}

	for (int16 row = 0, col; row < ROW; ++row)	  // ȥ����������
	{
		for (col = COL_DIS / 2 - trans; col < COL + COL_DIS / 2 - trans; ++col)	   // ȥ�����������
		{	 // �Ҷ�ֵС����ֵ����Ϊ�Ǻ�ɫ����ɫ�Ҷ�ֵ=0����ɫ�Ҷ�ֵ=255��
			videoData[row][col - COL_DIS / 2 + trans]
				= (mt9v03x_image[row][col] < dynamicBinary) ? BLACK : WHITE;	// Data����� 01,����0��255
		}
	}
}

/*
*��������Fast_OTSU
*������image-ͼ������,col-����,row-����
*����ֵ��ͼ���ֵ����ֵ
*���ܣ���򷨼����ֵ����ֵ���Ż��棩,�ο� https://www.cnblogs.com/ranjiewen/p/6385564.html
*���ߣ��쿡�� 2018/11/26
*��ע�������ԣ��Ż�ǰ��180MHZ��ֵ��188x120-33.8ms��152x100-32.4ms��
			   �Ż���180MHZ��ֵ��188x120- 3.0ms��152x100-2.2ms,128x64- 1.2ms
					   200MHZ��ֵ��152x100- 1.8ms��220MHZ��ֵ��152x100- 1.6ms
					   200MHZ��ֵ��188x70- 1.35ms
*/
uint8 Fast_OTSU(uint8* img, int16 row, int16 col)
{
	static int16 isFirstBinary = 1;						  // �״ζ�ֵ����־λ
	static int16 threshold;								  // ��ֵ����ֵ
	int16		 minGrayValue = 0, maxGrayValue = 255;	  // ��С�������Ч�Ҷ�ֵ���������ٱ�����
	// int16 Pix_Dis = (ROW_DIS * MT9V03X_CSI_W) / 2;      //ȥ��ͼ��δ����ʶ��Ĳ���

	// ���±���Ҫע���������������ʵ�ʵķֱ����޸��������͡�
	int grayHist[256] = {0};	// �Ҷ�ֱ��ͼ����������Ҫ��int16������һ�ֻҶȳ��ֵĴ���̫��ͻ������
	const int32 sumOfPixel	   = row * col;					// ��������
	int32		sumOfGrayValue = 0;							// ����ͼ����ܻҶ�ֵ
	int32		sumOfBackPixel = 0, sumOfForcePixel = 0;	// ǰ����������
	int32		sumOfBackGray = 0, sumOfForceGray = 0;		// ǰ���ܻҶ�ֵ

	float w0, w1, u0, u1;					// ������ǰ�����ر���
	float maxVariance = -1, tmpVariance;	// ��䷽��

	for (int i = 0; i < sumOfPixel; ++i)	// ��һ��ѭ�����Ա�����������±�ʱ����˷��������˸��Ӷ�
	{
		++grayHist[img[i]];	   // ��ûҶ�ֱ��ͼ��ͳ��0~255ÿ���Ҷȳ����˼��Σ�����㷨���90%��ʱ�仨�����
	}
	while (minGrayValue < 256 && 0 == grayHist[minGrayValue])	 // ������С��Ч�Ҷ�ֵ
	{
		++minGrayValue;
	}
	while (maxGrayValue >= minGrayValue && 0 == grayHist[maxGrayValue])	   // ���������Ч�Ҷ�ֵ
	{
		--maxGrayValue;
	}
	if (maxGrayValue - minGrayValue <= 1)	 // ����Ҷ�ֵ������2��(��Ȼ��������Ǽ��������ܵ�)
	{
		return (uint8) minGrayValue;	// ֱ����������ֵ
	}
	for (int16 i = minGrayValue; i <= maxGrayValue; ++i) {
		sumOfGrayValue += i * grayHist[i];	  // �����ܻҶ�ֵ
	}
	for (int16 i = minGrayValue; i <= maxGrayValue; ++i)	// �󷽲�Ĺ��̼�Ϊһ��ѭ������󽵵����㷨���Ӷ�
	{
		sumOfBackPixel += grayHist[i];		  // ������������
		sumOfBackGray  += i * grayHist[i];	  // �����ܻҶ�ֵ
		if (1 == isFirstBinary)				  // ��һ�ζ�ֵ��
		{
			goto GRAY_VARIANCE;
		} else	  // ���ǵ�һ�ζ�ֵ����������ֵ���ϴ���ֵ�ĸ����������ܿ켸ʮus��
		{
			if (i < threshold - 5 && maxGrayValue > threshold)	  // ���ϴ���ֵ�Ĳ�� > ĳ��ֵ����������䷽�
			{
				continue;
			}
			if (i > threshold + 5 && minGrayValue < threshold) {
				return (uint8) threshold;	 // �����䷽���Ӧ�ĻҶ�ֵ����Ϊ����ѷָ���ֵ
			}
		}
	GRAY_VARIANCE:													   // ������䷽��
		sumOfForcePixel = sumOfPixel - sumOfBackPixel;				   // ǰ����������
		sumOfForceGray	= sumOfGrayValue - sumOfBackGray;			   // ǰ���ܻҶ�ֵ
		w0				= (float) sumOfBackPixel / sumOfPixel;		   // �������ر���
		w1				= 1 - w0;									   // ǰ�����ر���
		u0				= (float) sumOfBackGray / sumOfBackPixel;	   // �����ҶȾ�ֵ
		u1				= (float) sumOfForceGray / sumOfForcePixel;	   // ǰ���ҶȾ�ֵ
		// ����u=w0*u0+w1*u1����䷽��w0*(u-u0)^2+w1*(u-u1)^2�ɻ���Ϊw0*w1*(u0-u1)^2
		tmpVariance		= w0 * w1 * (u0 - u1) * (u0 - u1);	  // ��䷽��
		if (tmpVariance > maxVariance) {
			maxVariance = tmpVariance;	  // ��¼�����䷽��
			threshold	= i;			  // ��¼�����䷽���Ӧ�ĻҶ�ֵ
		}
	}
	isFirstBinary = 0;			 // ��ɵ�һ�ζ�ֵ������ձ�־λ
	return (uint8) threshold;	 // �����䷽���Ӧ�ĻҶ�ֵ����Ϊ����ѷָ���ֵ
}
