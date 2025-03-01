#include "zf_common_headfile.h"
int guaidianshu=0;


/**
 * @brief 寻找左右边界的拐点 一般来说，小S弯和中S弯的左右边界会在视野内存在两个以上的拐点
 *
 * @return int 1：拐点个数满足条件，0：反之
 */
int AssertInterSectionPoint(void)
{
  int i;
  int LeftCount=0,RightCount=0;//保存左右边界找到的拐点数
  int leftsignflag=1,leftsignflag1=1,rightsignflag=1,rightsignflag1=1; //每次斜率极性变化时该标志位正负极性变化
  int div=0;  //由于近处像素密集，寻访时跳跃的更快，远处则一行一行的找
  
  //寻找左拐点
  for(i=ROW-1;i>ValidRow+4;i-=div)
  {
    div = 1;
    if(div<1) div=1;
    if((LeftLine[i]-LeftLine[i-div])*leftsignflag>0&&(LeftLine[i-div]-LeftLine[i-2*div])*leftsignflag>0)
    {
      leftsignflag=-leftsignflag;
      leftsignflag1=0;
      LeftCount++;     
      continue;
    }
    else if((LeftLine[i]-LeftLine[i-div])*leftsignflag1<0&&(LeftLine[i-div]-LeftLine[i-2*div])*leftsignflag1<0)
    {
      leftsignflag=0;
      leftsignflag1=-leftsignflag1;      
      LeftCount++;
    }
  }  
  //左边界拐点不足，则返回0
  if(LeftCount<2)
    return 0;
  //寻找右拐点
  for(i=ROW-1;i>ValidRow+4;i-=div)
  {
//    div = (int)(-6.708e-06*i*i*i+0.00111*i*i-0.006696*i+0.2882);
    div=1;
    if(div<1) div=1;
    if((RightLine[i]-RightLine[i-div])*rightsignflag>0&&(RightLine[i-div]-RightLine[i-2*div])*rightsignflag>0)
    {
      rightsignflag=-rightsignflag;
      rightsignflag1=0;
      RightCount++;
      continue;
    }
    else if((RightLine[i]-RightLine[i-div])*rightsignflag1<0&&(RightLine[i-div]-RightLine[i-2*div])*rightsignflag1<0)
    {      
      rightsignflag=0;
      rightsignflag1=-rightsignflag1;
      RightCount++;
    }
  }  
  //右边界拐点不足，则返回0
  if(RightCount<2)
    return 0;
  if(LeftCount<3 && RightCount<3)
    return 0;
  return 1;
}


/**
 * @brief 对全局赛道宽度进行判断，屏蔽十字、环路和大弯
 *
 * @return int类型，指示相对于小S是否有赛道宽度过宽的现象
 */
int AssertWidth1(void)
{
  int i;
  for(i=ROW-1;i>ValidRow+20;i--)
  {
    if(RealWidth1[i]>60)
      break;
  }
  if(i<=ValidRow+20)
    return 1;
  else
    return 0;
}


/**
 * @brief 对全局赛道宽度进行判断，屏蔽十字和环路
 *
 * @return int类型，指示相对于中S是否有赛道宽度过宽的现象
 */
int AssertWidth2(void)
{
  int i;
  for(i=ROW-1;i>ValidRow+20;i--)
  {
    if(RealWidth1[i]>65)
    {
      break;
    }
  }
  if(i<=ValidRow+20)
    return 1;
  else
    return 0;
}


/**
 * @brief 出小s时对全局赛道宽度进行判断，屏蔽十字、环路和大弯
 *
 * @return int类型，指示相对于小S是否有赛道宽度过宽的现象
 */
int OutAssertWidth1(void)
{
  int i;
  for(i=ROW-1;i>RealEndRow+20;i--)
  {
    if(RealMidLine2[i]<80&&RealWidth1[i]>65)
      break;
  }
  if(i<=RealEndRow+20)
    return 1;
  else 
    return 0;
}


/**
 * @brief 出中s时对全局赛道宽度进行判断，屏蔽十字和环路
 *
 * @return int类型，指示相对于中S是否有赛道宽度过宽的现象
 */
int OutAssertWidth2(void)
{
  int i;
  for(i=ROW-1;i>ValidRow+20;i--)
  {
    if(RealWidth1[i]>80)
    {
      break;
    }
  }
  if(i<=ValidRow+20)
    return 1;
  else
    return 0;
}

//小s弯识别
double nearVariance=0,remoteVariance=0,midVariance=0;//分别代表视野中近处赛道斜率方差，中部赛道斜率方差和远处赛道斜率方差
int SnakeFlag1=0;
int SnakeCount=0;//用于识别滤波，连续识别进或出多次才确认

//进出小S或者中S时保存当前小车走过的路程，之后一段距离用于路径优化的过渡
double OutSnakeStretch=0.0,InSnakeStretch=0.0;

/**
 * @brief s弯识别
 *
 * @return int类型，指示是否识别到s弯
 */
int Judge_SnakeBending(void)
{
  //remoteVariance=GetVariance((ValidRow+2+ROW-5)/2,ValidRow+2);
 //guaidianshu=AssertInterSectionPoint();
  //0：未识别到小s或中s；1；识别到小s；2：识别到中s。
  static int SnakeFlag=0;
  //未识别到小s之前
  if(SnakeFlag1==0)
  {
    //有效赛道可以延伸的视野最远处，即ValidRow=0;
    //且拐点个数满足条件
    if(ValidRow==0&&AssertInterSectionPoint()==1)
    {
      //针对小S,截止行必须是0，这意味着赛道中线斜率变化周期不能过大
      if(RealEndRow<=1&&AssertWidth1()==1)
      {
        //全局中线斜率方差在一定阈值范围内：需要实际仿真确定范围
        if(MidLineSlopeVariance>0.34&&MidLineSlopeVariance<0.46)                                   
        {         
//            //计算远处斜率方差
            remoteVariance=GetVariance((ValidRow+2+ROW-5)/2,ValidRow+2);
//            //远处斜率方差大于一定阈值
            if(remoteVariance>0.65&&remoteVariance<0.95)
            {
                //识别到小s
                SnakeFlag=1;
            }
            else
              SnakeFlag=0;
        }
        //全局中线斜率方差在一定阈值范围内：需要实际仿真确定范围
        else if(MidLineSlopeVariance>0.9&&MidLineSlopeVariance<1.28)                           
        {
              //识别到中S
              SnakeFlag=2;
        }
        else
          SnakeFlag=0;
      }
      //截止行比较小且宽度合理
      else if(EndRow<5&&AssertWidth2()==1)
      {
        //全局中线斜率方差在一定阈值范围内：需要实际仿真确定范围
        if(MidLineSlopeVariance>0.9&&MidLineSlopeVariance<1.28)                                      
        {
              //识别到中s
              SnakeFlag=2;
        }
        else
          SnakeFlag=0;
      }
      else
        SnakeFlag=0;
    }
    else
    {
      SnakeFlag=0;
    }
    //尚未确定识别，但当前识别到小s或中s；
    if((SnakeFlag>0)&&SnakeFlag1==0)
    {
      SnakeCount++;
      //连续识别到两次便予以确认
      if(SnakeCount>1)
      {
        //记录下当前路程
        InSnakeStretch = Stretch;
        if(SnakeFlag==1)
          SnakeFlag1=1;
        else if(SnakeFlag==2)
          SnakeFlag1=2;
        SnakeCount=0;
      }
    }
  }
  //在小s中
  else if(SnakeFlag1==1)
  {
    //中线斜率方差小于阈值或大于阈值，或者截止行大于阈值都认为出小s
    //宽度异常可认为出小s
    if(MidLineSlopeVariance<0.32||MidLineSlopeVariance>0.48
       ||OutAssertWidth1()==0||RealEndRow>5)
    {
      SnakeFlag=0;
    }
    if(SnakeFlag==0)
    {
      SnakeCount++;
      if(SnakeCount>0)
      {
        SnakeFlag1=0;
        //记录下当前路程
        OutSnakeStretch = Stretch;
        SnakeCount=0;
      }
    }
  }
  //在中s中
  else if(SnakeFlag1==2)
  {

    //中线斜率方差小于阈值或大于阈值，或者截止行大于阈值或宽度异常都认为出中s
    if(MidLineSlopeVariance<0.87||ValidRow>6||OutAssertWidth2()==0||MidLineSlopeVariance>1.3)
    {
      SnakeFlag=0;
    }
    if(SnakeFlag==0)
    {
      SnakeCount++;
      if(SnakeCount>0)
      {
        SnakeFlag1=0;
        //记录当前路程
        OutSnakeStretch = Stretch;
        SnakeCount=0;
      }
    }
  }
  if(SnakeFlag1>=1)
  {
    return 1;
  }
  else 
  {
    return 0;
  }
}


//非自然出s弯时调用
void OutSnake(void)
{
  SnakeFlag1=0;
  SnakeCount=0;
}

