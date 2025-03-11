#include "zf_common_headfile.h"

int RampDis;
double OutRampStrech = 0;
int RampFlag=0;
long RampMainCount=0;


/**
 * @brief 识别坡道 上坡时须将控制行压得很近，如90，否则远处图像异常会导致舵机打角异常
 *
 * @return int 1为识别到坡道，0为未识别到坡道
 */
int Judge_Ramp(void)
{
  static int RampCount=0;
  int i=0;
  //有角点存在则认为不是坡道，出坡道后2米不再识别坡道，防止下坡时识别成坡道
  if(MainCount<100||RightFound!=0||LeftFound!=0)//||(Stretch-OutRampStrech<=200)
  {
    return 0;
  }
  //没识别到坡道前的识别方案
  if(RampFlag==0)
  {
    //截止行最小且中线斜率方差很小的情况作进一步分析，否则认为不是坡道
    if(RealEndRow==0/*&&MidLineSlopeVariance<0.03*/)
    {
      //从控制行到截止行+8找异常宽度的赛道
      for(i=ControlRow;i>RealEndRow+8;i--)
      {
        //有赛道大于普通赛道宽度且宽度有增大的趋势，认为是坡道
        //利用了坡道与矫正视角平面的夹角导致赛道变宽的原理
        if(RealWidth1[i]>60
           &&RealWidth1[i-1]>RealWidth1[i]
             &&RealWidth1[i-2]>RealWidth1[i-1])
        {
          RampCount++;
          if(RampCount>1)
          {
            RampFlag=1;
            //RampStrech=Stretch;
            RampCount=0;
          }
          break;
        }
      }
      if(i<=RealEndRow+8)
      {
        RampFlag=0;
        RampCount=0;
      }
    }
  }
  //识别到坡道以后直接给一段距离，用于硬出，比识别出好用
  
  /*
  else if(RampFlag==1)
  {
//    if(Stretch-RampStrech>RampDis)CarPitch
    if(Stretch-RampStrech>RampDis)
    {
        OutRampStrech = Stretch;
        RampMainCount=MainCount;
        RampFlag=0;
    }
  }
  */

  if(RampFlag==0)
  {
    return 0;
  }
  else 
  {
    return 1;
  }
  
}


/**
 * @brief 判断是否出坡道 1s差不多跑了66个DMA中断
 *
 * @return int 1为出坡道，0为未出坡道
 */
int OutRamp(void)
{
  if(MainCount-RampMainCount>=0&&MainCount-RampMainCount<50&&MainCount>50) return 1;
  else return 0;
}


/**
 * @brief 坡道处理，标志位置位
 */
void RampDeal(void)
{
  RoadFlag[RAMP]=1;
}
