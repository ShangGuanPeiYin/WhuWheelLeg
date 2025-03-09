#include "zf_common_headfile.h"

int ruwanhang;
double Angle=0;

/************************************************************************/
/*
*函数名 double CaculateDistance(int row1,int row2)
*函数功能：计算两行赛道中点之间的距离
*形参：row1,row2,分别代表两行
*返回值：double类型，代表距离
*日期：2017.09.2
*作者：范昌平
*/
/************************************************************************/
double CaculateDistance(int row1,int row2)
{
  return InvSqrt((RealMidLine1[row1]-RealMidLine1[row2])
            *(RealMidLine1[row1]-RealMidLine1[row2])
              +(RealMidLine2[row1]-RealMidLine2[row2])
                *(RealMidLine2[row1]-RealMidLine2[row2]));
}

/************************************************************************/
/*
*函数名 void GetStraightDistance(void)
*函数功能：计算控制行到弯道的距离
*形参：无
*返回值：无
*日期：2017.09.2
*作者：范昌平
*修改：梁杰
*备注：细节有待处理 
*/
/************************************************************************/
double straightDistance=0;//控制行到弯道的距离
double RealMidSlopeSum[ROW]={0.0};//局部中线斜率求和
void GetStraightDistance(void)
{
  int i=0;
  //遍历的起始行和终止行
  int checkRow,checkRow1=0;
  //因为十字出的时候比较随意，所以用一个变量记住刚刚在十字当中
  static int Flag11=0;
  //默认情况下从Row-30行往远处找
  checkRow=ROW-30;
  //计算校正后中线斜率
  GetRealMidSlope();
  //默认终止行：ValidRow1+3
  checkRow1=ValidRow+3;
  //入弯到一定深度，确认出十字了，将Flag11置零
  if(ValidRow>13)
  {
    Flag11=0;
  }
 //入弯很深，直接将直道距离置为最小：-20（随意给的一个数字，可调整）
  if(RealEndRow+5>=RowSet-2)
  {
    straightDistance=-20;
    return;
  }
  //十字中计算直道的方式
  if(RoadFlag[CROSS]!=0||Flag11==1)
  {
    if(RoadFlag[CROSS]!=0)
    {
      Flag11=1;
    }
    //十字状态下有效行为0，可直接认为直道延伸到视野尽头
    if(ValidRow == 0&&RoadFlag[CROSS]!=0)
    {
        straightDistance=CaculateDistance(checkRow1+5,ControlRow);
        return;
    }
    else 
    {
      //在十字状态下 ，从远端十字路口开始找弯道
      if(RoadFlag[CROSS]!=0)
        checkRow=InflexionFar;
      //刚出十字，从控制行开始找弯道，此时控制行已经出了十字路口
      else
        checkRow=ControlRow;
    }
  }
   //识别到起跑线，则从起跑线远端开始找弯道
  else if(OutStartLineRow!=ROW-1)
  {
    checkRow=OutStartLineRow;
  }
  //识别到小s，如果有效行为0，可直接认为直道延伸到视野尽头
  else if(SnakeFlag1==1)
  {
    if(ValidRow == 0)
    {
        straightDistance=CaculateDistance(checkRow1+1,ControlRow);
        return;
    }
  }
  //识别到中s则不计算直道
  else if(SnakeFlag1==2)
  {
    straightDistance=-20;
    return;
  }
  //截止行过大，直接判断处于弯道中
  else if(EndRow>16)//可能要改 18
  {
    straightDistance=-20;
    return;
  }
  else if(MidLineSlopeVariance>0.6)
  {    
    straightDistance=-20;
    return;    
  }
  
  for(i=checkRow;i>checkRow1;i-=1)
  {
    //对真实中线斜率进行局部求和，特征更明显，对噪声抑制有很好的效果。
    RealMidSlopeSum[i]= RealMidSlope[i]+RealMidSlope[i+1]+RealMidSlope[i+2]+RealMidSlope[i+3];
    //找到斜率跳变处
    if(fabs(RealMidSlopeSum[i]-RealMidSlopeSum[i+4])>0.5)
    {
      int j;
      //从斜率跳变处往回找，直到找到斜率变化平缓的地方。
      //则认为此处是入弯处
      for(j=i+4;j<checkRow;j++)
      {
        if(fabs(RealMidSlopeSum[j]-RealMidSlopeSum[j+2])<0.2)
        {  
          ruwanhang=j;
          //入弯处在控制行之后
          if(j+5<=ControlRow)
          {
            straightDistance=CaculateDistance(j+5,ControlRow);//2
            return;
          }
          //入弯处在控制行之前
          else
          {
            float distance1=0;
            distance1=-CaculateDistance(j+5,ControlRow);//2
            if(distance1>-20)
            {
              straightDistance=distance1;
              return;
            }
            else
            {
              straightDistance=-20;
              return;
            }
          }
        }
      }
    }
  }
  //直到终止行都未找到弯道，则直道已经延伸到了终止行处
  if(i<=checkRow1)
  {
      straightDistance=CaculateDistance(checkRow1+5,ControlRow);
      return;
  }
  else 
  {
    straightDistance=0;
    return;
  }
    
}

/************************************************************************/
/*
*函数名 void GetTurningRadius(void)
*函数功能：计算转弯半径，请参考阿克曼转向几何
*形参：无
*返回值：无
*日期：2017.09.2
*作者：范昌平
*/
/************************************************************************/
//车长车宽：实测
int CarWidth = 154,CarLength = 197;
//转弯半径
double TurningRadius=0;
void GetTurningRadius(void)
{
  if( Angle>0)
  {
    TurningRadius=CarLength/tan(Angle)+CarWidth/2.0;
    TurningRadius=InvSqrt(TurningRadius*TurningRadius+CarLength*CarLength/4);
  }
  else if(Angle<0 )
  {
    TurningRadius=CarLength/tan(-Angle)+CarWidth/2.0;
    TurningRadius=InvSqrt(TurningRadius*TurningRadius+CarLength*CarLength/4);
  }
  else
  {
     TurningRadius=-1;
  }
}