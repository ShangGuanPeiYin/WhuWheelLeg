#include "zf_common_typedef.h"

#ifndef CODE_CAMERA_H_
#define CODE_CAMERA_H_

#define ROW_DIS 30
#define COL_DIS 28
#define BLACK	0
#define WHITE	1

extern int trans;

extern uint8 videoData[ROW][COL];	 // ͼ��洢����
extern int16 dynamicBinary;			 // ͼ��̬��ֵ����ֵ
extern int16 staticBinary;			 // ͼ��̶���ֵ����ֵ
extern int	 LightPoint;

void  Binary_Img(void);								  // ��ֵ��ͼ��
uint8 Fast_OTSU(uint8* img, int16 row, int16 col);	  // �������ֵ
void  OLED_Print_Img128X64(uint8 img[ROW][COL]);

#endif /* CODE_CAMERA_H_ */
