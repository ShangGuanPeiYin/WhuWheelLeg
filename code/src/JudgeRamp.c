#include "zf_common_headfile.h"

int RampDis;
double OutRampStrech = 0;
int RampFlag=0;
long RampMainCount=0;


/**
 * @brief ʶ���µ� ����ʱ�뽫������ѹ�úܽ�����90������Զ��ͼ���쳣�ᵼ�¶������쳣
 *
 * @return int 1Ϊʶ���µ���0Ϊδʶ���µ�
 */
int Judge_Ramp(void)
{
  static int RampCount=0;
  int i=0;
  //�нǵ��������Ϊ�����µ������µ���2�ײ���ʶ���µ�����ֹ����ʱʶ����µ�
  if(MainCount<100||RightFound!=0||LeftFound!=0)//||(Stretch-OutRampStrech<=200)
  {
    return 0;
  }
  //ûʶ���µ�ǰ��ʶ�𷽰�
  if(RampFlag==0)
  {
    //��ֹ����С������б�ʷ����С���������һ��������������Ϊ�����µ�
    if(RealEndRow==0/*&&MidLineSlopeVariance<0.03*/)
    {
      //�ӿ����е���ֹ��+8���쳣��ȵ�����
      for(i=ControlRow;i>RealEndRow+8;i--)
      {
        //������������ͨ��������ҿ������������ƣ���Ϊ���µ�
        //�������µ�������ӽ�ƽ��ļнǵ�����������ԭ��
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
  //ʶ���µ��Ժ�ֱ�Ӹ�һ�ξ��룬����Ӳ������ʶ�������
  
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
 * @brief �ж��Ƿ���µ� 1s�������66��DMA�ж�
 *
 * @return int 1Ϊ���µ���0Ϊδ���µ�
 */
int OutRamp(void)
{
  if(MainCount-RampMainCount>=0&&MainCount-RampMainCount<50&&MainCount>50) return 1;
  else return 0;
}


/**
 * @brief �µ�������־λ��λ
 */
void RampDeal(void)
{
  RoadFlag[RAMP]=1;
}
