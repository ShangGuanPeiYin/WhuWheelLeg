#include "zf_common_headfile.h"

float Correct_Offset_x=0;
float Correct_Offset_y=0;

float Trans_Form[8]=
{
  1.98033099303538,	-0.0311372797647050,	-149.962278873731,
-1.83351615321276e-16,	-0.798671225964742,	221.131230504030,
-6.95870761865348e-18,	0.0526220028023551	
};
/**
 * @brief  坐标转换
 * @param  coordinate_x  像素坐标x
 * @param  coordinate_y  像素坐标y
 * @param  Coordinate    转换后的坐标
 */
void Real_Location(int coordinate_x,int coordinate_y,float Coordinate[1][2])
{
  float Correct_Coordinate_x,Correct_Coordinate_y;
  Correct_Coordinate_x=(Trans_Form[0]*coordinate_x+Trans_Form[1]*coordinate_y+Trans_Form[2])/(Trans_Form[6]*coordinate_x+Trans_Form[7]*coordinate_y+1.0);
  Correct_Coordinate_y=(Trans_Form[3]*coordinate_x+Trans_Form[4]*coordinate_y+Trans_Form[5])/(Trans_Form[6]*coordinate_x+Trans_Form[7]*coordinate_y+1.0);
  Coordinate[0][0]=Correct_Coordinate_x;
  Coordinate[0][1]=Correct_Coordinate_y;
}

/**
 * @brief  计算两点之间的距离
 * @param  coordinate1  第一个点的坐标
 * @param  coordinate2  第二个点的坐标
 * @retval 两点之间的距离
 */
float GetDistance(float coordinate1[1][2],float coordinate2[1][2])
{
  float distance;
  distance = InvSqrt((coordinate1[0][0]-coordinate2[0][0])*(coordinate1[0][0]-coordinate2[0][0])
                     +(coordinate1[0][1]-coordinate2[0][1])*(coordinate1[0][1]-coordinate2[0][1]));
  return distance;
}
