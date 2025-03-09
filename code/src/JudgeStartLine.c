#include "zf_common_headfile.h"

int RaceFlag=0,StartRow=0;

//ÿһ�е������
int BWCount[ROW]={0};
//�����ж������ߵ��������ֵ
int BWcount = 9;
int temp16 = 0;
//�������ߵ���
int OutStartLineRow=ROW-1;
//�����߱�־λ
int StartFlag1=0;
int StartFlag=0;
int OutFlag=0;
int startsum;


/**
 * @brief ʶ�������� ��һ���������������������ߵ������������Ը��������ط�
 *
 * @return int 1Ϊʶ�������ߣ�0Ϊδʶ��������
 */
int Judge_StartLine(void)
{
  int i=0,j=0;
  //StartCount:ʶ���˲�   StartSum:ʶ�������ߴ���
  static int StartCount=0,StartSum=0;
  StartFlag=0;
  //startsum=StartSum;
  OutFlag=0;
  OutStartLineRow=ROW-1;
  //�տ������ֹ��̫��ʶ��������
  //��һ���ų���������Ҫд�ã�������С������
  if(StartFlag1==0&&EndRow>20)//||MainCount<50))
  {
    StartFlag1=0;
    StartCount=0;
    return 0;
  }
  //ʶ�𼰴������
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
    //ʶ�������ߺ�Ҫ�������������ߵĳ��ڣ�����OutStartLineRow��ֵ
    //�������߽������ĳһ��Χ�� ������ڶ��׶�
    for(i=ROW-1;i>10;i--)
    {
      BWCount[i]=0;
      //�������
      for(j=0;j<COLUMN-2;j++)
      {
        if(videoData[i][j]+videoData[i][j+1] == 1)
        {
          BWCount[i]++;
        }
      }  
      //����һ���ҵ������ߺ��ж�������λ�ã�������ROW-20�ڣ��������һ�׶�
      if(OutFlag==0&&BWCount[i]>=BWcount)
      {
        if(i>ROW-20) StartFlag = 2;
        
        OutFlag=1;
      }
      //��һ���ҵ��������Ժ�ʼ�������߳���
      if(OutFlag==1&&BWCount[i]<6)
      {
        OutStartLineRow=i-2;
        break;
      }
    }
  }
  //ʱ��ķѲ��Գ���
 
  
  //���¶�Ϊʶ���˲�����
  //����һ�׶�
  if(StartFlag1==0&&StartFlag==1)
  {
    StartCount++;
    if(StartCount>2)
    {
      StartCount=0;
      StartFlag1=1;  
    }
  }
  //����ڶ��׶�
  else if(StartFlag1==1&&StartFlag==2)
  {
    StartCount++;
    if(StartCount>2)
    {
      StartCount=0;
      StartFlag1=2;
    }
  }
  //��������
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
  
  //ʶ�����������ߺ󣬸���RaceFlag��ֵ�����Ƿ�ͣ�� 
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
 * @brief �������ұ߽磬��־λ��λ
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




