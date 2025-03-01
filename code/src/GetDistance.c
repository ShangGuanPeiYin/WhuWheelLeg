#include "zf_common_headfile.h"

int ruwanhang;
double Angle=0;

/************************************************************************/
/*
*������ double CaculateDistance(int row1,int row2)
*�������ܣ��������������е�֮��ľ���
*�βΣ�row1,row2,�ֱ��������
*����ֵ��double���ͣ��������
*���ڣ�2017.09.2
*���ߣ�����ƽ
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
*������ void GetStraightDistance(void)
*�������ܣ���������е�����ľ���
*�βΣ���
*����ֵ����
*���ڣ�2017.09.2
*���ߣ�����ƽ
*�޸ģ�����
*��ע��ϸ���д����� 
*/
/************************************************************************/
double straightDistance=0;//�����е�����ľ���
double RealMidSlopeSum[ROW]={0.0};//�ֲ�����б�����
void GetStraightDistance(void)
{
  int i=0;
  //��������ʼ�к���ֹ��
  int checkRow,checkRow1=0;
  //��Ϊʮ�ֳ���ʱ��Ƚ����⣬������һ��������ס�ո���ʮ�ֵ���
  static int Flag11=0;
  //Ĭ������´�Row-30����Զ����
  checkRow=ROW-30;
  //����У��������б��
  GetRealMidSlope();
  //Ĭ����ֹ�У�ValidRow1+3
  checkRow1=ValidRow+3;
  //���䵽һ����ȣ�ȷ�ϳ�ʮ���ˣ���Flag11����
  if(ValidRow>13)
  {
    Flag11=0;
  }
 //������ֱ�ӽ�ֱ��������Ϊ��С��-20���������һ�����֣��ɵ�����
  if(RealEndRow+5>=RowSet-2)
  {
    straightDistance=-20;
    return;
  }
  //ʮ���м���ֱ���ķ�ʽ
  if(RoadFlag[CROSS]!=0||Flag11==1)
  {
    if(RoadFlag[CROSS]!=0)
    {
      Flag11=1;
    }
    //ʮ��״̬����Ч��Ϊ0����ֱ����Ϊֱ�����쵽��Ұ��ͷ
    if(ValidRow == 0&&RoadFlag[CROSS]!=0)
    {
        straightDistance=CaculateDistance(checkRow1+5,ControlRow);
        return;
    }
    else 
    {
      //��ʮ��״̬�� ����Զ��ʮ��·�ڿ�ʼ�����
      if(RoadFlag[CROSS]!=0)
        checkRow=InflexionFar;
      //�ճ�ʮ�֣��ӿ����п�ʼ���������ʱ�������Ѿ�����ʮ��·��
      else
        checkRow=ControlRow;
    }
  }
   //ʶ�������ߣ����������Զ�˿�ʼ�����
  else if(OutStartLineRow!=ROW-1)
  {
    checkRow=OutStartLineRow;
  }
  //ʶ��Сs�������Ч��Ϊ0����ֱ����Ϊֱ�����쵽��Ұ��ͷ
  else if(SnakeFlag1==1)
  {
    if(ValidRow == 0)
    {
        straightDistance=CaculateDistance(checkRow1+1,ControlRow);
        return;
    }
  }
  //ʶ����s�򲻼���ֱ��
  else if(SnakeFlag1==2)
  {
    straightDistance=-20;
    return;
  }
  //��ֹ�й���ֱ���жϴ��������
  else if(EndRow>16)//����Ҫ�� 18
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
    //����ʵ����б�ʽ��оֲ���ͣ����������ԣ������������кܺõ�Ч����
    RealMidSlopeSum[i]= RealMidSlope[i]+RealMidSlope[i+1]+RealMidSlope[i+2]+RealMidSlope[i+3];
    //�ҵ�б�����䴦
    if(fabs(RealMidSlopeSum[i]-RealMidSlopeSum[i+4])>0.5)
    {
      int j;
      //��б�����䴦�����ң�ֱ���ҵ�б�ʱ仯ƽ���ĵط���
      //����Ϊ�˴������䴦
      for(j=i+4;j<checkRow;j++)
      {
        if(fabs(RealMidSlopeSum[j]-RealMidSlopeSum[j+2])<0.2)
        {  
          ruwanhang=j;
          //���䴦�ڿ�����֮��
          if(j+5<=ControlRow)
          {
            straightDistance=CaculateDistance(j+5,ControlRow);//2
            return;
          }
          //���䴦�ڿ�����֮ǰ
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
  //ֱ����ֹ�ж�δ�ҵ��������ֱ���Ѿ����쵽����ֹ�д�
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
*������ void GetTurningRadius(void)
*�������ܣ�����ת��뾶����ο�������ת�򼸺�
*�βΣ���
*����ֵ����
*���ڣ�2017.09.2
*���ߣ�����ƽ
*/
/************************************************************************/
//��������ʵ��
int CarWidth = 154,CarLength = 197;
//ת��뾶
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