#include "zf_common_headfile.h"

double Left_Slope[ROW]={0},Right_Slope[ROW]={0},MidLine_Slope[ROW]={0};
double RealMidSlope[ROW],RealLeftSlope[ROW],RealRightSlope[ROW];


/**
 * @brief 计算左右边界的斜率
 *
 * @param LeftLine 左边界
 * @param RightLine 右边界
 */
void GetSlope()
{
  int i=0;
  for(i=ROW-3;i>ValidRow+1;i--)
  {
    Left_Slope[i]=(LeftLine[i-2]+LeftLine[i-1]-LeftLine[i+1]-LeftLine[i+2])/6.0;
    Right_Slope[i]=(RightLine[i-2]+RightLine[i-1]-RightLine[i+1]-RightLine[i+2])/6.0;
    MidLine_Slope[i]=(MidLine[i-2]+MidLine[i-1]-MidLine[i+1]-MidLine[i+2])/6.0;
  }
  Left_Slope[ROW-2]=(LeftLine[ROW-3]-LeftLine[ROW-1])/2.0;
  Right_Slope[ROW-2]=(Right_Slope[ROW-3]-Right_Slope[ROW-1])/2.0;
  MidLine_Slope[ROW-2]=(MidLine_Slope[ROW-3]-MidLine_Slope[ROW-1])/2.0;
  
  Left_Slope[ROW-1]=Left_Slope[ROW-2];
  Right_Slope[ROW-1]=Right_Slope[ROW-2];
  MidLine_Slope[ROW-1]=MidLine_Slope[ROW-2];
}


/**
 * @brief 计算真实赛道中线斜率
 */
void GetRealMidSlope(void)
{
  int i=0;
  for(i=ROW-5;i>ValidRow+2;i--) //ROW-3 ValidRow+1
  {
    RealMidSlope[i]=(RealMidLine1[i-3]-RealMidLine1[i+3])/(RealMidLine2[i-3]-RealMidLine2[i+3])/3.0
                    +(RealMidLine1[i-2]-RealMidLine1[i+2])/(RealMidLine2[i-2]-RealMidLine2[i+2])/3.0
                    +(RealMidLine1[i-1]-RealMidLine1[i+1])/(RealMidLine2[i-1]-RealMidLine2[i+1])/3.0;
                   
  }
}


/**
 * @brief 计算真实左边界斜率
 */
void GetRealLeftSlope(void)
{
  int i=0;
  for(i=ROW-3;i>ValidRow+1;i--)
  {
      RealLeftSlope[i]=(RealLeftLine1[i-2]-RealLeftLine1[i+2])
        /(RealLeftLine2[i-2]-RealLeftLine2[i+2])/2
          +(RealLeftLine1[i-1]-RealLeftLine1[i+1])
            /(RealLeftLine2[i-1]-RealLeftLine2[i+1])/2;
  }
}


/**
 * @brief 计算真实右边界斜率
 */
void GetRealRightSlope(void)
{
  int i=0;
  for(i=ROW-3;i>ValidRow+1;i--)
  {
      RealRightSlope[i]=(RealRightLine1[i-2]-RealRightLine1[i+2])
        /(RealRightLine2[i-2]-RealRightLine2[i+2])/2
          +(RealRightLine1[i-1]-RealRightLine1[i+1])
            /(RealRightLine2[i-1]-RealRightLine2[i+1])/2;
  }
}

