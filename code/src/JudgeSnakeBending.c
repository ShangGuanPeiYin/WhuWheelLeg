#include "zf_common_headfile.h"
int guaidianshu=0;


/**
 * @brief Ѱ�����ұ߽�Ĺյ� һ����˵��СS�����S������ұ߽������Ұ�ڴ����������ϵĹյ�
 *
 * @return int 1���յ��������������0����֮
 */
int AssertInterSectionPoint(void)
{
  int i;
  int LeftCount=0,RightCount=0;//�������ұ߽��ҵ��Ĺյ���
  int leftsignflag=1,leftsignflag1=1,rightsignflag=1,rightsignflag1=1; //ÿ��б�ʼ��Ա仯ʱ�ñ�־λ�������Ա仯
  int div=0;  //���ڽ��������ܼ���Ѱ��ʱ��Ծ�ĸ��죬Զ����һ��һ�е���
  
  //Ѱ����յ�
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
  //��߽�յ㲻�㣬�򷵻�0
  if(LeftCount<2)
    return 0;
  //Ѱ���ҹյ�
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
  //�ұ߽�յ㲻�㣬�򷵻�0
  if(RightCount<2)
    return 0;
  if(LeftCount<3 && RightCount<3)
    return 0;
  return 1;
}


/**
 * @brief ��ȫ��������Ƚ����жϣ�����ʮ�֡���·�ʹ���
 *
 * @return int���ͣ�ָʾ�����СS�Ƿ���������ȹ��������
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
 * @brief ��ȫ��������Ƚ����жϣ�����ʮ�ֺͻ�·
 *
 * @return int���ͣ�ָʾ�������S�Ƿ���������ȹ��������
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
 * @brief ��Сsʱ��ȫ��������Ƚ����жϣ�����ʮ�֡���·�ʹ���
 *
 * @return int���ͣ�ָʾ�����СS�Ƿ���������ȹ��������
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
 * @brief ����sʱ��ȫ��������Ƚ����жϣ�����ʮ�ֺͻ�·
 *
 * @return int���ͣ�ָʾ�������S�Ƿ���������ȹ��������
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

//Сs��ʶ��
double nearVariance=0,remoteVariance=0,midVariance=0;//�ֱ������Ұ�н�������б�ʷ���в�����б�ʷ����Զ������б�ʷ���
int SnakeFlag1=0;
int SnakeCount=0;//����ʶ���˲�������ʶ��������β�ȷ��

//����СS������Sʱ���浱ǰС���߹���·�̣�֮��һ�ξ�������·���Ż��Ĺ���
double OutSnakeStretch=0.0,InSnakeStretch=0.0;

/**
 * @brief s��ʶ��
 *
 * @return int���ͣ�ָʾ�Ƿ�ʶ��s��
 */
int Judge_SnakeBending(void)
{
  //remoteVariance=GetVariance((ValidRow+2+ROW-5)/2,ValidRow+2);
 //guaidianshu=AssertInterSectionPoint();
  //0��δʶ��Сs����s��1��ʶ��Сs��2��ʶ����s��
  static int SnakeFlag=0;
  //δʶ��Сs֮ǰ
  if(SnakeFlag1==0)
  {
    //��Ч���������������Ұ��Զ������ValidRow=0;
    //�ҹյ������������
    if(ValidRow==0&&AssertInterSectionPoint()==1)
    {
      //���СS,��ֹ�б�����0������ζ����������б�ʱ仯���ڲ��ܹ���
      if(RealEndRow<=1&&AssertWidth1()==1)
      {
        //ȫ������б�ʷ�����һ����ֵ��Χ�ڣ���Ҫʵ�ʷ���ȷ����Χ
        if(MidLineSlopeVariance>0.34&&MidLineSlopeVariance<0.46)                                   
        {         
//            //����Զ��б�ʷ���
            remoteVariance=GetVariance((ValidRow+2+ROW-5)/2,ValidRow+2);
//            //Զ��б�ʷ������һ����ֵ
            if(remoteVariance>0.65&&remoteVariance<0.95)
            {
                //ʶ��Сs
                SnakeFlag=1;
            }
            else
              SnakeFlag=0;
        }
        //ȫ������б�ʷ�����һ����ֵ��Χ�ڣ���Ҫʵ�ʷ���ȷ����Χ
        else if(MidLineSlopeVariance>0.9&&MidLineSlopeVariance<1.28)                           
        {
              //ʶ����S
              SnakeFlag=2;
        }
        else
          SnakeFlag=0;
      }
      //��ֹ�бȽ�С�ҿ�Ⱥ���
      else if(EndRow<5&&AssertWidth2()==1)
      {
        //ȫ������б�ʷ�����һ����ֵ��Χ�ڣ���Ҫʵ�ʷ���ȷ����Χ
        if(MidLineSlopeVariance>0.9&&MidLineSlopeVariance<1.28)                                      
        {
              //ʶ����s
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
    //��δȷ��ʶ�𣬵���ǰʶ��Сs����s��
    if((SnakeFlag>0)&&SnakeFlag1==0)
    {
      SnakeCount++;
      //����ʶ�����α�����ȷ��
      if(SnakeCount>1)
      {
        //��¼�µ�ǰ·��
        InSnakeStretch = Stretch;
        if(SnakeFlag==1)
          SnakeFlag1=1;
        else if(SnakeFlag==2)
          SnakeFlag1=2;
        SnakeCount=0;
      }
    }
  }
  //��Сs��
  else if(SnakeFlag1==1)
  {
    //����б�ʷ���С����ֵ�������ֵ�����߽�ֹ�д�����ֵ����Ϊ��Сs
    //����쳣����Ϊ��Сs
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
        //��¼�µ�ǰ·��
        OutSnakeStretch = Stretch;
        SnakeCount=0;
      }
    }
  }
  //����s��
  else if(SnakeFlag1==2)
  {

    //����б�ʷ���С����ֵ�������ֵ�����߽�ֹ�д�����ֵ�����쳣����Ϊ����s
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
        //��¼��ǰ·��
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


//����Ȼ��s��ʱ����
void OutSnake(void)
{
  SnakeFlag1=0;
  SnakeCount=0;
}

