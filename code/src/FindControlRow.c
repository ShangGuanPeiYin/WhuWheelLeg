#include "zf_common_headfile.h"

int RowSet = 48,RealWidth,EndRowNotFind=0,CameraStopFlag=0,ADStopFlag=0,StopFlag=0;
int Control_Straightflag = 1;
//��������к�ֱ��������
int RowSet_S = 48,RowSet_C = 51;

/**
 * @brief �ҿ�����  RowSet_SΪֱ�������У�RowSet_CΪ��������У�RowSet��Һ��������Ӧ��RowSet_Sһ�£���ΪRowSet_S�ĳ�ֵ
 */
void Find_ControlRow(void)
{       
     float RealRightLine[1][2],RealLeftLine[1][2],RealMidLine[1][2];
     
     //������Ϊ������һ����ֱ�������У�һ�������������
     static int Control_CurveCount = 0,Control_CurveCount1 = 0;
     //�������и�һ����ֵ����Ȼ���ܻ�������
     ControlRow=RowSet_S;
     
     if(Control_Straightflag == 1)
     {
       //��ֹ�нϴ����л�Ϊ��������У�������ֱ��������
        if(EndRow < RowSet_C-11) //EndRow < RowSet_C-1
        {
          RowSet = RowSet_S;
          Control_CurveCount = 0;
        }
        else Control_CurveCount++;

        if(Control_CurveCount>1)
        {
          Control_CurveCount = Control_Straightflag = 0;
        }
     }
     if(Control_Straightflag == 0)
     {
       //��ֹ�н�С��ֱ���������һ��ֵ�л�Ϊֱ�������У����������������
        RowSet = RowSet_C;
       
        if((EndRow < 14 && straightDistance>=20)||(EndRow < 17 && straightDistance>=35))//������ֱ�������ſ�ʹ��
        {
          Control_CurveCount1++;
        }
        else Control_CurveCount1 = 0;

        if(Control_CurveCount1>1)
        {
          RowSet = RowSet_S;
          Control_CurveCount1 = 0;
          Control_Straightflag = 1;
        }
     }
     
     EndRowNotFind=0;   
     if (RealEndRow+5<RowSet)//Զ�����������ڣ���ֱ��
     {
          ControlRow=RowSet;
     }
     
     else if(RealEndRow+5>=RowSet&&RealEndRow+5<ROW-4)//ĳ������       //��ƫ��
     {
          ControlRow=RealEndRow+5;
     }
     else if(RealEndRow+5>=ROW-4&&RealEndRow+5<ROW-2&&Barrier_flag==0)
     {
       ControlRow=RealEndRow+3;
       EndRowNotFind=1;
     }     
     
    //  else if(MainCount>50)
    //  {
    //    //��ֹ�кܴ�ʱ����ͷͣ����־��1
    //    //ʶ���µ�����1�����µ�һ��ʱ���ڲ���1
    //    if(Barrier_flag == 0 && (RampFlag==0&&OutRamp()==0))
    //    {
    //      CameraStopFlag=1;
    //    }
    //  }

    //  //����ͷͣ����־��1��δʶ�𵽶�·���·�ϣ�ͣ��
    //  if(CameraStopFlag==1 && BrokenRoadFlag==0 && Barrier_flag==0)
    //  {
    //    StopFlag = 1;
    //  }     
     
     //��������������
     Real_Location(LeftLine[ControlRow],ControlRow,RealLeftLine);
     Real_Location(RightLine[ControlRow],ControlRow,RealRightLine);
     RealWidth=(int)GetDistance(RealLeftLine,RealRightLine);
     Real_Location(MidLine[ControlRow],ControlRow,RealMidLine);
}