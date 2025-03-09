#include "zf_common_headfile.h"

int RowSet = 48,RealWidth,EndRowNotFind=0,CameraStopFlag=0,ADStopFlag=0,StopFlag=0;
int Control_Straightflag = 1;
//弯道控制行和直道控制行
int RowSet_S = 48,RowSet_C = 51;

/**
 * @brief 找控制行  RowSet_S为直道控制行，RowSet_C为弯道控制行，RowSet在液晶调参上应与RowSet_S一致，作为RowSet_S的初值
 */
void Find_ControlRow(void)
{       
     float RealRightLine[1][2],RealLeftLine[1][2],RealMidLine[1][2];
     
     //控制行为两个，一个是直道控制行，一个是弯道控制行
     static int Control_CurveCount = 0,Control_CurveCount1 = 0;
     //给控制行赋一个初值，不然可能会有问题
     ControlRow=RowSet_S;
     
     if(Control_Straightflag == 1)
     {
       //截止行较大则切换为弯道控制行，否则用直道控制行
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
       //截止行较小且直道距离大于一定值切换为直道控制行，否则用弯道控制行
        RowSet = RowSet_C;
       
        if((EndRow < 14 && straightDistance>=20)||(EndRow < 17 && straightDistance>=35))//需引入直道距离后才可使用
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
     if (RealEndRow+5<RowSet)//远方都在赛道内，长直道
     {
          ControlRow=RowSet;
     }
     
     else if(RealEndRow+5>=RowSet&&RealEndRow+5<ROW-4)//某个区间       //大偏差
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
    //    //截止行很大时摄像头停车标志置1
    //    //识别到坡道不置1，出坡道一段时间内不置1
    //    if(Barrier_flag == 0 && (RampFlag==0&&OutRamp()==0))
    //    {
    //      CameraStopFlag=1;
    //    }
    //  }

    //  //摄像头停车标志置1且未识别到断路横断路障，停车
    //  if(CameraStopFlag==1 && BrokenRoadFlag==0 && Barrier_flag==0)
    //  {
    //    StopFlag = 1;
    //  }     
     
     //算控制行赛道宽度
     Real_Location(LeftLine[ControlRow],ControlRow,RealLeftLine);
     Real_Location(RightLine[ControlRow],ControlRow,RealRightLine);
     RealWidth=(int)GetDistance(RealLeftLine,RealRightLine);
     Real_Location(MidLine[ControlRow],ControlRow,RealMidLine);
}