#include "zf_common_headfile.h"

int RaceFlag=0,StartRow=0;

//每一行的跳变点
int BWCount[ROW]={0};
//用于判断起跑线的跳变点阈值
int BWcount = 9;
int temp16 = 0;
//出起跑线的行
int OutStartLineRow=ROW-1;
//起跑线标志位
int StartFlag1=0;
int StartFlag=0;
int OutFlag=0;
int startsum;


/**
 * @brief 识别起跑线 在一行中找跳变点个数，起跑线的跳变点个数明显高于其它地方
 *
 * @return int 1为识别到起跑线，0为未识别到起跑线
 */
int Judge_StartLine(void)
{
  int i=0,j=0;
  //StartCount:识别滤波   StartSum:识别到起跑线次数
  static int StartCount=0,StartSum=0;
  StartFlag=0;
  //startsum=StartSum;
  OutFlag=0;
  OutStartLineRow=ROW-1;
  //刚开机或截止行太大不识别起跑线
  //第一个排除条件必须要写好，尽量减小计算量
  if(StartFlag1==0&&EndRow>20)//||MainCount<50))
  {
    StartFlag1=0;
    StartCount=0;
    return 0;
  }
  //识别及处理程序
  if(StartFlag1 == 0)
  {
    for(i=40;i<65;i++)
    {
      BWCount[i]=0;
      for(j=35;j<COLUMN-37;j++)
      {
        if(videoData[i][j]+videoData[i][j+1] == 1)
        {
          BWCount[i]++;
        }
        if(BWCount[i]>=BWcount)
        {
          StartFlag = 1;
          break;
        }
      }   
      if(StartFlag == 1) break;
    }
  }
  if(StartFlag1 != 0)
  {
    //识别到起跑线后，要持续锁定起跑线的出口，即对OutStartLineRow赋值
    //当起跑线进入近处某一范围后 ，进入第二阶段
    for(i=ROW-1;i>10;i--)
    {
      BWCount[i]=0;
      //找跳变点
      for(j=0;j<COLUMN-2;j++)
      {
        if(videoData[i][j]+videoData[i][j+1] == 1)
        {
          BWCount[i]++;
        }
      }  
      //仅第一次找到起跑线后判断起跑线位置，若进入ROW-20内，则进入下一阶段
      if(OutFlag==0&&BWCount[i]>=BWcount)
      {
        if(i>ROW-20) StartFlag = 2;
        
        OutFlag=1;
      }
      //第一次找到起跑线以后开始找起跑线出口
      if(OutFlag==1&&BWCount[i]<6)
      {
        OutStartLineRow=i-2;
        break;
      }
    }
  }
  //时间耗费测试程序
 
  
  //以下都为识别滤波程序
  //进第一阶段
  if(StartFlag1==0&&StartFlag==1)
  {
    StartCount++;
    if(StartCount>2)
    {
      StartCount=0;
      StartFlag1=1;  
    }
  }
  //进入第二阶段
  else if(StartFlag1==1&&StartFlag==2)
  {
    StartCount++;
    if(StartCount>2)
    {
      StartCount=0;
      StartFlag1=2;
    }
  }
  //出起跑线
  else if(StartFlag==0&&StartFlag1==2)
  {
    StartCount++;
    if(StartCount>2)
    {
      StartCount=0;
      StartFlag1=0;
      //if(StartSum==0)//||MainCount>300)
      StartSum++;
    }
  }
  
  startsum = StartSum;
  
  //识别到两次起跑线后，根据RaceFlag的值决定是否停车 
  if(StartSum>=2)//&&RaceFlag==1)
  {    
    StopFlag=1;
  }
  if(StartFlag1!=0)
  {
    return 1;
  }
  else
    return 0;
}


/**
 * @brief 修正左右边界，标志位置位
 */
void StartLineDeal(void)
{
  int i=0;
  for(i=ROW-1;i>OutStartLineRow;i--)
  {
    LeftLine[i]=LeftLine1[i];
    RightLine[i]=RightLine1[i];
    MidLine[i]=(LeftLine[i]+RightLine[i])/2;
    Width[i]=RightLine[i]-LeftLine[i];
  }

  RoadFlag[STARTLINE]=1;
}




